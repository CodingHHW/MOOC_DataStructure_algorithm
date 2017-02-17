//
//  main.cpp
//  链表
//
//  Created by 何宏炜 on 16/7/6.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
#include <stack>
using namespace std;

typedef struct ListNode *PtrToListNode;
struct ListNode{
    int Value;
    PtrToListNode Next;
};
typedef PtrToListNode List;

List MakeEmptyList(){
    List list = NULL;
    return list;
}

void AddToList(List &list, int value){
    PtrToListNode pNew = new ListNode();
    pNew->Value = value;
    pNew->Next = NULL;
    
    if (list == NULL) {
        list = pNew;
    }
    else{
        PtrToListNode FindNode = list;
        while (FindNode->Next != NULL) {
            FindNode = FindNode->Next;
        }
        FindNode->Next = pNew;
    }
}

void RemoveNode(List &list, int value){
    if (list == NULL) {
        return;
    }
    PtrToListNode ToBeDeleted = NULL;
    if (list->Value == value) {
        ToBeDeleted = list;
        list = list->Next;
    }
    else{
        PtrToListNode FindNode = list;
        while (FindNode != NULL && FindNode->Next->Value != value) {
            FindNode = FindNode->Next;
        }
        ToBeDeleted = FindNode->Next;
        FindNode->Next = FindNode->Next->Next;
    }
    if (ToBeDeleted != NULL) {
        delete ToBeDeleted;
        ToBeDeleted = NULL;
    }
}

void InsertNode(List &list, int index, int InsertValue){
    if (list == NULL) {
        return;
    }
    PtrToListNode pNew = new ListNode();
    pNew->Value = InsertValue;
    PtrToListNode FindNode = list;
    if (index == 0) {
        pNew->Next = list;
        list = pNew;
    }
    else{
        for (int i=1; i < index; ++i) {
            FindNode = FindNode->Next;
        }
        pNew->Next = FindNode->Next;
        FindNode->Next = pNew;
    }
    
}
//*********用stack反向输出***********//
void ReversePrintList(List list){
    stack<PtrToListNode> nodes;
    PtrToListNode pNode = list;
    
    while (pNode != NULL) {
        nodes.push(pNode);
        pNode = pNode->Next;
    }
    while (!nodes.empty()) {
        pNode = nodes.top();
        cout << pNode->Value << ' ';
        nodes.pop();
    }
    cout << endl;
}
//*********用递归反向输出***********//
void PrintListReverse(List list){
    if (list != NULL) {
        if (list->Next != NULL) {
            PrintListReverse(list->Next);
        }
        cout << list->Value << ' ';
    }
}

void PrintList(List list){
    while (list != NULL) {
        cout << list->Value << ' ';
        list = list->Next;
    }
    cout << endl;
}
int main() {
    List mylist = MakeEmptyList();
    for (int i=0; i < 10; ++i) {
        AddToList(mylist, i);
    }
    InsertNode(mylist, 2, 100);
    RemoveNode(mylist, 4);
    PrintList(mylist);
    ReversePrintList(mylist);
    PrintListReverse(mylist);
    cout << endl;
    return 0;
}
