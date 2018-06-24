//
// Created by aSUSS on 2018/6/23.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;


int inpro(char pro[100][100], char *word) {
    for (int i = 0; i < 100; ++i) {
        if (strcmp(word, pro[i]) == 0) {
            //printf("find");
            return 0;
        }
    }
    return 1;
}

//int main() {
//    char pro[100][100] = {"int", "char", "string", "boolean"};
//    char word[100] = "char";
//    printf("%d", inpro(pro, word));
//}

int createTableMain() {

    char szTest[1000] = {0};
    int count = 0;
    char str[30][30] = {'\0'};
    char pro[100][100] = {"int", "char", "string", "boolean"};

    FILE *fp = fopen("E:\\output.dyd", "r");
    FILE *fp2 = fopen("E:\\finishCompile.txt", "w");
    if (NULL == fp) {
        printf("failed to open dos.txt\n");
        return 1;
    }
    if (NULL == fp2) {
        printf("failed to open dos.txt\n");
        return 1;
    }
    while (!feof(fp)) {

        char word[10] = {'\0'};
        memset(szTest, 0, sizeof(szTest));
        fgets(szTest, sizeof(szTest), fp); // 包含了换行符
        for (int i = 0; szTest[i] != '\t'; ++i) {
            if (szTest[i] == 0) {
                break;
            }
            word[i] = szTest[i];
            str[count][i] = szTest[i];
            str[count][i + 1] = '\0';
        }


        //printf("xx=%s\n", str[count]);

        count++;
    }


    if (!strcmp(str[0], "create")) {
        fprintf(fp2, "create ");
        if (!strcmp(str[2], "(")) {
            fprintf(fp2, "%s ", str[1]);
            if (inpro(pro, str[4])) {
                fclose(fp2);
                fp2 = fopen("E:\\finishCompile.txt", "w");
                fclose(fp2);
                return 1;
            } else {
                fprintf(fp2, "%s(%s) ", str[3], str[4]);
            }
            int num = 0;
            for (int i = 5; strcmp(str[i], ")") != 0; num = ++i) {
                if (i >= 100) {
                    fclose(fp2);
                    fp2 = fopen("E:\\finishCompile.txt", "w");
                    fclose(fp2);
                    return 1;
                }
                if ((!strcmp(str[i], ",")) && (!inpro(pro, str[i + 2]))) {
                    fprintf(fp2, "%s(%s) ", str[i + 1], str[i + 2]);
                    i = i + 2;
                } else {
                    fclose(fp2);
                    fp2 = fopen("E:\\finishCompile.txt", "w");
                    fclose(fp2);
                    return 1;
                }
            }
            if (strcmp(str[num + 1], ";") != 0) {
                fclose(fp2);
                fp2 = fopen("E:\\finishCompile.txt", "w");
                fclose(fp2);
                return 1;
            }
            if (str[num + 2][0] != '\0') {
                fclose(fp2);
                fp2 = fopen("E:\\finishCompile.txt", "w");
                fclose(fp2);
                return 1;
            }


        } else {
            fclose(fp2);
            fp2 = fopen("E:\\finishCompile.txt", "w");
            fclose(fp2);
            return 1;
        }
        fclose(fp);
        fclose(fp2);
        return 0;
    } else {
        fclose(fp2);
        fp2 = fopen("E:\\finishCompile.txt", "w");
        fclose(fp2);
        return 1;
    }

}