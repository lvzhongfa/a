#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include<vector>
#include<string>
#include<algorithm>//�㷨 al gor i thm

void myPrint(int val)
{
	cout << val << endl;
}

void test01()
{
	//����һ��������vector�Ǹ���õ�����  
	vector<int>v;

	//�������в�������
	v.push_back(10);//β��
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);

	//��������	ͨ��������
	//ÿ�����������Լ�ר���ĵ�����	iterator ������
	vector<int>::iterator itBegin = v.begin();//��ʼ��������ָ�������е�һ��Ԫ�صĵ�ַ

	vector<int>::iterator itEnd = v.end();//������������ָ�����������һ��Ԫ�ص���һ����ַ
	//v������	vector<int>::iterato�ǵ����� �Ǹ�����  itBegin�ǵ���������	itBegin	��itEnd����ָ��

	//��������

	//��һ�ֱ���
	//while (itBegin != itEnd)
	//{
	//	cout << *itBegin << endl;
	//	itBegin++;
	//}


	//�ڶ��ֱ���
	//for (vector<int>::iterator itBegin = v.begin(); itBegin != v.end(); itBegin++)
	//{
	//	cout << *itBegin << endl;
	//}

	//�����ֱ���
	for_each(v.begin(), v.end(), myPrint);
}
//2.�Զ�����������
//Person��
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

//2���Զ�����������
void test02()
{
	//����һ��������vector�Ǹ���õ����� 
	vector<Person>v;
	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);

	//�������в�������
	v.push_back(p1);
	v.push_back(p2);
	v.push_back(p3);

	//��������
	for (vector<Person>::iterator it = v.begin(); it != v.end(); it++)
	{
		//* it��ʲô����Person����
		cout << "������" << it->m_Name << "���䣺" << it->m_Age << endl;
	}

}

//3������Զ����������� ָ��
void test03()
{
	//����һ��������vector�Ǹ���õ����� 
	vector<Person*>v;
	//�������в�������
	Person p1("aaa", 10);
	Person p2("bbb", 20);
	Person p3("ccc", 30);

	v.push_back(&p1);
	v.push_back(&p2);
	v.push_back(&p3);

	//��������
	for (vector<Person*>::iterator it = v.begin(); it != v.end(); it++)
	{
		//*it �ǣ�Person*
		cout << "������" << (*it)->m_Name << "���䣺" << (*it)->m_Age << endl;
	}

}

//4.����Ƕ������
void test04()
{
	//����һ��������vector�Ǹ���õ����� 
	vector<vector<int>>v;
	//�������в�������
	vector<int>v1;
	vector<int>v2;
	vector<int>v3;

	for (int i = 0; i < 5; i++)
	{
		v1.push_back(i);
		v2.push_back(i + 10);
		v3.push_back(i + 100);

	}

	//С�������뵽��������
	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);

	//����������
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