//
//  main.cpp
//  Saving007
//
//  Created by 何宏炜 on 16/6/17.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
using namespace std;

#define MaxSize 100
struct crocodiles{
    float x;
    float y;
};
struct crocodiles cro[MaxSize];

int dis;
int num;
bool Visited[MaxSize] = {0};

bool Jump(int x1, int y1, int x2, int y2){
    if ((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) <= dis * dis) {
        return 1;
    }
    return 0;
}

bool isSafe(int v){
    if ( (cro[v].x + dis >= 50) || (cro[v].x + dis <= -50) ||
        (cro[v].y + dis >= 50) || (cro[v].y + dis <= -50)) {
        return 1;
    }
    return 0;
}

bool DFS(int v){
    bool answer = 0;
    Visited[v] = 1;
    if (isSafe(v)) {
        answer = 1;
    }
    else{
        for (int i=0; i < num; ++i) {
            if (!Visited[i] && Jump(cro[v].x, cro[v].y, cro[i].x, cro[i].y)) {
                answer = DFS(i);
                if (answer == 1) {
                    break;
                }
            }
        }
    }
    return answer;
}

bool firstJump(int x, int y){
    if (x*x + y*y <= (7.5+dis)*(7.5+dis)) {
        return 1;
    }
    return 0;
}

void save007(){
    bool answer = 0;
    for (int i=0; i < num; ++i) {
        if ( !Visited[i] && firstJump(cro[i].x, cro[i].y)) {
            answer = DFS(i);
            if (answer == 1) {
                break;
            }
        }
    }
    if (answer == 1) {
        cout << "Yes" << endl;
    }
    else{
        cout << "No" << endl;
    }
}

int main() {
    cin >> num >> dis;
    for (int i=0; i < num; ++i) {
        cin >> cro[i].x >> cro[i].y;
    }
    save007();
    return 0;
}
