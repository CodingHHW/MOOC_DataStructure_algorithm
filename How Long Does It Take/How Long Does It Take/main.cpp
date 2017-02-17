#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N,M;
struct Node {
    int to;
    int time;
};
vector<Node> LGraph[101];
int Pre[101];
int CostTime[101];
int Out_path[101];

bool TopSort(){
    int Indegree[101];
    queue<int> Q;
    int cnt = 0;
    for (int i=1; i <= N; ++i) {
        Indegree[i] = 0;
    }
    for (int i=1; i <= N ; ++i) {
        for (auto it = LGraph[i].begin(); it != LGraph[i].end(); ++it) {
            Indegree[it->to]++;
        }
    }
    for (int i=1; i <= N; ++i) {
        if (Indegree[i] == 0) {
            Q.push(i);
        }
    }
    while (!Q.empty()) {
        int V = Q.front();Q.pop();
        Out_path[cnt++] = V;
        for (auto it = LGraph[V].begin(); it != LGraph[V].end(); ++it) {
            if (CostTime[V] + it->time > CostTime[it->to]) {
                CostTime[it->to] = CostTime[V] + it->time;
            }
            if (--Indegree[it->to] == 0) {
                Q.push(it->to);
            }
        }
    }
    if (cnt != N) {
        return 0;
    }
    else{
        return 1;
    }
}
int main() {
    cin >> N >> M;
    for (int i=0; i < M; ++i) {
        int from;Node nod;
        cin >> from >> nod.to >> nod.time;
        from++;nod.to++;
        LGraph[from].push_back(nod);
    }
    bool flag = TopSort();
    if (flag == 0) {
        cout << "Impossible" << endl;
    }
    else{
        int Max = -1;
        for (int i=1; i <= N ; ++i) {
            if (CostTime[i] > Max) {
                Max = CostTime[i];
            }
        }
        cout << Max << endl;
    }
    /*
     for (int i=1; i <= N ; ++i) {
     cout << CostTime[i] << " ";
     }
     cout << endl;
     for (int i=0; i < N ; ++i) {
     cout << Out_path[i] << " ";
     }
     */
    return 0;
}
