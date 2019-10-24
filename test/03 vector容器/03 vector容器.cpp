#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include<vector>

//测试内存分配空间机制
void test01()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
		cout << v.capacity() << endl;//v.capacity()容器的容量

	}
}


/*
3.2.4.1 vector构造函数
vector<T> v; //采用模板实现类实现，默认构造函数
vector(v.begin(), v.end());//将v[begin(), end())区间中的元素拷贝给本身。
vector(n, elem);//构造函数将n个elem拷贝给本身。
vector(const vector &vec);//拷贝构造函数。

//例子 使用第二个构造函数 我们可以...
int arr[] = {2,3,4,1,9};
vector<int> v1(arr, arr + sizeof(arr) / sizeof(int));

3.2.4.2 vector常用赋值操作
assign(beg, end);//将[beg, end)区间中的数据拷贝赋值给本身。
assign(n, elem);//将n个elem拷贝赋值给本身。
vector& operator=(const vector  &vec);//重载等号操作符
swap(vec);// 将vec与本身的元素互换。
*/

//创建一个函数用于打印容器中的数字
void printVector(vector<int>v)
{
	for (vector<int>::iterator it = v.begin(); it != v.end; it++)
	{
		cout << *it << " ";
	}
	cout << endl;

}


void test02()
{
	vector<int>v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);

	vector<int>v2(v.begin(), v.end());
	printVector(v);


}








int main(){

	test02();

	system("pause");
	return EXIT_SUCCESS;
}