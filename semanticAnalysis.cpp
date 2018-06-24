//
// Created by aSUSS on 2018/6/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;


int semanticAnalysisMain() {
    char szTest[1000] = {0};
    char szTest2[30] = {0};
    int count = 0;
    char str[30][30];
    char str1[30][30]={0};
    int countFinish=0;

    FILE *fp = fopen("E:\\output.dyd", "r");

    FILE *fp3 = fopen("E:\\finishCompile.txt", "r");
    if (NULL == fp) {
        printf("failed to open dos.txt\n");
        return 1;
    }

    if (NULL == fp3) {
        printf("failed to open dos.txt\n");
        return 1;
    }
//    while (!feof(fp3)) {
//        fgets(szTest2, sizeof(szTest2), fp3);
//        //str1[countFinish]=szTest2;
//        for (int i = 0; szTest2[i]!=0 ; ++i) {
//            str1[countFinish][i]=szTest2[i];
//        }
//        //printf("%s\n", str1[countFinish]);
//        countFinish++;
//    }
//    fclose(fp3);

    //===
    FILE *fp2 = fopen("E:\\finishCompile.txt", "w");
    if (NULL == fp2) {
        printf("failed to open dos.txt\n");
        return 1;
    }
//    for (int k = 0; k<countFinish ; ++k) {
//        fprintf(fp2,str1[k]);
//    }
//    fprintf(fp2,"\n");

    //===
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


        //printf("xx=%s\n",word);
        //str[count]=word;
        count++;
    }
    //printf("%s",str[5]);
    if (!strcmp(str[0], "insert")) {
        fprintf(fp2, "insert ");
    } else if (!strcmp(str[0], "update")) {
        fprintf(fp2, "update ");
    } else if (!strcmp(str[0], "delete")) {
        fprintf(fp2, "delete ");
    } else if (!strcmp(str[0], "select")) {
        fprintf(fp2, "select ");
    }
    int data[20] = {0};
    int dataNum = 0;
    for (int j = 0; strcmp(str[j], ";"); ++j) {
        if (!strcmp(str[0], "insert")) {

            //printf("%s\n",str[j]);
            if (!strcmp(str[j], "into")) {
                //("%s ", str[j + 1]);
                fprintf(fp2, "%s ", str[j + 1]);
                //printf("find");
            }

            if (str[j][0] >= '0' && str[j][0] <= '9') {
                data[dataNum] = atoi(str[j]);
                fprintf(fp2, "%d ", data[dataNum]);
                //printf("%d ", data[dataNum]);
                dataNum++;
            }
        } else if (!strcmp(str[0], "select")) {
            //fprintf(fp2, "select ");
            if (!strcmp(str[j], "from")) {
                //printf("%s\n", str[j + 1]);
                fprintf(fp2, "%s ", str[j + 1]);
                //printf("find");
            }
            if (str[j][0] >= '0' && str[j][0] <= '9') {

                fprintf(fp2, "%d ", atoi(str[j]));
                //printf("%d ", atoi(str[j]));

            }
        } else if (!strcmp(str[0], "delete")) {
            //fprintf(fp2, "delete ");
            if (!strcmp(str[j], "from")) {
                //printf("%s\n", str[j + 1]);
                fprintf(fp2, "%s ", str[j + 1]);
                //printf("find");
            }
            if (str[j][0] >= '0' && str[j][0] <= '9') {

                fprintf(fp2, "%d ", atoi(str[j]));
                //printf("%d ", atoi(str[j]));

            }
        } else if (!strcmp(str[0], "update")) {
            //fprintf(fp2, "update ");
            if (!strcmp(str[j], "update")) {
                //printf("%s\n", str[j + 1]);
                fprintf(fp2, "%s ", str[j + 1]);
                //printf("find");
            }
            if (str[j][0] >= '0' && str[j][0] <= '9') {

                fprintf(fp2, "%d ", atoi(str[j]));
                //printf("%d ", atoi(str[j]));

            }
        }
    }

    fclose(fp);
    fclose(fp2);


    return 0;
}