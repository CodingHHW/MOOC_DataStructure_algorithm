//
//  main.cpp
//  重建二叉树
//
//  Created by 何宏炜 on 16/7/9.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
#include <queue>
using namespace std;

//********定义二叉树*********//
struct BinaryTreeNode{
    int Value;
    BinaryTreeNode *Left;
    BinaryTreeNode *Right;
};
BinaryTreeNode * ConstructCore(int *startPreorder, int * endPreorder, int *startInorder, int *endInorder){
    //********前序遍历序列的第一个数字是跟节点的值********//
    int rootValue = startPreorder[0];
    BinaryTreeNode *root = new BinaryTreeNode();
    root->Value = rootValue;
    root->Left = root->Right = NULL;
    
    if (startPreorder == endPreorder) {
        if (startInorder == endInorder && *startPreorder == *startInorder) {
            return root;
        }
        else{
            throw exception();
        }
    }
    //******在中序遍历中找到跟节点的值*******//
    int *rootInorder = startInorder;
    while (rootInorder <= endInorder && *rootInorder != rootValue) {
        ++ rootInorder;
    }
    if (rootInorder == endInorder && *rootInorder != rootValue) {
        throw exception();
    }
    long leftLength = rootInorder - startInorder;
    int *leftPreorderEnd =  startPreorder + leftLength;
    if (leftLength > 0) {
        //构建左子树
        root = ConstructCore(startPreorder+1, leftPreorderEnd, startInorder, rootInorder-1);
    }
    if (leftLength < endPreorder - startPreorder) {
        //构建右子树
        root = ConstructCore(leftPreorderEnd+1, endPreorder, rootInorder+1, endInorder);
    }
    return root;
}
BinaryTreeNode* Construct(int* preorder, int* inorder, int length){
    if (preorder == NULL || inorder == NULL || length < 0) {
        return NULL;
    }
    return ConstructCore(preorder, preorder+length-1, inorder, inorder+length-1);
}
//**********二叉树的输出************//
//前序遍历
void PreorderTraversal(BinaryTreeNode *BT){
    if (BT) {
        cout << BT->Value << ' ';
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
}
//中序遍历
void InorderTraversal(BinaryTreeNode *BT){
    if (BT) {
        InorderTraversal(BT->Left);
        cout << BT->Value << ' ';
        InorderTraversal(BT->Right);
    }
}
//后续遍历
void PostorderTraversal(BinaryTreeNode *BT){
    if (BT) {
        PostorderTraversal(BT->Left);
        PostorderTraversal(BT->Right);
        cout << BT->Value << ' ';
    }
}
//层序遍历
void LevelorderTraversal(BinaryTreeNode *BT){
    queue<BinaryTreeNode*> Q;
    BinaryTreeNode* T;
    if (!BT) {
        return;
    }
    Q.push(BT);
    while (!Q.empty()) {
        T = Q.front();
        cout << T->Value << ' ';
        Q.pop();
        if (T->Left) {
            Q.push(T->Left);
        }
        if (T->Right) {
            Q.push(T->Right);
        }
    }
}

int main() {
    int preorder[8],inorder[8];
    for (int i=0; i < 8; ++i) {
        cin >> preorder[i];
    }
    for (int j=0; j < 8; ++j) {
        cin >> inorder[j];
    }
    int *Pre = preorder;
    int *In = inorder;
    BinaryTreeNode *BT;
    BT = Construct(Pre, In, 8);
    PreorderTraversal(BT);
    InorderTraversal(BT);
    PostorderTraversal(BT);
    LevelorderTraversal(BT);
    return 0;
}


