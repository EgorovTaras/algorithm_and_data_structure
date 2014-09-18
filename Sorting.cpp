#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

void BublSort(int[],int);
void InsSort(int a[], int n);
void Hoare(int a[], int L, int R);

int main()
{
	srand(time(NULL));
	int n;
	cout << "Input please amount  elements:"; cin >> n;
	cout << "Pleas wait."<<endl;
	int *a = new int[n], *pTemp = new int[n];;
	for (int i = 0; i < n; i++)a[i]= rand();
	
	cout << "Bubl sorting." << endl;
	for (int i = 0; i < n; i++)pTemp[i] = a[i];
	float startBSort=clock();
	BublSort(pTemp,n);
	float finishBSort = clock();

	cout << "InsSotr." << endl;
	for (int i = 0; i < n; i++)pTemp[i] = a[i];
	float startISort = clock();
	InsSort(pTemp, n);
	float finishISort = clock();
	delete pTemp;

	cout << "Hoare Sorting." << endl;
	int z=100;
	int **pH = new int *[z];
	for (int i = 0; i < z; i++)
	{
		pH[i] = new int[n];
		for (int j = 0; j < n; j++)
			pH[i][j] = a[j];
	}

	float startHoare = clock();
	for (int i = 0; i < z;i++)Hoare(pH[i], 0, n - 1);
	float finishHoare = clock();
	for (int i = 0; i < z;i++)delete pH[i];
	delete pH;

	delete a;
	cout << "Time work sortings:" << endl
		<< "Bublsort:" << (finishBSort - startBSort)/1000  <<"sec."<< endl
		<< "InsSort:" << (finishISort - startISort)/1000  <<"sec."<< endl
		<< "Hoare:" << (finishHoare - startHoare)/(1000*z)  <<"sec."<< endl;
	_getch();
	return 0;
}


void BublSort(int a[],int n) //Сортировка вставками обменами
{
	for (int i = n-1; i > 0; i--)
	for (int j = 0; j < i; j++)
		if (a[j]>a[j+1])
		{
			int temp = a[j];
			a[j] = a[j + 1];
			a[j + 1] = temp;
		}
		
}

void InsSort(int a[], int n)//Вставками
{
	for (int i = 1; i < n; i++)
		if (a[i] < a[i - 1])
		{
			int k = i, l = 0, r = i - 1,j=(l+r)/2;
			while (l != r)
			{
				if (a[k]>a[j])
					l = j + 1;
				else r = j;
				j = (l + r) / 2;
			}
			int temp = a[k];
			for (; k > j; k--)
			{
				a[k] = a[k - 1];
			}
			a[j] = temp;
		}
}

void Hoare(int a[], int L, int R)//сортировка методом Хоаре
{
	int M = (L + R) / 2,first=L,last=R;
	while (a[first] < a[M] || a[first] == a[M] && first != M)first++;
	while (a[last]>a[M] || a[last] == a[M] && last != M)last--;
	while (first != last)
	{
		if (first == M)M = last;
		else if (last == M)M = first;
		int temp = a[first];
		a[first] = a[last];
		a[last] = temp;
		while (a[first] < a[M] || a[first] == a[M] && first != M)first++;
		while (a[last]>a[M] || a[last] == a[M] && last != M)last--;
	}
	if (M - L>1)Hoare(a, L, M-1);
	if (R - M > 1)Hoare(a, M + 1, R);
}