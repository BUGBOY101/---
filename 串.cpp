#define	_CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//串的堆分配存储表示
typedef struct {
	char* ch;//串的初始位置
	int length;//串的长度
}HString;
//串的初始化
void InitString(HString &S) {
	S.length = 0;
	S.ch = NULL;
}
void StringAssign(HString&T , char* ch1) {//生成一个其值等于串常量ch的串T
	int i = 0, l = 0;
	if (T.ch)
		free(T.ch);//释放T原有空间
	l = strlen(ch1);
	if (l == 0) {
		T.ch = NULL;
		T.length = 0;
	}
	else {
		if (!(T.ch = (char*)malloc(sizeof(char) * l))) {
			cout << "内存分配失败" << endl;
			return;
		}
		for (i = 0; i < l; i++) {
			T.ch[i] = ch1[i];
		}
		T.length = l;
	}
}
//返回串的长度
int StrLength(HString T) {
	return T.length;
}
//串的比较
int StrCompare(HString S, HString T) {
	//若S>T,则返回值>0，若S=T,则返回值=0，若S<T,则返回值<0;
	for (int i = 0; i < S.length && i < T.length; i++) {
		if (S.ch[i] != T.ch[i])
			return S.ch[i] - T.ch[i];
	}
	return S.length - T.length;
}
//求串的子串
void SubString(HString& T, HString S, int i, int len) {
	//用T返回串S的第i个字符起长度为len的子串
	if (T.ch)
		free(T.ch);
	if (i<1 || i>S.length || len<0 || len>S.length - i + 1) {
		cout << "输入错误，无法返回子串" << endl;
		return;
	}
	if (!len) {
		T.ch = NULL;
		T.length = 0;
	}
	else {
		if (!(T.ch = (char*)malloc(len * sizeof(char)))) {
			cout << "内存分配失败" << endl;
			return;
		}
		for (int j = 0; j < len; j++) {
			T.ch[j] = S.ch[i - 1 + j];
		}
		T.length = len;
	}
}

//串的连接操作:用T返回由S1和S2连接的新串
void Concat(HString S1, HString S2, HString& T) {
	if (T.ch)
		free(T.ch);
	if (!(T.ch = (char*)malloc((S1.length + S2.length) * sizeof(char)))) {
		cout << "内存分配失败" << endl;
		return;
	}
	int i = 0;
	T.length = S1.length + S2.length;
	for (i = 0; i <S1.length; i++) {
		T.ch[i] = S1.ch[i];
	}
	for (i=0; i < S2.length; i++) {
		T.ch[i+S1.length] = S2.ch[i];
	}
	T.ch[T.length] = '\0';
}

//在一个串中删除一个子串
void DeleteString(HString& S,int i,int len) {
	//在串S中删除起始位置为i，长度为len的子串
	if (i<1 || i>S.length || len<0 || len>S.length - i + 1) {
		cout << "输入错误，删除操作不合理" << endl;
		return;
	}
	for (int j = i - 1 + len; j < S.length; j++) {
		//将i-1+len后的元素前移len位
		S.ch[j - len] = S.ch[j];
	}
	S.length -= len;
}

//串的定位
//返回子串T在主串S中第pos个字符之后的位置((下标)，若不存在，则函数值为0
int Index_BF(HString S, HString T, int pos) {
	int i = pos-1, j = 0;
	while (i < S.length && j < T.length) {
		if (S.ch[i] == T.ch[j]) {//主串和子串依次匹配下一个字符
			i++; 
			j++;
		}
		else {//主串和子串指针回溯重新开始下一次匹配
			i = i - j + 1;
			j = 0;
		}
	}
	if (j >= T.length)
		return i - T.length;//返回匹配的第一个字符的下标
	else
		return 0;
}

//打印串
void print(HString S) {
	int i = 0;
	for (i = 0; i < S.length; i++) {
		cout << S.ch[i];
	}
	cout << endl;
}

int main() {
	HString S, T, N;
	InitString(S);
	InitString(T);
	InitString(N);
	char ch1[1000];
	char ch2[1000];
	cout << "*************************************************************************************" << endl;
	cout << "1.串的创建 2.求串长 3.串的比较 4.串的子串 5.两串连接 6.删除子串 7.串的定位 8.退出程序" << endl;
	cout << "*************************************************************************************" << endl;
	while (1) {
		int input;
		cout << "请输入您需要的操作指令：";
		cin >> input;
		getchar();
		switch (input) {
		case 1: {
			cout << "请输入创建串中的元素：";
			gets_s(ch1);
			StringAssign(T,ch1);
			cout << "打印串的内容：";
			print(T);
			break;
		}
		case 2: {
			cout << "请输入您需要进行获取串长操作的串：";
			gets_s(ch1);
			StringAssign(T, ch1);
			cout << "串长为：" << StrLength(T) << endl;
			break;
		}
		case 3: {
			cout << "进行串S和串T的比较：(若S>T,则返回值>0，若S=T,则返回值=0，若S<T,则返回值<0)" << endl;
			cout << "创建串S：";
			gets_s(ch1);
			StringAssign(S, ch1);
			cout << "创建串T：";
			gets_s(ch2);
			StringAssign(T, ch2);
			cout << "比较结果：";
			cout << StrCompare(S, T) << endl;
			break;
		}
		case 4: {
			int i, len;
			cout << "用T返回串S的第i个字符起长度为len的子串" << endl;
			cout << "创建串S：";
			gets_s(ch1);
			StringAssign(S, ch1);
			cout << "请输入起始位置i：";
			cin >> i;
			cout << "请输入要获取的子串长度：";
			cin >> len;
			SubString(T,S, i, len);
			cout << "获取的子串为：";
			print(T);
			break;
		}
		case 5: {
			cout << "串的连接操作:用N返回由S和T连接的新串" << endl;
			cout << "请输入串S：";
			gets_s(ch1);
			StringAssign(S, ch1);
			cout << "请输入串T：";
			gets_s(ch2);
			StringAssign(T, ch2);
			Concat(S, T, N);
			cout << "两串连接后串N:";
			print(N);
			break;
		case 6: {
			int i, len;
			cout << "在串S中删除起始位置为i，长度为len的子串" << endl;
			cout << "请输入串S：";
			gets_s(ch1);
			StringAssign(S, ch1);
			cout << "请输入删除起始位置i:";
			cin >> i;
			cout << "请输入删除字串长度len:";
			cin >> len;
			DeleteString(S, i, len);
			cout << "删除后串S:";
			print(S);
			break;
		}
		case 7: {
			cout << "串的定位：返回子串T在主串S中第pos个字符之后的位置，若不存在，则函数值为0" << endl;
			int pos;
			cout << "请输入查找的起始位置pos:";
			cin >> pos;
			getchar();//吸收掉在缓存区的回车
			cout << "请输入主串S：";
			gets_s(ch1);
			StringAssign(S, ch1);
			cout << "请输入子串T：";
			gets_s(ch2);
			StringAssign(T, ch2);
			cout << "子串T在主串S的位置下标为：" << Index_BF(S, T, pos) << endl;
			break;
		}
		case 8: {
			cout << "退出程序" << endl;
			exit(-1);
		}
		default: {
			cout << "输入错误" << endl;
			break;
		}
		}
		}
	}
}

