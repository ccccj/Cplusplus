#include "string.h"
#include <algorithm>
#include <iostream>

using namespace std;

// 构造函数
String::String(const char* str) {
	size_t len = strlen(str);
	_str = new char[len];
	strcpy(_str, str);
	_size = len;
	_capacity = len;
}

// 析构函数
String::~String() {
	delete[] _str;
	_str = NULL;
	_size = 0;
	_capacity = 0;
}

// 拷贝构造
/*
// 方法1：
String::String(const String& s) {
	size_t len = strlen(s._str);
	_str = new char[len];
	strcpy(_str, s._str);
	_size = len;
	_capacity = len;
}
*/

// 借用了构造函数的拷贝构造
String::String(const String& s) {
	String tmp(s._str);
	swap(_str, tmp._str);
	_size = tmp._size;
	_capacity = tmp._capacity;
}

// 交换
void String::Swap(String& s) {
	swap(_str, s._str);
	swap(_size, s._size);
	swap(_capacity, s._capacity);
}

// 赋值运算符重载
/*
// 传统写法：
String& String::operator=(const String& s) {
	size_t len = strlen(s._str);
	Expand(len);
	strcpy(_str, s._str);
	_size = s._size;
	return *this;
}
*/

// 借用传参时的临时拷贝，直接赋值交换
String& String::operator=(String s) {
	swap(_str, s._str);
	_size = s._size;
	_capacity = s._capacity;
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
	return this->_str;
}

size_t String::c_size() {
	return this->_size;
}

size_t String::c_capacity() {
	return this->_capacity;
}

void String::PushBack(char ch) {
	if (_size == _capacity) {
		Expand(_size * 2 + 1);
	}
	_str[_size++] = ch;
	_str[_size] = '\0';
}

void String::PushBack(const char* str) {
	size_t len = strlen(str);
	if (_size + len > _capacity) {
		Expand(_size + len);
	}
	strcpy(_str + _size, str);
	_size += len;
}

void String::PopBack() {
	if (_size > 0) {
		--_size;
		_str[_size] = '\0';
	}
}

void String::Insert(size_t pos, char ch) {
	if (pos > _size) {
		return;
	}
	if (_size == _capacity) {
		Expand(_size * 2 + 1);
	}
	// 这里 pos 必须强转为 int，否则段错误，
	// 因为int i 与 size_t pos 比较时，
	// i 类型提升，也变成了 size_t，--i，i 又变成了无符号长整型的最大值
	for (int i = _size; i >= (int)pos; --i) {
		_str[i + 1] = _str[i];
	}
	_str[pos] = ch;
	++_size;
}

void String::Insert(size_t pos, const char* str) {
	if (pos > _size) {
		return;
	}
	size_t len = strlen(str);
	if (_size + len > _capacity) {
		Expand(_size + len);
	}
	for (int i = _size; i >= (int)pos; --i) {
		_str[i + len] = _str[i];
	}
	memcpy(_str + pos, str, sizeof(char) * len);
	_size += len;
}

void String::Erase(size_t pos, size_t n) {
	if (pos >= _size) {
		return;
	}
	if (_size - pos < n) {
		_str[pos] = '\0';
		_size = pos;
		return;
	}
	memmove(_str + pos, _str + pos + n, n + 1);
	_size -= n;
	return;
}

void String::Replace(char ch1, char ch2) {
	for (int i = 0; i < _size; ++i) {
		if (_str[i] == ch1) {
			_str[i] = ch2;
		}
	}
}





bool String::operator==(const String& s) {
	size_t i = 0, j = 0;
	while ((this->_str)[i] != '\0' && (s._str)[j] != '\0') {
		if ((this->_str)[i] == (s._str)[j]) {
			++i, ++j;
		} else {
			return false;
		}
	}
	if ((this->_str)[i] == '\0' && (s._str)[j] == '\0') {
		return true;
	} else {
		return false;
	}
}

bool String::operator!=(const String& s) {
	return !(*this == s);
}

bool String::operator>(const String& s) {
	size_t i = 0, j = 0;
	while ((this->_str)[i] != '\0' && (s._str)[j] != '\0') {
		if ((this->_str)[i] == (s._str)[j]) {
			++i, ++j;
		} else if ((this->_str)[i] > (s._str)[j]) {
			return true;
		} else {
			return 0;
		}
	}
	if ((this->_str)[i] != '\0') {
		return true;
	} else {
		return false;
	}
}

bool String::operator>=(const String& s) {
	if ( (*this > s) || (*this == s) ) {
		return true;
	} else {
		return false;
	}
}

