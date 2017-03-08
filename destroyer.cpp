/*
题目： 毁灭者问题
*/

#include <iostream>
#include <vector>
using namespace std;

struct MagicPara
{
	int Si, mi, ri;
};

struct OperatorNum
{
	int t, l, r;
};

int main()
{
	int n, m, res=0, time=0;
	cin >> n;
	vector<MagicPara> MagicParameter(n);
	vector<int> MagicNow(n);
	for(int i=0; i<n; i++)
		cin >> MagicParameter[i].Si >> MagicParameter[i].mi >> MagicParameter[i].ri;
	cin >> m;
	vector<OperatorNum> OperatorNums(m);
	for(int i=0; i<m; i++)
		cin >> OperatorNums[i].t >> OperatorNums[i].l >> OperatorNums[i].r;
	for(int i=0; i<m; i++)
	{
		for(int j=0; j<n; j++)
		{
			int temp=((MagicParameter[j].Si+(OperatorNums[i].t-time)*MagicParameter[j].ri)>MagicParameter[j].mi?MagicParameter[j].mi:(MagicParameter[j].Si+(OperatorNums[i].t-time)*MagicParameter[j].ri));
			if(j>=OperatorNums[i].l-1&&j<=OperatorNums[i].r-1)
			{
				res+=temp;
				MagicParameter[j].Si=0;
			}
			else
			{
				MagicParameter[j].Si=temp;
			}
		}
		time=OperatorNums[i].t;
	}
	cout << res << endl;
	system("pause");
	return 0;
}