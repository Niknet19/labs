#include<iostream>
#include<string>
#include<algorithm>
#include<Windows.h>
struct students {
		std::string name;
		short math_mark;
		short biology_mark;
		short physics_mark;
	};
bool comp(const students &s1,const students &s2) {
	double sum1 = (double)((s1.biology_mark + s1.math_mark + s1.physics_mark) / 3);
	double sum2 = (double) ((s2.biology_mark + s2.math_mark + s2.physics_mark) / 3);
	return sum1 > sum2;
}
int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int count;
	std::cin >> count;
	students *a;
	a = new struct students[count];
	for (int i = 0; i < count; i++) {
		std::cin >> a[i].name;
		std::cin >> a[i].biology_mark;
		std::cin >> a[i].math_mark;
		std::cin >> a[i].physics_mark;
	}
	std::sort(a, a + count, comp);
	for (int i = 0; i < count; i++) {
		std::cout << a[i].name;
	}
	return 0;
}
