//
// Created by aSUSS on 2018/6/21.
//
#include "wordAnalysis.h"
#include "grammarAnalysis.h"
#include "semanticAnalysis.h"
#include "createTable.h"
int compile() {
    int a = wordAnalysisMain();
    if (a != 0) {
        return 1;
    }
    int createTable=createTableMain();
    if(createTable!=0) {
        int b = grammarAnalysisMain();
        if (b != 0) {
            return 2;
        }
        int c = semanticAnalysisMain();
        if (c != 0) {
            return 3;
        }
    }
    return 0;

}