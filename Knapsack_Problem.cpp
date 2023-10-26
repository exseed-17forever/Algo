#include<iostream>
#include<vector>
#include<algorithm>	
void test_2_wei_bag_problem()
{
	std::vector<int> weight = {1,3,4};
	std::vector<int> value = {15,20,30};
	int bagweight = 4;

	//二维数组
	std::vector<std::vector<int>> dp(weight.size(),std::vector<int>(bagweight + 1,0));

	//初始化
	for(int j = weight[0];j <= bagweight;j++)
	{
		dp[0][j] = value[0];
	}

	//weight数组的大小，就是物品个数
	for(int i = 1;i < weight.size();i++)
	{
		for(int j = 0;j <= bagweight;j++)
		{
			if(j < weight[i]) dp[i][j] = dp[i - 1][j];
			else dp[i][j] = std::max(dp[i - 1][j],dp[i - 1][j - weight[i]] + value[i]);
		}
	}
	std::cout << dp[weight.size() - 1][bagweight] << std::endl;
}

int main()
{
	test_2_wei_bag_problem();
	return 0;
}
