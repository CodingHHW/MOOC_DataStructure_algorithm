//
//  main.cpp
//  set例子
//
//  Created by 何宏炜 on 16/6/21.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
#include <set>
#include <vector>
#include <list>
using namespace std;

int main() {
    vector<int> v;
   // v.push_back(1);
    for (int i=0; i < 5; ++i) {
        v.push_back(i);
    }
    v[2] = 10;
    cout << v[2] << endl;
    for (auto it = v.begin(); it != v.end(); it = it + 1) {
        cout << *it << ' ';
    }
    cout << endl;
    set<int> colll;
    colll.insert(4);
    colll.insert(3);
    colll.insert(5);
    colll.insert(1);
    colll.insert(6);
    colll.insert(2);
    colll.insert(9);
    for (auto pos=colll.begin(); pos != colll.end(); ++pos) {
        cout << *pos << ' ';
    }
    cout << endl;
    list<int> l;
    for (int i=6; i < 11; ++i) {
        l.push_back(i);
    }
    list<int>::iterator Iter = find(l.begin(), l.end(), 8);
    
    l.insert(Iter, 111);
    
    for (auto lit = l.begin(); lit != l.end(); lit++) {
        cout << *lit << ' ';
    }
    cout << endl;
    return 0;
}
