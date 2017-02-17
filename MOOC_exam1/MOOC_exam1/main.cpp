//
//  main.cpp
//  MOOC_exam1
/*  题目内容：
输入一段由英文字母组成的文字，将这段文字的前面一半逆序（当文字长度为奇数时，前一半的长度是stringlength/2取整），然后写出其行程编码。
编码方法是：将字符串中k个连续相同的字母X记为kX。当k=1时，省略。
输入格式:
一段由英文字母组成的文字，长度小于200.

输出格式：
编码字符串，一行，无空格

输入样例：
AAAABCCCCC

输出样例：
B4A5C
*/
//  Created by 何宏炜 on 16/6/1.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

void print(vector<char> S){
    int num = 1;
    for (int i=0; i<S.size(); ++i) {
        if (S[i]==S[i+1]) {
            num ++;
        }
        else if (num == 1){
            cout << S[i];
        }
        else if (num > 1){
            cout << num << S[i];
        }
    }
}

int main(int argc, const char * argv[]) {
    string str;
    cin >> str;
    unsigned long L = str.length();
    unsigned long halfL = L/2;
    
    vector<char> str1,str2;
    for (int i=halfL-1; i>=0; --i) {
        str1.push_back(str[i]);
    }
    for (int i=halfL; i<L; ++i) {
        str2.push_back(str[i]);
    }
    
    print(str1);
    print(str2);
    
   
    return 0;
}
