#include <iostream>
#include <string>

using namespace std;

// 处理 + / -；
// 找到小数点；
// 整数部分删除前导 0；
// 小数部分删除末尾 0；
// 如果小数部分为空，删除小数点；
// 如果整个数是 0，忽略正负号。

string normalize(string s) {
    // 1. 处理符号
    bool is_negative = false;
    if (!s.empty() && (s[0] == '+' || s[0] == '-')) {
        is_negative = (s[0] == '-');
        s = s.substr(1);
    }

    // 2. 找到小数点, 拆成整数部分和小数部分
    string intPart, fracPart;

    size_t dot_pos = s.find('.');
    if (dot_pos == string::npos) {
        intPart = s;
        fracPart = "";
    } else {
        intPart = s.substr(0, dot_pos);
        fracPart = s.substr(dot_pos + 1);
    }

    // 3. 整数部分删除前导 0
    int p = 0;
    while(p < (int)intPart.size() && intPart[p] == '0') {
        p++;
    }
    intPart = intPart.substr(p);
    if(intPart.empty()) {
        intPart = "0";
    }

    // 4. 小数部分删除末尾 0
    while(!fracPart.empty() && fracPart.back() == '0') {
        fracPart.pop_back();
    }
    if(fracPart.empty()) {
        fracPart = "";
    }

    // 判断是否为 0
    bool isZero = (intPart == "0" && fracPart.empty());

    // 0 不需要符号
    if(isZero) {
        return "0";
    }

    // 拼接规范形式
    string result;

    if(is_negative) result += "-";
    result += intPart;
    if(!fracPart.empty()) {
        result += "." + fracPart;
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    string A, B;

    while(cin >> A >> B) {
        string normalizedA = normalize(A);
        string normalizedB = normalize(B);
        if(normalizedA == normalizedB) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}