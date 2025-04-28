#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 100

// 邻接表中的边节点
typedef struct ArcNode {
    int adjvex;              // 邻接点的位置
    struct ArcNode *next;    // 指向下一条边的指针
} ArcNode;

// 邻接表中的顶点节点
typedef struct VertexNode {
    int data;               // 顶点数据
    ArcNode *firstArc;      // 指向第一条边的指针
} VertexNode;

// 图的结构定义
typedef struct {
    VertexNode vertices[MAX_VERTEX];  // 顶点数组
    int vertexNum, arcNum;            // 顶点数和边数
} ALGraph;

// 初始化图
void initGraph(ALGraph *G) {
    G->vertexNum = 0;
    G->arcNum = 0;
}

// 创建有向图
void createGraph(ALGraph *G, int n, int e) {
    G->vertexNum = n;
    G->arcNum = e;
    
    // 初始化顶点
    for (int i = 0; i < n; i++) {
        G->vertices[i].data = i;      // 顶点值设为索引
        G->vertices[i].firstArc = NULL;
    }
    
    // 添加边
    for (int i = 0; i < e; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);     // 输入一条边的两个顶点
        
        // 创建新的边节点
        ArcNode *p = (ArcNode *)malloc(sizeof(ArcNode));
        p->adjvex = v2;
        
        // 插入到邻接表头部
        p->next = G->vertices[v1].firstArc;
        G->vertices[v1].firstArc = p;
    }
}

// 拓扑排序算法
int topologicalSort(ALGraph *G, int topo[]) {
    int indegree[MAX_VERTEX] = {0};   // 存储各顶点的入度
    int count = 0;                    // 已排序的顶点数
    
    // 计算所有顶点的入度
    for (int i = 0; i < G->vertexNum; i++) {
        ArcNode *p = G->vertices[i].firstArc;
        while (p) {
            indegree[p->adjvex]++;
            p = p->next;
        }
    }
    
    // 使用队列存储入度为0的顶点
    int queue[MAX_VERTEX], front = 0, rear = 0;
    
    // 将所有入度为0的顶点入队
    for (int i = 0; i < G->vertexNum; i++) {
        if (indegree[i] == 0) {
            queue[rear++] = i;
        }
    }
    
    // 处理队列中的顶点
    while (front < rear) {
        int v = queue[front++];       // 取出一个入度为0的顶点
        topo[count++] = v;            // 将其加入拓扑序列
        
        // 将所有v指向的顶点的入度减1，如果入度变为0，则入队
        ArcNode *p = G->vertices[v].firstArc;
        while (p) {
            int k = p->adjvex;
            indegree[k]--;
            if (indegree[k] == 0) {
                queue[rear++] = k;
            }
            p = p->next;
        }
    }
    
    // 如果排序的顶点数小于图中顶点数，则图中有环
    if (count < G->vertexNum) {
        return 0;   // 有环，拓扑排序失败
    } else {
        return 1;   // 无环，拓扑排序成功
    }
}

// 释放图的内存
void destroyGraph(ALGraph *G) {
    for (int i = 0; i < G->vertexNum; i++) {
        ArcNode *p = G->vertices[i].firstArc;
        while (p) {
            ArcNode *q = p;
            p = p->next;
            free(q);
        }
    }
}

int main() {
    ALGraph G;
    int n, e;   // n为顶点数，e为边数
    
    printf("请输入顶点数和边数：\n");
    scanf("%d %d", &n, &e);
    
    initGraph(&G);
    printf("请输入%d条边的起点和终点：\n", e);
    createGraph(&G, n, e);
    
    int topo[MAX_VERTEX];  // 存储拓扑序列结果
    int result = topologicalSort(&G, topo);
    
    if (result) {
        printf("拓扑排序成功，拓扑序列为：\n");
        for (int i = 0; i < G.vertexNum; i++) {
            printf("%d ", topo[i]);
        }
        printf("\n");
    } else {
        printf("拓扑排序失败，图中存在环路\n");
    }
    
    destroyGraph(&G);
    return 0;
}