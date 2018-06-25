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
//ע��ȷ��GoodsInfo[]��С
typedef struct GoodsInfo1 {
    int id;//��Ʒid
    int deliveryOrder;//��Ʒ����˳��
    int vip;//vip�ȼ�
    int value;//���س̶�
    int emergency;//�Ƿ�Ӽ�1.�� 0����
    int transpotation;//���䷽ʽ 1�𳵣�2���� 3.����
    int weight;//��������λǧ��
    int volumn;//�������λm^3
    int from;//���
    int to;//�յ�
} GoodsInfo;

//��ʼ����Ʒ��Ϣ
void initGoods(GoodsInfo *goodsInfo, int num) {
    cout << "��Ʒid " << "vip�ȼ� " << "���س̶� " << "�Ƿ�Ӽ� " << "��Ʒ���� " << "��Ʒ��� " << "��Ʒ�����أ����ţ� " << "��ƷĿ�ĵأ����ţ�"
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

    cout << "��Ʒid " << "vip�ȼ� " << "���س̶� " << "�Ƿ�Ӽ� " << "��Ʒ���� " << "��Ʒ��� " << "����˳��" << "���䷽ʽ" << "��Ʒ�����أ����ţ� "
         << "��ƷĿ�ĵأ����ţ�"
         << endl;
    for (int i = 0; i < num; ++i) {
        printf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n", goodsInfo[i].id, goodsInfo[i].vip, goodsInfo[i].value,
               goodsInfo[i].emergency,
               goodsInfo[i].weight, goodsInfo[i].volumn, goodsInfo[i].deliveryOrder, goodsInfo[i].transpotation,
               goodsInfo[i].from, goodsInfo[i].to);
    }
}

//�����ҳ�ʼ�����﷢��˳��,���㿪ʼ
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
//����Ʒ��������
//������ת��Ϊ������
typedef struct node1 {
    GoodsInfo goodsInfo;//����������Ʒ
    struct node1 *left, *right;
} node;

//���������������
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
//Djstra�㷨�����·��
#define MaxSize 20
#define INFINITY 65535
typedef char VertexType;
//����ͼ ���ڽӾ����ʾ���ṹ
typedef struct Graph {
    //���嶨�����
    VertexType ver[MaxSize + 1];
    //����ߴ�С
    int edg[MaxSize][MaxSize];
} Graph;

