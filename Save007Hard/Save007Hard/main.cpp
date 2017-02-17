#include "iostream"
#include "math.h"
#include "queue"
#include "stack"
#include "algorithm"
using namespace std;
int n, m;
#define MINLEN 42.5
struct Pointer {
    int x;
    int y;
}point[101];
bool answer = false; /* 记录007能否安全逃生~~ */
bool visited[101] = { false }; /* 判断当前点是否被访问过 */
int path[101] = {-1}; /* 记录跳跃过程中踩过的鳄鱼 */
bool isSave(int x) { /* 判断从当前点能否跳到岸上 */
    if ((point[x].x - m <= -50) || (point[x].x + m >= 50) || (point[x].y - m <= -50) || (point[x].y + m >= 50))
        return true;
    return false;
}

bool jump(int x, int y) { /* 判断2个点距离是否在跳跃能力内 */
    int p1 = pow(point[x].x - point[y].x, 2);
    int p2 = pow(point[x].y - point[y].y, 2);
    int r = m * m;
    if (p1 + p2 <= r)
        return true;
    return false;
}

int firstJump(int x) {  /* 当007处于孤岛时 第一次可以选择跳的鳄鱼 因为第一次判断能否跳跃的计算方法与后面dfs不相同 所以要单独写 */
    int p1 = pow(point[x].x, 2);
    int p2 = pow(point[x].y, 2);
    int r = (m + 7.5) * (m + 7.5);
    if (p1 + p2 <= r) {
        return p1+p2;
    }
    return 0;
}
bool cmp(int a,int b) {
    return firstJump(a) < firstJump(b);
}
void bfs() { /* 用bfs来判断最少要踩几个小鳄鱼才能上岸 */
    int b[101];
    queue<int>q;
    /* 将第一步能踩到的鳄鱼按距离从小到大的顺序进队列~ 因为输出结果要保证在踩的鳄鱼数量相等的情况下 输出第一步距离最短的~~*/
    for (int i = 0; i < n; i++) {
        b[i] = i;
    }
    sort(b, b + n, cmp); /* 按照第一步的距离排序~~~ */
    int last;
    for (int i = 0; i < n; i++) {
        if (firstJump(b[i])) { /* 能跳上去！ */
            q.push(b[i]);
            visited[b[i]] = true; /* 指向当前层数最后一个数~ */
            last = b[i];
        }
    }
    int step = 2;  /* 记录最少要跳跃的次数 */
    int tail;
    while (!q.empty()) {
        int p = q.front();
        q.pop();
        if (isSave(p)) {
            int k = 1;
            stack<int> s;
            cout << step << endl;
            while (k < step) {
                //cout << point[p].x << " " << point[p].y << endl;
                s.push(p);
                p = path[p];
                k++;
            }
            while (!s.empty()) {
                p = s.top();
                s.pop();
                cout << point[p].x << " " << point[p].y << endl;
            }
            return;
        }
        for (int i = 0; i < n; i++) {
            if (!visited[i] && jump(p, i)) { /* 没踩过并且能跳到 */
                q.push(i);
                path[i] = p; /* 记得当前进队节点的父节点~ */
                visited[i] = true;
                tail = i; /* 指向下一层的最后一个元素 */
            }
        }
        if (last == p) { /* 即将进入下一层~ */
            step += 1;
            last = tail;
        }
    }
    if (q.empty()) { /* 如果队列为空  说明没跳出去啊~ */
        cout << "0" << endl;
    }
}
int main() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> point[i].x >> point[i].y;
    }
    if (m >= MINLEN) { /* 可以直接从孤岛上提到岸上 直接输出 */
        cout << "1" << endl;
        return 0;
    }
    bfs();
    return 0;
}