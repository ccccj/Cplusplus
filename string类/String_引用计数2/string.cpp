#include "string.h"
#include <iostream>

using namespace std;

int& String::GetpCount() {
	return *(int*)(_str - 4);
}

// 构造函数
String::String(const char* str) {
	size_t len = strlen(str);
	_str = new char[len + 5];
	_str += 4;
	strcpy(_str, str);
	GetpCount() = 1;
	_size = len;
	_capacity = len;
}

// 析构函数
String::~String() {
	if (--(GetpCount()) == 0) {
		if (_str != NULL) {
			delete[] (_str - 4);
			_str = NULL;
			_size = 0;
			_capacity = 0;
		}
	}
}

// 拷贝构造
String::String(const String& s)
	:_size(s._size)
	,_capacity(s._capacity) 
{
	_str = s._str - 4;
	_str += 4;
	++(GetpCount());
}

// 写时拷贝
void String::CopyOnWrite() {
	if (GetpCount() > 1) {
		char* tmp = new char[strlen(_str) + 5];
		tmp += 4;
		strcpy(tmp, _str);
		--(GetpCount());
		_str = tmp;
		GetpCount() = 1;
	}
}

String& String::operator=(const String& s) 
{
	_str = s._str - 4;
	_str += 4;
	_size = s._size;
	_capacity = s._capacity;
	++(GetpCount());
	return *this;
}

void String::Expand(size_t n) {
	char* new_String = new char[n + 5];
	strcpy(new_String + 4, _str);
	delete[] (_str - 4);
	_str = new_String;
	_capacity = n;
}

const char* String::c_str() {
	return _str;
}

size_t String::c_size() {
	return _size;
}

size_t String::c_capacity() {
	return _capacity;
}

char& String::operator[](size_t pos) {
	CopyOnWrite();
	return _str[pos];
}

/////////////////////////
// 以下为测试代码
/////////////////////////

#if 1
#include <iostream>
#include <cstdio>
#include <cstdlib>

#define TEST_HEADER printf("\n========%s=======\n", __FUNCTION__)

void Test_c_str() {
	TEST_HEADER;
	String s("hello");
	cout << "str expert: hello actual: ";
	cout << s.c_str() << endl;
	cout << "pCount expert: 1 actual: ";
	cout << s.GetpCount() << endl;
}

void Test_String() {
	TEST_HEADER;
	String s1;
	cout << "s1:" << endl;
	printf("_str expert:   actual:%s\n", s1.c_str());
	printf("_pCount expert: 1  actual:%lu\n", s1.GetpCount());
	String s2("hello");
	cout << "s2:" << endl;
	printf("_str expert: hello  actual:%s\n", s2.c_str());
	printf("_pCount expert: 1  actual:%lu\n", s2.GetpCount());
}

void Test_CopyString() {
	TEST_HEADER;
	String s1("hello");
	printf("_pCount expert: 1  actual:%lu\n", s1.GetpCount());
	String s2(s1);
	cout << "s2:" << endl;
	printf("_str expert: %p  actual:%p\n", s1.c_str(), s2.c_str());
	printf("_pCount expert: 2  actual:%lu\n", s1.GetpCount());
	printf("_pCount expert: 2  actual:%lu\n", s2.GetpCount());
}

void Test_operator1() {
	TEST_HEADER;
	String s1("hello");
	String s2("xxxxx");
	String s3;
	s3 = s2 = s1;

	printf("_pCount expert: 3  actual:%lu\n", s1.GetpCount());
	printf("_pCount expert: 3  actual:%lu\n", s2.GetpCount());
	printf("_pCount expert: 3  actual:%lu\n", s1.GetpCount());

	cout << "s2:" << endl;
	printf("_str expert: hello  actual:%s\n", s2.c_str());
	cout << "s3:" << endl;
	printf("_str expert: hello  actual:%s\n", s2.c_str());
}

void Test_operator() {
	TEST_HEADER;
	String s1("hello");
	String s2("xxxxx");
	String s3;
	
	s3 = s2 = s1;
	
	cout << "初始化完成后" << endl;

	printf("_pCount expert: 3  actual:%lu\n", s2.GetpCount());
	printf("_pCount expert: 3  actual:%lu\n", s1.GetpCount());

	s2[3] = 'a';
	
	cout << "修改s2" << endl;
	
	printf("_pCount expert: 2  actual:%lu\n", s1.GetpCount());
	printf("_pCount expert: 1  actual:%lu\n", s2.GetpCount());
	printf("_pCount expert: 2  actual:%lu\n", s1.GetpCount());
}

int main() {
	system("clear");
	Test_c_str();
  Test_String();
  Test_CopyString();
  Test_operator1();

  Test_operator();

  return 0;
}
#endif
