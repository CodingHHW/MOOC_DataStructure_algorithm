#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
int const MaxVertexNum = 500;
#define INFINITY 65535
#define Vertex int
#define WeightType int
//***********边的定义*************//
struct Enode{
    Vertex V1,V2;
    WeightType Weight;
    WeightType Money;
};
typedef Enode *Edge;
//*************图节点定义************//
struct Gnode{
    int Nv;//顶点数
    int Ne;//边数
    WeightType G[MaxVertexNum][MaxVertexNum];
    WeightType M[MaxVertexNum][MaxVertexNum];
};
typedef Gnode *MGraph;
//***************函数声明*****************//
MGraph CreateGraph(int VertexNum);
void InsertEdge(MGraph Graph, Edge E);
MGraph BuildGraph(Vertex &S, Vertex &D);
Vertex FindMinDist(MGraph Graph, int dist[],int collected[]);
void dijkstra(MGraph Graph, int dist[],int path[],int cost[],Vertex S);
void FindThePathOut(MGraph Graph,Vertex S,Vertex D);

int main(){
    MGraph Graph;
    Vertex S,D;
    Graph = BuildGraph(S, D);
    FindThePathOut(Graph, S, D);
    return 0;
}
//*****************以下是建立图数据结构*****************//
MGraph CreateGraph(int VertexNum){
    MGraph Graph;
    Graph = new Gnode;
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for (Vertex V=0; V < Graph->Nv; ++V) {
        for (Vertex W=0; W < Graph->Nv; ++W) {
            Graph->G[V][W] = INFINITY;
            Graph->M[V][W] = INFINITY;
        }
    }
    return Graph;
}
void InsertEdge(MGraph Graph, Edge E){
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->M[E->V1][E->V2] = E->Money;
    Graph->G[E->V2][E->V1] = E->Weight;
    Graph->M[E->V2][E->V1] = E->Money;
}
MGraph BuildGraph(Vertex &S,Vertex &D){
    MGraph Graph;
    Edge E;
    Vertex Nv;
    cin >> Nv;
    Graph = CreateGraph(Nv);
    cin >> Graph->Ne >> S >> D;
    
    if (Graph->Ne != 0) {
        E = new Enode;
        for (int i=0; i < Graph->Ne; ++i) {
            cin >> E->V1 >> E->V2 >> E->Weight >> E->Money;
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}
//*********************建立图结束*******************//
//*********************以下是最短路径算法**********************//
void dijkstra(MGraph Graph,int dist[],int path[],int cost[],Vertex S){
    int collected[Graph->Nv];
    //初始化
    for (Vertex V=0; V < Graph->Nv; ++V) {
        dist[V] = cost[V] = INFINITY;
        path[V] = -1;
        collected[V] = 0;
    }
    dist[S] = cost[S] = 0;
    for (int V=0; V < Graph->Nv; ++V) {
        int K = FindMinDist(Graph, dist, collected);
        collected[K] = 1;
        for (int W=0; W < Graph->Nv; ++W) {
            if (!collected[W] && Graph->G[V][W] < INFINITY) {
                if (dist[V] + Graph->G[V][W] < dist[W]) {
                    dist[W] = dist[V] + Graph->G[V][W];
                    path[W] = V;
                    cost[W] = cost[V] + Graph->M[V][W];
                }
                else if (dist[V]+Graph->G[V][W]==dist[W] && cost[V]+Graph->M[V][W]<cost[W]){
                    dist[W] = dist[V] + Graph->G[V][W];
                    path[W] = V;
                    cost[W] = cost[V] + Graph->M[V][W];
                }
            }
        }
    }
}
/*
bool Dijkstra(MGraph Graph, int dist[],int path[],int cost[],Vertex S){
    int collected[Graph->Nv];
    Vertex V;
    for (V=0; V < Graph->Nv; ++V) {
        dist[V] = Graph->G[S][V];
        cost[V] = Graph->M[S][V];
       // path[V] = S;
        path[V] = -1;
        collected[V] = false;
    }
    for (int V=0; V < Graph->Nv; ++V) {
        if (Graph->G[S][V] < INFINITY) {
            path[V] = S;
        }
    }
    dist[S] = 0;cost[S] = 0;collected[S] = true;
    while (true) {
        V = FindMinDist(Graph, dist, collected);
        if (V == -1) {
            break;
        }
        collected[V] = true;
        for (Vertex W=0; W < Graph->Nv; ++W) {
            if (collected[W]==false && Graph->G[V][W] < INFINITY) {
                if (Graph->G[V][W] < 0) {
                    return false;
                }
                if (dist[V] + Graph->G[V][W] < dist[W]) {
                    dist[W] = dist[V] + Graph->G[V][W];
                    path[W] = V;
                    cost[W] = cost[V] + Graph->M[V][W];
                }
                else if (dist[V]+Graph->G[V][W]==dist[W] && cost[V]+Graph->M[V][W]<cost[W]){
                    dist[W] = dist[V] + Graph->G[V][W];
                    path[W] = V;
                    cost[W] = cost[V] + Graph->M[V][W];
                }
            }
        }
    }
    return true;
}
 */
Vertex FindMinDist(MGraph Graph,int dist[],int collected[]){
    Vertex MinV=0;
    int MinDist = INFINITY;
    for (Vertex V=0; V < Graph->Nv; ++V) {
        if (collected[V] == false && dist[V] < MinDist) {
            MinDist = dist[V];
            MinV = V;
        }
    }
    if (MinDist < INFINITY) {
        return MinV;
    }
    else{
        return -1;
    }
}
//********************最短路劲算法结束**********************//
void FindThePathOut(MGraph Graph,Vertex S,Vertex D){
    int dist[Graph->Nv];
    int path[Graph->Nv];
    int cost[Graph->Nv];
    dijkstra(Graph, dist, path, cost, S);
    
    //使用堆栈反向输出路径
    stack<int> Out_Path;
    Vertex P = D;
    while (P != -1) {
        Out_Path.push(P);
        P = path[P];
    }
    bool have = 1;
    while (!Out_Path.empty()) {
        if (have) {
            cout << Out_Path.top();
            Out_Path.pop();
            have = 0;
        }
        else{
            cout << "->" << Out_Path.top();
            Out_Path.pop();
        }
    }    
    cout << endl;
    cout << dist[D] << ' ' << cost[D] << endl;
}


