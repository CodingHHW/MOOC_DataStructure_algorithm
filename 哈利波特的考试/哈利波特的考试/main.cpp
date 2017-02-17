//
//  main.cpp
//  哈利波特的考试
//
//  Created by 何宏炜 on 16/6/18.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
using namespace std;

#define MaxVertexNum 100
#define INFINITY 65535
typedef int Vertex;
typedef int WeightType;

//*********边的定义
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1,V2;
    WeightType Weight;
};
typedef PtrToENode Edge;

//*********图节点的定义
typedef struct GNode *PtrToGnode;
struct GNode{
    int Nv;       //顶点数
    int Ne;       //边数
    WeightType G[MaxVertexNum][MaxVertexNum];
};
typedef PtrToGnode MGraph;

//*********创建空图
MGraph CreateGraph (int VertexNum){
    Vertex V, W;
    MGraph Graph;
    
    Graph = new GNode;
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for (V=0; V < Graph->Nv; ++V) {
        for (W=0; W < Graph->Nv; ++W) {
            Graph->G[V][W] = INFINITY;
        }
    }
    return Graph;
}
//*********插入边
void InsertEdge( MGraph Graph, Edge E){
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight;
}
//*********建立图
MGraph BuildGraph(){
    MGraph Graph;
    Edge E;
    int Nv,i;
    cin >> Nv;
    Graph = CreateGraph(Nv);
    cin >> Graph->Ne;
    if (Graph->Ne != 0) {
        E = new ENode;
        for (i=0; i < Graph->Ne; ++i) {
            cin >> E->V1 >> E->V2 >> E->Weight;
            --(E->V1);--(E->V2);
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}
//**********Floyd算法
void Floyd( MGraph Graph, WeightType D[][MaxVertexNum]){
    Vertex i,j,k;
    //****** 初始化
    for (i=0; i < Graph->Nv; ++i) {
        for (j=0; j < Graph->Nv; ++j) {
            D[i][j] = Graph->G[i][j];
        }
    }
    for (k=0; k < Graph->Nv; ++k) {
        for (i=0; i < Graph->Nv; ++i) {
            for (j=0; j < Graph->Nv; ++j) {
                if (D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }
}
//*********选择动物
WeightType FindMaxDist( WeightType D[][MaxVertexNum], Vertex i, int N){
    WeightType MaxDist;
    Vertex j;
    
    MaxDist = 0;
    for (j=0; j < N ; ++j) {
        if (i != j && D[i][j] > MaxDist) {
            MaxDist = D[i][j];
        }
    }
    return MaxDist;
}
void FindAnimal( MGraph Graph){
    WeightType D[MaxVertexNum][MaxVertexNum];
    WeightType MaxDist, MinDist;
    Vertex Animal = 0, i;
    Floyd(Graph, D);
    MinDist = INFINITY;
    for (i=0; i < Graph->Nv; ++i) {
        MaxDist = FindMaxDist(D, i, Graph->Nv);
        if (MaxDist == INFINITY) {
            cout << "0" << endl;
            return;
        }
        if (MinDist > MaxDist) {
            MinDist = MaxDist;
            Animal = i+1;
        }
    }
    cout << Animal << ' ' << MinDist << endl;
}

int main() {
    MGraph G;
    G = BuildGraph();
    FindAnimal(G);
    return 0;
}
