#pragma once

class Date {
public:
	// 构造函数
	Date(int year, int month, int date);
	// 设置
	Date& set(int year, int month, int date);
	// 拷贝构造
	Date(const Date& d);
	// 赋值符重载
	Date& operator=(const Date& d);

	// 运算符重载
	bool operator==(const Date& d);
	bool operator>=(const Date& d);
	bool operator<=(const Date& d);
	bool operator<(const Date& d);
	bool operator>(const Date& d);
	bool operator!=(const Date& d);

	Date operator+(int day);
	Date operator-(int day);
	int operator-(const Date& d);

	Date& operator+=(int day);
	Date& operator-=(int day);

	Date& operator++();
	Date operator++(int);
	Date& operator--();
	Date operator--(int);

	// 析构
	~Date();

	// 显示
	void show();

private:
	bool IsLeap(int year);
	int GetMonthDay(int year, int month);
	bool IsValid(const Date& d);
	int GetYearDay(int year);

	int _year;
	int _month;
	int _date;
};

