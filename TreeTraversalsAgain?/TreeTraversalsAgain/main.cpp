//
//  main.cpp
//  TreeTraversalsAgain
//
//  Created by 何宏炜 on 16/6/7.
//  Copyright © 2016年 何宏炜. All rights reserved.
//已知二叉树的前序遍历和中序遍历求二叉树的后序遍历

#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

// 给定前序遍历和中序遍历，求出二叉树的后序遍历
void getPostOrder(vector<int> preOrder, int preL, vector<int> inOrder, int inL,
                  vector<int> &postOrder, int postL, int n)
{
    if (n == 0) return ;
    if (n == 1) {
        postOrder[postL] = preOrder[preL];
        return ;
    }
    auto root = preOrder[preL];
    postOrder[postL + n - 1] = root;
    //在中序遍历数组上找出root的位置
    int i = 0;
    while (i < n) {
        if (inOrder[inL + i] == root) break;
        ++i;
    }
    // 计算出root节点左右子树节点的个数
    int L = i, R = n - i - 1;
    // 递归的进行求解
    getPostOrder(preOrder, preL + 1, inOrder, inL, postOrder, postL, L);
    getPostOrder(preOrder, preL + L + 1, inOrder, inL + L + 1, postOrder, postL + L, R);
}

vector<vector<int>> getOrder(int N)
{
    vector<int> preOrder(N, 0);
    vector<int> inOrder(N, 0);
    stack<int> st;
    int preL = 0, inL = 0;
    
    for (int i = 0; i < 2*N; ++i) {
        string str; int tmp;
        cin >> str;
        if (str == "Push") {
            cin >> tmp;
            preOrder[preL++] = tmp;
            st.push(tmp);
        } else if (str == "Pop") {
            inOrder[inL++] = st.top();
            st.pop();
        }
    }
    return {preOrder, inOrder};
}

int main()
{
    int N;
    cin >> N;
    auto res = getOrder(N);
    vector<int> postOrder(N, 0);
    getPostOrder(res[0], 0, res[1], 0, postOrder, 0, N);
    
    int i = 0;
    for (; i < N-1; ++i) {
        cout << postOrder[i] << " ";
    }
    cout << postOrder[i] << endl;
    return 0;
}