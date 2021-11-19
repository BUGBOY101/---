#define	_CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
int main()
{
	int n;
	char ch[1000], ch2[1000];
	while (cin >> n) {
		getchar();
		while (n--) {
			gets_s(ch);
			cout << ch << endl;
			gets_s(ch2);
			cout << ch2 << endl;
		}
	}
	
}