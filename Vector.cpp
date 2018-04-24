#include "Vector.h"
#include <cstring>
#include <iostream>

using namespace std;

Vector::Vector() 
	:_first(NULL)
	,_finish(NULL)
	,_endofstorage(NULL) {
}

size_t Vector::Size() const
{ 
	return _finish - _first;
}

size_t Vector::Capacity() const
{
	return _endofstorage - _first;
}

void Vector::Expand(size_t n) {
	if (n > Capacity()) {
		DataType* new_vector = new DataType[n];
		size_t size = Size();
		memcpy(new_vector, _first, size * sizeof(DataType));
		delete[] _first;
		_first = new_vector;
		_finish = _first + size;
		_endofstorage = _first + n;
	}
}

// 需要初始化列表，否则指针随机，容易造成当前 Size 很大
Vector::Vector(const Vector& v) 
	:_first(NULL)
	,_finish(NULL)
	,_endofstorage(NULL)
{
	size_t size = v.Size();
	Expand(size);
	memcpy(_first, v._first, size * sizeof(DataType));
	_finish = _first + size;
	_endofstorage = _first + size;
}

/*
传统写法
Vector& Vector::operator=(const Vector& v) {
	_first = NULL;
	_finish = NULL;
	_endofstorage = NULL;
	size_t size = v.Size();
	Expand(size);
	memcpy(_first, v._first, size * sizeof(DataType));
	_finish = _first + size;
	_endofstorage = _first + size;
	return *this;
}
*/

//现代写法
Vector& Vector::operator=(const Vector& v) {
	Vector tmp(v);
	swap(_first, tmp._first);
	swap(_finish, tmp._finish);
	swap(_endofstorage, tmp._endofstorage);
	delete[] tmp._first;
}

Vector::~Vector() {
	delete[] _first;
	_first = NULL;
	_finish = NULL;
	_endofstorage = NULL;
}

void Vector::Insert(size_t pos, DataType x) {
	if (pos > Size()) {
		return;
	}
	if (Size() >= Capacity()) {
		Expand(2 * Capacity() + 1);
	}
	for (int i = Size() - 1; i >= (int)pos; --i) {
		_first[i + 1] = _first[i];
	}
	_first[pos] = x;
	++_finish;
}

void Vector::PushBack(DataType x) {
	Insert(Size(), x);
}

void Vector::PopBack() {
	if (Size() > 0) {
		--_finish;
	}
}

void Vector::Show() {
	DataType* cur = _first;
	while (cur != _finish) {
		cout << *cur << ' '; 
		++cur;
	}
	cout << endl;
}

void Vector::Reserve(size_t n) {
	Expand(n);
}

void Vector::Erase(size_t pos) {
	size_t size = Size();
	for (int i = pos; i < size - 1; ++i) {
		_first[i] = _first[i + 1];
	}
	--_finish;
}

size_t Vector::Find(DataType x) {
	for (int i = 0; i < Size(); ++i) {
		if (_first[i] == x) {
			return i;
		}
	}
	return (size_t)-1;
}
////////////////////////////
// 测试函数
////////////////////////////
#if 1
#include <cstdio>
#include <cstdlib>
#define TEST_HEADER printf("\n=========%s=========\n", __FUNCTION__)

void Test_Vector() {
	TEST_HEADER;
	Vector v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
  v.PushBack(5);
  v.PushBack(6);
	v.Show();
	
	v.Insert(0, 10);
	v.Show();
	// 拷贝构造
	Vector v2(v);
	v2.Show();
	
	// 赋值运算符重载
	Vector v3;
	v3 = v;
	v3.Show();

	v3.Erase(0);
	v3.Show();

	v3.Erase(6);
	v3.Show();

	v3.Erase(3);
	v3.Show();

	size_t ret = v2.Find(10);
	printf("ret expert: 0 actual :%lu\n", ret);
	ret = v2.Find(4);
	printf("ret expert: 4 actual :%lu\n", ret);
	ret = v2.Find(6);
	printf("ret expert: 6 actual :%lu\n", ret);
	ret = v2.Find(19);
	printf("ret expert: -1 actual :%d\n", (int)ret);
}


int main() {
	system("clear");
	Test_Vector();

	return 0;
}


#endif
