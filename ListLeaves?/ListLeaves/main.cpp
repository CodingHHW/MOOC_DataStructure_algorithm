//
//  main.cpp
//  ListLeaves
//
//  Created by 何宏炜 on 16/6/4.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
#include <queue>
#include <vector>
using namespace std;

using Tree = int;
#define null -1

struct TreeNode{
    int Data;
    int Left;
    int Right;
};


int buildTree(vector<TreeNode> &tree, int N)
{
    //cin >> N;
    vector<int> check(N, 0);
    char lef, rig;
    Tree root;
    
    int i = 0;
    if (N) {
        for (i=0; i<N; ++i) {
            tree[i].Data = i;
            cin >> lef >> rig ;
            if (lef != '-') {
                tree[i].Left = lef - '0';
                check[tree[i].Left] = 1;
            }
            else{
                tree[i].Left = -1;
            }
            if (rig != '-') {
                tree[i].Right = rig - '0';
                check[tree[i].Right] = 1;
            }
            else{
                tree[i].Right = -1;
            }
        }
        for (i=0; i<N; ++i) {
            if (!check[i]) {
                break;
            }
        }
        root = i;
    }
    return root;
}

vector<int> LevelOrderTraversal(const vector<TreeNode> &tree, Tree root)
{
    queue<TreeNode> qu;
    vector<int> leaves;
    TreeNode node;
    
    if (root == null) {
        return {};
    }
    qu.push(tree[root]);
    while (!qu.empty()) {
        node = qu.front();
        //cout << node.Data << ' ';
        qu.pop();
        leaves.push_back(node.Data);
        
        if (node.Left != null) {
            qu.push(tree[node.Left]);
        }
        if (node.Right != null) {
            qu.push(tree[node.Right]);
        }
    }
    return leaves;
    /*
    for (auto it=leaves.begin(); it != leaves.end(); ++it) {
        cout << *it << ' ';
    }
     */
}

int main()
{
    int N;
    cin >> N;
    vector<TreeNode> tree(10);     //放10个元素，默认值
    Tree root;
    root = buildTree(tree, N);
    
    //LevelOrderTraversal(tree, root);
    auto res = LevelOrderTraversal(tree, root);
    for (decltype(res.size()) i=0; i != res.size(); ++i) {
        cout << res[i] << ' ';
    }
    return 0;
}


