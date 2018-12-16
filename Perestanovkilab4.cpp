#include<iostream>
#include<vector>
#include<stdio.h>
#include<string>
using namespace std;
void next_set(int *a, const int size) {
	int j = size - 2;
	while (j != -1 && a[j] >= a[j + 1]) j--;
	if (j == -1) // если больше нет перестановок
		exit(0);
	int k = size - 1;
	while (a[j] >= a[k]) k--;
	swap(a[j], a[k]);
	int l = j + 1, r = size - 1;
	while (l<r)
		swap(a[l++], a[r--]);//Инверсия
}
int main() {
	int arr[10];
	std::string str;
	std::getline(std::cin, str);
	int count;
	cin >> count;
	for (int i = 0; i < str.length(); i++) {
		arr[i] = (int)(str[i]) % 48;
		if (((int)(str[i]) % 48) > 9) {
			cout << "bad input";
			exit(0);
		}
	}
	int n;
	n = str.length();
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++)
			if (arr[i] == arr[j]) {
				cout << "bad input";
				exit(0);
			}
	for (int i = 0; i < count; i++) {
		next_set(arr,n);
		for (int i = 0; i < n; i++)
			cout << arr[i];
		cout << "\n";
	}
	return 0;
}