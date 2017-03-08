/********************************************************************
����
СHiʵ�������ڵĽ���һ¥��һ�������������ĺڰ壬��ͣ�����µĺ�����������
Ҳ�ᰲ����Ա���ϵĶԺ�������������������ֵ���СHiȥ�Ժ�����������

�ڰ���һ��W*H��С��������������½�Ϊֱ������ϵ�Ļ������ϴ�������i��
����ȥ�ĺ��������������½�Ϊ(x_1i, y_1i)�����Ͻ�Ϊ(x_2i, y_2i)��һ�����Ρ�

˺ȥһ�ź����ᵼ�����и��������ϵĺ�������ͬʱ˺������������Ϊ���������
�����Ǿ��д����Եģ������A����B��B����C����ô˺��C�ᵼ��A��B����˺������
����һ�ź�����Ҫ���ֶ�˺���Ļ���Ҫ���ٴ���һ����û�б������������ǣ�����A
������B���ǵ��ҽ������Ǵ����������0�Ľ�������A��B֮ǰ����������A��һ����
������B���ǵ��ҽ���������㴦�ں���B���ڲ�����

���������������ˣ�Ϊ�˽�Լʱ�䣬СHi����һ����˺�������ܶ�ĺ�������ô��
Ӧ��ѡ�����ź����أ���Ч����ͬ������£�СHi������ѡ����������ĺ�����

����
ÿ�������ļ�����������������ݡ�

ÿ��������ݵĵ�һ��Ϊ����������W��H��N���ֱ��ʾ�ڰ�Ŀ����Լ�Ŀǰ������
�ĺ���������

��������N�У�ÿ��Ϊ�ĸ�������x_1i��y_1i��x_2i��y_2i��������i�������ĺ�����

����20%�����ݣ�����1<=N<=5��1<=W,H<=10

����100%�����ݣ�����1<=N<=1000��0<=x_1i, x_2i <= W, 0<=y_1i, y_2i<=H, 1<=W,H<=108

���
����ÿ��������ݣ��������������Ans��K����ʾСHiһ�������˺�������ź�����
����ѡ��ĺ����ǵڼ��������ġ�

��������
6 7 4
0 0 4 4
1 0 3 4
1 4 4 6
0 0 3 5
�������
3 1
*********************************************************************/

#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;

const int MAX_NUM = 1000;
ll x_1[MAX_NUM], x_2[MAX_NUM], y_1[MAX_NUM], y_2[MAX_NUM];	// ���Ϻ���������
bool iscover[MAX_NUM][MAX_NUM], fourAngles[MAX_NUM][4];	// ����Ƿ񸲸ǣ��Ƿ��ĸ��Ǳ����
int num[MAX_NUM];										// �ӵ�i��������ʼ������ĺ�������
int visited[MAX_NUM];									// ����Ƿ��ѱ����ʹ�������dfs��
int N;													// �����ֵ�ĸ���

bool CheckPoint(int index, ll xpoint, ll ypoint)
// ����(xpoint, ypoint)�Ƿ��ڵ�index��������
{
	return (xpoint > x_1[index] && xpoint< x_2[index]
		&& ypoint > y_1[index] && ypoint < y_2[index]);
}

bool CheckCover(int firstindex, int secondindex)
// ����������Ƿ��и��ǵĵط�
{
	return !(x_1[firstindex] >= x_2[secondindex] ||
			x_2[firstindex] <= x_1[secondindex] ||
			y_1[firstindex] >= y_2[secondindex] ||
			y_2[firstindex] <= y_1[secondindex]);
}

void dfs(int i, int& num)
// ��i�������������������������ܸ�����δ�����ʵ��ĵ㣬�������+1
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
			//	��������ĺ������ĸ����Ƿ񱻸���
			{
				if (CheckPoint(j, x_1[i], y_1[i])) fourAngles[i][0] = 1;
				if (CheckPoint(j, x_2[i], y_1[i])) fourAngles[i][1] = 1;
				if (CheckPoint(j, x_1[i], y_2[i])) fourAngles[i][2] = 1;
				if (CheckPoint(j, x_2[i], y_2[i])) fourAngles[i][3] = 1;
			}
		}
	}
	for (int i = 0; i < N; ++i) {
		// ����ĸ��Ƕ��Ѿ������ǣ��򲻻���Ϊ��˺�ĵ�һ�ź���
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