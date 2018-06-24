//
// Created by aSUSS on 2018/6/23.
//

#include <cstring>
#include "stdio.h"
#include "stdlib.h"



int inputSQLMain(){
    FILE *fp = fopen("E:\\index.txt", "w+");

    char input[1000]={0};
    char in[100]={0};
    printf("«Î ‰»ÎSQL”Ôæ‰£∫");
    gets(in);
    gets(input);
    fprintf(fp,"%s EOF",input);
    fclose(fp);
    return 0;
}

