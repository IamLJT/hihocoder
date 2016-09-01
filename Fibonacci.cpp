#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

#define Nlimit 1000000007

//	算法复杂度过高，不适用
/*
ll FibonacciNum(vector<int> num)
{
	ll res=(ll)0;
	vector<vector<int>> temp;		//	构建临时存放Fibonacci矩阵的位置
	vector<int> t(1,0);

	for(int i=0; i<(int)num.size(); i++)
	{
		int len=temp.size();		//	1目前出现的个数
		if(num[i]==1)
		{
			res++;
			if(res>(ll)Nlimit)
				res%=(ll)Nlimit;
			temp.push_back(t);
			temp.back().push_back(1);
		}
		for(int j=0; j<len; j++)
		{
			//	存放进temp的vector至少大小为2
			int v1=temp[j][temp[j].size()-2];
			int v2=temp[j][temp[j].size()-1];
			if(num[i]==v1+v2)
			{
				res++;
				if(res>(ll)Nlimit)
					res%=(ll)Nlimit;
				temp[j].push_back(num[i]);
			}
			if(num[i]<v1+v2&&num[i]!=1)
			{
				int pos=lower_bound(temp[j].begin(),temp[j].end(),num[i])-temp[j].begin();
				if(pos<(int)temp[j].size()&&temp[j][pos]==num[i])
				{
					vector<int> t0;
					t0.assign(temp[j].begin(),temp[j].begin()+pos+1);
					res++;
					if(res>(ll)Nlimit)
						res%=(ll)Nlimit;
					temp.push_back(t0);
				}
			}
		}
	}
	return res;
}
*/

int FibonacciNum(vector<int> num, vector<int> t)
{
	//	用find函数锁定斐波那契数
	
	vector<int> fibonaccnum(t.size()+1,0);

	fibonaccnum[0]=1;
	for(int i=0; i<num.size(); i++)
	{
		if(num[i]==1)
		{
			//	num[i]为1时需注意
			fibonaccnum[2]=(fibonaccnum[1]+fibonaccnum[2])%Nlimit;
			fibonaccnum[1]=fibonaccnum[1]+fibonaccnum[0];
		}
		else
		{
			//int pos=find(t.begin(),t.end(),num[i])-t.begin();
			int pos=lower_bound(t.begin(),t.end(),num[i])-t.begin();
			//	num[i]一定是>0,<=100000的数，所以pos>0
			if(pos!=(int)t.size()&&t[pos]==num[i])
			{
				fibonaccnum[pos]=(fibonaccnum[pos-1]+fibonaccnum[pos])%Nlimit;
			}
		}
	}
	
	////	进一步优化，用空间来换时间
	//vector<int> fibonaccnum(t.back()+1,-1);
	//for(int i=1; i<t.size(); i++)
	//	fibonaccnum[t[i]]=0;
	////	用0代替1的位置
	//fibonaccnum[0]=0;
	//for(int i=0; i<num.size(); i++)
	//{
	//	if(num[i]==1)
	//	{
	//		//	num[i]为1时需注意
	//		fibonaccnum[1]=fibonaccnum[1]+fibonaccnum[0];
	//		fibonaccnum[0]=fibonaccnum[0]+1;
	//	}
	//	else if(fibonaccnum[num[i]]!=-1)
	//	{
	//		int j;
	//		for(j=num[i]-1; j>=0; j--)
	//		{
	//			if(fibonaccnum[j]!=-1)
	//				break;
	//		}
	//		fibonaccnum[num[i]]=(fibonaccnum[num[i]]+fibonaccnum[j])%Nlimit;
	//	}
	//}

	int sum=0;
	for(int i=1; i<fibonaccnum.size(); i++)
	{
		sum=(sum+fibonaccnum[i])%Nlimit;
	}
	return sum;
}

int main()
{
	//	因为ai已经规定<100000，所以可以直接先求出100000以内所有的斐波那契数
	vector<int> t;
	t.push_back(0);
	t.push_back(1);
	int a,b;
	do
	{
		a=t[t.size()-2];
		b=t[t.size()-1];
		t.push_back(a+b);
	}while(a+b<=100000);

	int n;
	cin >> n;
	vector<int> num(n,0);
	for(int i=0; i<n; i++)
		cin >> num[i];
	cout << FibonacciNum(num,t) << endl;
	system("pause");
	return 0;
}