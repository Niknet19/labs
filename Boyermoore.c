#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSHABLON 17
void table(unsigned char shablon[MAXSHABLON], int *sdvig) {
	if (strlen(shablon) == 1)
		for (int i = 0; i < 256; i++)
			sdvig[i] = 1;
	else {
		for (int i = 0; i < 256; i++)
			sdvig[i] = strlen(shablon);
		for (int i = 0; i <= strlen(shablon) - 2; i++)
			sdvig[shablon[i]] = strlen(shablon) - i - 1;
	}
}

int algorithm(unsigned char shablon[MAXSHABLON], unsigned char substring[MAXSHABLON], int blink, int *sdvig) {
	int l = strlen(shablon), j = 0, shift = 0;
	j = l;
	if (substring[j - 1] != shablon[j - 1])
		printf("%d ", j + blink);
	else
		while ((j != 0) && (substring[j - 1] == shablon[j - 1])) {
			printf("%d ", j + blink);
			j--;
			if ((j != 0) && (substring[j - 1] != shablon[j - 1]))
					printf("%d ", j + blink);
		}
	shift = sdvig[substring[l - 1]];
	return shift;
}

int main()
{
	unsigned char  shablon[MAXSHABLON] = { 0 }, input[MAXSHABLON] = { 0 };
	int blink = 0, sdvig[256] = { 0 }, shift = 0;
	gets(shablon);
	table(shablon, sdvig);
	fgets(input, strlen(shablon) + 1, stdin);
	if (strlen(shablon) == strlen(input)) {
		shift = algorithm(shablon, input, blink, sdvig);
		blink += shift;
		memmove(input, input + shift, strlen(input) - shift);
		while (1) {
			fgets(input + (strlen(input) - shift), shift + 1, stdin);
			if (!feof(stdin)) {
				shift = algorithm(shablon, input, blink, sdvig);
				blink += shift;
					memmove(input, input + shift, strlen(input) - shift);
			}
			else
				exit(0);
		}
	}
	return 0;
}