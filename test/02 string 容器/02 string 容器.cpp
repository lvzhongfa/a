#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include<string>
#include<stdexcept>
#include<vector>


/*
3.1.2.1 string 构造函数
string();//创建一个空的字符串 例如: string str;
string(const string& str);//使用一个string对象初始化另一个string对象
string(const char* s);//使用字符串s初始化
string(int n, char c);//使用n个字符c初始化

3.1.2.2 string基本赋值操作
string& operator=(const char* s);//char*类型字符串 赋值给当前的字符串
string& operator=(const string &s);//把字符串s赋给当前的字符串
string& operator=(char c);//字符赋值给当前的字符串
string& assign(const char *s);//把字符串s赋给当前的字符串
string& assign(const char *s, int n);//把字符串s的前n个字符赋给当前的字符串
string& assign(const string &s);//把字符串s赋给当前字符串
string& assign(int n, char c);//用n个字符c赋给当前字符串
string& assign(const string &s, int start, int n);//将s从start开始n个字符赋值给字符串
*/

void test01()
{
	string str1;//创建一个空的字符串 例如: string str;
	string str2 = str1;//使用一个string对象初始化另一个string对象
	string str3("abcd");//使用字符串s初始化
	string str4(10, 'a');//使用n个字符c初始化

	cout << str3 << endl;
	cout << str4 << endl;


	string str5;
	str5 = str4;//把字符串s赋给当前的字符串
	str5 = "def";//char*类型字符串 赋值给当前的字符串
	cout << str5 << endl;


	string str6;
	//把字符串s的前n个字符赋给当前的字符串
	str6.assign("abcdefg", 3);//assign是赋值的意思
	cout << "str6 = " << str6 << endl;

	//string& assign(const string &s, int start, int n);//将s从start开始n个字符赋值给字符串
	string str7;
	str7.assign(str6, 1, 2);//从数组位置1 开始赋值2个
	// str6   abc
	cout << "str7 = " << str7 << endl;
}


/*
3.1.2.3 string存取字符操作
char& operator[](int n);//通过[]方式取字符
char& at(int n);//通过at方法获取字符
*/

void test02()
{
	string str = "hello world";
	for (int i = 0; i < str.size(); i++)
	{
		//cout << str[i] << endl;
		cout << str.at(i) << endl;
	}

	//[] 和at区别， []如果访问越界 直接中断  at访问越界 抛出异常 

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
		cout << "异常捕获" << endl;
	}
}



/*
3.1.2.4 string拼接操作
string& operator+=(const string& str);//重载+=操作符
string& operator+=(const char* str);//重载+=操作符
string& operator+=(const char c);//重载+=操作符
string& append(const char *s);//把字符串s连接到当前字符串结尾
string& append(const char *s, int n);//把字符串s的前n个字符连接到当前字符串结尾
string& append(const string &s);//同operator+=()
string& append(const string &s, int pos, int n);//把字符串s中从pos开始的n个字符连接到当前字符串结尾
string& append(int n, char c);//在当前字符串结尾添加n个字符c

*/

void test03()
{
	//string 拼接操作分为两种 += append

	string str1 = "i am ";
	string str2 = "a chinese";
	//const char* str3 = "a chinese";
	//char c = 'a';
	//str1 += str2;//两个都是字符串
	//str1 += c;//一个字符串，一个字母
	//str1 += str3;//一个字符串，一个指针
	//cout << str1 << endl;

	//测试append
	//str1.append("a chinese");//两个都是字符串
	//str1.append("achinese",1 );//把字符串s的前n个字符连接到当前字符串结尾

	//const char* str3 = "a chinese";//一个字符串，一个指针
	//str1.append(str3);

	
	str1.append("achinese", 1, 6);//把字符串s中从pos开始的n个字符连接到当前字符串结尾

	str1.append(3, 'a');
	cout << str1 << endl;


}


/*
3.1.2.5 string查找和替换
int find(const string& str, int pos = 0) const; //查找str第一次出现位置,从pos开始查找
int find(const char* s, int pos = 0) const;  //查找s第一次出现位置,从pos开始查找
int find(const char* s, int pos, int n) const;  //从pos位置查找s的前n个字符第一次位置
int find(const char c, int pos = 0) const;  //查找字符c第一次出现位置
int rfind(const string& str, int pos = npos) const;//查找str最后一次位置,从pos开始查找
int rfind(const char* s, int pos = npos) const;//查找s最后一次出现位置,从pos开始查找
int rfind(const char* s, int pos, int n) const;//从pos查找s的前n个字符最后一次位置
int rfind(const char c, int pos = 0) const; //查找字符c最后一次出现位置
string& replace(int pos, int n, const string& str); //替换从pos开始n个字符为字符串str
string& replace(int pos, int n, const char* s); //替换从pos开始的n个字符为字符串s
*/


void test04()
{

	string str = "abcfgdefgh";
	//int find(const string& str, int pos = 0) const; //查找str第一次出现位置,从pos开始查找
	//int a = str.find("cde");

	const char* s = "fg";
	//int find(const char* s, int pos = 0) const;  //查找s第一次出现位置,从pos开始查找
	int b = str.find(s);
	
	//int find(const char* s, int pos, int n) const;  //从pos位置查找s的前n个字符第一次位置
	int c = str.find(s, 5, 2);

	//int find(const char c, int pos = 0) const;  //查找字符c第一次出现位置
	int d = str.find('d');

	//int rfind(const string& str, int pos = npos) const;//查找str最后一次位置,从pos开始查找
	//cout << d<< endl;

	
	string str1 = "abcdefghigklmn";
	//rfind从右往左进行查找		find从左往右

	//参数2  代表 起始查找的位置，默认是从0开始
	int pos = str1.find("de");

	//cout << pos << endl;
	if (pos != -1)
	{
		cout << "找到了子串 ，位置：" << pos << endl;
	}
	else
	{
		cout << "未找到子串" << endl;
	}

	//replace替换
	//string& replace(int pos, int n, const char* s); //替换从pos开始的n个字符为字符串s
	str1.replace(1, 3, "11111");
	cout << str1 << endl;

}

/*
3.1.2.6 string比较操作
compare函数在>时返回 1，<时返回 -1，==时返回 0。
比较区分大小写，比较时参考字典顺序，排越前面的越小。
大写的A比小写的a小。
int compare(const string &s) const;//与字符串s比较
int compare(const char *s) const;//与字符串s比较
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