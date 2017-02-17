#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
typedef struct AVLNode *Position;
typedef struct AVLNode *AVLTree;
struct AVLNode{
    int Data;
    AVLTree Left,Right;
    int Height;
};
int GetHeight(Position P){
    if (!P) {
        return -1;
    }
    return P->Height;
}
AVLTree SingleLeftRotation(AVLTree A){
    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;
    A->Height = max(GetHeight(A->Left), GetHeight(A->Right))+1;
    B->Height = max(GetHeight(B->Left), GetHeight(B->Right))+1;
    return B;
}
AVLTree SingleRightRotation(AVLTree A){
    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Left = A;
    A->Height = max(GetHeight(A->Left), GetHeight(A->Right))+1;
    B->Height = max(GetHeight(B->Left), GetHeight(B->Right))+1;
    return B;
}
AVLTree DoubleLeftRightRotation(AVLTree A){
    A->Left = SingleRightRotation(A->Left);
    return SingleLeftRotation(A);
}
AVLTree DoubleRightLeftRotation(AVLTree A){
    A->Right = SingleLeftRotation(A->Right);
    return SingleRightRotation(A);
}
AVLTree Insert(AVLTree T,int X){
    if (!T) {
        T = new AVLNode;
        T->Data = X;
        T->Left = T->Right = NULL;
        T->Height = 0;
    }
    else if (X < T->Data){
        T->Left = Insert(T->Left, X);
        if (GetHeight(T->Left)-GetHeight(T->Right)==2) {
            if (X < T->Left->Data) {
                T = SingleLeftRotation(T);
            }
            else{
                T = DoubleLeftRightRotation(T);
            }
        }
    }
    else if ( X > T->Data ) {
        T->Right = Insert( T->Right, X );
        if ( GetHeight(T->Left)-GetHeight(T->Right) == -2 )
            if ( X > T->Right->Data ){
                T = SingleRightRotation(T);
            }
            else{
                T = DoubleRightLeftRotation(T);
            }
    }
    T->Height = max( GetHeight(T->Left), GetHeight(T->Right) ) + 1;
    return T;
}
int main(){
    int n, x;
    AVLTree T=NULL;
    cin >> n;
    for (int i=0; i<n ; ++i) {
        cin >> x;
        T = Insert(T,x);
    }
    cout << T->Data;
    return 0;
}