bool String::operator<(const String& s) {
	return !(*this >= s);
}

bool String::operator<=(const String& s) {
	return !(*this > s);
}

String String::operator+(char ch) {
	String tmp(*this);
	tmp.PushBack(ch);
	return tmp;
}

String& String::operator+=(char ch) {
	(*this).PushBack(ch);
	return *this;
}

String String::operator+(const char* str) {
	String tmp(*this);
	//tmp.PushBack(str);
	return tmp;
}

String& String::operator+=(const char* str) {
	(*this).PushBack(str);
	return *this;
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
	cout << "size expert: 5 actual: ";
	cout << s.c_size() << endl;
	cout << "capacity expert: 5 actual: ";
	cout << s.c_capacity() << endl;
}

void Test_String() {
	TEST_HEADER;
	String s1;
	cout << "s1:" << endl;
	printf("_str expert:   actual:%s\n", s1.c_str());
	printf("_size expert: 0  actual:%d\n", s1.c_size());
	printf("_capacity expert: 0  actual:%d\n", s1.c_capacity());
	String s2("hello");
	cout << "s2:" << endl;
	printf("_str expert: hello  actual:%s\n", s2.c_str());
	printf("_size expert: 5  actual:%d\n", s2.c_size());
	printf("_capacity expert: 5  actual:%d\n", s2.c_capacity());
}

void Test_CopyString() {
	TEST_HEADER;
	String s1("hello");
	String s2(s1);
	cout << "s2:" << endl;
	printf("_str expert: hello  actual:%s\n", s2.c_str());
	printf("_size expert: 5  actual:%d\n", s2.c_size());
	printf("_capacity expert: 5  actual:%d\n", s2.c_capacity());
}

void Test_Swap() {
	TEST_HEADER;
	String s1("caojing");
	String s2("hello");
	s1.Swap(s2);
	cout << "s1:" << endl;
	printf("_str expert: hello  actual:%s\n", s1.c_str());
	printf("_size expert: 5  actual:%d\n", s1.c_size());
	printf("_capacity expert: 5  actual:%d\n", s1.c_capacity());
	cout << "s2:" << endl;
	printf("_str expert: caojing  actual:%s\n", s2.c_str());
	printf("_size expert: 7  actual:%d\n", s2.c_size());
	printf("_capacity expert: 7  actual:%d\n", s2.c_capacity());
}

void Test_operator1() {
	TEST_HEADER;
	String s1("hello");
	String s2("xxxxx");
	String s3;
	s3 = s2 = s1;

	cout << "s2:" << endl;
	printf("_str expert: hello  actual:%s\n", s2.c_str());
	printf("_size expert: 5  actual:%d\n", s2.c_size());
	printf("_capacity expert: 5  actual:%d\n", s2.c_capacity());
	cout << "s3:" << endl;
	printf("_str expert: hello  actual:%s\n", s2.c_str());
	printf("_size expert: 5  actual:%d\n", s2.c_size());
	printf("_capacity expert: 5  actual:%d\n", s2.c_capacity());
}

void Test_PushBackch() {
	TEST_HEADER;
	String s("hello world");
	s.PushBack('!');
	s.PushBack('!');
	s.PushBack('!');
	cout << "str expert: hello world!!! actual: ";
	cout << s.c_str() << endl;
	cout << "size expert: 14 actual: ";
	cout << s.c_size() << endl;
	cout << "capacity expert: 23 actual: ";
	cout << s.c_capacity() << endl;
}

void Test_PushBackstr() {
	TEST_HEADER;
	String s("hello ");
	s.PushBack("world");
	cout << "str expert: hello world actual: ";
	cout << s.c_str() << endl;
	cout << "size expert: 11 actual: ";
	cout << s.c_size() << endl;
	cout << "capacity expert: 11 actual: ";
	cout << s.c_capacity() << endl;
}

void Test_PopBack() {
	TEST_HEADER;
	String s("hello");
	s.PopBack();
	cout << "str expert: hell world actual: ";
	cout << s.c_str() << endl;
	cout << "size expert: 4 actual: ";
	cout << s.c_size() << endl;
	cout << "capacity expert: 5 actual: ";
	cout << s.c_capacity() << endl;
}

