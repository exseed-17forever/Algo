#include<stdio.h>

//交换两个元素的值
void swap(int* a,int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

//将一个数组调整为最大堆
void heapify(int arr[],int n,int i)
{
	int largest = i; //初始化父节点为最大值
	int left = 2 * i + 1;
	int right = 2 * i + 2;
       	
	//检查左子节点是否比父节点大
	if(left < n && arr[left] > arr[largest])
		largest	= left;
	//检查右子节点是否比父节点大
	if(right < n && arr[right] > arr[largest])
		largest = right;

	//如果最大值不是父节点，则交换并递归调整堆
	if(largest != i)
	{
		swap(&arr[i],&arr[largest]);
		heapify(arr,n,largest);
	}
}

void heapSort(int arr[],int n)
{
	//构建最大堆
	for(int i = n / 2 - 1;i >= 0;i--)
	{
		heapify(arr,n,i);
	}

	//从堆顶逐个取出元素，重新构建堆
	for(int i = n - 1;i >= 0;i--)
	{
		swap(&arr[0],&arr[i]); //将最大元素放到数组末尾
		heapify(arr,i,0);		
	}
}

//按照percdown实现
void PercDown(int a[],int i,int N)
{
	int Child;
	int tmp;

	for(tmp = a[i];(2 * (i) + 1) < N;i = Child) //保证左子节点的下标不越界
	{
		Child = 2 * (i) + 1;
		
		if(Child != N - 1 && a[Child + 1] > a[Child]) //保证child不为数组最后有效值
		{
			Child++;
		}
		if(tmp < a[Child])
		{
			a[i] = a[Child];
		}
	}
	a[Child] = tmp;
}

void HeapSort(int a[],int N)
{
	int i;

	for(i = N / 2 - 1;i >= 0;i--)
	{
		PercDown(a,i,N);
	}

	for(i = N - 1;i > 0;i--)
	{
		swap(&a[0],&a[i]);
		PercDown(a,0,N);
	}
}

int main()
{
	int arr[] = {12,11,13,5,3,7};
	int len = sizeof(arr) / sizeof(arr[0]);
	
	printf("Unsorted array: \n");
	for(int i = 0;i < len;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");

	printf("After sorted array: \n");
	heapSort(arr,len);

	for(int i = 0;i < len;i++)
	{
		printf("%d ",arr[i]);
	}
	printf("\n");

	return 0;
}






