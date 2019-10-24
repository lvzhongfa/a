#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<algorithm>//算法 al gor i thm

void myPrint(int val)
{
	cout << val << endl;
}

void test01()
{
	//创建一个容器，vector是个最常用的容器  
	vector<int>v;

	//向容器中插入数据
	v.push_back(10);//尾插
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);

	//遍历数组	通过迭代器
	//每个容器都有自己专属的迭代器	iterator 迭代器
	vector<int>::iterator itBegin = v.begin();//起始迭代器，指向容器中第一个元素的地址

	vector<int>::iterator itEnd = v.end();//结束迭代器，指向容器中最后一个元素的下一个地址
	//v是容器	vector<int>::iterato是迭代器 是个类型  itBegin是迭代器对象	itBegin	和itEnd都是指针

	//遍历容器

	//第一种遍历
	//while (itBegin != itEnd)
	//{
	//	cout << *itBegin << endl;
	//	itBegin++;
	//}


	//第二种遍历
	//for (vector<int>::iterator itBegin = v.begin(); itBegin != v.end(); itBegin++)
	//{
	//	cout << *itBegin << endl;
	//}

	//第三种遍历
	for_each(v.begin(), v.end(), myPrint);
}
//2.自定义数据类型
//Person类
class Person
{
public:
	Person(string name, int age)
	{
		this->m_Name = name;
		this->m_Age = age;
	
	}

	string m_Name;
	int m_Age;

};

//2、自定义数据类型
void test02()
{
	//创建一个容器，vector是个最常用的容器 
	vector<Person>v;
	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);

	//向容器中插入数据
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);

	//遍历容器
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
	{
		//* it是什么？？Person类型
		cout << "姓名：" << it->m_Name << "年龄：" << it->m_Age << endl;
	}

}

//3、存放自定义数据类型 指针
void test03()
{
	//创建一个容器，vector是个最常用的容器 
	vector<Person*>v;
	//向容器中插入数据
	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);

	v.push_back(&p1);
	v.push_back(&p2);
	v.push_back(&p3);

	//遍历容器
	for (vector<Person*>::iterator it = v.begin(); it != v.end(); it++)
	{
		//*it 是？Person*
		cout << "姓名：" << (*it)->m_Name << "年龄：" << (*it)->m_Age << endl;
	}

}

//4.容器嵌套容器
void test04()
{
	//创建一个容器，vector是个最常用的容器 
	vector<vector<int>>v;
	//向容器中插入数据
	vector<int>v1;
	vector<int>v2;
	vector<int>v3;

	for (int i = 0; i < 5; i++)
	{
		v1.push_back(i);
		v2.push_back(i + 10);
		v3.push_back(i + 100);

	}

	//小容器插入到大容器中
	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);

	//遍历大容器
	for (vector<vector<int>>::iterator it = v.begin(); it != v.end(); it++)
	{
		//* it->vector<int>
		for (vector<int>::iterator vit = (*it).begin(); vit != (*it).end(); vit++)
		{
			cout << *vit << " ";
		}
		cout << endl;

	}

}



int main(){


	test04();
	system("pause");
	return EXIT_SUCCESS;
}