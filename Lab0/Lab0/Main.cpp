#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string>
using namespace std;
int change_to_decimal(char test[], short int i) {
	switch (test[i]) {
	case 'A':return 10;
	case 'B':return 11;
	case 'C':return 12;
	case 'D':return 13;
	case 'E':return 14;
	case 'F':return 15;
	case '0':return 0;
	case '1':return 1;
	case '2':return 2;
	case '3':return 3;
	case '4':return 4;
	case '5':return 5;
	case '6':return 6;
	case '7':return 7;
	case '8':return 8;
	case '9':return 9;
	case 'a':return 10;
	case 'b':return 11;
	case 'c':return 12;
	case 'd':return 13;
	case 'e':return 14;
	case 'f':return 15;
	default:
		printf("Bad input");
		exit(0);
	}
}
int main() {
	int b1, b2;
	scanf("%d%d", &b1, &b2);
	if (b1 > 16 || b1 < 2 || b2>16 || b2 < 2) {
		printf("Bad input");
		exit(0);
	}
	const int n = 52;
	char number[n];
	scanf("%s", number);
	int pos = -1;
	for (int i = 0; i < strlen(number); i++)
		if (number[i] == '.')pos = i;
	if ((pos == strlen(number) - 1) || (pos == 0)) {
		printf("Bad input");
		exit(0);
	}
	for (int i = 0; i < strlen(number); i++) {
		if (i == pos)continue;
		if (change_to_decimal(number, i) >= b1) {
			printf("Bad input");
			exit(0);
		}
	}
	if (b1 == b2) {
		printf("%s", number);
		exit(0);
	};
	bool f = 0;
	long long des = 0;
	if (pos == -1)
	{
		pos = strlen(number);
		f = 1;
	}
	for (int i = 0; i < strlen(number); i++) {
		if (number[i] == '.')break;
		else des = des + (change_to_decimal(number, i)*pow(b1, pos - i - 1));
	}
	double ddes = 0;
	for (int i = pos + 1; i < strlen(number); i++) {
		ddes += (change_to_decimal(number, i)*pow(b1, pos - i));
	}
	const char symbols[16] = { '0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F' };
	for (int i = 0; i < n; i++) {
		number[i] = symbols[des%b2];
		des = des / b2;
		if (des == 0) {
			number[i + 1] = '.';
			pos = i + 1;
			break;
		}
	}
	for (int i = pos + 1; i < n; i++) {
		number[i] = symbols[(int)(ddes*b2)];
		ddes = (double)(ddes*b2) - (int)(ddes*b2);
		if (ddes == 0) {
			number[i + 1] = '\0';
			break;
		}
	}
	if (f)number[strlen(number) - 2] = '\0';
	for (int i = pos - 1; i >= 0; i--)
		printf("%c", number[i]);
	for (int i = pos; i<strlen(number); i++)
		printf("%c", number[i]);
	return 0;
}