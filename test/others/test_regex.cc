#include<regex>



#include <iostream>
#include <regex>
#include <string>

int main() {
    std::string text = "Hello, my email address is example@example.com. Please contact me.";

    // 匹配电子邮件地址的正则表达式
    std::regex emailRegex(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b)");

    // 使用 regex_search 搜索匹配的第一个结果
    std::smatch match;
    if (std::regex_search(text, match, emailRegex)) {
        std::cout << "Found email address: " << match.str() << std::endl;
    }

    // 使用 regex_match 测试是否完全匹配
    if (std::regex_match(text, emailRegex)) {
        std::cout << "The text is an email address." << std::endl;
    }

    // 使用 regex_replace 替换匹配的部分
    std::string replacedText = std::regex_replace(text, emailRegex, "<EMAIL>");
    std::cout << "Replaced text: " << replacedText << std::endl;

    return 0;
}
