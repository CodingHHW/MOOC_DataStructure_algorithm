//
//  main.cpp
//  PopSequence
//
//  Created by 何宏炜 on 16/6/3.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <stdlib.h>
using namespace std;
void rand_num(int *num,int n){
    srand((signed)time(NULL));
    for (int i=0; i<n ; ++i) {
        num[i] = rand()%2;
    }
}

int main(int argc, const char * argv[]) {
    int ran[100];int j=0;
    rand_num(ran, 100);
    
    stack<int> sta;
    vector<int> v;
    int M;
    cin >> M;
    sta.push(1);
    for (int i=2; i< M ; ++i) {
       // for (int j=2; j< M ; ++j) {
            if (ran[j++]) {
                cout << sta.top();
                sta.pop();
            }
            sta.push(i);
       // }
    }
    cout << endl;
    
    return 0;
}
