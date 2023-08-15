#include <iostream>
#include <vector>
#include <set>
#include<algorithm>
#include<cassert>


using namespace std;
// 以下会有问题
template<typename T>
std::ostream& operator<<(std::ostream& os,  T& c) {
    os << '[';
    for (auto it = c.begin(); it != c.end(); ++it) {
        os << (*it);
        if (std::next(it) != c.end()) {
            os << ',';
        }
    }
    os << ']';
    return os;
}


void test_assert(){
    // std::cout<< string("test_assert_run")<< '\n';
    int a = 10;
    assert(a==5);
}





int main() {
    test_assert();

    std::vector<int> v = {1, 2, 3, 3, 4, 4, 5};

    unique(v.begin(), v.end());
    cout<< v<<endl;
    
    std::multiset<int> st;
    for (int i=1; i<7; i++) st.insert(i*10); 
    
    std::cout<< st<< std::endl;

    // 使用迭代器输出元素地址

    vector<vector<int> > ids;
    ids.push_back({0, 0});
    cout<< ids<<endl;

    return 0;
}