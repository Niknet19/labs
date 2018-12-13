#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
#include<Windows.h>
using namespace std;
ifstream fin("in.txt");
ofstream fout("out.txt");
std::string stroka;
int table[256];
std::string shablon;
int main() {
	getline(fin, shablon);
	getline(fin, stroka,'.');
	int M = shablon.size();
	int N = stroka.size();
	bool f = 1;
	if ((M==0)||(N==0))
		f = 0;
	for (int i = 0; i < 256; i++)
		table[i] = shablon.length();
	for (int i = 0; i < M - 1; i++)
		table[(int)((unsigned char)shablon[i])] = M - i - 1;
	int i = M - 1;
	do {
		int j = M - 1;
		int k = i;
		while ((f)&&(j >= 0) && (stroka[k] == shablon[j])) {
			fout << k + 1 << " ";
			k--;
			j--;
		}
		if((j>=0)&&(f))fout << k+1<<" ";
		i += table[(int)((unsigned char)stroka[i])];
	} while (i < N);
	fin.close();
	fout.close();
	return 0;
}