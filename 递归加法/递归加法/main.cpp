//
//  main.cpp
//  递归加法
//
//  Created by 何宏炜 on 16/7/9.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
using namespace std;
int AddFrom1ToN(int n){
    if (n == 0) {
        return 0;
    }
    return n + AddFrom1ToN(n-1);
}
int main(int argc, const char * argv[]) {
    int num = AddFrom1ToN(5000);
    cout << num << endl;
    return 0;
}
