#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;
#include<vector>

//�����ڴ����ռ����
void test01()
{
	vector<int>v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
		cout << v.capacity() << endl;//v.capacity()����������

	}
}


/*
3.2.4.1 vector���캯��
vector<T> v; //����ģ��ʵ����ʵ�֣�Ĭ�Ϲ��캯��
vector(v.begin(), v.end());//��v[begin(), end())�����е�Ԫ�ؿ���������
vector(n, elem);//���캯����n��elem����������
vector(const vector &vec);//�������캯����

//���� ʹ�õڶ������캯�� ���ǿ���...
int arr[] = {2,3,4,1,9};
vector<int> v1(arr, arr + sizeof(arr) / sizeof(int));

3.2.4.2 vector���ø�ֵ����
assign(beg, end);//��[beg, end)�����е����ݿ�����ֵ������
assign(n, elem);//��n��elem������ֵ������
vector& operator=(const vector  &vec);//���صȺŲ�����
swap(vec);// ��vec�뱾���Ԫ�ػ�����
*/

//����һ���������ڴ�ӡ�����е�����
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