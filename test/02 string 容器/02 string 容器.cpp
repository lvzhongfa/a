#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include<string>
#include<stdexcept>
#include<vector>


/*
3.1.2.1 string ���캯��
string();//����һ���յ��ַ��� ����: string str;
string(const string& str);//ʹ��һ��string�����ʼ����һ��string����
string(const char* s);//ʹ���ַ���s��ʼ��
string(int n, char c);//ʹ��n���ַ�c��ʼ��

3.1.2.2 string������ֵ����
string& operator=(const char* s);//char*�����ַ��� ��ֵ����ǰ���ַ���
string& operator=(const string &s);//���ַ���s������ǰ���ַ���
string& operator=(char c);//�ַ���ֵ����ǰ���ַ���
string& assign(const char *s);//���ַ���s������ǰ���ַ���
string& assign(const char *s, int n);//���ַ���s��ǰn���ַ�������ǰ���ַ���
string& assign(const string &s);//���ַ���s������ǰ�ַ���
string& assign(int n, char c);//��n���ַ�c������ǰ�ַ���
string& assign(const string &s, int start, int n);//��s��start��ʼn���ַ���ֵ���ַ���
*/

void test01()
{
	string str1;//����һ���յ��ַ��� ����: string str;
	string str2 = str1;//ʹ��һ��string�����ʼ����һ��string����
	string str3("abcd");//ʹ���ַ���s��ʼ��
	string str4(10, 'a');//ʹ��n���ַ�c��ʼ��

	cout << str3 << endl;
	cout << str4 << endl;


	string str5;
	str5 = str4;//���ַ���s������ǰ���ַ���
	str5 = "def";//char*�����ַ��� ��ֵ����ǰ���ַ���
	cout << str5 << endl;


	string str6;
	//���ַ���s��ǰn���ַ�������ǰ���ַ���
	str6.assign("abcdefg", 3);//assign�Ǹ�ֵ����˼
	cout << "str6 = " << str6 << endl;

	//string& assign(const string &s, int start, int n);//��s��start��ʼn���ַ���ֵ���ַ���
	string str7;
	str7.assign(str6, 1, 2);//������λ��1 ��ʼ��ֵ2��
	// str6   abc
	cout << "str7 = " << str7 << endl;
}


/*
3.1.2.3 string��ȡ�ַ�����
char& operator[](int n);//ͨ��[]��ʽȡ�ַ�
char& at(int n);//ͨ��at������ȡ�ַ�
*/

void test02()
{
	string str = "hello world";
	for (int i = 0; i < str.size(); i++)
	{
		//cout << str[i] << endl;
		cout << str.at(i) << endl;
	}

	//[] ��at���� []�������Խ�� ֱ���ж�  at����Խ�� �׳��쳣 

	try
	{
		cout << str[100] << endl;
	}

	catch (exception & e)//out_of_range
	{
		cout << e.what() << endl;
	}

	catch (...)
	{
		cout << "�쳣����" << endl;
	}
}



/*
3.1.2.4 stringƴ�Ӳ���
string& operator+=(const string& str);//����+=������
string& operator+=(const char* str);//����+=������
string& operator+=(const char c);//����+=������
string& append(const char *s);//���ַ���s���ӵ���ǰ�ַ�����β
string& append(const char *s, int n);//���ַ���s��ǰn���ַ����ӵ���ǰ�ַ�����β
string& append(const string &s);//ͬoperator+=()
string& append(const string &s, int pos, int n);//���ַ���s�д�pos��ʼ��n���ַ����ӵ���ǰ�ַ�����β
string& append(int n, char c);//�ڵ�ǰ�ַ�����β���n���ַ�c

*/

