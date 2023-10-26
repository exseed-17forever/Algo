#include<stdio.h>

int
MaxSubsequenceSum3(const int A[],int N)
{
	int ThisSum,MaxSum,i,j,k;

	MaxSum = 0;
	for(i = 0;i < N;i++)
		for(j = i;j < N;j++)
		{
			ThisSum = 0;
			for(k = i;k <= j;k++)
				ThisSum += A[k];
			if(ThisSum > MaxSum)
				MaxSum = ThisSum;
		}
	return MaxSum;
}
int
MaxSubsequenceSum2(const int A[],int N)
{
	int ThisSum,MaxSum,i,j;
	for(i = 0;i < N;i++)
	{
		ThisSum = 0;
		for(j = i;j < N;j++)
		{
			ThisSum += A[j];
			if(ThisSum > MaxSum)
				MaxSum = ThisSum;
		}
	}
	return MaxSum;
}
int Max3(int leftsum,int rightsum,int sum)
{
	int max = 0;
	max = leftsum > rightsum ? leftsum : rightsum;
	max = max > sum ? max : sum;
	return max;
}

static int
MaxSubSum(const int A[],int left,int right)
{
	int MaxLeftSum,MaxRightSum; //divide-and-sum
	int MaxLeftBorderSum,MaxRightBorderSum;
	int LeftBorderSum,RightBorderSum;
	int Center,i;
	
	if(left == right) //base case
	{
		if(A[left] > 0)
			return A[left];
		else
			return 0;
	}
	Center = (left + right) / 2;
	MaxLeftSum = MaxSubSum(A,left,Center);
	MaxRightSum = MaxSubSum(A,Center,right); //2T(N/2)个时间单元
	
	MaxLeftBorderSum = 0;LeftBorderSum = 0;
	for(i = Center;i >= left;i--)
	{
		LeftBorderSum += A[i];
		if(LeftBorderSum > MaxLeftBorderSum)
			MaxLeftBorderSum = LeftBorderSum;

	}

	MaxRightBorderSum = 0;RightBorderSum = 0;
	for(i = Center + 1;i <= right;i++)
	{
		RightBorderSum +=A[i];
		if(RightBorderSum > MaxRightBorderSum)
			MaxRightBorderSum = RightBorderSum;
	}

	return Max3(MaxLeftSum,MaxRightSum,MaxLeftBorderSum + MaxRightBorderSum);

}
int
MaxSubsequenceSum(const int A[],int N)
{
	return MaxSubSum(A,0,N - 1);
}

int MaxSubsequenceSum4(const int A[],int N)
{
	int ThisSum,MaxSum,j;
	ThisSum = MaxSum = 0;
	for(j = 0;j < N;j++)
	{
		ThisSum +=A[j];
		if(ThisSum > MaxSum)
			MaxSum = ThisSum;
		else if(ThisSum < 0) //如果序列相加小于0则不可能产生最大序列和
			ThisSum = 0;
	}
	return MaxSum;
}

int main()
{
	int maxSum;
	int sequence[8] = {4,-3,5,-2,-1,2,6,-2};
	maxSum = MaxSubsequenceSum4(sequence,8);
	printf("maxsum = %d\n",maxSum);
	return 0;
}
