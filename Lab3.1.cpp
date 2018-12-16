#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
void sift_down(int i,long int heapSize,long int list[])
	{
		int leftChild;
		int rightChild;
		int largestChild;
		for (;;)
		{
			leftChild = 2 * i + 1;
			rightChild = 2 * i + 2;
			largestChild = i;

			if (leftChild < heapSize && list[leftChild] > list[largestChild])
			{
				largestChild = leftChild;
			}
			if (rightChild < heapSize && list[rightChild] > list[largestChild])
			{
				largestChild = rightChild;
			}
			if (largestChild == i)
			{
				break;
			}
			swap(list[i], list[largestChild]);
			i = largestChild;
		}
	}
void buildheap(long int heapSize,long int list[]) {
		for (int i = heapSize / 2; i >= 0; i--)
		{
			sift_down(i,heapSize,list);
		}
	}
int main() {
	long int *H;
	long int size;	
	cin >> size;
	const long int size_h = size;
	//H = (int*)malloc(n*sizeof(int));
	H = new long int[size];
	for (long int i = 0; i < size; i++)
		scanf("%ld",&H[i]);
	buildheap(size,H);
	for (long int i = size - 1; i >= 0; i--) {
		swap(H[0], H[i]);
		size = size - 1;
		sift_down(0,size,H);
	}
	for (long i = 0; i < size_h; i++)
		printf("%ld ",H[i]);
	delete[]H;
	return 0;
}