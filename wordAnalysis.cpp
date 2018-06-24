//
// Created by aSUSS on 2018/6/21.
//

#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include "stack"
#include "iostream"

using namespace std;
//==============================一些符号初始化======================================================
int errorLine = 1;
int i, row = 0, line = 0;
char a[1000];  //程序
int number[1000][100];  //常数表
char mark[100][5];   //标识符表

//词法分析器函数
int wordAnalysis(FILE *fp, FILE *fp2, FILE *fp3) {
//==============================基本字和标识符识别====================================================
    if ((a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= 'a' && a[i] <= 'z')) {
        char word[10];//读入一个单词
        char pro[100][100] = {"select", "delete", "update", "insert", "from", "into", "where", "values", "set",
                              "EOF", "EOLN"}; //基本字表

        int n = 0;
        word[n++] = a[i++];
        while ((a[i] >= 'A' && a[i] <= 'Z') || (a[i] >= '0' && a[i] <= '9') || (a[i] >= 'a' && a[i] <= 'z')) {
            word[n++] = a[i++];
        }
        word[n] = '\0';
        i--;

        //判断标识符是否是保留字
        for (n = 0; n < 100; n++) {
            if (strcmp(word, pro[n]) == 0) {
                if (strcmp(word, "EOF") == 0) {
                    return 4;
                }
                if (strcmp(word, "EOLN") == 0) {
                    return 5;
                }
                //printf("%s\t(%d,-) \n", pro[n], n + 1);
                fprintf(fp, "%s\t(%d,-) \n", pro[n], n + 1);
                return 3;
            }
        }
        //判断标识符长度是否超出规定，规定最大长度是10
        if (strlen(word) > 10) {
            //printf("%s\tERROR\n", word);
            fprintf(fp2, "在第%d行标识符过长", errorLine);
            return 6;
        }
        //判断该标识符是否存在标识符表中
        int m = 0;
        if (line != 0) {
            int q = 0;
            while (q < line) {
                if (strcmp(word, mark[q++]) == 0) {
                    //printf("%s\t(10,%d) \n", word, q);
                    fprintf(fp, "%s\t(10,%d) \n", word, q);
                    return 3;
                }
            }

        }

        //将该标识符保存到标识符表中
        strcpy(mark[line], word);
        //printf("%s\t(10, %d) \n", word, line + 1);
        fprintf(fp, "%s\t(10, %d) \n", word, line + 1);
        line++;
        return 3;
    }
//==========================================常数分析==================================================================================
    else if (a[i] >= '0' && a[i] <= '9') {
        char x[100];
        int n = 0, sum;
        x[n++] = a[i++];
        //判断字符是否是0~9
        while (a[i] >= '0' && a[i] <= '9') {
            x[n++] = a[i++];
        }


        if ((a[i] >= 'a' && a[i] <= 'z') || (a[i] >= 'A' && a[i] <= 'Z')) {
            while (a[i] != ' ') {
                x[n++] = a[i++];
            }
            //x[n - 1] = ' ';
            //printf("在第%d行，%s不符合变量规范\n", errorLine, x);
            fprintf(fp2, "在第%d行，%s不符合变量规范\n", errorLine, x);
            return 6;
        }


        x[n] = '\0';
        i--;
        int num = atoi(x); //将字符串转换成int型

        //判断该常数是否存在于常数表中
        if (row != 0) {
            int y;
            for (y = 0; y < 1000; y++) {
                int w = number[y][0];
                sum = 0;
                int d;
                for (d = 1; d <= number[y][0]; d++) {
                    w = w - 1;
                    sum = sum + number[y][d] * pow(2, w);
                }
                if (num == sum) {
                    //printf("%d\t(11,%d)\n", num, y + 1);
                    fprintf(fp, "%d\t(11,%d)\n", num, y + 1);
                    return 3;
                }
            }
        }
        int z = num, c = num;
        int m = 0;
        do        //计算是几位二进制数
        {
            z = z / 2;
            m++;
        } while (z != 0);

        for (n = m; n > 0; n--)  //将二进制保存于常数表中
        {
            number[row][n] = c % 2;
            c = c / 2;
        }
        number[row][0] = m;

        int line = row;
        //printf("%d\t(11,%d)\n", num, line + 1);
        fprintf(fp3, "%d:%d\n", line + 1, num);
        fprintf(fp, "%d\t(11,%d)\n", num, line + 1);
        row++;

        return 3;
    }
//==================================特殊符号分析=====================================
    else
        switch (a[i]) {
            case ' ':
            case '\n':
                return -1;
            case '#':
                return 0;
            case '=':
                //printf("=\t(12,-)\n");
                fprintf(fp, "=\t(12,-)\n");
                return 3;
            case '<':
                i++;
                if (a[i] == '=') {
                    //printf("<= \t(14,-)\n");
                    fprintf(fp, "<= \t(14,-)\n");
                    return 3;
                } else if (a[i] == '>') {
                    //printf("<>\t(13,-)\n");
                    fprintf(fp, "<>\t(13,-)\n");
                    return 3;
                } else {
                    i--;
                    //printf("<\t(15,-)\n");
                    fprintf(fp, "<\t(15,-)\n");
                    return 3;
                }
            case '>':
                i++;
                if (a[i] == '=') {
                    //printf(">=\t(16,-)\n");
                    fprintf(fp, ">=\t(16,-)\n");
                    return 3;
                } else {
                    i--;
                    //printf(">\t(17,-)\n");
                    fprintf(fp, ">\t(17,-)\n");
                    return 3;
                }

            case '-':
                //printf("-\t(18,-)\n");
                fprintf(fp, "-\t(18,-)\n");
                return 3;
            case '*':
                //printf("*\t(19,-)\n");
                fprintf(fp, "*\t(19,-)\n");
                return 3;
            case ':':
                i++;
                if (a[i] == '=') {
                    //printf(":=\t(20,-)\n");
                    fprintf(fp, ":=\t(20,-)\n");
                    return 3;
                } else {
                    i--;
                    //printf(":\t(24,-)\n");
                    fprintf(fp, ":\t(24,-)\n");
                    return 3;
                }

            case ';':
                //printf(";\t(23,-)\n");
                fprintf(fp, ";\t(23,-)\n");
                return 3;
            case '(':
                //printf("(\t(21,-)\n");
                fprintf(fp, "(\t(21,-)\n");
                return 3;
            case ')':
                //printf(")\t(22,-)\n");
                fprintf(fp, ")\t(22,-)\n");
                return 3;
            case ',':
                //printf(",\t(25,-)\n");
                fprintf(fp, ",\t(25,-)\n");
                return 3;
            default:
                //printf("在第%d行有未识别单词", errorLine);
                fprintf(fp2, "在第%d行有未识别单词", errorLine);
                return 3;
        }
}

//==================================主函数==================================
int wordAnalysisMain() {

    int l = 0;
    int m;
    i = 0;
    FILE *fp, *fp2, *fp3, *fp4;
    fp = fopen("E:\\index.txt", "r");
    fp2 = fopen("E:\\output.dyd", "w");
    fp3 = fopen("E:\\out.error", "w");
    fp4 = fopen("E:\\constant.txt", "w");
    if (fp == NULL) {
        printf("Can't open file!\n");
        exit(0);
    }
    if (fp2 == NULL) {
        printf("Can't open file!\n");
        exit(0);
    }

    while (!feof(fp)) {
        a[l++] = fgetc(fp);
    }
    a[l] = '#';
    do {
        m = wordAnalysis(fp2, fp3, fp4);

        switch (m) {
            case -1:
                i++;
                break;
            case 0:
                i++;
                break;
            case 3:
                i++;
                break;
            case 4:
                fclose(fp);
                fclose(fp2);
                fclose(fp3);
                fclose(fp4);
                return 0;
            case 5:
                i++;
                errorLine++;
                break;
            case 6:
                fclose(fp);
                fclose(fp2);
                fclose(fp3);
                fclose(fp4);
                return 1;
        }
    } while (m != 0);
    return 0;
}