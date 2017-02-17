//
//  main.cpp
//  栈的压入弹出
//
//  Created by 何宏炜 on 16/7/13.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
#include <stack>
using namespace std;

bool IsPopOrder(const int* pPush, const int* pPop, int nlength){
    bool bPossible = false;
    if (pPush != NULL && pPop != NULL && nlength > 0) {
        const int* pNextPush = pPush;
        const int* pNextPop = pPop;
        stack<int> stackDada;
        while (pNextPop - pPop < nlength) {
            while (stackDada.empty() || stackDada.top() != *pNextPop) {
                if (pNextPush - pPush == nlength) {
                    break;
                }
                stackDada.push(*pNextPush);
                ++pNextPush;
            }
            if (stackDada.top() != *pNextPop) {
                break;
            }
            stackDada.pop();
            ++ pNextPop;
        }
        if (stackDada.empty() && pNextPop - pPop == nlength) {
            bPossible = true;
        }
    }
    return bPossible;
}
int main() {
    int *pPush,*pPop;
    int n;
    cin >> n;
    pPush = pPop = new int(n);
    
    for (int i =0; i < n; ++i) {
        cin >> pPush[i];
    }
    for (int i =0; i < n; ++i) {
        cout << pPush[i];
    }
    cout << endl;
    
    for (int j=0; j < n; ++j) {
        cin >> pPop[j];
    }
    for (int j=0; j < n; ++j) {
        cout << pPop[j];
    }
    cout << endl;
    cout << IsPopOrder(pPush, pPop, n) << endl;
    if (IsPopOrder(pPush, pPop, n)) {
        cout << "Yes" << endl;
    }
    else
        cout << "No" << endl;
    return 0;
}
