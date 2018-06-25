//
// Created by aSUSS on 2018/6/10.
//

//
// Created by aSUSS on 2018/4/19.
//
#include <iostream>

using namespace std;

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>
#include "inputSQL.h"
#include "compile.h"

//===========================================================================================================
//注意确定GoodsInfo[]大小
typedef struct GoodsInfo1 {
    int id;//产品id
    int deliveryOrder;//产品发货顺序
    int vip;//vip等级
    int value;//贵重程度
    int emergency;//是否加急1.是 0不是
    int transpotation;//运输方式 1火车，2动车 3.空运
    int weight;//重量，单位千克
    int volumn;//体积，单位m^3
    int from;//起点
    int to;//终点
} GoodsInfo;

//初始化商品信息
void initGoods(GoodsInfo *goodsInfo, int num) {
    cout << "产品id " << "vip等级 " << "贵重程度 " << "是否加急 " << "产品重量 " << "产品体积 " << "产品出发地（填编号） " << "产品目的地（填编号）"
         << endl;
    for (int i = 0; i < num; ++i) {
        cin >> goodsInfo[i].id >> goodsInfo[i].vip >> goodsInfo[i].value >> goodsInfo[i].emergency
            >> goodsInfo[i].weight
            >> goodsInfo[i].volumn >> goodsInfo[i].from >> goodsInfo[i].to;
        if (goodsInfo[i].emergency == 1) {
            goodsInfo[i].transpotation = 3;
        } else if (goodsInfo[i].value > 1) {
            goodsInfo[i].transpotation = 2;
        } else {
            goodsInfo[i].transpotation = 1;
        }
    }
}

void initGoods2(GoodsInfo *goodsInfo) {
    char buf[1024];
    FILE *fp;
    int len;
    if ((fp = fopen("E:\\goodsInfo.txt", "r")) == NULL) {
        perror("fail to read");
        exit(1);
    }

    int num = 0;
    while (fgets(buf, 1024, fp) != NULL) {
        len = strlen(buf);
        buf[len - 1] = '\0';
        char *result = NULL;
        result = strtok(buf, " ");
        goodsInfo[num].id = atoi(result);
        //printf("%d ", atoi(result));
        result = strtok(NULL, " ");
        goodsInfo[num].vip = atoi(result);
        //printf("%d ", atoi(result));
        result = strtok(NULL, " ");
        goodsInfo[num].value = atoi(result);
        //printf("%d ", atoi(result));
        result = strtok(NULL, " ");
        goodsInfo[num].emergency = atoi(result);
        //printf("%d ", atoi(result));
        result = strtok(NULL, " ");
        goodsInfo[num].weight = atoi(result);
        //printf("%d ", atoi(result));
        result = strtok(NULL, " ");
        goodsInfo[num].volumn = atoi(result);
        //printf("%d ", atoi(result));
        result = strtok(NULL, " ");
        goodsInfo[num].from = atoi(result);
        //printf("%d ", atoi(result));
        result = strtok(NULL, " ");
        goodsInfo[num].to = atoi(result);
        //printf("%d\n", atoi(result));


        if (goodsInfo[num].emergency == 1) {
            goodsInfo[num].transpotation = 3;
        } else if (goodsInfo[num].value > 1) {
            goodsInfo[num].transpotation = 2;
        } else {
            goodsInfo[num].transpotation = 1;
        }
        num++;
    }
}

void printGoodsInfo(GoodsInfo *goodsInfo, int num) {

    cout << "产品id " << "vip等级 " << "贵重程度 " << "是否加急 " << "产品重量 " << "产品体积 " << "发货顺序" << "运输方式" << "产品出发地（填编号） "
         << "产品目的地（填编号）"
         << endl;
    for (int i = 0; i < num; ++i) {
        printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", goodsInfo[i].id, goodsInfo[i].vip, goodsInfo[i].value,
               goodsInfo[i].emergency,
               goodsInfo[i].weight, goodsInfo[i].volumn, goodsInfo[i].deliveryOrder, goodsInfo[i].transpotation,
               goodsInfo[i].from, goodsInfo[i].to);
    }
}

