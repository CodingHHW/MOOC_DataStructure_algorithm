//
//  main.cpp
//  FileTransfer
//
//  Created by 何宏炜 on 16/6/15.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
using namespace std;

const int MaxSize = 1000000;

//***************路径压缩***************//
int Find(int S[],int X){
    if (S[X] < 0) {
        return X;
    }
    else{
        return S[X] = Find(S, S[X]);
    }
}

void Union(int S[],int X1,int X2){
    int Root1 = Find(S, X1);
    int Root2 = Find(S, X2);
    if (Root1 == Root2) {
        return;
    }
    if (S[Root2] < S[Root1]) {
        S[Root1] = Root2;
    }
    else{
        if (S[Root1] == S[Root2]) {//树的高度
            S[Root1]--;
        }
        S[Root2] = Root1;
    }
}
void Input_connection(int S[]){
    int u,v;
    cin >> u >> v;
    Union(S,u,v);
}
void Check_connection(int S[]){
    int u,v;
    cin >> u >> v;
    int Root1 = Find(S, u);
    int Root2 = Find(S, v);
    if (Root1 == Root2) {
        cout << "yes" << endl;
    }
    else{
        cout << "no" << endl;
    }
}
void Check_network(int S[],int n){
    int counter = 0;
    for (int i=1; i <= n; ++i) {
        if (S[i] < 0) {
            ++counter;
        }
    }
    if (counter == 1) {
        cout << "The network is connected." << endl;
    }
    else{
        cout << "There are " << counter << " components." << endl;
    }
}
int main() {
    int N;
    int S[MaxSize];
    cin >> N;
    for (int i=1; i <= N; ++i) {
        S[i] = -1;
    }
    char in;
    do {
        cin >> in;
        switch (in) {
            case 'I':Input_connection(S);break;
            case 'C':Check_connection(S);break;
            case 'S':Check_network(S,N);break;
            default:break;
        }
    } while (in != 'S');
    return 0;
}
