//
//  main.cpp
//  树的同构
//  结构数组表示二叉树
//  Created by 何宏炜 on 16/6/4.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

int const MaxTree = 10;
int const Null = -1;
#define ElementType char
#define Tree int

struct TreeNode{
    ElementType Element;
    Tree Left;
    Tree Right;
}T1[MaxTree],T2[MaxTree];

//**************建立二叉树******//返回跟节点
Tree BuildTree(struct TreeNode T[]){
    int N;
    cin >> N;
    int *check;check = new int[N];
    char cl,cr;
    int Root = Null;
    int i = 0;
    if (N) {
        
        for (i=0; i< N ; ++i) {
            check[i] = 0;
        }
         
        for (i=0; i<N ; ++i) {
            cin >> T[i].Element >> cl >> cr;
            if (cl != '-') {
                T[i].Left = cl - '0';
                check[T[i].Left] = 1;
            }
            else{
                T[i].Left = Null;
            }
            if (cr != '-') {
                T[i].Right = cr - '0';
                check[T[i].Right] = 1;
            }
            else{
                T[i].Right = Null;
            }
        }
        for (i=0; i<N ; ++i) {
            if (!check[i]) {
                break;
            }
        }
        Root = i;
    }
    return Root;
}

//****************比较是否同构*****************//
int Isomorphic(Tree R1,Tree R2){
    if ((R1 == Null) && (R2 == Null)) {
        return 1;
    }
    if ((R1 == Null && R2 != Null) || (R1 != Null && R2 == Null)) {
        return 0;
    }
    if (T1[R1].Element != T2[R2].Element) {          //树根的值不一样
        return 0;
    }
    if ((T1[R1].Left == Null) && (T2[R2].Left == Null)) {
        return Isomorphic(T1[R1].Right, T2[R2].Right);
    }
    if (((T1[R1].Left != Null)&&(T2[R2].Left != Null))&&((T1[T1[R1].Left].Element) == (T2[T2[R2].Left].Element))) {
        return (Isomorphic(T1[R1].Left, T2[R2].Left)&&Isomorphic(T1[R1].Right, T2[R2].Right));
    }
    else{
        return (Isomorphic(T1[R1].Left , T2[R2].Right) && Isomorphic(T1[R1].Right, T2[R2].Left));
    }
}

int main(int argc, const char * argv[]) {
    Tree R1,R2;
    
    R1 = BuildTree(T1);
    R2 = BuildTree(T2);
    if (Isomorphic(R1,R2)) {
        cout << "Yes" << endl;
    }
    else{
        cout << "No" << endl;
    }
    
    return 0;
}


