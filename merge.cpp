#include<iostream>
#include<cstdlib>

void print(int* arr,int len)
{
    int i;
    for(i = 0;i < len;i++)
        printf("%d ",arr[i]);
    printf("\n");
}

void merge(int arr[],int left,int middle,int right)
{
    int n1 = middle - left + 1; //左边界
    int n2 = right - middle; //右边界

    //创建临时数组来存储左右子数组
    int* L = new int[n1 * sizeof(int)];
    int* R = new int[n2 * sizeof(int)];

    //将数据复制到临时数组
    for(int i = 0;i < n1;i++)
    {
        L[i] = arr[left + i];
    }

    for(int j = 0;j < n2;j++)
    {
        R[j] = arr[middle + 1 + j];
    }

    //合并临时数组为一个有序数组
    int i = 0,j = 0,k = left;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[i])
        {
            arr[k] = L[i];
            i++;
        }
        else{
            arr[k] = R[j];
            j++;
        }
        k++;
        //arr[k++] = L[i++];
        //arr[k++] = R[j++];
    }

    //处理剩余的元素
    while(i < n1)
        arr[k++] = L[i++];
    while(j < n2)
        arr[k++] = R[j++];
    
    //释放临时数组内存
    delete[] L;
    delete[] R;
    
}

void mergeSort(int arr[],int left,int right)
{
    if(left < right)
    {
        int middle = left + (right - left) / 2;

        //递归地排列左右子数组
        mergeSort(arr,left,middle);
        mergeSort(arr,middle + 1,right);

        //合并两个排好序的子数组
        merge(arr,left,middle,right);
    }
}

int min(int a,int b)
{return a < b ? a : b;}

int main()
{
    int arr[] = {12,11,13,5,6,7};
    int n = sizeof(arr) / sizeof(arr[0]);

    std::cout << "Unsorted Array: " << std::endl;
    print(arr,n);
    
    mergeSort(arr,0,n - 1);
    std::cout << "After sorted: " << std::endl;
    print(arr,n);
    return EXIT_SUCCESS;
}