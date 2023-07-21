# tinywebserver
first change

[note: ] 不到100行的代码就只有一个`.h`文件, 就直接在头文件中实现


### 0 代码风格
- [C++ 风格指南](https://zh-google-styleguide.readthedocs.io/en/latest/google-cpp-styleguide/contents/)
- 


#### 1. 命名规则

- **文件名要全部小写**, 可以包含下划线 (\_) 或连字符 (-), 依照项目的约定. 如果没有约定, 那么“_”更好.
- **内联函数**必须放在 .h 文件中. 如果内联函数比较短, 就直接放在 .h 中.
- 
- **类名**称的每个单词**首字母均大写**, 不包含下划线: 形如`MyExcitingClass`, MyExcitingEnum.
- **变量** (包括函数参数) 和数据成员名一律小写, 单词之间用下划线连接. 类的成员变量以下划线结尾,
- **常量** 声明为 constexpr 或 const 的变量, 或在程序运行期间其值始终保持不变的, 命名时以“k”开头, 大小写混合.`const int kDaysInAWeek = 7;`
- 函数名的每个单词**首字母大写** (即“驼峰变量名”或“帕斯卡变量名”), 没有下划线. 对于首字母**缩写**的单词, 更倾向于将它们视作一个单词进行首字母大写 (例如, 写作 StartRpc() 而非 StartRPC()).



较好的起名

```c++
int price_count_reader; // 用于读取价格计数器

int num_errors; // 错误数量

int num_dns_connections; // DNS 连接数量

int count; // 计数器

int error_count; // 错误数量

int num_completed_connections; // 完成的连接数量

int web_gateway_connections; // Web 网关连接数量

int page_cache_reader; // 用于读取页面缓存

int customer_id; // 客户 ID


// 类内变量名的规范
string table_name; // 好 - 用下划线.
string tablename; // 好 - 全小写.
string tableName; // 差 - 混合大小写


// 常量命名规范
const int kDaysInAWeek = 7;
```








#### 0.2 注释风格

下面的规则描述了如何注释以及在哪儿注释

三层的注释

- 文件注释
- 类注释
- 函数注释
- 变量注释/ 实现注释

- 使用 // 或 /* */, **统一**就好.
- **文件注释**描述了该文件的内容. 如果一个文件只声明, 或实现, 或测试了一个对象, 并且这个对象已经在它的声明处进行了详细的注释, 那么就没必要再加上文件注释. 除此之外的其他文件都需要文件注释



我们使用空格缩进. **不要在代码中使用制表符**. 你应该设置**编辑器**将制表符转为空格.

```c++
ReturnType LongClassName::ReallyReallyReallyLongFunctionName(
    Type par_name1,
    // 4 space indent
    Type par_name2,
    Type par_name3) {
  DoSomething();
  // 2 space indent
...
}
```




#### 0.3 不懂的地方是如何注释

如果在源码中有不懂得地方, 会用以下方式注释

```c++
// ###################[Question]#######################
```




#### 0.4 在 C++ 项目中，什么时候该用 Boost，什么时候该用 STL 呢？

优先使用 STL，项目允许使用 boost 可以用 boost 作 STL **补充**。

这是使用C++11重写的muduo网络库，比原版简单的多。
https://github.com/Cdreamfly/CmfNetLib
这是使用上面重写的网络库写的集群聊天服务器，也比较简单。
https://github.com/Cdreamfly/ClusterChatServer
我GitHub上还有一些简单的项目欢迎Start




#### 0.5 如果在写某一个模块的时候, 出现了没有写过的模块的代码怎么办

- 给未知模块上声明你需要的函数, 并注明其作用
- 当你写到未知模块上, 再写具体的实现
- 原因可能是 模块是紧耦合的, 例如, Channel 是用于封装文件描述符的事件和回调，并与 EpollPoller（基于 epoll 的事件循环）一起使用。它们之间存在紧密的关系，以便实现事件驱动的网络编程。


tinywebserver
