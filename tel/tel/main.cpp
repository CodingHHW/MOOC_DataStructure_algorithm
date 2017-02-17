//
//  main.cpp
//  tel
//
//  Created by 何宏炜 on 16/6/27.
//  Copyright © 2016年 何宏炜. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int main() {
    int arr[] = {8,2,1,0,3};
    int index[] = {2,0,3,2,4,0,1,3,2,3,3};
    stringstream tel;
    string Telephon = "";
    for (auto &i : index) {
        tel << arr[i];
        Telephon += tel.str();
        tel.str("");
    }
    cout << Telephon << endl;
    return 0;
}