//排序并且初始化货物发货顺序,从零开始
void bubbleSort(GoodsInfo *goodsInfo, int num) {
    int i, j, temp;
    int store[20];
    for (int k = 0; k < num; ++k) {
        store[k] = goodsInfo[k].vip * 3 + goodsInfo[k].value * 4;
    }
    for (i = 0; i < num; ++i) {
        for (j = num - 1; j > i; --j) {
            if (store[j] > store[j - 1]) {
                temp = store[j];
                store[j] = store[j - 1];
                store[j - 1] = temp;
            }
        }
    }
    int vip[20];
    for (int l = 0; l < num; ++l) {
        vip[l] = goodsInfo[l].vip * 3 + goodsInfo[l].value * 4;
    }
    for (int l = 0; l < num; ++l) {
        int find = 0;
        for (int k = 0; k < num; ++k) {
            if (vip[k] == store[l]) {
                //store[l] = 0;
                vip[k] = 1000;
                find = k;
                break;
            }
        }
        goodsInfo[find].deliveryOrder = l;
    }
}

//=============================================================================================================
//将商品存入树中
//将此树转化为二叉树
typedef struct node1 {
    GoodsInfo goodsInfo;//数据区存物品
    struct node1 *left, *right;
} node;

//往二叉树添加数据
node *initTree(GoodsInfo *goodsInfo, int num) {
    node *head = (node *) malloc(sizeof(node));
    node *transPlanOne = (node *) malloc(sizeof(node));
    transPlanOne->goodsInfo = goodsInfo[0];
    node *transPlanTwo = (node *) malloc(sizeof(node));
    transPlanTwo->goodsInfo = goodsInfo[0];
    node *transPlanThree = (node *) malloc(sizeof(node));
    transPlanThree->goodsInfo = goodsInfo[0];
    head->left = transPlanOne;
    transPlanOne->right = transPlanTwo;
    transPlanTwo->right = transPlanThree;
    node *nodeOne = transPlanOne;
    int planOne = 0;
    node *nodeTwo = transPlanTwo;
    int planTwo = 0;
    node *nodeThree = transPlanThree;
    int planThree = 0;
    for (int i = 0; i < num; ++i) {
        if (goodsInfo[i].transpotation == 1) {
            if (planOne == 0) {
                nodeOne->left = (node *) malloc(sizeof(node));
                nodeOne = nodeOne->left;
                nodeOne->goodsInfo = goodsInfo[i];
                planOne++;
            } else {
                nodeOne->right = (node *) malloc(sizeof(node));
                nodeOne = nodeOne->right;
                nodeOne->goodsInfo = goodsInfo[i];
            }
        }
        if (goodsInfo[i].transpotation == 2) {
            if (planTwo == 0) {
                nodeTwo->left = (node *) malloc(sizeof(node));
                nodeTwo = nodeTwo->left;
                nodeTwo->goodsInfo = goodsInfo[i];
                planTwo++;
            } else {
                nodeTwo->right = (node *) malloc(sizeof(node));
                nodeTwo = nodeTwo->right;
                nodeTwo->goodsInfo = goodsInfo[i];
            }
        }
        if (goodsInfo[i].transpotation == 3) {
            if (planThree == 0) {
                nodeThree->left = (node *) malloc(sizeof(node));
                nodeThree = nodeThree->left;
                nodeThree->goodsInfo = goodsInfo[i];
                planThree++;
            } else {
                nodeThree->right = (node *) malloc(sizeof(node));
                nodeThree = nodeThree->right;
                nodeThree->goodsInfo = goodsInfo[i];
            }
        }
    }
    return head;
}





//=============================================================================================================
//Djstra算法求最短路径
#define MaxSize 20
#define INFINITY 65535
typedef char VertexType;
//定义图 的邻接矩阵表示法结构
typedef struct Graph {
    //定义定点个数
    VertexType ver[MaxSize + 1];
    //定义边大小
    int edg[MaxSize][MaxSize];
} Graph;

//邻接矩阵法图的生成函数
void CreateGraph(Graph *g) {
    int i = 0;
    int j = 0;
    int VertexNum;
    VertexType Ver;
    printf("请输入图的顶点:\n");
    while ('\n' != (Ver = getchar()))
        g->ver[i++] = Ver;
    g->ver[i] = '\0';
    VertexNum = strlen(g->ver);
    printf("请输入相应的的邻接矩阵:\n");
    for (i = 0; i < VertexNum; i++)
        for (j = 0; j < VertexNum; j++)
            scanf("%d", &g->edg[i][j]);
}

