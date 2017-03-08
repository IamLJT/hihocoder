/*
题目：Trie树
*/

#include <iostream>
#include <cstring>
using namespace std;

#define Max 26

struct Trie
{
	Trie *next[Max];
	int Times;
	char val;
}*root;

//	初始化Trie树
struct Trie *init()
{
	Trie* root=(Trie*)malloc(sizeof(Trie));
	int i=0;
	for(i=0;i<Max;i++)
	{
		root->next[i]=NULL;
	}
	root->Times=0;
	root->val=0;
	return root;
}

//	插入字符串到字典树中
void insertTrie(char s[])
{
	Trie *t, *p=root;
	int i, j, n=strlen(s);
	for(int i=0; i<n; i++)
	{
		if(p->next[s[i]-'a'] == NULL)
		{
			t = (Trie*)malloc(sizeof(Trie));
			for(j=0; j<Max; j++)
			{
				t->next[j]=NULL;
			}
			t->Times = 0;
			t->val = s[i];
			p->next[s[i]-'a'] = t;
		}
		p->next[s[i]-'a']->Times++;
		p=p->next[s[i]-'a'];
	}
}

int findTimes(char s[])
{
	int n = strlen(s);
	Trie *p=root;
	for(int i=0; i<n; i++)
	{
		if(p->next[s[i]-'a']==NULL)
			return 0;
		p=p->next[s[i]-'a'];
	}
	return p->Times;
}

int main()
{
	int Ans, n_Pre;
	scanf("%d", &Ans);
	char str[50];
	root=init();
	for(int i=0;i<Ans;i++)
	{
		scanf("%s",&str);
		insertTrie(str);
	}
	scanf("%d", &n_Pre);
	int *res=new int[n_Pre];
	for(int i=0;i<n_Pre; i++)
	{
		scanf("%s",&str);
		res[i]=findTimes(str);
	}
	for(int i=0; i<n_Pre; i++)
	{
		printf("%d\n",res[i]);
	}
	system("pause");
	return 0;
}