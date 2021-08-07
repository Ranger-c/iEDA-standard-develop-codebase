/*
 * Part of Cosmos by OpenGenus Foundation
 */
/*邻接表是基于链表的思想实现的。在邻接表中，对于中的每个顶点建立一个单链表，第i个单链表中的节点表示依附于顶点的vi的边。
每个节点由3个域组成其中邻接点域（adjvex）指示与顶点vi邻接的点在图中的位置，链域（nextarc）指示下一条边或弧的节点；
数据域（info）存储和边或弧相关的信息，如权值等，每个链表上附设一个表头节点。
在表头节点中除了设有链域（firstarc）指向链表中的第一个节点之外，还设有存储顶点vi的名或其他有关信息的数据域（data）。*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define maxn 1024   //最大顶点数

//边节点
struct ArcNode{
    int adjvex; //改边指向的顶点的位置
    ArcNode* next;  //指向的下一个顶点
    // int lowcost;  //权值
};

//顶点
struct VNode{
    ArcNode* firstArc;   //指向的第一条依附于该顶点的指针
}vlist[maxn];   //vlist[i]表示第i条顶点的信息

int n,m;  //顶点个数（编号从1-n），边的个数

/*
增加一条连接v1和v2的边
*/
void link(int v1,int v2){
    //在v1表的表头插入v2
    ArcNode* p1 = new ArcNode();
    p1->adjvex = v2;
    p1->next = vlist[v1].firstArc;   //这两行是链表插入的常规操作
    vlist[v1].firstArc = p1;

    //同时也在v2的表头插入v1
    ArcNode* p2 = new ArcNode();
    p2->adjvex = v1;
    p2->next = vlist[v2].firstArc;   //这两行是链表插入的常规操作
    vlist[v2].firstArc = p2;
}

/*
初始化
*/
void init(){
    n = 5;
    m = 6;
    //以下n行初始化vlist
    for(int i = 1;i<=n;++i)
    {
        vlist[i].firstArc = NULL;
    }
    //以下m行建图
    link(1,2);
    link(1,4);
    link(2,3);
    link(2,5);
    link(3,4);
    link(3,5);
}

/*
打印邻接表
*/
void printArc(){
    for(int i = 1;i<=n;++i)
    {
        cout << i << " -> ";
        ArcNode* an = vlist[i].firstArc;
        while(an)
        {
            cout << an->adjvex << " -> ";
            an = an->next;
        }
        cout << " ^" << endl;
    }
}

int main() {
	init();
    printArc();
	return 0;
}

