#pragma once
 
#include <map>
#include <memory>
#include <queue>
#include <vector>
#include <list>
#include <string>
#include <functional>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <atomic>

 
class ThreadPool
{
    DECLARE_UNCOPYABLE(ThreadPool);
 
public:
    typedef std::function<void ()> TaskHandler;
 
public:
    explicit ThreadPool(
            int min_num_threads = -1,
            int max_num_threads = -1,
            const std::string& name = "");
    ~ThreadPool();
 
public:
    //设置线程最小个数
    void set_min_thread_number(int num_threads);
 
    //设置线程最大个数
    void set_max_thread_number(int num_threads);
 
    //增加线程任务
    uint64_t add_task(const TaskHandler& callback);
 
    uint64_t add_task(const TaskHandler& callback, int priority);
 
    //取消任务
    bool cancel_task(uint64_t task_id);
 
    //终止
    void terminate();
 
    void clear_tasks();
 
    void wait_for_idle();
 
    void get_stats() const;
 
private:
    struct Task
    {
        Task(const TaskHandler& entry,
                uint64_t id,
                int priority) :
            on_schedule(entry),
            id(id),
            priority(priority),
            is_canceled(false) {}
        
        void set_schedule_timeout_flag(bool flag)
        {
            is_canceled = flag;
        }
 
        void set_cancel_flag(bool flag)
        {
            is_canceled = flag;
        }
 
        bool check_cancel_flag() const
        {
            return is_canceled;
        }
 
        TaskHandler on_schedule;
        uint64_t id; // task id
        int priority; // task priority, lower is better
        bool is_canceled; // task flag, schedule timeout or canceled
        std::mutex task_lock; // task inner lock
    };
 
    struct ThreadContext
    {
        ThreadContext() :
            waiting_timer_id(0),
            is_waiting_timeout(false) {}
 
        void set_waiting_timeout_flag(bool flag)
        {
            is_waiting_timeout = flag;
        }
 
        bool check_waiting_timeout_flag() const
        {
            return is_waiting_timeout;
        }
 
        std::shared_ptr<std::thread> thread;
        uint64_t waiting_timer_id;
        bool is_waiting_timeout; 
    };
 
    typedef std::map<uint64_t, std::shared_ptr<Task> > TaskMap;
    typedef std::list<ThreadContext*> ThreadList;
 
private:
    void work(ThreadContext* thread);
 
private:
    /// @brief auto generate a new task id
    uint64_t new_task_id();
 
    uint64_t add_task_internal(const TaskHandler& callback,
            int priority);
 
    bool dequeue_task_in_lock(std::shared_ptr<Task>& task);
 
    bool need_new_thread() const;
 
    bool need_shrink_thread() const;
 
    // expand a thread into pool
    void expand_thread();
 
private:
    struct TaskCompare
    {
        bool operator()(const std::shared_ptr<Task>& a,
                const std::shared_ptr<Task>& b)
        {
            return a->priority > b->priority;
        }
    };
 
private:
    int m_min_num_threads;
    int m_max_num_threads;
 
    // current threads number
    std::atomic<int>    m_num_threads;
 
    // current on-busy threads number
    std::atomic<int>  m_num_busy_threads;
 
      // tasks container
    TaskMap m_tasks;
 
    // exit flags
    volatile bool m_exit;
 
    mutable std::mutex m_lock;
 
    // all threads are free now
    std::condition_variable m_exit_cond;
 
    // tasks been requested
    std::condition_variable m_task_cond;
 
    // not suitable for std::vector since uncopyable structures
    // list with m_num_threads elements running with each work thread routine
    ThreadList m_threads;
 
    // tasks queue，此处优先队列使用小根堆，priority越小越先被执行
    std::priority_queue<
        std::shared_ptr<Task>,
        std::vector<std::shared_ptr<Task> >,
        TaskCompare> m_task_queue;
};


#include <cstddef>
#include <iostream>
#include <string>
#include <atomic>
#include <chrono>
 
 
using namespace std;
 
static uint64_t s_thread_name_index = 0;
 
ThreadPool::ThreadPool(
        int min_num_threads, int max_num_threads, const std::string& name) :
    m_min_num_threads(0),
    m_max_num_threads(0),
    m_num_threads(0),
    m_num_busy_threads(0),
    m_exit(false)
{
    if (min_num_threads <= 0) {
        m_min_num_threads = SysInfo::get_logical_cpu_number();
    } else {
        m_min_num_threads = min_num_threads;
    }
    if (max_num_threads < m_min_num_threads) {
        m_max_num_threads = 2 * m_min_num_threads;
    } else {
        m_max_num_threads = max_num_threads;
    }
 
    std::unique_lock<std::mutex> lock(m_lock);
    for (int i = 0; i < m_min_num_threads; i++) {
        ThreadContext* thread = new ThreadContext();
        thread->thread.reset(
                new std::thread(std::bind(
                        &ThreadPool::work, this, thread)));
        m_threads.push_back(thread);
        m_num_threads++;
    }
    s_thread_name_index += m_min_num_threads;
 
}
 
ThreadPool::~ThreadPool()
{
    terminate();
}
 
void ThreadPool::terminate()
{
    std::cout << __LINE__ << " " << __FUNCTION__ << std::endl;
    if (m_exit) {
        return;
    }
 
    {
        std::unique_lock<std::mutex> lock(m_lock);
        m_exit = true;
 
        // send signal to all busy threads to exit
        for (int i = 0; i < m_num_threads; i++) {
            m_task_cond.notify_all();
        }
 
        // wait until all busy threads exited
        while (m_num_busy_threads > 0) {
            m_exit_cond.wait(lock);
        }
    }
 
    for (auto it = m_threads.begin(); it != m_threads.end(); it++) {
        if ((*it)->thread->joinable()) {
            (*it)->thread->join();
        }
    }
 
 
    // threads clear
    while (!m_threads.empty()) {
        ThreadContext* thread = m_threads.front();
        m_threads.pop_front();
        thread->thread.reset();
        delete thread; 
    }
 
    m_num_threads = 0;
    m_num_busy_threads = 0;
 
    // tasks clear
    clear_tasks();
}
 
