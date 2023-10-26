#include<iostream>
#include<vector>
#include<algorithm>
#include<cstdlib>


void test_Complete_Pack() //先便利物品，再遍历背包
{
    std::vector<int> weight = {1,3,4};
    std::vector<int> value = {15,20,30};
    int bagWeight = 4;
    std::vector<int> dp(bagWeight + 1,0);

    for(int i = 0;i < weight.size();i++)
    {
        for(int j = weight[i];j <= bagWeight;j++)
        {
            auto fun = [&]->int{
                return dp[j] > dp[j - weight[i]] + value[i] ? dp[j] : dp[j - weight[i]] + value[i];
            };
            dp[j] = fun();
        }
    }
    std::cout << dp[bagWeight] << std::endl;
}

int max(int a,int b){return a > b ? a : b;}

void test1_Complete_Pack() //先遍历背包，再遍历物品
{
    std::vector<int>weight = {1,3,4};
    std::vector<int>value = {15,20,30};
    int bagWeight = 4;
    std::vector<int>dp(bagWeight + 1,0);
    
    for(int j = 0;j <= bagWeight;j++)
    {
        for(int i = 0;i < weight.size();i++)
        {
      		if(j - weight[i] >= 0)dp[j] = max(dp[j],dp[j - weight[i]] + value[i]);
        }
    }
    std::cout << dp[bagWeight] << std::endl;
}


int main()
{
    test_Complete_Pack();
    return EXIT_SUCCESS;
}
