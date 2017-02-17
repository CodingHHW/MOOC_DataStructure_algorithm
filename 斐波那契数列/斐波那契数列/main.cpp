//
//  main.cpp
//  斐波那契数列
//
//  Created by 何宏炜 on 16/7/9.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
#include <cmath>
using namespace std;

int main(int argc, const char * argv[]) {
    long long f = 0;
    int n;

    while (cin >> n) {
        f = (1/sqrt(5))*((pow((1+sqrt(5))/2, n))-pow((1-sqrt(5))/2, n));
        cout << f << endl;
    }
    return 0;
}
