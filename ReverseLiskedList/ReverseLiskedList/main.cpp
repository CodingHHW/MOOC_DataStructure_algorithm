#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 100001
typedef struct{
    int addr;
    int data;
    int next;
}Node;

void RevList(vector<Node> &list, int k){     //引用传递    &list
    int length = list.size();
    int round = length/k;
    
    for(int i = 1; i <= round; ++i){
        int start = (i-1)*k;
        int end = i*k;
        reverse(list.begin() + start, list.begin() + end);
    }
}

void PrintList(vector<Node> list){
    int length = list.size();
    for(int i = 0; i < length-1; ++i){
        printf("%05d %d %05d\n", list[i].addr, list[i].data, list[i+1].addr);
    }
    printf("%05d %d %d\n",list[length-1].addr, list[length-1].data, -1);
}

int main(){
    
//*************输入函数**************//
    Node nodes[MAXN];
   
    int firstAdd, n, k;
    scanf("%d%d%d", &firstAdd, &n, &k);
    while(n--){
        Node nn;
        scanf("%d%d%d", &nn.addr, &nn.data, &nn.next);
        nodes[nn.addr] = nn;
    }
//************通过list把链表排好序***********//
    vector<Node> list;
    int address = firstAdd;
    while(address != -1){
        list.push_back(nodes[address]);
        address = nodes[address].next;
    }

    RevList(list,k);
    PrintList(list);
    
    return 0;
}
