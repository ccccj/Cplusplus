#pragma once
#include <cstring>

class String {
public:
	
	
	// 构造函数
	String(const char* str = "");
	
	// 拷贝构造
	String(const String& s);
	
	// 析构函数
	~String();
	
	// 交换
	void Swap(String& s);
	
	// 赋值运算符重载
	// String& operator=(const String& s);
	String& operator=(String s);
	
	// 查看_str
	const char* c_str();
	// 这两个这里用于测试
	size_t c_size();
	size_t c_capacity();

	// 扩容
	void Expand(size_t n);

	// 尾插
	void PushBack(char ch);
	void PushBack(const char* str);

	// 尾删
	void PopBack();

	// 插入
	void Insert(size_t pos, char ch);
	void Insert(size_t pos, const char* str);

	// 删除
	void Erase(size_t pos, size_t n = 1);

	// 替代
	void Replace(char ch1, char ch2);


	// +
	String operator+(char ch);
	String& operator+=(char ch); 
	String operator+(const char* str);
	String& operator+=(const char* str);


	// 比较
	bool operator==(const String& s); 
	bool operator!=(const String& s); 
	bool operator>(const String& s); 
	bool operator>=(const String& s); 
	bool operator<(const String& s); 
	bool operator<=(const String& s); 



private:
	char* _str;
	size_t _size; // 已用空间
	size_t _capacity; // 可用总大小
};
