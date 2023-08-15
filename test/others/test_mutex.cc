#include<iostream>
#include<thread>
#include<mutex>
#include<unistd.h>


using namespace std;
std::mutex mtx;           // mutex for critical section

void has_mutex (int n, char c) {
  // critical section (exclusive access to std::cout signaled by locking mtx):
  mtx.lock();
  for (int i=0; i<n; ++i) { std::cout << c; }
  std::cout << '\n';
  mtx.unlock();
}

void not_mutex (int n, char c) {
  // critical section (exclusive access to std::cout signaled by locking mtx):
  for (int i=0; i<n; ++i) { std::cout << c; }
  cout<< '\n';

}


int main(){
    thread h1(has_mutex, 20, 'a');
    thread h2(has_mutex, 20, 'b');
    
    h1.detach();
    h2.detach();

    // sleep(5);  
    thread n1(not_mutex, 200, 'c');
    thread n2(not_mutex, 200, 'd');
    n1.detach();
    n2.detach();
    sleep(4);
    return 0;


}