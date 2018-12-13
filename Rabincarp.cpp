#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXPAT 18
int power(int i) {
	int prod = 1;
	while (i != 0) {
		prod *= 3;
		i--;
	}
	return prod;
}
long Hash(char *pattern, int length) {
	long h = 0;
	for (int i = 0; i < length; i++)
		h += (pattern[i] % 3) * (power(i));
	return h;
}
int main() {
	char pattern[MAXPAT] = { 0 };
	char substring[MAXPAT] = { 0 };
	fgets(pattern, MAXPAT, stdin);
	int length = strlen(pattern) - 1;
	int Mainhash = Hash(pattern, length);
	unsigned char letter;
	int MaxP = power(length - 1);
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
		SubHash = (SubHash - (substring[i % length] % 3)) / 3 + ((letter % 3) * MaxP);
		substring[i % length] = letter;
	}
	return 0;
}