void test03()
{
	//string ƴ�Ӳ�����Ϊ���� += append

	string str1 = "i am ";
	string str2 = "a chinese";
	//const char* str3 = "a chinese";
	//char c = 'a';
	//str1 += str2;//���������ַ���
	//str1 += c;//һ���ַ�����һ����ĸ
	//str1 += str3;//һ���ַ�����һ��ָ��
	//cout << str1 << endl;

	//����append
	//str1.append("a chinese");//���������ַ���
	//str1.append("achinese",1 );//���ַ���s��ǰn���ַ����ӵ���ǰ�ַ�����β

	//const char* str3 = "a chinese";//һ���ַ�����һ��ָ��
	//str1.append(str3);

	
	str1.append("achinese", 1, 6);//���ַ���s�д�pos��ʼ��n���ַ����ӵ���ǰ�ַ�����β

	str1.append(3, 'a');
	cout << str1 << endl;


}


/*
3.1.2.5 string���Һ��滻
int find(const string& str, int pos = 0) const; //����str��һ�γ���λ��,��pos��ʼ����
int find(const char* s, int pos = 0) const;  //����s��һ�γ���λ��,��pos��ʼ����
int find(const char* s, int pos, int n) const;  //��posλ�ò���s��ǰn���ַ���һ��λ��
int find(const char c, int pos = 0) const;  //�����ַ�c��һ�γ���λ��
int rfind(const string& str, int pos = npos) const;//����str���һ��λ��,��pos��ʼ����
int rfind(const char* s, int pos = npos) const;//����s���һ�γ���λ��,��pos��ʼ����
int rfind(const char* s, int pos, int n) const;//��pos����s��ǰn���ַ����һ��λ��
int rfind(const char c, int pos = 0) const; //�����ַ�c���һ�γ���λ��
string& replace(int pos, int n, const string& str); //�滻��pos��ʼn���ַ�Ϊ�ַ���str
string& replace(int pos, int n, const char* s); //�滻��pos��ʼ��n���ַ�Ϊ�ַ���s
*/


void test04()
{

	string str = "abcfgdefgh";
	//int find(const string& str, int pos = 0) const; //����str��һ�γ���λ��,��pos��ʼ����
	//int a = str.find("cde");

	const char* s = "fg";
	//int find(const char* s, int pos = 0) const;  //����s��һ�γ���λ��,��pos��ʼ����
	int b = str.find(s);
	
	//int find(const char* s, int pos, int n) const;  //��posλ�ò���s��ǰn���ַ���һ��λ��
	int c = str.find(s, 5, 2);

	//int find(const char c, int pos = 0) const;  //�����ַ�c��һ�γ���λ��
	int d = str.find('d');

	//int rfind(const string& str, int pos = npos) const;//����str���һ��λ��,��pos��ʼ����
	//cout << d<< endl;

	
	string str1 = "abcdefghigklmn";
	//rfind����������в���		find��������

	//����2  ���� ��ʼ���ҵ�λ�ã�Ĭ���Ǵ�0��ʼ
	int pos = str1.find("de");

	//cout << pos << endl;
	if (pos != -1)
	{
		cout << "�ҵ����Ӵ� ��λ�ã�" << pos << endl;
	}
	else
	{
		cout << "δ�ҵ��Ӵ�" << endl;
	}

	//replace�滻
	//string& replace(int pos, int n, const char* s); //�滻��pos��ʼ��n���ַ�Ϊ�ַ���s
	str1.replace(1, 3, "11111");
	cout << str1 << endl;

}

/*
3.1.2.6 string�Ƚϲ���
compare������>ʱ���� 1��<ʱ���� -1��==ʱ���� 0��
�Ƚ����ִ�Сд���Ƚ�ʱ�ο��ֵ�˳����Խǰ���ԽС��
��д��A��Сд��aС��
int compare(const string &s) const;//���ַ���s�Ƚ�
int compare(const char *s) const;//���ַ���s�Ƚ�
*/

void test05()
{
	string str1 = "abcde";
	string str2 = "abcd";

	if (str1.compare(str2) == 0)
	{
		cout << "str1==str2" << endl;
	}
	else if (str1.compare(str2) > 0)
	{
		cout << "str1>str2" << endl;
	}
	else
	{
		cout << "str1 < str2 " << endl;
	}

}














int main(){

	test05();
	system("pause");
	return EXIT_SUCCESS;
}