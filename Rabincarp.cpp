#include <stdio.h>
#include<Windows.h>
#include <string.h>
#include<math.h>
#include <stdlib.h>
int pow(int i) {
	int prod = 1;
	while (i != 0) {
		prod *= 3;
		i--;
	}
	return prod;
}
long Hash(char *pattern, int length) {
	long long h = 0;
		for (int i = 0; i < length; i++)
		h +=(((unsigned int)(pattern[i])) % 3) * (pow(i));
	return h;
}
int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	const int maxpattern = 18;
	char pattern[maxpattern] = { 0 };
	char substring[maxpattern] = { 0 };
	fgets(pattern, maxpattern, stdin);
	int length = strlen(pattern) - 1;
	int Mainhash = Hash(pattern, length);
	unsigned char letter;
	int MaxP = pow(length - 1);
	fgets(substring, length + 1, stdin);
	int SubHash = Hash(substring, length);
	printf("%d ", Mainhash);
	for (int i = 0; feof(stdin) == 0; ++i) {
		if (Mainhash == SubHash) {
			for (int j = 0; j < length; j++) {
				printf("%d ", j + i + 1);
				if (pattern[j] != substring[(i + j) % length])
					break;
			}
		}
		letter = fgetc(stdin);
		SubHash = (SubHash - ((unsigned int)substring[i % length] % 3)) / 3 + ((letter % 3) * MaxP);
		substring[i % length] = letter;
	}
	return 0;
}