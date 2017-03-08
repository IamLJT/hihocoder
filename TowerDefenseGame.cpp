/*
题目：Tower Defense Game
要求：There is a tower defense game with n levels(missions). The n levels form a 
tree whose root is level 1.
In the i-th level, you have to spend pi units of money buying towers and after 
the level, you can sell the towers so that you have qi units of money back.

Each level is played once. You can choose any order to complete all the levels, but 
the order should follow the following rules:
1: A level can be played when all its ancestors are completed.
2: The levels which form a subtree of the original tree should be completed 
consecutively in your order.
You want to know in which order of completion you can bring the minimum money before 
starting the first level.
*/

#include <iostream>
#include <vector>
using namespace std;

#define MAX_SIZE 10000
int wallet = 200000000;
int minwallet = 200000000;

typedef int ElemType;

//	孩子结点
typedef struct Node
{
	int child;				//	孩子结点的下标
	struct Node *next;		//	指向下一个结点的下标
}*ChildPtr, CNode;

//	表头结构
typedef struct
{
	ElemType p, q;			//	存放在树中的结点的数据
	int parent;				//	存放双亲的下标
	ChildPtr firstchild;	//	指向第一个孩子的指针
}CTBox, *CTree;

void Treevisit(CTree *T, int& minmoney)
{
	wallet=wallet-(*T)->p;
	if(wallet<minwallet)
		minwallet=wallet;
	wallet=wallet+(*T)->q;
	if((*T)->firstchild==NULL)
		return;
	ChildPtr temp=(*T)->firstchild;
	while(temp!=NULL)
	{
		Treevisit((T+temp->child), minmoney);
		temp=temp->next;
	}
}

int minmoney(CTree *T)
{
	int res=0;
	Treevisit(T,res);
	return res;
}

int main()
{
	int n, p, q, s, e;
	cin >> n;
	CTBox *nodes=new CTBox[n+1];
	
	for(int i=0; i<=n; i++)
		nodes[i].firstchild=NULL;
	for(int i=1; i<=n; i++)
	{
		cin >> p >> q;
		nodes[i].p=p;
		nodes[i].q=q;
	}
	for(int i=0; i<n-1; i++)
	{
		cin >> s >> e;
		nodes[e].parent=s;
		ChildPtr node=new CNode[];
		node->child=e;
		node->next=NULL;
		ChildPtr temp=nodes[s].firstchild;
		if(temp!=NULL)
		{
			while(temp->next!=NULL&&nodes[temp->child].q>nodes[e].q)	//	按q值大小排序
				temp=temp->next;
			if(temp==nodes[s].firstchild&&nodes[temp->child].q<nodes[e].q)
			{
				node->next=temp;
				nodes[s].firstchild=node;
			}
			else
			{
				node->next=temp->next;
				temp->next=node;
			}
		}
		else
		{
			nodes[s].firstchild=node;
		}
	}
	if(n>0)
		nodes[0]=nodes[1];
	cout << minmoney(&nodes) << endl;
	system("pause");
	return 0;
}