//�ڽӾ���ͼ�����ɺ���
void CreateGraph(Graph *g) {
    int i = 0;
    int j = 0;
    int VertexNum;
    VertexType Ver;
    printf("������ͼ�Ķ���:\n");
    while ('\n' != (Ver = getchar()))
        g->ver[i++] = Ver;
    g->ver[i] = '\0';
    VertexNum = strlen(g->ver);
    printf("��������Ӧ�ĵ��ڽӾ���:\n");
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


//��ӡͼ�Ľ���ʶ�����ڽӾ���
void PrintGraph(Graph g) {
    int i, j;
    int VertexNum = strlen(g.ver);
    printf("ͼ�Ķ���Ϊ:\n");
    for (i = 0; i < VertexNum; i++)
        printf("%c ", g.ver[i]);
    printf("\n");
    printf("ͼ���ڽӾ���Ϊ:\n");
    for (i = 0; i < VertexNum; i++) {
        for (j = 0; j < VertexNum; j++)
            printf("%d ", g.edg[i][j]);
        printf("\n");
    }
}

//��ͼ�Ķ�����
int CalVerNum(Graph g) {
    return strlen(g.ver);
}

//�����ڽӵĶ���֮���Ȩֵ����ΪINFINITY�����������ͺ�
void SetWeight(Graph *g) {
    for (int i = 0; i < CalVerNum(*g); i++)
        for (int j = 0; j < CalVerNum(*g); j++)
            if (0 == g->edg[i][j])
                g->edg[i][j] = INFINITY;
}

//Dijkstra�����·������
void Dijkstra(Graph g, int from, int to) {
    int VertexNum = CalVerNum(g);
    int j;
    int mini;
    int index = 0;
    int *used = (int *) malloc(sizeof(int) * VertexNum);
    int *distance = (int *) malloc(sizeof(int) * VertexNum);
    int *parent = (int *) malloc(sizeof(int) * VertexNum);
    int *last = (int *) malloc(sizeof(int) * VertexNum);

    SetWeight(&g);                    //����Ȩֵ

    //distance[i]��ʾ����Ϊfrom�ľ���
    for (int i = 0; i < VertexNum; i++) {
        used[i] = 0;
        distance[i] = g.edg[from][i];   //��ʼ��Ϊ����Ϊfrom�Ķ���ľ���
        last[i] = 0;
    }

    used[from] = 1;
    parent[index++] = from;

    for (int i = 0; i < VertexNum - 1; i++) {
        j = from;
        mini = INFINITY;

        //mini�洢����Ϊ0����̾���
        //j������Ӧ��0���������Ӧ�Ľڵ�
        for (int k = 0; k < VertexNum; k++)
            if ((0 == used[k]) && (distance[k] < mini)) {
                mini = distance[k];
                j = k;          //jΪ�ո��ҵ���V-U�е�Դ��·����̵Ķ���
            }

        //������ҵ��Ľڵ�ı�־λ��Ϊ1
        used[j] = 1;

        //�㷨���裬�½ڵ����
        for (int k = 0; k < VertexNum; k++)
            if ((0 == used[k]) &&
                (distance[k] > distance[j] + g.edg[j][k])) {   //�����ж����¼���U���ϣ��Ծ�������distance���и��£��Ƚ�ԭ·�����������¼���Ķ���Ϊ�м���·������
                distance[k] = distance[j] + g.edg[j][k];
            }
        parent[index++] = j;
        if (used[to] == 1) {
            break;
        }
    }

    if (mini < INFINITY) {
        printf("%c��%c�����·��������������Ϊ:\n", g.ver[from], g.ver[to]);
        for (int i = 0; i < index; i++)
            printf("%c ", g.ver[parent[i]]);
        printf("\n");

        printf("���·������Ϊ: %d\n", mini);
    } else {
        printf("�޷�����");
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
        cout << "·��һû�л���" << endl;
    } else {
        node *out = node3->left;
        for (int j = 0; j < linOne; j++) {
            //cout<<out->goodsInfo.id<<endl;
            sortOne[j] = out->goodsInfo;
            out = out->right;
        }
    }
    if (node4->left == NULL) {
        cout << "·�߶�û�л���" << endl;
    } else {
        node *out = node4->left;
        for (int j = 0; j < linTwo; j++) {
            //cout<<out->goodsInfo.id<<endl;
            sortTwo[j] = out->goodsInfo;
            out = out->right;
        }
    }
    if (node5->left == NULL) {
        cout << "·����û�л���" << endl;
    } else {
        node *out = node5->left;
        for (int j = 0; j < linThree; j++) {
            //cout<<out->goodsInfo.id<<endl;
            sortThree[j] = out->goodsInfo;
            out = out->right;
        }
    }
    cout << "��·һ����˳��" << endl;
    for (int k = 0; k < linOne; ++k) {
        int min = 0;
        for (int i = 0; i < linOne; ++i) {
            if (sortOne[min].deliveryOrder > sortOne[i].deliveryOrder) {
                min = i;
            }
        }
        cout << "id:" << sortOne[min].id << "����˳��" << sortOne[min].deliveryOrder << endl;
        Dijkstra(graph1, sortOne[min].from, sortOne[min].to);
        sortOne[min].deliveryOrder = 1000;
    }


    cout << "��·������˳��" << endl;
    /* for (int k = 0; k <linTwo ; ++k) {
         cout<<sortTwo[k].deliveryOrder<<endl;}*/
    for (int k = 0; k < linTwo; ++k) {
        int min = 0;
        for (int i = 0; i < linTwo; ++i) {
            if (sortTwo[min].deliveryOrder > sortTwo[i].deliveryOrder) {
                min = i;
            }
        }
        cout << "id:" << sortTwo[min].id << "����˳��" << sortTwo[min].deliveryOrder << endl;
        Dijkstra(graph2, sortTwo[min].from, sortTwo[min].to);
        sortTwo[min].deliveryOrder = 1000;
    }

    cout << "��·������˳��" << endl;
    for (int k = 0; k < linThree; ++k) {
        int min = 0;
        for (int i = 0; i < linThree; ++i) {
            if (sortThree[min].deliveryOrder > sortThree[i].deliveryOrder) {
                min = i;
            }
        }
        cout << "id:" << sortThree[min].id << "����˳��" << sortThree[min].deliveryOrder << endl;
        cout << "�ɻ�ֱ��" << endl;
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
        printf("������ѡ�1���鿴������Ϣ 2.�鿴��Ʒ��Ϣ 3.���ݿ���� �������˳�\n");

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
                printf("����ɹ���ʼ����\n");
                int res=system("java FileLockTest");
                if (res==0){
                    printf("���гɹ�");
                }

            } else if(a==1){
                printf("�ʷ�����ʧ��\n");
            } else if (a==2){
                printf("�﷨��������\n");
            } else if(a==3){
                printf("�����������\n");
            } else{
                printf("δ֪����\n");
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