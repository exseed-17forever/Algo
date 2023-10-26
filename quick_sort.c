#include<stdio.h>
#include<stdlib.h>
#include<time.h>

clock_t start;
clock_t end;

#define ElementType int
#define Cutoff (3)

//快排实现
void Quick_Sort(ElementType A[],int N);
ElementType Median3(ElementType A[],int Left,int Right);
void QSort(ElementType A[],int Left,int Right);
void Swap(int* a,int* b);
void insertion_sort(int* arr,int len);


void Swap(int* a,int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void insertion_sort(int* arr,int len)
{
	int i,j,tmp;
	
	for(i = 1;i < len;i++)
	{
		tmp = arr[i];
		for(j = i;j > 0 && arr[j - 1] > tmp;j--)
			arr[j] = arr[j - 1];
		arr[j] = tmp;
	}
}

void Quick_Sort(ElementType A[],int N)
{
	QSort(A,0,N - 1);
}

ElementType Median3(ElementType A[],int Left,int Right)
{
	int Center = (Left + Right) / 2;

	if(A[Left] > A[Center])
		Swap(&A[Left],&A[Center]);
	if(A[Left] > A[Right])
		Swap(&A[Left],&A[Right]);
	if(A[Center] > A[Right])
		Swap(&A[Center],&A[Right]);

	//after swap: A[Left] <= A[Center] <= A[Right]
	//三数中值分割法 找到左中右并进行排序
	
	Swap(&A[Center],&A[Right - 1]); //将枢纽元与右值的前一位进行交换
	
	return A[Right - 1]; //将枢纽元返回
}

void QSort(ElementType A[],int Left,int Right)
{
	int i,j; //用来操作左值和右值的两个角标
	ElementType Pivot; //枢纽元
	
	if(Left + Cutoff <= Right)
	{
		Pivot = Median3(A,Left,Right);
		i = Left,j = Right - 1; //right - 1在median3操作后是枢纽元的位置

		for(;;)
		{
			while(A[++i] < Pivot){}
			while(A[--j] > Pivot){}

			//暂停循环后
			if(i < j)
				Swap(&A[i],&A[j]);
			else
				break; //i > j  ij相交
		}
		Swap(&A[i],&A[Right - 1]); //将i下标的元素与pivot枢纽元交换 A[i] 一定是大于A[Right - 1]即Pivot枢纽元

		QSort(A,Left,i - 1); //现在的i是pivot的下标，i - 1是左数组的最后一位 即right位
		QSort(A,i + 1,Right); //同理 i + 1是右数组的第一位 即left位

	}
	else //do an insertion-sort on the subarray
	{
		insertion_sort(A + Left,Right - Left + 1);
	}
}

void print(int* arr,int len)
{
	for(int i = 0;i < len;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
}

void quick_sort_recursive(int arr[],int start,int end)
{
	if(start >= end)
		return;
	int mid = arr[end];
	int left = start,right = end - 1; //指向倒数第二个数组元素
	while(left < right)
	{
		while(arr[left] < mid && left < right)
			left++;
		while(arr[right] >= mid && left < right)
			right--;
		Swap(&arr[left],&arr[right]);
	}
	if(arr[left] >= arr[end])
		Swap(&arr[left],&arr[end]);
	else
		left++;
	if(left)
		quick_sort_recursive(arr,left + 1,end);
	quick_sort_recursive(arr,left + 1,end);
}

void quick_sort(int arr[],int len)
{
	quick_sort_recursive(arr,0,len - 1);
}

int main(void)
{
	int arr[] = {8,1,4,9,0,3,5,2,7,6};
	int len = sizeof(arr) / sizeof(arr[0]);
	
	printf("Before sorted: \n");
	
	print(arr,len);

	printf("After sorted: \n");
	
	start = clock();
	//insertion_sort(arr,len);
	//Quick_Sort(arr,len);
	quick_sort(arr,len);
	end = clock();
	
	print(arr,len);
	int duration = (double)(end - start) / CLOCKS_PER_SEC;
	printf("time: %d\n",duration);
	return 0;
}


