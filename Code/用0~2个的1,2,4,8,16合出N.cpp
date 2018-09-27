// ConsoleApplication1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include<iostream>
#include<math.h>
#include<time.h>
#include<set>
using namespace std;
int nums[63];//num[i]��ʾ2^i�ĸ�����ֻ��0,1,2����ȡֵ
			 //���ݷ�
int IsOk(long long n, int *nums, int len)
{
	long long sum = 0;
	for (int i = 0; i < len; i++)
		sum += nums[i] * pow(2, i);
	if (sum == n)
		return 0;
	else if (sum > n)
		return -1;
	else
		return 1;
}
void solve(long long n, int index, int *nums, int len, int &count)
{
	if (index >= len)
		return;
	for (int i = 0; i <= 2; i++)
	{
		nums[index] = i;
		if (IsOk(n, nums, len) == 0)
			count++;
		else if (IsOk(n, nums, len) == 1)
			solve(n, index + 1, nums, len, count);
	}
	nums[index] = 0;//���ݷ���Ҫ������һ���ļ���
}


long long DP(long long n)//ʹ�ö�̬�滮����
{
	int len = log(n) / log(2) + 1;
	long long **dp = new long long*[n + 1];
	for (long long i = 0; i <= n; i++)
	{
		dp[i] = new long long[len];
	}
	//long long dp[5][3] = { 0 };
	for (int i = 0; i < len; i++)
		for (long long j = 0; j <= n; j++)
			dp[j][i] = 0;

	//dp[n][i]��ʾʹ��1��1��2��2��4��4��...��2^i������ϳ�n�ķ�����
	for (int i = 0; i < len; i++)
		dp[0][i] = 1;
	if (n == 1 || n == 2)
		return n;
	dp[1][0] = 1;
	dp[2][0] = 1;
	for (int i = 3; i <= n; i++)
		dp[i][0] = 0;

	//dp[n][i]=
	//  cout << "len=" << len << endl;
	for (int i = 1; i < len; i++) 
	{
		for (long long j = 1; j <= n; j++)
		{
			for (int m = 0; m <= 2; m++)
				if (j - pow(2, i)*m >= 0)
				{
					dp[j][i] = dp[j][i] + dp[(long long)(j - pow(2, i)*m)][i - 1];
					//cout <<"j="<< j << " " << "i=" << i << " " << "m=" << m<<" "<< dp[j][i]<<endl;
				}
		}
	}
	return dp[n][len - 1];
}

int solve3(long long n)
{
	long long stop = n / 2;
	long long res = 0;
	set<int> myset;
	/*
	��Ӳ�ҷ�Ϊ���ݣ�1��2��4��8��16��.....��1��2��4��8��16....
	���������ֵΪa,b���������֣����ǵĺ���a+b=n;
	a��ÿһ����ֻ������һ����Ϸ�ʽ�������Ƶ�˼�룩
	*/
	for (int i = 1; i <= stop; i++)
	{
		res = i ^ (n - i);
		myset.insert(res);
	}
	//����1,2,4,8����ټ�1.
	int len = log(n) / log(2) + 1;
	if (pow(2, len - 1) == n)
		return myset.size() + 1;

	return myset.size();
}


int main()
{
	for (int i = 0; i < 63; i++)
		nums[i] = 0;
	long long n;
	clock_t start, finish;
	while (true)
	{
		cin >> n;
		if (n < 1)
		{
			return 0;
		}
		int len = log(n) / log(2) + 1;
		int count = 0;
		start = clock();
		solve(n, 0, nums, len, count);
		cout << count << endl;
		finish = clock();
		cout << "���ݷ��ķ�ʱ��Ϊ" << (double)(finish - start) / CLOCKS_PER_SEC << "��" << endl;
		//
		//
		start = clock();
		long long res = DP(n);
		cout << res << endl;
		finish = clock();
		cout << "��̬�滮�����ķ�ʱ��Ϊ" << (double)(finish - start) / CLOCKS_PER_SEC << "��" << endl;

		start = clock();
		res = solve3(n);
		cout << res << endl;
		finish = clock();
		cout << "�����ַ����ķ�ʱ��Ϊ" << (double)(finish - start) / CLOCKS_PER_SEC << "��" << endl;
	}

	return 0;
}