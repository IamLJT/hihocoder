/*
题目：网络流一·Ford-Fulkerson算法
题目描述：见hihocoder115周
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

typedef long long ll;
#define N 40005
using namespace std;

const int MaxN=505;
const int inf=0x7fffffff;

struct Edge{
	int u,v,c;
	int next;
}edge[N];

int cnt;
int head[N];

void addedge(int u, int v, int c)
{
	edge[cnt].u=u; edge[cnt].v=v; edge[cnt].c=c;
	edge[cnt].next=head[u]; head[u]=cnt++;

	edge[cnt].u=v; edge[cnt].v=u; edge[cnt].c=0;
	edge[cnt].next=head[v]; head[v]=cnt++;
}

int m,n;
int source,sink;	//	源点和汇点
int gap[MaxN];		//	gap优化
int dep[MaxN];		//	层数
int cur[MaxN];		//	当前弧优化
int stck[MaxN];		//	用一个栈储存增广路径

void rec_bfs()		//	对残余网络逆向分层
{
	memset(dep, -1, sizeof(dep));
	memset(gap, 0, sizeof(gap));
	queue<int> q;
	dep[sink]=0;	//	汇点sink的深度为0
	gap[0]=1;		//	层数为0的点一个
	q.push(sink);

	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(int i=head[u];i!=-1;i=edge[i].next)	//	以u为起点的边
		{
			int v=edge[i].v;
			if(edge[i^1].c>0&&dep[v]==-1)		//	每次存储边都是两条边一起存的，因为是逆序搜索，所以edge[i^1].c表示u->v的边
			{
				q.push(v);
				dep[v]=dep[u]+1;
				gap[dep[v]]++;
			}
		}
	}
}

int SAP()
{
	rec_bfs();		//	只需要bfs分层一次，之后的层数更新不用重新bfs
	memcpy(cur, head, sizeof(cur));	//	当前弧初始化为邻接表的第一条弧，即head[i]
	int maxflow=0;
	int u=source;
	int top=0;
	int i;
	while(dep[source]<n)	//	最大层数只会是n，如果大于等于n说明中间已经断层了
	{
		if(u==sink)	//	找到一条增广路，沿着增广路修改流量
		{
			int delta=inf;
			int flag=n;		//	记录增广路径上残余流量最少的边
			for(i=0; i!=top; i++)
			{
				if(delta>edge[stck[i]].c)
				{
					delta=edge[stck[i]].c;
					flag=i;
				}
			}
			for(i=0; i!=top; i++)	//	路径上各边残余流量减少，反向边残余流量增加，总流量增加
			{
				edge[stck[i]].c-=delta;
				edge[stck[i]^1].c+=delta;
			}
			maxflow+=delta;
			top=flag;				//	回溯到流量恰好变为0的最上层节点，继续寻找增广路径
			u=edge[stck[top]].u;
		}
		for(i=cur[u]; i!=-1; i=edge[i].next)
		{
			int v=edge[i].v;
			if(edge[i].c>0 && dep[u]==dep[v]+1) break;	//	若找到一条满足条件的边则停止
		}
		if(i!=-1)
		{
			cur[u]=i;	//	设为当前弧
			stck[top++]=i;
			u=edge[i].v;
		}
		else	//	找不到允许弧，回溯，重新寻找增广路
		{
			//	对u节点的层数进行修改
			if(--gap[dep[u]]==0) break;//	如果出现断层，结束
			int mind=n+1;
			for(i=head[u]; i!=-1; i=edge[i].next)
			//	寻找可以增广的最小标号
			{
				if(edge[i].c>0 && mind>dep[edge[i].v])
				{
					mind=dep[edge[i].v];
					cur[u]=i;
				}
			}
			dep[u]=mind+1;
			gap[dep[u]]++;
			u=(u==source)?u:edge[stck[--top]].u;	//	回溯
		}
	}
	return maxflow;
}

int main()
{
    while(~scanf("%d%d",&n,&m))
    {
        int u,v,w;
        cnt=0;
        memset(head,-1,sizeof(head));
        for(int i=0;i<m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            addedge(u,v,w);
        }
        source=1,sink=n;
        printf("%d\n",SAP());
    }
    return 0;
}