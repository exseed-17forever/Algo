#include<stdio.h>
#include<stdlib.h>

void print(int* arr,int len)
{
	int i;
	for(i = 0;i < len;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");
}

void merge(int arr[],int left,int middle,int right)
{
	int n1 = middle - left + 1; //middle - left + 1是左边界
	int n2 = right - middle; //right - middle 是右边界

	//创建临时数组来存储左右子数组
	int* L = (int*)malloc(n1 * sizeof(int));
	int* R = (int*)malloc(n2 * sizeof(int));

	//将数据复制到临时数组
	for(int i = 0;i < n1;i++)
	{
		L[i] = arr[left + i]; //
	}
	for(int j = 0;j < n2;j++)
	{
		R[j] = arr[middle + 1 + j];
	}

	//合并临时数组为一个有序数组
	int i = 0,j = 0,k = left;
	
	while(i < n1 && j < n2)
	{
		if(L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
		//arr[k++] = L[i++];
		//arr[k++] = R[j++];
	}

	//处理剩余的元素
	while(i < n1)
	{
		arr[k++] = L[i++];
	}
	while(j < n2)
	{
		arr[k++] = R[j++];
	}

	//释放临时数组的内存
	free(L);
	free(R);
}

void mergeSort(int arr[],int left,int right)
{
	if(left < right)
	{
		int middle = left + (right - left) / 2;
		
		//递归地排序左右子数组
		mergeSort(arr,left,middle);
		mergeSort(arr,middle + 1,right);

		//合并两个排序好的子数组
		merge(arr,left,middle,right);
	}	
} 

int min(int a,int b)
{
	return a < b ? a : b;
}

void merge_sort(int* arr,int len)
{
	int* a = arr;
	int* b = (int*)malloc(sizeof(int) * len);

	int seg,start;
	for(seg = 1;seg < len;seg += seg)
	{
		for(start = 0;start < len;start += seg + seg)
		{
			int low = start,mid = min(start + seg,len),high = min(start + seg + seg,len);
			int k = start;
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
		a = b; //a指向已经排好列的数组
		b = temp; //b指向arr b = temp = arr
	}
	if(a != arr)
	{
		int i;
		for(i = 0;i < len;i++)
		{
			b[i] = a[i]; //修改arr里面的值
		}
		b = a; //改变指向
	}
	free(b);
}

void MSort(int* A,int* TmpArray,int left,int right);

//另一种递归实现merge方法
void Merge_sort(int* A,int N)
{
	int* TmpArray = (int*)malloc(sizeof(int) * N);
	
	if(TmpArray != NULL)
	{
		MSort(A,TmpArray,0,N - 1);
		free(TmpArray); //申请空间不要忘记释放空间
	}
	else
	{
		printf("Out of space!\n");
		exit(0);
	}
}

void Merge(int* A,int* TmpArray,int Lpos,int Rpos,int RightEnd);

void MSort(int* A,int* TmpArray,int left,int right)
{
	int Center = (left + right) / 2; //center = left + (right - left) / 2;
	
	if(left < right)
	{
		MSort(A,TmpArray,left,Center);
		MSort(A,TmpArray,Center + 1,right);
		Merge(A,TmpArray,left,Center + 1,right);
	}	
}

void Merge(int* A,int* TmpArray,int Lpos,int Rpos,int RightEnd)
{
	int LeftEnd,TmpPos,NumElements;

	LeftEnd = Rpos - 1;
	TmpPos = Lpos;
	NumElements = RightEnd - Lpos + 1; //rightend是原数组的最后一个下标，所以要+1
	
	//main loop
	while(Lpos <= LeftEnd && Rpos <= RightEnd)
		TmpArray[TmpPos++] = A[Lpos] < A[Rpos] ? A[Lpos++] : A[Rpos++];
	while(Lpos <= LeftEnd)
		TmpArray[TmpPos++] = A[Lpos++];
	while(Rpos <= RightEnd)
		TmpArray[TmpPos++] = A[Rpos++];
	
	//copy tmparray back
	for(int i = 0;i < NumElements;i++,RightEnd--)
		A[RightEnd] = TmpArray[RightEnd];
	//A[RightEnd--] = TmpArray[RightEnd--];
}

int main()
{
	int arr[] = {12,11,13,5,6,7};
	int n = sizeof(arr) /sizeof(arr[0]);

	printf("Unsorted array: \n");
	print(arr,n);
	
	//mergeSort(arr,0,n - 1);
	//merge_sort(arr,n);
	
	Merge_sort(arr,n);
	printf("After sorted: \n");
	print(arr,n);
	return EXIT_SUCCESS;
}

