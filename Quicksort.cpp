#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h> 
#include <malloc.h>
#include<iostream>
void myswap(int *x, int *y) {
	int t = *x;
	*x = *y;
	*y = t;
}
void q_sort(int *a, int begin, int end)
{
	int temp;
	int left = begin, right = end;
	int mid = a[(right + left) / 2];
	do
	{
		while (a[right] > mid)
			right--;
		while (a[left] < mid)
			left++;
		if (left <= right)
		{
			myswap(&a[left], &a[right]);
			left++;
			right--;
		}
	} while (left < right);
	if (begin < right)
		q_sort(a, begin, right);
	if (left < end)
		q_sort(a, left, end);
}
int main()
{
	int *a;
	int n;
	scanf("%d", &n);
	a = (int*)malloc(n * sizeof(int));//Динамически выделяет память для массива
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	q_sort(a, 0, n - 1);
	for (int i = 0; i < n; i++)
		printf("%d ", a[i]);
	return 0;
}