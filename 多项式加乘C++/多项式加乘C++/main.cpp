//
//  main.cpp
//  多项式加乘C++引用
//
//  Created by 何宏炜 on 16/6/2.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
using namespace std;

typedef class PolyNode *Polynomial;
class PolyNode{
private:
    int coef;
    int expon;
    Polynomial link;
public:
    Polynomial ReadPoly();
    Polynomial Add(Polynomial P1, Polynomial P2);
    Polynomial Mult(Polynomial P1, Polynomial P2);
    void PrintPoly(Polynomial P);
    void Attach( int c, int e, Polynomial *pRear);
};

int main() {
    Polynomial P1,P2,PP,PS;
    
    P1 = P1->ReadPoly();
    P2 = P2->ReadPoly();
    
    PP = PP->Mult(P1, P2);
    PP->PrintPoly(PP);
    
    PS = PS->Add(P1, P2);
    PS->PrintPoly(PS);
    
    return 0;
}
//***************连接函数*********************//
void PolyNode::Attach(int c, int e, Polynomial *pRear){
    Polynomial P;
    P = new PolyNode;
    P->coef = c;
    P->expon = e;
    P->link = NULL;
    (*pRear)->link = P;
    *pRear = P;
}
//*************多项式输入****************//
Polynomial PolyNode:: ReadPoly(){
    int N;
    cin >> N;
    
    Polynomial P,Rear,t;
    int c,e;
    P = new PolyNode;
    P->link = NULL;  //头结点为空
    Rear = P;
    while (N--) {
        cin >> c >> e;
        Attach(c , e , &Rear );
    }
    t = P;P = P->link;delete t; //删除临时生成的空节点
    return P;
}
//****************多项式输出*********************//
void PolyNode::PrintPoly(Polynomial P){
    int flag = 0;
    
    if (!P) {
        cout << "0 0" << endl;
        return;
    }
    
    while (P) {
        if (!flag) {
            flag = 1;
        }
        else{
            cout << ' ';
        }
        cout << P->coef << ' ' << P->expon;
        P = P->link;
    }
    cout << endl;
}
//**************多项式加法******************//
int Compare(int a,int b){
    if (a > b) {
        return 1;
    }
    else if (a < b){
        return -1;
    }
    else {
        return 0;
    }
}

Polynomial PolyNode::Add(Polynomial P1, Polynomial P2){
    Polynomial front, rear, temp;
    int sum;
    rear = new PolyNode;
    front = rear;
    while (P1 && P2) {
        switch (Compare(P1->expon,P2->expon)) {
            case 1:
                Attach(P1->coef, P1->expon, &rear);
                P1 = P1->link;
                break;
            case -1:
                Attach(P2->coef, P2->expon, &rear);
                P2 = P2->link;
                break;
            case 0:
                sum = P1->coef + P2->coef;
                if (sum) {
                    Attach(sum, P1->expon, &rear);
                }
                P1 = P1->link;
                P2 = P2->link;
                break;
            default:
                break;
        }
    }
    for (; P1;P1 = P1->link) {
        Attach(P1->coef, P1->expon, &rear);
    }
    for (; P2; P2 = P2->link) {
        Attach(P2->coef, P2->expon, &rear);
    }
    rear->link = NULL;
    temp = front;
    front = front->link;
    delete temp;
    return front;
}
//****************多项式乘法*****************//
Polynomial PolyNode::Mult(Polynomial P1, Polynomial P2){
    Polynomial P,Rear,t1,t2,t;
    int c,e;
    
    if (!P1 || !P2) {
        return NULL;
    }
    
    t1 = P1;t2 = P2;
    P = new PolyNode;
    P->link = NULL;
    Rear = P;
    
    while (t2) {
        Attach(t1->coef*t2->coef, t1->expon+t2->expon, &Rear);
        t2 = t2->link;
    }
    
    t1 = t1->link;
    while (t1) {
        t2 = P2;Rear = P;
        while (t2) {
            e = t1->expon + t2->expon;
            c = t1->coef * t2->coef;
            while (Rear->link && Rear->link->expon > e ) {
                Rear = Rear->link;
            }
            if (Rear->link && Rear->link->expon == e) {
                if (Rear->link->coef + c ) {
                    Rear->link->coef += c;
                }
                else{
                    t = Rear->link;
                    Rear->link = t->link;
                    delete t;
                }
            }
            else{
                t = new PolyNode;
                t->coef = c;t->expon = e;
                t->link = Rear->link;
                Rear->link = t;Rear = Rear->link;
            }
            t2 = t2->link;
        }
        t1 = t1->link;
    }
    t2 = P;P = P->link;delete t2;
    return P;
}