void ThreadPool::clear_tasks()
{
    std::unique_lock<std::mutex> lock(m_lock);
    while (!m_task_queue.empty()) {
        m_task_queue.pop();
    }
}
 
void ThreadPool::wait_for_idle()
{
    if (m_exit) {
        return;
    }
 
    for (;;) {
        {
            std::unique_lock<std::mutex> lock(m_lock);
            if (m_task_queue.empty() && m_num_busy_threads == 0) {
                return;
            }
        }
        //阻塞1秒
        this_thread::sleep_for(chrono::seconds(1));
    }
}
 
void ThreadPool::set_min_thread_number(int num_threads)
{
    if (m_exit) {
        return;
    }
    if (num_threads <= 0) {
        m_min_num_threads = SysInfo::get_logical_cpu_number();
    } else {
        m_min_num_threads = num_threads;
    }
}
 
void ThreadPool::set_max_thread_number(int num_threads)
{
    if (m_exit) {
        return;
    }
    if (num_threads < m_min_num_threads) {
        m_max_num_threads = 2 * m_min_num_threads;
    } else {
        m_max_num_threads = num_threads;
    }
}
 
uint64_t ThreadPool::add_task(const TaskHandler& callback)
{
    return add_task_internal(callback, 10);
}
 
uint64_t ThreadPool::add_task(const TaskHandler& callback, int priority)
{
    return add_task_internal(callback, priority);
}
 
bool ThreadPool::cancel_task(uint64_t task_id)
{
    std::unique_lock<std::mutex> lock(m_lock);
    TaskMap::iterator it = m_tasks.find(task_id);
    if (it != m_tasks.end()) {
        it->second->set_cancel_flag(true);
        return true;
    } else {
        return false;
    }
}
 
void ThreadPool::get_stats() const
{
    std::unique_lock<std::mutex> lock(m_lock);
    std::cout << "######## ThreadPool Stats ################" << std::endl;
    std::cout << "m_min_num_threads:" << m_min_num_threads << std::endl;
    std::cout << "m_max_num_threads:" << m_max_num_threads << std::endl;
    std::cout << "m_num_threads:" << m_num_threads << std::endl;
    std::cout << "m_num_busy_threads:" << m_num_busy_threads << std::endl;
    std::cout << "m_threads size:" << m_threads.size() << std::endl;
    std::cout << "##########################################" << std::endl;
}
 
 
// working threads logic
void ThreadPool::work(ThreadContext* thread)
{
    m_num_busy_threads++;
    for (;;) {
        std::shared_ptr<Task> task;
        {
            std::unique_lock<std::mutex> lock(m_lock);
            if (m_exit || thread->check_waiting_timeout_flag()) {
                break;
            }
 
            if (!dequeue_task_in_lock(task)) {
                m_num_busy_threads--;
                m_task_cond.wait(lock);
                m_num_busy_threads++;
                continue;
            }
        }
 
        if (!task) {
            continue;
        }
 
        // execute task
        if (task->on_schedule) {
            task->on_schedule();
        }
    }
 
    // quit native-thread, move to freethread list
    {
        std::unique_lock<std::mutex> lock(m_lock);
        m_num_threads--;
        m_num_busy_threads--;
        if (m_num_busy_threads == 0) {
            m_exit_cond.notify_all();
        }
    }
}
 
/// private methods
static std::atomic<size_t> s_task_id(0);
 
uint64_t ThreadPool::new_task_id()
{
    return static_cast<uint64_t>(++s_task_id);
}
 
uint64_t ThreadPool::add_task_internal(const TaskHandler& callback,
        int priority)
{
    if (m_exit) {
        return 0;
    }
 
    uint64_t id = new_task_id();
    std::shared_ptr<Task> task(new Task(callback, id, priority));
 
    {
        std::unique_lock<std::mutex> lock(m_lock);
        // check whether need expand threads
        if (need_new_thread()) {
            expand_thread(); 
        }
        
        // add to task map
        m_tasks[id] = task;
 
        // push into priority task queue
        m_task_queue.push(task);
        m_task_cond.notify_all();
    }
    
    return id;
}
 
bool ThreadPool::need_new_thread() const
{
    if (m_num_threads >= m_max_num_threads) {
        return false;
    }
    if (m_num_threads < m_min_num_threads ||
            m_num_threads == m_num_busy_threads) {
        return true;
    }
    return false;
}
 
bool ThreadPool::need_shrink_thread() const
{
    if (m_num_threads > m_min_num_threads) {
        return true;
    }
    return false;
}
 
void ThreadPool::expand_thread()
{
    ThreadContext* thread = new ThreadContext();
    // stored in threadcontext.thread use scoped_ptr
    thread->thread.reset(
            new std::thread(std::bind(
                    &ThreadPool::work, this, thread)));
    // add threads into busythreads list 
    m_threads.push_back(thread);
    m_num_threads++;
}
 
bool ThreadPool::dequeue_task_in_lock(std::shared_ptr<Task>& task)
{
    if (m_task_queue.empty()) {
        return false;
    }
 
    task = m_task_queue.top();
    // remove from task queue
    m_task_queue.pop();
 
    // remove task map
    m_tasks.erase(task->id);
 
    return true;
}