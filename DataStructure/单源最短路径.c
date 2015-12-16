#include <stdio.h>
#include <limits.h>
#define SIZE_OF_GRAPH 100
typedef int graph[SIZE_OF_GRAPH][SIZE_OF_GRAPH];
//初始化邻接阵
void init(graph G, int vex_num);
void Dijkstra(graph G, int D[], int vex_num, int pre_vex[SIZE_OF_GRAPH]);
void path(int pre_vex[], int vex);
int main(){
    graph G;
    int vex_num;
    printf("输入顶点个数：");
    scanf("%d", &vex_num);
    init(G, vex_num);
    int D[SIZE_OF_GRAPH];
    int pre_vex[SIZE_OF_GRAPH];
    Dijkstra(G, D, vex_num, pre_vex);
    int i;
    printf("VEX\tLENGTH\tPATH\n");
    for(i = 2; i <= vex_num; i++){
        printf("%d\t", i);
        if(D[i] == INT_MAX)
            printf("∞\tno path");
        else{
            printf("%d\t", D[i]);
            path(pre_vex, i);
        }
        printf("\n");
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
    }
}
/**
 * 确定源点 1, D为各点到源点最短路径
 * 找出D中最小值及其对应点，该点的最短路径则可确定(否则经其他点，必使路径变长)
 * 新点的加入会破坏D值的最小性，故需要重新确定
 */
void Dijkstra(graph G, int D[], int vex_num, int pre_vex[]){
    int flag[SIZE_OF_GRAPH];
    int i, j;
    //init D, flag
    for(i = 1; i <= vex_num; i++){
        D[i] = G[1][i];
        flag[i] = 0;
        pre_vex[i] = 1;
    }
    flag[1] = 1;
    int vex, temp;
    for(i = 2; i <= vex_num; i++){
        //确定vex最短路径
        {
            vex = 2;
            temp = INT_MAX;
            for(j = 2; j <= vex_num; j++)
            if(!flag[j] && D[j] < temp){
                vex = j;
                temp = D[vex];
            }
            flag[vex] = 1;
        }
        int sum;
        for( j = 2; j <= vex_num; j++){
            if(!flag[j] && G[vex][j] != INT_MAX){
                sum = D[vex] + G[vex][j];
                if(sum < D[j]){
                    D[j] = sum;
                    pre_vex[j] = vex;
                }
            }
        }
    }
}
void path(int pre_vex[], int vex){
    if(vex != 1)
        path(pre_vex, pre_vex[vex]);
    printf("%d ", vex);
}