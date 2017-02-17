//
//  main.cpp
//  kids
//
//  Created by 何宏炜 on 16/5/31.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int inStr(char a,string s){
    int flag = 0;
    for (int i=0; i<s.length(); ++i) {
        if (a==s[i]) {
            flag = 1;
        }
    }
    return flag;
}

int main(int argc, const char * argv[]) {
    string str[7]={"大人","小人","高大","人前人后","你好","东哥","大傻逼"};
    string my_str="大人小高前后";
    vector<string> CoutStr;
    vector<string> outStr;
    for (int i=0; i<my_str.length(); ++i) {
        for (int j=0; j<4; ++j) {
            if (my_str[i]==str[j][0]) {
                for (int k=1; k<str[j].length(); ++k) {
                    if (inStr(str[j][k], my_str)) {
                        outStr.push_back(str[j]);
                        //cout << str[j] << ' ';
                        break;
                    }
                }
            }
        }
    }
    
    sort(outStr.begin(), outStr.end());
    /*
    for (auto iter=outStr.begin(); iter!= outStr.end(); ++iter) {
        cout << *iter << ' ';
    }
    cout << endl;
    */
    
    for (auto it=outStr.begin(); it != outStr.end(); ++it) {
        if (*(it+1)==*it) {
            outStr.erase(it+1);
            --it;
        }
    }
    for (auto iter=outStr.begin(); iter!= outStr.end(); ++iter) {
        cout << *iter << ' ';
    }
    
    return 0;
}
