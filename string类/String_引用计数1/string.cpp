#include "string.h"
#include <iostream>

using namespace std;

// 构造函数
String::String(const char* str) 
	:_pCount(new size_t(1))
{
	size_t len = strlen(str);
	_str = new char[len + 1];
	strcpy(_str, str);
	_size = len;
	_capacity = len;
}

// 析构函数
String::~String() {
	if (--(*_pCount) == 0) {
		if (_str != NULL) {
			delete[] _str;
			delete _pCount;
			_str = NULL;
			_size = 0;
			_capacity = 0;
		}
	}
}

// 借用了构造函数的拷贝构造
String::String(const String& s)
	:_str(s._str)
	,_size(s._size)
	,_capacity(s._capacity) 
{
	++(*s._pCount);
	_pCount = s._pCount;
}

// 写时拷贝
void String::CopyOnWrite() {
	if (*_pCount > 1) {
		char* tmp = new char[strlen(_str) + 1];
		strcpy(tmp, _str);
		--(*_pCount);
		_pCount = new size_t(1);
		_str = tmp;
	}
}

String& String::operator=(const String& s) 
{
	_str = s._str;
	_size = s._size;
	_capacity = s._capacity;
	_pCount = s._pCount;
	++(*_pCount);
	return *this;
}

void String::Expand(size_t n) {
	char* new_String = new char[n + 1];
	strcpy(new_String, _str);
	delete[] _str;
	_str = new_String;
	_capacity = n;
}

const char* String::c_str() {
	return _str;
}

const size_t* String::c_pCount() {
	return _pCount;
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
	cout << *s.c_pCount() << endl;
}

void Test_String() {
	TEST_HEADER;
	String s1;
	cout << "s1:" << endl;
	printf("_str expert:   actual:%s\n", s1.c_str());
	printf("_pCount expert: 1  actual:%lu\n", *s1.c_pCount());
	String s2("hello");
	cout << "s2:" << endl;
	printf("_str expert: hello  actual:%s\n", s2.c_str());
	printf("_pCount expert: 1  actual:%lu\n", *s2.c_pCount());
}

void Test_CopyString() {
	TEST_HEADER;
	String s1("hello");
	printf("_pCount expert: 1  actual:%lu\n", *s1.c_pCount());
	String s2(s1);
	cout << "s2:" << endl;
	printf("_str expert: %p  actual:%p\n", s1.c_str(), s2.c_str());
	printf("_pCount expert: 2  actual:%lu\n", *s1.c_pCount());
	printf("_pCount expert: 2  actual:%lu\n", *s2.c_pCount());
}

void Test_operator1() {
	TEST_HEADER;
	String s1("hello");
	String s2("xxxxx");
	String s3;
	s3 = s2 = s1;

	printf("_pCount expert: 3  actual:%lu\n", *s1.c_pCount());
	printf("_pCount expert: 3  actual:%lu\n", *s2.c_pCount());
	printf("_pCount expert: 3  actual:%lu\n", *s1.c_pCount());

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
	printf("_pCount expert: 3  actual:%lu\n", *s1.c_pCount());
	printf("_pCount expert: 3  actual:%lu\n", *s2.c_pCount());
	printf("_pCount expert: 3  actual:%lu\n", *s1.c_pCount());

	s2[3] = 'a';
	
	cout << "修改s2" << endl;
	
	printf("_pCount expert: 2  actual:%lu\n", *s1.c_pCount());
	printf("_pCount expert: 1  actual:%lu\n", *s2.c_pCount());
	printf("_pCount expert: 2  actual:%lu\n", *s1.c_pCount());
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
