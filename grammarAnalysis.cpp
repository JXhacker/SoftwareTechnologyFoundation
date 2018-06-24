//
// Created by aSUSS on 2018/6/21.
//
#include<iostream>
#include <cstring>
#include"stack"

using namespace std;
//预测分析表
int forecastTable[7][26][30] = {0};
//分析栈
stack<int> stk;

void initStack() {
    stk.push(0);
    stk.push(100);//100当作A 101：A1 102：A2 103：A3 104：A4
}

//初始化预测表
void initForecastTable() {


    for (int i = 0; i < 9; ++i) {
        //int x[] = {1, 19, 5, 10, 7, 10, 12, 11, 23};//select * from table where id = 1;
        int x[30] = {101};
        forecastTable[0][1][i] = x[i];
    }
    for (int i = 0; i < 8; ++i) {
        //int x[] = {2, 5, 10, 7, 10, 12, 11, 23};//delete from table where id = 1;
        int x[30] = {104};
        forecastTable[0][2][i] = x[i];
    }
    for (int i = 0; i < 11; ++i) {
        //int x[] = {3, 10, 9, 10, 12, 11, 7, 10, 12, 11, 23};//update table set id=1 where id=2;
        int x[30] = {103};
        forecastTable[0][3][i] = x[i];
    }
    for (int i = 0; i < 22; ++i) {
        //int x[] = {4, 6, 10, 8, 21, 11, 25, 11, 25, 11, 25, 11, 25, 11, 25, 11, 25, 11, 25, 11, 22, 23};
        //insert into table values(1,1,1,1,1,1,1,1);
        int x[30] = {102};
        forecastTable[0][4][i] = x[i];
    }
    for (int i = 0; i < 9; ++i) {
        int x[30] = {1, 19, 5, 10, 7, 10, 12, 11, 23};
        forecastTable[1][1][i] = x[i];
    }
    for (int i = 0; i < 22; ++i) {

        int x[30] = {4, 6, 10, 8, 21, 11, 25, 11, 25, 11, 25, 11, 25, 11, 25, 11, 25, 11, 25, 11, 22, 23};
        forecastTable[2][4][i] = x[i];
    }
    for (int i = 0; i < 11; ++i) {
        int x[30] = {3, 10, 9, 10, 12, 11, 7, 10, 12, 11, 23};
        forecastTable[3][3][i] = x[i];
    }
    for (int i = 0; i < 8; ++i) {
        int x[30] = {2, 5, 10, 7, 10, 12, 11, 23};
        forecastTable[4][2][i] = x[i];
    }
}

int analysis(int *input) {
    int countInput = 0;
    int length = 0;
    for (int i = 0; input[i] != 0; ++i) {
        length++;
    }
    while (stk.top() != 0) {
        if (stk.top() >= 100) {
            if (forecastTable[stk.top() - 100][input[countInput]][0] == 0) {
                return 1;
            } else {
                int tableNum = 0;
                while (forecastTable[stk.top() - 100][input[countInput]][tableNum] != 0) {
                    //printf("%d,%d\n",stk.top() - 100,input[countInput]);
                    tableNum++;
                }
                //printf("\n");
                int x = stk.top();
                stk.pop();
                while (tableNum != 0) {
                    stk.push(forecastTable[x - 100][input[countInput]][tableNum - 1]);
                    tableNum--;
                }
            }
        } else {
            if (stk.top() == input[countInput]) {
                stk.pop();
                countInput++;
            } else {
                return 1;
            }
        }
    }
    return 0;
}

int grammarAnalysisMain() {

    initForecastTable();
    initStack();

    int input[30] = {0};
    int inputI = 0;
    char szTest[1000] = {0};

    FILE *fp = fopen("E:\\output.dyd", "r");
    if (NULL == fp) {
        printf("failed to open dos.txt\n");
        return 1;
    }
    while (!feof(fp)) {
        char shuzi[4] = {'\0'};
        int location = 0;
        memset(szTest, 0, sizeof(szTest));
        fgets(szTest, sizeof(szTest), fp); // 包含了换行符
        for (int i = 1; szTest[i] != 0; ++i) {
            if (szTest[i] == '(') {
                i++;
                while (szTest[i] != ',') {
                    shuzi[location] = szTest[i];
                    i++;
                    location++;
                }
                shuzi[location] = '\0';
                input[inputI] = atoi(shuzi);
                inputI++;
            }
        }
    }
//    for (int j = 0; input[j] != 0; ++j) {
//        printf("%d ", input[j]);
//    }

    fclose(fp);

    int a = analysis(input);
    return a;

}
