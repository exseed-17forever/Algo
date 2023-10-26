#include<stdio.h>
#include<stdlib.h>
#define ElementType int
#define NotFound -1

int BinarySearch(const ElementType A[],ElementType X,int N)
{
	int Low,Mid,High;

	Low = 0;High = N - 1;

	while(Low <= High)
	{
		Mid = (Low + High) / 2;
		if(A[Mid] < X)
			Low = Mid + 1;
		else if(A[Mid] > X)
			High = Mid - 1;
		else 
			return Mid;
	}
	return NotFound;
}

int min(int x,int y)
{
	return x < y ? x : y; 
}

void Merge_sort(int arr[],int len)
{
	int* a = arr;
	int* b = (int*)malloc(len * sizeof(*arr));
	int seg,start;
	for(seg = 1;seg < len;seg += seg)
	{
		for(start = 0;start < len;start += seg + seg)
		{
			int low = start,mid = min(start + seg,len),high = min(start + seg + seg,len);
			int k = low;
			int start1 = low,end1 = mid;
			int start2 = mid,end2 = high;
			while(start1 < end1 && start2 < end2)
				b[k++] = a[start1] < a[start2] ? a[start1++] : a[start2++];
			while(start1 < end1)
				b[k++] = a[start1++];
			while(start2 < end2)
				b[k++] = a[start2++];
		}
		int* temp = a;
		a = b;
		b = temp;
	}
	if(a != arr)
	{
		int i;
		for(i = 0;i < len;i++)
			b[i] = a[i];
		b = a;
	}
	free(b);
}

int print(int arr[],int len)
{
	int i;
	for(i = 0;i < len;i++)
		printf("%d  ",arr[i]);
}

int main(int argc,char* argv[])
{
	printf("%d ",argc);

	int a[] = {32,25,67,43,18,80,56,49};
	int len = sizeof(a) / sizeof(a[0]);
	Merge_sort(a,len);
	int p = BinarySearch(a,67,len);
	print(a,len);	
	printf("\n找到啦，在数组下标:%d处\n",p);
}

