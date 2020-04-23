#pragma once
#include <cstring>

class String {
public:
	
	// 构造函数
	String(const char* str = "");
	
	int& GetpCount();

	// 拷贝构造
	String(const String& s);
	
	// 析构函数
	~String();
	
	// 写时拷贝
	void CopyOnWrite();
	
	// 赋值运算符重载
	String& operator=(const String& s);
	
	// 查看_str
	const char* c_str();

	size_t c_size();
	size_t c_capacity();

	// 扩容
	void Expand(size_t n);

	// 重载括号
	char& operator[](size_t pos); 

private:
	char* _str; // 引用计数在开头
	size_t _size; // 已用空间
	size_t _capacity; // 可用总大小
};
