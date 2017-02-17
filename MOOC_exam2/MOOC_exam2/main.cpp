//
//  main.cpp
//  MOOC_exam2
/* 题目内容：
输入若干学生的成绩，统计各班的成绩的平均值，并按班级名称的机内码从小到大排序输出。
学生成绩信息包括：班级，学号和成绩。班级名称是"000"'时表示成绩输入结束。
班级名称不超过20字符，学号不超过10个字符，成绩为整数，平均成绩为双精度实数，保留三位小数。班级数不超过10个，总人数不超过100个。

输入格式:
若干行，每行信息包括班级，学号和成绩，用空格隔开，
最后一行为：000 000 000

输出格式：
若干行，每行信息包括：班级和平均成绩，中间用一个空格隔开。行数由输入中的班级数确定。

输入样例：
航天  001 80
信计  001 90
航天  002 70
航天  003 80
信计  002 91
000 000 000

输出样例：
航天 76.667
信计 90.500
*/
//  Created by 何宏炜 on 16/6/1.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;

class tongji{
    string banji;
    string xuehao;
    double chengji;
public:
    void shuru(){
        cin >> banji >> xuehao >> chengji;
    }
    string Getbanji(){
        return banji;
    }
    string Getxuehao(){
        return xuehao;
    }
    double Getchengji(){
        return chengji;
    }
};

bool compare(tongji A,tongji B){
    return A.Getbanji()>B.Getbanji();
}

int main(int argc, const char * argv[]) {
    
    vector<tongji> T;
    for (int i=0; ; ++i) {
        tongji t;
        t.shuru();
        if (t.Getbanji()=="000") {
            break;
        }
        else{
            T.push_back(t);
        }
    }
    
    sort(T.begin(), T.end(), compare);
    
    double CJ=0;int number=0;
    for (auto it=T.begin(); it != T.end(); ++it) {
        if (it->Getbanji() == (it+1)->Getbanji()) {
            CJ += it->Getchengji();
            number++;
        }
        else{
            CJ += it->Getchengji();
            number++;
            cout << it->Getbanji() << ' ' ;
            printf("%.3f",CJ/number);
            cout << endl;
            CJ = number = 0;
        }
    }
    
    return 0;
}
