//
//  main.cpp
//  两个栈实现队列
//
//  Created by 何宏炜 on 16/7/9.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
#include <stack>
using namespace std;

template <typename T> class CQueue{
public:
    CQueue(void);
    ~CQueue(void);
    void appendTail(const T& node);
    T deleteHead();
private:
    stack<T> stack1;
    stack<T> stack2;
};

template <typename T >
void CQueue<T>::appendTail(const T& element) {
    stack1.push(element);
}

template <typename T >
T CQueue<T>::deleteHead() {
    if (stack2.size()<=0) {
        while (stack1.size()>0) {
            T & data  = stack1.top();
            stack1.pop();
            stack2.push(data);
        }
    }
    if (stack2.size() == 0) {
        throw new exception();
    }
    T head = stack2.top();
    stack2.pop();
    return head;
}

int main() {
    CQueue<int> Q;
    for (int i=0; i < 5; ++i) {
        Q.appendTail(i);
    }
    for (int i=0; i < 5; ++i) {
        cout << Q.deleteHead();
    }
    return 0;
}
