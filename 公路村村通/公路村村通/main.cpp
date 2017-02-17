#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <set>
#include <algorithm>
using namespace std;
const int INF = 9999999;
int N,M;
int Graph[1001][1001];
int dist[1001];
int parent[1001];
int collected[1001];

int FindMinDist(){
    int MinDist = INF;int MinV = -1;
    for (int V=1; V <= N; ++V) {
        if (!collected[V] && dist[V] < MinDist) {
            MinDist = dist[V];
            MinV = V;
        }
    }
    return MinV;
}
int Prim(){
    for (int i=1; i < N+1; ++i) {
        collected[i] = 0;
        dist[i] = INF;
        parent[i] = -1;
    }
    int Vcount = 0,TotalWeight = 0;
    parent[1] = -1;
    dist[1] = 0;
    for (int i=1; i < N+1; ++i) {
        int V = FindMinDist();
        if (V == -1) {
            break;
        }
        collected[V] = 1;
        Vcount++;
        TotalWeight += dist[V];
        for (int W=1; W < N+1; ++W) {
            if (!collected[W] && Graph[V][W] < INF) {
                if (Graph[V][W] < dist[W]) {
                    dist[W] = Graph[V][W];
                    parent[W] = V;
                }
            }
        }
    }
    if (Vcount < N) {
        TotalWeight = -1;
    }
    return TotalWeight;
}
int main(){
    cin >> N >> M;
    for (int i=1; i < N+1; ++i) {
        for (int j=1; j < N+1; ++j) {
            Graph[i][j] = INF;
        }
    }
    for (int i=0; i < M; ++i) {
        int from,to,cost;
        cin >> from >> to >> cost;
        Graph[from][to] = Graph[to][from] = cost;
    }
    int ans = 0;
    ans = Prim();
    cout << ans << endl;
    return 0;
}