void CreateGraph2(Graph *g) {
    char buf[1024];
    FILE *fp;
    int len;
    if ((fp = fopen("E:\\graph.txt", "r")) == NULL) {
        perror("fail to read");
        exit(1);
    }
    int lin = 0;
    while (fgets(buf, 1024, fp) != NULL) {
        if (lin != 0) {
            len = strlen(buf);
            buf[len - 1] = '\0';
            char *result = NULL;
            result = strtok(buf, " ");
            g->edg[lin - 1][0] = atoi(result);
            //printf("%d ", g->edg[lin - 1][0]);
            for (int j = 0; j < 5; ++j) {
                result = strtok(NULL, " ");
                g->edg[lin - 1][j + 1] = atoi(result);
                //printf("%d ", g->edg[lin - 1][j + 1]);
            }
            //printf("\n");
        } else {
            for (int i = 0; i < 6; ++i) {
                //printf("%c", buf[i]);
                g->ver[i] = buf[i];
                g->ver[i+1] = '\0';
            }
            //printf("\n");
        }
        lin++;
    }
}


//打印图的结点标识符和邻接矩阵
void PrintGraph(Graph g) {
    int i, j;
    int VertexNum = strlen(g.ver);
    printf("图的顶点为:\n");
    for (i = 0; i < VertexNum; i++)
        printf("%c ", g.ver[i]);
    printf("\n");
    printf("图的邻接矩阵为:\n");
    for (i = 0; i < VertexNum; i++) {
        for (j = 0; j < VertexNum; j++)
            printf("%d ", g.edg[i][j]);
        printf("\n");
    }
}

//求图的顶点数
int CalVerNum(Graph g) {
    return strlen(g.ver);
}

//将不邻接的顶点之间的权值设置为INFINITY，当成无穷大就好
void SetWeight(Graph *g) {
    for (int i = 0; i < CalVerNum(*g); i++)
        for (int j = 0; j < CalVerNum(*g); j++)
            if (0 == g->edg[i][j])
                g->edg[i][j] = INFINITY;
}

//Dijkstra求最短路径函数
void Dijkstra(Graph g, int from, int to) {
    int VertexNum = CalVerNum(g);
    int j;
    int mini;
    int index = 0;
    int *used = (int *) malloc(sizeof(int) * VertexNum);
    int *distance = (int *) malloc(sizeof(int) * VertexNum);
    int *parent = (int *) malloc(sizeof(int) * VertexNum);
    int *last = (int *) malloc(sizeof(int) * VertexNum);

    SetWeight(&g);                    //设置权值

    //distance[i]表示与编号为from的距离
    for (int i = 0; i < VertexNum; i++) {
        used[i] = 0;
        distance[i] = g.edg[from][i];   //初始化为与编号为from的顶点的距离
        last[i] = 0;
    }

    used[from] = 1;
    parent[index++] = from;

    for (int i = 0; i < VertexNum - 1; i++) {
        j = from;
        mini = INFINITY;

        //mini存储与编号为0点最短距离
        //j储存相应与0距离最短相应的节点
        for (int k = 0; k < VertexNum; k++)
            if ((0 == used[k]) && (distance[k] < mini)) {
                mini = distance[k];
                j = k;          //j为刚刚找到的V-U中到源点路径最短的顶点
            }

        //将这个找到的节点的标志位定为1
        used[j] = 1;

        //算法精髓，新节点加入
        for (int k = 0; k < VertexNum; k++)
            if ((0 == used[k]) &&
                (distance[k] > distance[j] + g.edg[j][k])) {   //由于有顶点新加入U集合，对距离数组distance进行更新，比较原路径长度与以新加入的顶点为中间点的路径长度
                distance[k] = distance[j] + g.edg[j][k];
            }
        parent[index++] = j;
        if (used[to] == 1) {
            break;
        }
    }

    if (mini < INFINITY) {
        printf("%c到%c的最短路径经过顶点依次为:\n", g.ver[from], g.ver[to]);
        for (int i = 0; i < index; i++)
            printf("%c ", g.ver[parent[i]]);
        printf("\n");

        printf("最短路径长度为: %d\n", mini);
    } else {
        printf("无法到达");
    }
}


