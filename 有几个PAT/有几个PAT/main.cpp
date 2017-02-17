//
//  main.cpp
//  有几个PAT
//
//  Created by 何宏炜 on 16/6/29.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;
int main() {
    string S;
    cin >> S;
    int P_Count=0;
    long long PA_Count=0;
    long long PAT_Count=0;
    for (int i=0; i < S.length(); ++i) {
        if (S[i] == 'P') {
            ++P_Count;
        }
        else if (S[i] == 'A'){
            PA_Count += P_Count;
            PA_Count %=1000000007;
        }
        else if (S[i] == 'T'){
            PAT_Count += PA_Count;
            PAT_Count %=1000000007;
        }
    }
    cout << PAT_Count << endl;
    return 0;
}
