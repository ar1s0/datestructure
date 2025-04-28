#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;

// 判断是否为运算符
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// 运算符优先级
int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// 中缀转后缀（支持括号和多位数字）
string infixToPostfix(const string& infix) {
    stack<char> s;
    string postfix;
    for (size_t i = 0; i < infix.size(); ++i) {
        char c = infix[i];
        if (isspace(c)) continue;
        if (isdigit(c)) {
            // 处理多位数字
            while (i < infix.size() && isdigit(infix[i])) {
                postfix += infix[i++];
            }
            postfix += ' ';
            --i;
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                postfix += ' ';
                s.pop();
            }
            if (!s.empty()) s.pop(); // 弹出 '('
        } else if (isOperator(c)) {
            while (!s.empty() && precedence(s.top()) >= precedence(c) && s.top() != '(') {
                postfix += s.top();
                postfix += ' ';
                s.pop();
            }
            s.push(c);
        }
    }
    while (!s.empty()) {
        if (s.top() != '(') {
            postfix += s.top();
            postfix += ' ';
        }
        s.pop();
    }
    // 去除末尾多余空格
    if (!postfix.empty() && postfix.back() == ' ') postfix.pop_back();
    return postfix;
}

// 计算后缀表达式（仅支持整数）
int evalPostfix(const string& postfix) {
    stack<int> s;
    istringstream iss(postfix);
    string token;
    while (iss >> token) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
            s.push(stoi(token));
        } else if (token.size() == 1 && isOperator(token[0])) {
            if (s.size() < 2) throw runtime_error("Invalid postfix expression");
            int b = s.top(); s.pop();
            int a = s.top(); s.pop();
            switch (token[0]) {
                case '+': s.push(a + b); break;
                case '-': s.push(a - b); break;
                case '*': s.push(a * b); break;
                case '/': s.push(a / b); break;
            }
        }
    }
    if (s.size() != 1) throw runtime_error("Invalid postfix expression");
    return s.top();
}

int main() {
    struct TestCase {
        string infix;
        string expectedPostfix;
        int expectedValue;
    } tests[] = {
        {"1+2", "1 2 +", 3},
        {"1+2*3", "1 2 3 * +", 7},
        {"(1+2)*3", "1 2 + 3 *", 9},
        {"10+20*30-40/5", "10 20 30 * + 40 5 / -", 609},
        {"(10+20)*(30-5)", "10 20 + 30 5 - *", 750},
        {"1+2*(3-4)/5", "1 2 3 4 - * 5 / +", 1},
        {"(1+2)*(3+4)", "1 2 + 3 4 + *", 21},
        {"100", "100", 100},
        {"((7))", "7", 7},
        {"1+2+3", "1 2 + 3 +", 6},
        {"2*(3+4*(5-6))", "2 3 4 5 6 - * + *", -10},
        {"(8+2)/(3-1)", "8 2 + 3 1 - /", 5},
        {"2*(3+4)/2", "2 3 4 + * 2 /", 7},
        {"1+2*(3+4*5)", "1 2 3 4 5 * + * +", 47},
        {"(1+2)*(3+4)*(5+6)", "1 2 + 3 4 + * 5 6 + *", 231}
    };

    for (const auto& test : tests) {
        string postfix = infixToPostfix(test.infix);
        int value = evalPostfix(postfix);
        cout << "中缀: " << test.infix << "\n后缀: " << postfix
             << "\n期望后缀: " << test.expectedPostfix
             << "\n计算结果: " << value
             << "\n期望结果: " << test.expectedValue
             << "\n" << ((postfix == test.expectedPostfix && value == test.expectedValue) ? "通过" : "未通过") << "\n\n";
    }
    return 0;
}