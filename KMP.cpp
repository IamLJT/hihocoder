/*
题目：KMP算法
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

void NextArray(vector<int>& next, string dst)
{
	if(next.size()>=1) next[0]=-1;
	int j=-1, i=0;
	while(i<dst.size()-1)
	{
		if(-1==j || dst[i]==dst[j])
		{
			i++;
			j++;
			if(dst[i]!=dst[j])
				next[i]=j;
			else
				next[i]=next[j];	//	对于相同元素，不需要经过多次的比较
		}
		else
		{
			j=next[j];
		}
	}
}

int main()
{
	int Times;
	string dst, src;
	scanf("%d", &Times);
	vector<int> res(Times);
	for(int i=0; i<Times; i++)
	{
		cin >> dst >> src;
		if(dst.size()>src.size())
		{
			res[i]=0;
			continue;
		}
		vector<int> next(dst.size());
		NextArray(next, dst);
		int k=0;
		for(int j=0; j<src.size();)
		{
			if(k==dst.size())
			{
				res[i]++;
				k=0;
				j--;
			}
			if(dst[k]==src[j])
				k++,j++;
			else if(next[k]!=-1)
				k=next[k];
			else
				k=0,j++;
		}
		if(k==dst.size())
		{
			res[i]++;
			k=0;
		}
	}
	for(int i=0; i<res.size(); i++)
		cout << res[i] << endl;
	system("pause");
	return 0;
}