// hiho 139周
/*************************************************
描述
小Ho很喜欢在课间去小卖部买零食。然而不幸的是，这个学期他又有在一教的课，而一教的小卖部姐姐以冷若冰霜著称。第一次去一教小卖部买零食的时候，小Ho由于不懂事买了好一大堆东西，被小卖部姐姐给了一个“冷若冰霜”的眼神，食欲都下降了很多。

从那以后，小Ho就学乖了，去小卖部买东西只敢同时买3包以内的零食，并且价格加起来必须是5的整数倍，方便小卖部姐姐算价格。

但是小Ho不擅长计算，所以他把小卖部里所有零食的价格以及他对这个零食的渴望度都告诉了你，希望你能够帮他计算出在不惹恼小卖部姐姐的前提下，能够买到零食的渴望度之和最高是多少？

输入
每个输入文件包含多组测试数据，在每个输入文件的第一行为一个整数Q，表示测试数据的组数。

每组测试数据的第一行为一个正整数N，表示小卖部中零食的数量。

接下来的N行，每行为一个正实数A和一个正整数B，表示这种零食的价格和小Ho对其的渴望度。

一种零食仅有一包。

对于100%的数据，满足1 <= Q <= 10，1<=N<=50，0<A<=10，1<=B<=100。

对于100%的数据，满足A的小数部分仅可能为0.5或0。

输出
对于每组测试数据，输出一个整数Ans，表示小Ho可以获得最大的渴望度之和。
*****************************************************/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int cmp(pair<double, int> p1, pair<double, int> p2)
{
	if (p1.second > p2.second)
		return 1;
	else if (p1.first > p2.first)
		return 1;
	else
		return 0;
}

int FindMaxSock(vector<pair<double, int>> Data)
{
	
	//sort(Data.begin(), Data.end(), cmp);	// 对数据按渴望度排序

	Data.push_back(make_pair(0, 0));
	Data.push_back(make_pair(0, 0));	// 建立能够买1到3种商品的情况
	
	int len = Data.size(), res = 0;

	for (int i = 0; i < len-2; i++) {
		for (int j = i + 1; j < len-1; ++j) {
			for (int k = j + 1; k < len; ++k) {
				double s = (Data[i].first + Data[j].first + Data[k].first)/5;
				if (s == (double)(int)s) res = (res > Data[i].second + Data[j].second + Data[k].second ? 
					res : Data[i].second + Data[j].second + Data[k].second);
			}
		}
	}

	return res;
}

int main(void)
{
	int Q, N;
	cin >> Q;
	vector<int> res;
	for (int i = 0; i < Q; ++i) {
		cin >> N;
		vector<pair<double, int>> Data;
		for (int j = 0; j < N; ++j) {
			double A;
			int B;
			cin >> A >> B;
			Data.push_back(make_pair(A, B));
		}
		res.push_back(FindMaxSock(Data));
	}
	for (int i = 0; i < Q; i++)
		cout << res[i] << endl;

	system("pause");
	return 0;
}