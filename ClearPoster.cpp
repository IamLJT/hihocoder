/********************************************************************
描述
小Hi实验室所在的建筑一楼有一个用于贴海报的黑板，不停的有新的海报往上贴，
也会安排人员不断的对海报进行清理，而最近，轮到了小Hi去对海报进行清理。

黑板是一块W*H大小的区域，如果以左下角为直角坐标系的话，在上次清理后第i张
贴上去的海报可以视作左下角为(x_1i, y_1i)，右上角为(x_2i, y_2i)的一个矩形。

撕去一张海报会导致所有覆盖在其上的海报都被同时撕掉（这样被称为连带，这个
过程是具有传递性的，即如果A覆盖B，B覆盖C，那么撕掉C会导致A和B均被撕掉），
但是一张海报想要被手动撕掉的话需要至少存在一个角没有被其他海报覆盖（海报A
被海报B覆盖当且仅当他们存在面积大于0的交集并且A在B之前贴出，海报A的一个角
被海报B覆盖当且仅当这个顶点处于海报B的内部）。

于是现在问题来了，为了节约时间，小Hi决定一次性撕掉尽可能多的海报，那么他
应该选择哪张海报呢？在效果相同的情况下，小Hi倾向于选择更早贴出的海报。

输入
每个输入文件仅包含单组测试数据。

每组测试数据的第一行为三个正整数W，H和N，分别表示黑板的宽、高以及目前张贴出
的海报数量。

接下来的N行，每行为四个正整数x_1i、y_1i、x_2i和y_2i，描述第i张贴出的海报。

对于20%的数据，满足1<=N<=5，1<=W,H<=10

对于100%的数据，满足1<=N<=1000，0<=x_1i, x_2i <= W, 0<=y_1i, y_2i<=H, 1<=W,H<=108

输出
对于每组测试数据，输出两个正整数Ans和K，表示小Hi一次最多能撕掉多少张海报，
和他选择的海报是第几张贴出的。

样例输入
6 7 4
0 0 4 4
1 0 3 4
1 4 4 6
0 0 3 5
样例输出
3 1
*********************************************************************/

#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;

const int MAX_NUM = 1000;
ll x_1[MAX_NUM], x_2[MAX_NUM], y_1[MAX_NUM], y_2[MAX_NUM];	// 左上和右下坐标
bool iscover[MAX_NUM][MAX_NUM], fourAngles[MAX_NUM][4];	// 标记是否覆盖，是否四个角被填充
int num[MAX_NUM];										// 从第i个海报开始能清除的海报个数
int visited[MAX_NUM];									// 标记是否已被访问过，用在dfs中
int N;													// 输入的值的个数

bool CheckPoint(int index, ll xpoint, ll ypoint)
// 检查点(xpoint, ypoint)是否在第index个海报内
{
	return (xpoint > x_1[index] && xpoint< x_2[index]
		&& ypoint > y_1[index] && ypoint < y_2[index]);
}

bool CheckCover(int firstindex, int secondindex)
// 检查两海报是否有覆盖的地方
{
	return !(x_1[firstindex] >= x_2[secondindex] ||
			x_2[firstindex] <= x_1[secondindex] ||
			y_1[firstindex] >= y_2[secondindex] ||
			y_2[firstindex] <= y_1[secondindex]);
}

void dfs(int i, int& num)
// 从i点出发，深度优先搜索，遇到能覆盖且未被访问到的点，则清除数+1
{
	visited[i] = true;
	for (int j = i + 1; j < N; ++j) {
		if (iscover[i][j] && !visited[j]) {
			num++;
			dfs(j, num);
		}
	}
}

int main()
{
	int W, H;
	cin >> W >> H >> N;
	for (int i = 0; i < N; ++i) {
		cin >> x_1[i] >> y_1[i] >> x_2[i] >> y_2[i];
	}
	for (int i = 0; i < N; ++i) {
		for (int j = i + 1; j < N; ++j) {
			if (CheckCover(i, j))
				iscover[i][j] = 1;
			//	检查先贴的海报上四个角是否被覆盖
			{
				if (CheckPoint(j, x_1[i], y_1[i])) fourAngles[i][0] = 1;
				if (CheckPoint(j, x_2[i], y_1[i])) fourAngles[i][1] = 1;
				if (CheckPoint(j, x_1[i], y_2[i])) fourAngles[i][2] = 1;
				if (CheckPoint(j, x_2[i], y_2[i])) fourAngles[i][3] = 1;
			}
		}
	}
	for (int i = 0; i < N; ++i) {
		// 如果四个角都已经被覆盖，则不会作为被撕的第一张海报
		if (fourAngles[i][0] && fourAngles[i][1] && fourAngles[i][2]
			&& fourAngles[i][3])
			continue;
		memset(visited, 0, sizeof(visited));
		num[i] = 1;
		dfs(i, num[i]);
	}
	int res = 0, pos = 0;
	for (int i = 0; i < N; ++i) {
		if (fourAngles[i][0] && fourAngles[i][1] && fourAngles[i][2]
			&& fourAngles[i][3])
			continue;
		if (res < num[i]) {
			res = num[i];
			pos = i + 1;
		}
	}

	cout << res << " " << pos << endl;
	system("pause");
	return 0;
}