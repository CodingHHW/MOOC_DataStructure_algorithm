//
//  main.cpp
//  列出连通集
//
//  Created by 何宏炜 on 16/6/17.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
#include <queue>
using namespace std;

/* 图的邻接矩阵表示法 */

#define MaxVertexNum 100    /* 最大顶点数设为100 */
#define INFINITY 0        /* ∞设为双字节无符号整数的最大值65535*/
typedef int Vertex;         /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;        /* 边的权值设为整型 */
typedef char DataType;        /* 顶点存储的数据类型设为字符型 */

#define MAXN 15
int visited[MAXN] = {0};
int Visited[MAXN] = {0};     //没有遍历过就为0，遍历过置为1

/* 边的定义 */
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;      /* 有向边<V1, V2> */
 //   WeightType Weight;  /* 权重 */
};
typedef PtrToENode Edge;

/* 图结点的定义 */
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;  /* 顶点数 */
    int Ne;  /* 边数   */
    WeightType G[MaxVertexNum][MaxVertexNum]; /* 邻接矩阵 */
 //   DataType Data[MaxVertexNum];      /* 存顶点的数据 */
    /* 注意：很多情况下，顶点无数据，此时Data[]可以不用出现 */
};
typedef PtrToGNode MGraph; /* 以邻接矩阵存储的图类型 */



MGraph CreateGraph( int VertexNum )
{ /* 初始化一个有VertexNum个顶点但没有边的图 */
    Vertex V, W;
    MGraph Graph;
    
    Graph = (MGraph)malloc(sizeof(struct GNode)); /* 建立图 */
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    /* 初始化邻接矩阵 */
    /* 注意：这里默认顶点编号从0开始，到(Graph->Nv - 1) */
    for (V=0; V<Graph->Nv; V++)
        for (W=0; W<Graph->Nv; W++)
            Graph->G[V][W] = INFINITY;
    
    return Graph;
}

void InsertEdge( MGraph Graph, Edge E )
{
    /* 插入边 <V1, V2> */
    Graph->G[E->V1][E->V2] = 1;// E->Weight;
    /* 若是无向图，还要插入边<V2, V1> */
    Graph->G[E->V2][E->V1] = 1;//E->Weight;
}

MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
 //   Vertex V;
    int Nv, i;
    
    cin >> Nv; /* 读入顶点个数 */
    Graph = CreateGraph(Nv); /* 初始化有Nv个顶点但没有边的图 */
    cin >> Graph->Ne;  /* 读入边数 */
    if ( Graph->Ne != 0 ) { /* 如果有边 */
        E = (Edge)malloc(sizeof(struct ENode)); /* 建立边结点 */
        /* 读入边，格式为"起点 终点 权重"，插入邻接矩阵 */
        for (i=0; i<Graph->Ne; i++) {
            cin >> E->V1 >> E->V2 ;//>> E->Weight;
            /* 注意：如果权重不是整型，Weight的读入格式要改 */
            InsertEdge( Graph, E );
        }
    }
    
    /* 如果顶点有数据的话，读入数据 */
 //   for (V=0; V<Graph->Nv; V++)
 //       scanf(" %c", &(Graph->Data[V]));
    
    return Graph;
}

/* IsEdge(Graph, V, W)检查<V, W>是否图Graph中的一条边，即W是否V的邻接点。  */
bool IsEdge( MGraph Graph, Vertex V, Vertex W )
{
    return Graph->G[V][W] != INFINITY ? true : false;
}
/* 邻接矩阵存储的图 - DFS */
void DFS (MGraph Graph, Vertex S){
    visited[S] = true;
    cout << S << ' ';
    for (Vertex v=0; v < Graph->Nv; ++v) {
        if (!visited[v] && IsEdge(Graph, S, v)) {
            DFS(Graph, v);
        }
    }
}

void ListComponentsDFS(MGraph Graph){
    for (int i=0; i < Graph->Nv; ++i) {
        if (!visited[i]) {
            cout << "{ ";
            DFS(Graph, i);
            cout << "}" << endl;
        }
    }
}

/* 邻接矩阵存储的图 - BFS */

/* 此函数根据图的不同类型要做不同的实现，关键取决于对不存在的边的表示方法。*/
/* 例如对有权图, 如果不存在的边被初始化为INFINITY, 则函数实现如下:         */


/* Visited[]为全局变量，已经初始化为false */
void BFS ( MGraph Graph, Vertex S)
{   /* 以S为出发点对邻接矩阵存储的图Graph进行BFS搜索 */
    queue<Vertex> Q; //创建空队列
    Vertex V, W;
    
    /* 访问顶点S：此处可根据具体访问需要改写 */
    Visited[S] = true; /* 标记S已访问 */
    Q.push(S); /* S入队列 */
    while ( !Q.empty() ) {
        V = Q.front();Q.pop();  /* 弹出Q第一个元素，并赋值给V */
        cout << V << ' ';
        for( W=0; W<Graph->Nv; W++ ) /* 对图中的每个顶点W */
        /* 若W是V的邻接点并且未访问过 */
            if ( !Visited[W] && IsEdge(Graph, V, W) ) {
                /* 访问顶点W */
                Visited[W] = true; /* 标记W已访问 */
                Q.push(W); /* W入队列 */
            }
    } /* while结束*/
}

void ListComponentsBFS(MGraph Graph){
    for (int i=0; i < Graph->Nv; ++i) {
        if (!Visited[i]) {
            cout << "{ ";
            BFS(Graph, i);
            cout << "}" << endl;
        }
    }
}

int main() {
    MGraph M;
    M = BuildGraph();
    ListComponentsDFS(M);
    ListComponentsBFS(M);
    
    /* 输出矩阵
    for (int i=0; i < M->Nv; ++i) {
        for (int j=0; j < M->Nv; ++j) {
            cout << M->G[i][j] << ' ';
        }
        cout << endl;
    }
     */
    
    return 0;
}
