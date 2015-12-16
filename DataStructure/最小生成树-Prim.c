#include <stdio.h>
#include <limits.h>
#define SIZE_OF_GRAPH 100
typedef int graph[SIZE_OF_GRAPH][SIZE_OF_GRAPH];

void init(graph G, int vex_num);
void Prim(graph G, int closest[], int vex_num);
int main(){
    int vex_num;
    int closest[SIZE_OF_GRAPH];
    graph G;
    printf("顶点个数：");
    scanf("%d", &vex_num);
    init(G, vex_num);
    Prim(G, closest, vex_num);
    printf("最小生成树各边为：\n");
    int i;
    for(i = 2; i <= vex_num; i++){
        printf("(%d, %d)\t", i, closest[i]);
    }
    return 0;
}

void init(graph G, int vex_num){
    int start, end, length;
    for(start = 1; start <= vex_num; start++)
        for(end = 1; end <= vex_num; end++)
            G[start][end] = INT_MAX;
    printf("依次输入各边起点、终点及边长，起点输0结束：\n");
    while(1){
        scanf("%d%d%d", &start, &end, &length);
        if(start == 0)
            break;
        G[start][end] = length;
        G[end][start] = length;
    }
}
/**
 * 任取一顶点，如点 1 , low_cost为剩下点到点 1 的最短路径(实际是未确定点到已确定点的最短路径)
 * 找出low_cost中最小值，对应的点为新确定的点 v
 * v 的加入会使low_cost不满足"最短路径", 故需要重新验证即比较G[v] low_cost的各值确定最短路径
 */
void Prim(graph G, int closest[], int vex_num){
    int low_cost[SIZE_OF_GRAPH];
    int flag[SIZE_OF_GRAPH];
    int i, j, v;
    for(i = 2; i <= vex_num; i++){
        low_cost[i] = G[1][i];
        closest[i] = 1;
        flag[i] = 0;
    }
    flag[1] = 1;
    for(v = i = 2; i <= vex_num; i++){
        int temp = INT_MAX;
        for(j = 2; j <= vex_num; j++){
            if(flag[j] == 0 && low_cost[j] < temp){
                v = j;
                temp = low_cost[j];
            }
        }
        flag[v] = 1;
        for(j = 2; j <= vex_num; j++){
            if(flag[j] == 0 && G[v][j] < low_cost[j]){
                low_cost[j] = G[v][j];
                closest[j] = v;
            }
        }
    }
}