void print(GoodsInfo *goodsInfo, int num, Graph graph1, Graph graph2) {
    GoodsInfo sortOne[20];
    GoodsInfo sortTwo[20];
    GoodsInfo sortThree[20];
    int linOne = 0;
    int linTwo = 0;
    int linThree = 0;
    node *node2 = initTree(goodsInfo, num);
    node *node3 = node2->left;
    for (int i = 0; i < num; ++i) {
        if (goodsInfo[i].transpotation == 1) {
            linOne++;
        } else if (goodsInfo[i].transpotation == 2) {
            linTwo++;
        } else if (goodsInfo[i].transpotation == 3) {
            linThree++;
        }
    }
    node *node4 = node3->right;
    node *node5 = node4->right;
    if (node3->left == NULL) {
        cout << "路线一没有货物" << endl;
    } else {
        node *out = node3->left;
        for (int j = 0; j < linOne; j++) {
            //cout<<out->goodsInfo.id<<endl;
            sortOne[j] = out->goodsInfo;
            out = out->right;
        }
    }
    if (node4->left == NULL) {
        cout << "路线二没有货物" << endl;
    } else {
        node *out = node4->left;
        for (int j = 0; j < linTwo; j++) {
            //cout<<out->goodsInfo.id<<endl;
            sortTwo[j] = out->goodsInfo;
            out = out->right;
        }
    }
    if (node5->left == NULL) {
        cout << "路线三没有货物" << endl;
    } else {
        node *out = node5->left;
        for (int j = 0; j < linThree; j++) {
            //cout<<out->goodsInfo.id<<endl;
            sortThree[j] = out->goodsInfo;
            out = out->right;
        }
    }
    cout << "线路一出货顺序" << endl;
    for (int k = 0; k < linOne; ++k) {
        int min = 0;
        for (int i = 0; i < linOne; ++i) {
            if (sortOne[min].deliveryOrder > sortOne[i].deliveryOrder) {
                min = i;
            }
        }
        cout << "id:" << sortOne[min].id << "发货顺序：" << sortOne[min].deliveryOrder << endl;
        Dijkstra(graph1, sortOne[min].from, sortOne[min].to);
        sortOne[min].deliveryOrder = 1000;
    }


    cout << "线路二出货顺序" << endl;
    /* for (int k = 0; k <linTwo ; ++k) {
         cout<<sortTwo[k].deliveryOrder<<endl;}*/
    for (int k = 0; k < linTwo; ++k) {
        int min = 0;
        for (int i = 0; i < linTwo; ++i) {
            if (sortTwo[min].deliveryOrder > sortTwo[i].deliveryOrder) {
                min = i;
            }
        }
        cout << "id:" << sortTwo[min].id << "发货顺序：" << sortTwo[min].deliveryOrder << endl;
        Dijkstra(graph2, sortTwo[min].from, sortTwo[min].to);
        sortTwo[min].deliveryOrder = 1000;
    }

    cout << "线路三出货顺序" << endl;
    for (int k = 0; k < linThree; ++k) {
        int min = 0;
        for (int i = 0; i < linThree; ++i) {
            if (sortThree[min].deliveryOrder > sortThree[i].deliveryOrder) {
                min = i;
            }
        }
        cout << "id:" << sortThree[min].id << "发货顺序：" << sortThree[min].deliveryOrder << endl;
        cout << "飞机直达" << endl;
        sortThree[min].deliveryOrder = 1000;
    }
}


//================================================================================================================


int m() {




    while (true) {

        FILE *pf = fopen("E:\\goodsInfo.txt", "r");
        char buf[1000];
        int lineCnt = 0;
        if (!pf)
            return -1;
        while (fgets(buf, 1000, pf))
            lineCnt++;
        fclose(pf);

        int option = 0;
        printf("请输入选项：1：查看物流信息 2.查看物品信息 3.数据库操作 其它：退出\n");

        scanf("%d", &option);
        GoodsInfo goodsInfo[20];
        int num = lineCnt;
        initGoods2(goodsInfo);
        bubbleSort(goodsInfo, num);
        Graph graph1;
        Graph graph2;
        CreateGraph2(&graph1);
        CreateGraph2(&graph2);

        if(option==2){
            print(goodsInfo, num, graph1, graph2);
        } else if (option==1){
            printGoodsInfo(goodsInfo,num);
        }else if(option==3){
            inputSQLMain();
            int a=compile();
            if (a==0){
                printf("编译成功开始运行\n");
                int res=system("java FileLockTest");
                if (res==0){
                    printf("运行成功");
                }

            } else if(a==1){
                printf("词法分析失败\n");
            } else if (a==2){
                printf("语法分析错误\n");
            } else if(a==3){
                printf("语义分析错误\n");
            } else{
                printf("未知错误\n");
            }
        } else{
            return 0;
        }
    }



    return 0;
}

//int main() {
//    Graph graph1;
//    CreateGraph2(&graph1);
//    PrintGraph(graph1);
//    return 1;
//}