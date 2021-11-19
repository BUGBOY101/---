#define	_CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
//���Ķѷ���洢��ʾ
typedef struct {
	char* ch;//���ĳ�ʼλ��
	int length;//���ĳ���
}HString;
//���ĳ�ʼ��
void InitString(HString &S) {
	S.length = 0;
	S.ch = NULL;
}
void StringAssign(HString&T , char* ch1) {//����һ����ֵ���ڴ�����ch�Ĵ�T
	int i = 0, l = 0;
	if (T.ch)
		free(T.ch);//�ͷ�Tԭ�пռ�
	l = strlen(ch1);
	if (l == 0) {
		T.ch = NULL;
		T.length = 0;
	}
	else {
		if (!(T.ch = (char*)malloc(sizeof(char) * l))) {
			cout << "�ڴ����ʧ��" << endl;
			return;
		}
		for (i = 0; i < l; i++) {
			T.ch[i] = ch1[i];
		}
		T.length = l;
	}
}
//���ش��ĳ���
int StrLength(HString T) {
	return T.length;
}
//���ıȽ�
int StrCompare(HString S, HString T) {
	//��S>T,�򷵻�ֵ>0����S=T,�򷵻�ֵ=0����S<T,�򷵻�ֵ<0;
	for (int i = 0; i < S.length && i < T.length; i++) {
		if (S.ch[i] != T.ch[i])
			return S.ch[i] - T.ch[i];
	}
	return S.length - T.length;
}
//�󴮵��Ӵ�
void SubString(HString& T, HString S, int i, int len) {
	//��T���ش�S�ĵ�i���ַ��𳤶�Ϊlen���Ӵ�
	if (T.ch)
		free(T.ch);
	if (i<1 || i>S.length || len<0 || len>S.length - i + 1) {
		cout << "��������޷������Ӵ�" << endl;
		return;
	}
	if (!len) {
		T.ch = NULL;
		T.length = 0;
	}
	else {
		if (!(T.ch = (char*)malloc(len * sizeof(char)))) {
			cout << "�ڴ����ʧ��" << endl;
			return;
		}
		for (int j = 0; j < len; j++) {
			T.ch[j] = S.ch[i - 1 + j];
		}
		T.length = len;
	}
}

//�������Ӳ���:��T������S1��S2���ӵ��´�
void Concat(HString S1, HString S2, HString& T) {
	if (T.ch)
		free(T.ch);
	if (!(T.ch = (char*)malloc((S1.length + S2.length) * sizeof(char)))) {
		cout << "�ڴ����ʧ��" << endl;
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

//��һ������ɾ��һ���Ӵ�
void DeleteString(HString& S,int i,int len) {
	//�ڴ�S��ɾ����ʼλ��Ϊi������Ϊlen���Ӵ�
	if (i<1 || i>S.length || len<0 || len>S.length - i + 1) {
		cout << "�������ɾ������������" << endl;
		return;
	}
	for (int j = i - 1 + len; j < S.length; j++) {
		//��i-1+len���Ԫ��ǰ��lenλ
		S.ch[j - len] = S.ch[j];
	}
	S.length -= len;
}

//���Ķ�λ
//�����Ӵ�T������S�е�pos���ַ�֮���λ��((�±�)���������ڣ�����ֵΪ0
int Index_BF(HString S, HString T, int pos) {
	int i = pos-1, j = 0;
	while (i < S.length && j < T.length) {
		if (S.ch[i] == T.ch[j]) {//�������Ӵ�����ƥ����һ���ַ�
			i++; 
			j++;
		}
		else {//�������Ӵ�ָ��������¿�ʼ��һ��ƥ��
			i = i - j + 1;
			j = 0;
		}
	}
	if (j >= T.length)
		return i - T.length;//����ƥ��ĵ�һ���ַ����±�
	else
		return 0;
}

//��ӡ��
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
	cout << "1.���Ĵ��� 2.�󴮳� 3.���ıȽ� 4.�����Ӵ� 5.�������� 6.ɾ���Ӵ� 7.���Ķ�λ 8.�˳�����" << endl;
	cout << "*************************************************************************************" << endl;
	while (1) {
		int input;
		cout << "����������Ҫ�Ĳ���ָ�";
		cin >> input;
		getchar();
		switch (input) {
		case 1: {
			cout << "�����봴�����е�Ԫ�أ�";
			gets_s(ch1);
			StringAssign(T,ch1);
			cout << "��ӡ�������ݣ�";
			print(T);
			break;
		}
		case 2: {
			cout << "����������Ҫ���л�ȡ���������Ĵ���";
			gets_s(ch1);
			StringAssign(T, ch1);
			cout << "����Ϊ��" << StrLength(T) << endl;
			break;
		}
		case 3: {
			cout << "���д�S�ʹ�T�ıȽϣ�(��S>T,�򷵻�ֵ>0����S=T,�򷵻�ֵ=0����S<T,�򷵻�ֵ<0)" << endl;
			cout << "������S��";
			gets_s(ch1);
			StringAssign(S, ch1);
			cout << "������T��";
			gets_s(ch2);
			StringAssign(T, ch2);
			cout << "�ȽϽ����";
			cout << StrCompare(S, T) << endl;
			break;
		}
		case 4: {
			int i, len;
			cout << "��T���ش�S�ĵ�i���ַ��𳤶�Ϊlen���Ӵ�" << endl;
			cout << "������S��";
			gets_s(ch1);
			StringAssign(S, ch1);
			cout << "��������ʼλ��i��";
			cin >> i;
			cout << "������Ҫ��ȡ���Ӵ����ȣ�";
			cin >> len;
			SubString(T,S, i, len);
			cout << "��ȡ���Ӵ�Ϊ��";
			print(T);
			break;
		}
		case 5: {
			cout << "�������Ӳ���:��N������S��T���ӵ��´�" << endl;
			cout << "�����봮S��";
			gets_s(ch1);
			StringAssign(S, ch1);
			cout << "�����봮T��";
			gets_s(ch2);
			StringAssign(T, ch2);
			Concat(S, T, N);
			cout << "�������Ӻ�N:";
			print(N);
			break;
		case 6: {
			int i, len;
			cout << "�ڴ�S��ɾ����ʼλ��Ϊi������Ϊlen���Ӵ�" << endl;
			cout << "�����봮S��";
			gets_s(ch1);
			StringAssign(S, ch1);
			cout << "������ɾ����ʼλ��i:";
			cin >> i;
			cout << "������ɾ���ִ�����len:";
			cin >> len;
			DeleteString(S, i, len);
			cout << "ɾ����S:";
			print(S);
			break;
		}
		case 7: {
			cout << "���Ķ�λ�������Ӵ�T������S�е�pos���ַ�֮���λ�ã��������ڣ�����ֵΪ0" << endl;
			int pos;
			cout << "��������ҵ���ʼλ��pos:";
			cin >> pos;
			getchar();//���յ��ڻ������Ļس�
			cout << "����������S��";
			gets_s(ch1);
			StringAssign(S, ch1);
			cout << "�������Ӵ�T��";
			gets_s(ch2);
			StringAssign(T, ch2);
			cout << "�Ӵ�T������S��λ���±�Ϊ��" << Index_BF(S, T, pos) << endl;
			break;
		}
		case 8: {
			cout << "�˳�����" << endl;
			exit(-1);
		}
		default: {
			cout << "�������" << endl;
			break;
		}
		}
		}
	}
}

