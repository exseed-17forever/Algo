#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MaxDegree 5

clock_t start,stop;

//定义一个用数组实现的adt结构体
typedef struct Po
{
	int CoeffArray[MaxDegree + 1];
	int HighPower;
}*Polynomial;

void ZeroPolynomial(Polynomial Poly)
{
	int i;

	for(i = 0;i <= MaxDegree;i++)
		Poly->CoeffArray[i] = 0;
	Poly->HighPower = 0;
}//将多项式初始化为0的过程

int Max(int a,int b)
{
	return a > b ? a : b;
}

void AddPolynomial(const Polynomial Poly1,
		const Polynomial Poly2,Polynomial PolySum)
{
	int i;

	ZeroPolynomial(PolySum);
	PolySum->HighPower = Max(Poly1->HighPower,
				Poly2->HighPower);
	
	for(i = PolySum->HighPower;i >= 0;i--)
		PolySum->CoeffArray[i] = Poly1->CoeffArray[i]
					+ Poly2->CoeffArray[i];
}

void MultPolynomial(const Polynomial Poly1,const Polynomial Poly2,Polynomial PolyProd)
{
	int i,j;

	ZeroPolynomial(PolyProd);
	PolyProd->HighPower = Poly1->HighPower + Poly2->HighPower;

	if(PolyProd->HighPower > MaxDegree)
	{	
		printf("Exceeded array size");
		return;
	}
	else
	{
		for(i = 0;i <= Poly1->HighPower;i++)
		{
			for(j = 0;j <= Poly2->HighPower;j++)
			{
				PolyProd->CoeffArray[i + j] = 
					Poly1->CoeffArray[i] * 
					Poly2->CoeffArray[j];
			}
		}
	}
}

int main()
{
	#if defined(_WIN16) || defined(_WIN32) || defined(_WIN64)
	//system("chop 65501");
	#endif
	

	start = clock();
	Polynomial p1 = malloc(sizeof(struct Po));
	Polynomial p2 = malloc(sizeof(struct Po));
	Polynomial sum = malloc(sizeof(struct Po));

	ZeroPolynomial(p1);
	ZeroPolynomial(p2);
	
	
	p1->HighPower = 1;
	p2->HighPower = 2;

	p1->CoeffArray[0] = 1;
	p2->CoeffArray[0] = 3;
	AddPolynomial(p1,p2,sum);
		
	stop = clock();

	double duration = ((double)(stop - start)) / CLK_TCK; //CLK_TCK为机器时钟每秒所走的时钟打点数
	
	printf("当前程序执行所消耗的时间为：%f\n",duration);
	return EXIT_SUCCESS;

}
