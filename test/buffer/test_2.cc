#include <iostream>
#include <vector>

using namespace std;
int countExpressions(int n) {
    std::vector<int> dp(n + 1, 0);
    dp[0] = 1;
    dp[1] =1;
    dp[2] = 2;

    for(int i= 2; i <= n ;i++)
    {
        if(i&1)
            dp[i] = dp[i-1];
        else
            dp[i] = (dp[i/2] + dp[i-1])%1000000007;
    }

    return dp[n];
}

int main() {
    int n;
    while(1){
        std::cout << "请输入一个正整数 n：";
        std::cin >> n;
        
        int count = countExpressions(n);
        cout << "正整数 " << n << " 的不同表达方式数量为：" << count << std::endl;
    }


    return 0;
}