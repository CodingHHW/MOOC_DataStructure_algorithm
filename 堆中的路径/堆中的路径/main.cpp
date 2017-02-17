//
//  main.cpp
//  堆中的路径
//
//  Created by 何宏炜 on 16/6/15.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
using namespace std;

#define MAXN 1001
#define MINH -10001

int H[MAXN],size;
//********创建一个空堆**********//
void Creat(){
    size = 0;
    H[0] = MINH; //设置哨兵
}
//*******插入元素**********//
void Insert(int X){
    int i;
    for (i=++size; H[i/2] > X; i/=2) {
        H[i] = H[i/2];
    }
    H[i] = X;
}

int main() {
    int n,m,x,i,j;
    cin >> n >> m;
    Creat();
    for (i=0; i < n; ++i) {
        cin >> x;
        Insert(x);
    }
    for (i=0; i < m; ++i) {
        cin >> j;
        bool have=1;
        while (j >= 1) {
            if (have) {
                cout << H[j];
                have = 0;
            }
            else{
                cout << " " << H[j];
            }
            j /= 2;
        }
        cout << endl;
    }
    return 0;
}