void Test_Insert1() {
	TEST_HEADER;
	String s("hello");

	s.Insert(6, 'a');
	cout << "str expert: hello actual: ";
	cout << s.c_str() << endl;
	cout << "size expert: 5 actual: ";
	cout << s.c_size() << endl;
	cout << "capacity expert: 5 actual: ";
	cout << s.c_capacity() << endl;
	cout << endl;

	s.Insert(5, 'a');
	cout << "str expert: helloa actual: ";
	cout << s.c_str() << endl;
	cout << "size expert: 6 actual: ";
	cout << s.c_size() << endl;
	cout << "capacity expert: 11 actual: ";
	cout << s.c_capacity() << endl;
	cout << endl;

	s.Insert(3, 'a');
	cout << "str expert: helaloa actual: ";
	cout << s.c_str() << endl;
	cout << "size expert: 7 actual: ";
	cout << s.c_size() << endl;
	cout << "capacity expert: 11 actual: ";
	cout << s.c_capacity() << endl;
	cout << endl;
	
	s.Insert(0, 'a');
	cout << "str expert: ahelaloa actual: ";
	cout << s.c_str() << endl;
	cout << "size expert: 8 actual: ";
	cout << s.c_size() << endl;
	cout << "capacity expert: 11 actual: ";
	cout << s.c_capacity() << endl;
	cout << endl;
}

void Test_Insert2() {
	TEST_HEADER;
	String s("hello");

	s.Insert(6, "!!");
	cout << "str expert: hello actual: ";
	cout << s.c_str() << endl;
	cout << "size expert: 5 actual: ";
	cout << s.c_size() << endl;
	cout << "capacity expert: 5 actual: ";
	cout << s.c_capacity() << endl;
	cout << endl;

	s.Insert(5, "!!");
	cout << "str expert: hello!! actual: ";
	cout << s.c_str() << endl;
	cout << "size expert: 7 actual: ";
	cout << s.c_size() << endl;
	cout << "capacity expert: 7 actual: ";
	cout << s.c_capacity() << endl;
	cout << endl;

	s.Insert(5, " world");
	cout << "str expert: hello world!! actual: ";
	cout << s.c_str() << endl;
	cout << "size expert: 13 actual: ";
	cout << s.c_size() << endl;
	cout << "capacity expert: 13 actual: ";
	cout << s.c_capacity() << endl;
	cout << endl;
	
	s.Insert(0, "emmmm ");
	cout << "str expert: emmmm hello world!! actual: ";
	cout << s.c_str() << endl;
	cout << "size expert: 19 actual: ";
	cout << s.c_size() << endl;
	cout << "capacity expert: 19 actual: ";
	cout << s.c_capacity() << endl;
	cout << endl;
}

void Test_Erase() {
	TEST_HEADER;
	String s("hello world");

	s.Erase(12);
	cout << "str expert: hello world actual: ";
	cout << s.c_str() << endl;
	cout << "size expert: 11 actual: ";
	cout << s.c_size() << endl;
	cout << "capacity expert: 11 actual: ";
	cout << s.c_capacity() << endl;
	cout << endl;
	
	s.Erase(10, 2);
	cout << "str expert: hello worl actual: ";
	cout << s.c_str() << endl;
	cout << "size expert: 10 actual: ";
	cout << s.c_size() << endl;
	cout << "capacity expert: 11 actual: ";
	cout << s.c_capacity() << endl;
	cout << endl;

	s.Erase(6, 2);
	cout << "str expert: hello rl actual: ";
	cout << s.c_str() << endl;
	cout << "size expert: 8 actual: ";
	cout << s.c_size() << endl;
	cout << "capacity expert: 11 actual: ";
	cout << s.c_capacity() << endl;
	cout << endl;

	s.Erase(0, 4);
	cout << "str expert: o rl actual: ";
	cout << s.c_str() << endl;
	cout << "size expert: 4 actual: ";
	cout << s.c_size() << endl;
	cout << "capacity expert: 11 actual: ";
	cout << s.c_capacity() << endl;
	cout << endl;
}

void Test_Replace1() {
	TEST_HEADER;
	String s("ohello worldo");
	s.Replace('o', 'a');
	cout << "str expert: ahella warlda actual: ";
	cout << s.c_str() << endl;
}

void Test_equal() {
	TEST_HEADER;
	String s1("hello");
	String s2("hello");
	String s3("hella");
	String s4("world");
	String s5("helloa");
	bool ret = (s1 == s2);
	printf("ret expert: 1 actual: %d\n", ret);
	ret = (s1 == s3);
	printf("ret expert: 0 actual: %d\n", ret);
	ret = (s1 == s4);
	printf("ret expert: 0 actual: %d\n", ret);
	ret = (s1 == s5);
	printf("ret expert: 0 actual: %d\n", ret);
}

