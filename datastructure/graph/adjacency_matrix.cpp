/*
 * Part of Cosmos by OpenGenus Foundation
 */
/*
所谓邻接矩阵存储结构就每个顶点用一个一维数组存储边的信息，这样所有点合起来就是用矩阵表示图中各顶点之间的邻接关系。所谓矩阵其实就是二维数组。
对于有 n个顶点的图 G=(V,E) 来说，我们可以用一个 n×n 的矩阵 A来表示 G 中各顶点的相邻关系，如果 i和 j​ 之间存在边（或弧），则 A[i][j]=1，否则 A[i][j]=0=0。
*/
/*有向图的邻接矩阵代码*/
#include <cstdio>
const int N = 1005;
int g[N][N];
int main() {
	int n, m; //n个点 m条边 
	scanf("%d%d", &n, &m);
	int u, v; //表示2个点u--->v 
	for (int i = 0; i < m; i++) 
  {
		scanf("%d%d", &u, &v);
		g[u][v] = 1;//有向图 u-->v 
	} 
	//输出
	for (int i = 1; i <= n; i++)
  {
		for (int j = 1; j <= n; j++)
    {
			printf("%d", g[i][j]);
		}
		printf("\n");
	} 
	return 0;
} 
