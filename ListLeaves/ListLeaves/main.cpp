//
//  main.cpp
//  ListLeaves
//
//  Created by 何宏炜 on 16/6/4.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include<iostream>
#include<vector>
#include<queue>
using namespace std;

using Tree = int ;
#define null -1  //用来表示-

struct TreeNode {
    int data;
    Tree left;
    Tree right;
};

int buildTree(vector<TreeNode> &tree, int N)
{
    Tree root= -1;
    char lef, rig;
    vector<int> check(N, 0);
    
    for(int i = 0; i < N; ++i)
    {
        tree[i].data = i;  //赋值元素
        cin >> lef >> rig;

        if(lef != '-') {
            tree[i].left = (int)(lef - '0');
            check[tree[i].left] = 1;    //标记该节点，及不可能为根节点
        } else
            tree[i].left = null;
        if (rig != '-') {
            tree[i].right = (int)(rig - '0');
            check[tree[i].right] = 1;
        } else
            tree[i].right = null;
    }
    int i = 0;
    for(; i < N; ++i)
        if(!check[i]) {
            root = i;
            break; //如果该节点没有被标记则为根节点
        }
    return root;   //返回跟节点元素
}

vector<int> findLeaves(const vector<TreeNode> &tree, Tree root)
{
    vector<int> leaves;
    queue<TreeNode> qu;
    TreeNode node;
    
    if(root == null)
        return {};
    qu.push(tree[root]);
    while(!qu.empty()) {
        node = qu.front();
        qu.pop();
        //如果该节点左右儿子都不存在则为根节点
        if((node.left == null) &&(node.right == null))
            leaves.push_back(node.data);
        if(node.left != null) qu.push(tree[node.left]);
        if(node.right != null) qu.push(tree[node.right]);
    }
    return leaves;
}

int main()
{
    int N;
    //vector<Tree> tree;
    Tree root;
    
    cin >> N;   //输入节点的个数
    vector<TreeNode> tree(10);      //放10个元素，默认值
    root = buildTree(tree, N);
    
    auto res = findLeaves(tree, root);
    for(decltype(res.size())i=0; i != res.size(); ++i)
    {
        cout << res[i];
        //注意：最后一个数字输出后没有空格
        i != res.size() - 1 ? cout <<" " : cout << endl;
    }
    return 0;
}