void Test_not_equal() {
	TEST_HEADER;
	String s1("hello");
	String s2("hello");
	String s3("hella");
	String s4("world");
	bool ret = (s1 != s2);
	printf("ret expert: 0 actual: %d\n", ret);
	ret = (s1 != s3);
	printf("ret expert: 1 actual: %d\n", ret);
	ret = (s1 != s4);
	printf("ret expert: 1 actual: %d\n", ret);
}

void Test_big() {
	TEST_HEADER;
	String s1("hello");
	String s2("hello");
	String s3("hella");
	String s4("world");
	String s5("helloa");
	String s6("hell");
	bool ret = (s1 > s2);
	printf("ret expert: 0 actual: %d\n", ret);
	ret = (s1 > s3);
	printf("ret expert: 1 actual: %d\n", ret);
	ret = (s1 > s4);
	printf("ret expert: 0 actual: %d\n", ret);
	ret = (s1 > s5);
	printf("ret expert: 0 actual: %d\n", ret);
	ret = (s1 > s6);
	printf("ret expert: 1 actual: %d\n", ret);
}

void Test_big_equal() {
	TEST_HEADER;
	String s1("hello");
	String s2("hello");
	String s3("hella");
	String s4("world");
	String s5("helloa");
	String s6("hell");
	bool ret = (s1 >= s2);
	printf("ret expert: 1 actual: %d\n", ret);
	ret = (s1 >= s3);
	printf("ret expert: 1 actual: %d\n", ret);
	ret = (s1 >= s4);
	printf("ret expert: 0 actual: %d\n", ret);
	ret = (s1 >= s5);
	printf("ret expert: 0 actual: %d\n", ret);
	ret = (s1 >= s6);
	printf("ret expert: 1 actual: %d\n", ret);
}

void Test_small_equal() {
	TEST_HEADER;
	String s1("hello");
	String s2("hello");
	String s3("hella");
	String s4("world");
	String s5("helloa");
	String s6("hell");
	bool ret = (s1 <= s2);
	printf("ret expert: 1 actual: %d\n", ret);
	ret = (s1 <= s3);
	printf("ret expert: 0 actual: %d\n", ret);
	ret = (s1 <= s4);
	printf("ret expert: 1 actual: %d\n", ret);
	ret = (s1 <= s5);
	printf("ret expert: 1 actual: %d\n", ret);
	ret = (s1 <= s6);
	printf("ret expert: 0 actual: %d\n", ret);
}

void Test_small() {
	TEST_HEADER;
	String s1("hello");
	String s2("hello");
	String s3("hella");
	String s4("world");
	String s5("helloa");
	String s6("hell");
	bool ret = (s1 < s2);
	printf("ret expert: 0 actual: %d\n", ret);
	ret = (s1 < s3);
	printf("ret expert: 0 actual: %d\n", ret);
	ret = (s1 < s4);
	printf("ret expert: 1 actual: %d\n", ret);
	ret = (s1 < s5);
	printf("ret expert: 1 actual: %d\n", ret);
	ret = (s1 < s6);
	printf("ret expert: 0 actual: %d\n", ret);
}

void Test_operator_add_ch1() {
		TEST_HEADER;
		String s1("hello");
		String s2 = s1 + 'a';
		printf("s1:\nstr expert: hello actual:%s\n", s1.c_str());
		printf("s2:\nstr expert: helloa actual:%s\n", s2.c_str());
}

void Test_operator_add_ch2() {
		TEST_HEADER;
		String s("hello");
		s += 'a';
		printf("s:\nstr expert: helloa actual:%s\n", s.c_str());
}

void Test_operator_add_str1() {
		TEST_HEADER;
		String s1("hello");
		String s2 = s1 + " world";
		printf("s1:\nstr expert: hello actual:%s\n", s1.c_str());
		printf("s2:\nstr expert: hello world actual:%s\n", s2.c_str());
}

void Test_operator_add_str2() {
		TEST_HEADER;
		String s("hello");
		s += " world";
		printf("s:\nstr expert: hello world actual:%s\n", s.c_str());
}


int main() {
	system("clear");
	Test_String();
	Test_CopyString();
	Test_Swap();
	Test_operator1();
	Test_c_str();
	Test_PushBackch();
	Test_PushBackstr();
	Test_PopBack();	
	Test_Insert1();
	Test_Insert2();
	Test_Erase();
	Test_Replace1();

	Test_equal();
	Test_not_equal();
	Test_big();
	Test_big_equal();
	Test_small();

	Test_operator_add_ch1();
	Test_operator_add_ch2();
	Test_operator_add_str1();
	Test_operator_add_str2();

	return 0;
}
#endif
