using namespace std;
#include "Date.h"
#include <iostream>
#include <cassert>


void Date::show() {
	cout << _year << '-' << _month << '-' << _date << endl;
}

bool Date::IsLeap(int year) {
	if ((year % 4 == 0 && year % 100 != 0) 
			|| year % 400 == 0)
		return true;
	return false;
}

int Date::GetMonthDay(int year, int month) {
	int monthday[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int day = monthday[month];
	if (month == 2 && IsLeap(year) == true)
		++day;
	return day;
}

bool Date::IsValid(const Date& d) {
	if (d._year > 0
			&& d._month >= 1 && d._month <= 12
			&& d._date <= GetMonthDay(d._year, d._month) && d._date >= 1)
		return true;
	return false;
}

int Date::GetYearDay(int year) {
	if (IsLeap(year))
		return 366;
	else
		return 365;
}

// 构造函数
Date::Date(int year = 1900, int month = 1, int date = 1) {
	_year = year;
	_month = month;
	_date = date;
	assert(IsValid(*this) > 0);
}

Date& Date::set(int year, int month, int date) {
	_year = year;
	_month = month;
	_date = date;
	assert(IsValid(*this) > 0);
	return *this;
}

// 拷贝构造
Date::Date(const Date& d) {
	// 实际上还传入了 this 指针(d2), d 为 d1
	_year = d._year;
	_month = d._month;
	_date = d._date;
}

// 赋值符重载
Date& Date::operator=(const Date& d) {
	_year = d._year;
	_month = d._month;
	_date = d._date;
	return *this;
}


// 运算符重载
bool Date::operator==(const Date& d) {
	return (_year == d._year && _month == d._month && _date == d._date);
}

bool Date::operator>(const Date& d) {
	if (_year > d._year 
			|| (_year == d._year && _month > d._month)
			|| (_year == d._year && _month == d._month && _date > d._date))
		return true;
	return false;
}

bool Date::operator<=(const Date& d) {
	return !(*this > d);
}

bool Date::operator>=(const Date& d) {
	return (*this > d) || (*this == d);
}

bool Date::operator<(const Date& d) {
	return !(*this >= d);
}

bool Date::operator!=(const Date& d) {
	return !(*this == d);
}

Date& Date::operator+=(int day) {
	_date += day;
	while (!IsValid(*this)) {
		_date -= GetMonthDay(_year, _month);
		++_month;
		if (_month == 13) {
			_month = 1;
			++_year;
		}
	}
	return *this;
}

Date Date::operator+(int day) {
	Date d(*this);
	d += day;
	return d;
}

Date& Date::operator-=(int day) {
	_date -= day;
	while (!IsValid(*this)) {
		if (_month > 1) {
			_date += GetMonthDay(_year, _month - 1);
		} else {
			_date += GetMonthDay(_year, 12);
		}
		--_month;
		if (_month == 0) {
			_month = 12;
			--_year;
		}
	}
	return *this;
}

Date Date::operator-(int day) {
	Date d(*this);
	d -= day;
	return d;
}

Date& Date::operator++() {
	// 前置++
	*this += 1;
	return *this;
}

Date Date::operator++(int) {
	// 后置++
	Date ret(*this);
	*this += 1;
	return ret;
}

int Date::operator-(const Date& d) {
	int flag = (*this > d) ? 1 : -1;
	int ybig = flag == 1 ? _year : d._year;
	int ysml = flag != 1 ? _year : d._year;
	int mbig = flag == 1 ? _month : d._month;
	int msml = flag != 1 ? _month : d._month;
	int dbig = flag == 1 ? _date : d._date;
	int dsml = flag != 1 ? _date : d._date;

	int day = GetMonthDay(ysml++, msml++) - dsml + dbig;
	while (msml <= 12) {
		day += GetMonthDay(ysml, msml++);
	}
	while (ysml < ybig) {
		day += GetYearDay(ysml++);
	}
	msml = 1;
	while (msml < mbig) {
		day += GetMonthDay(ysml, msml++);
	}
	return -flag * day;
}

Date& Date::operator--() {
	*this -= 1;
	return *this;
}

Date Date::operator--(int) {
	Date ret(*this);
	*this -= 1;
	return ret;
}

Date::~Date() {
	_year = 1900;
	_month = 1;
	_date = 1;
	// 为了验证
	// this->show();
}

/////////////////////////////
// 以下为测试
/////////////////////////////
#if 1
#include <cstdio>
#include <cstdlib>
#include <cstddef>
#define TEST_HEADER printf("\n========%s=======\n", __FUNCTION__)

void TestDate() {
	TEST_HEADER;
	Date d1;
	d1.show();
	Date d2(2018, 3, 20);
	d2.show();
//	Date d3(2018, 2, 29);
}

void TestDateSet() {
	TEST_HEADER;
	Date d;
	d.show();
	d.set(2018, 3, 20);
	d.show();
}

void TestCopy() {
	TEST_HEADER;
	Date d1(2018, 3, 20);
	Date d2(d1);
	d2.show();
}

void TestOperateEqual() {
	TEST_HEADER;
	Date d1(2018, 3, 20);
	Date d2(1997, 12, 7);
	Date d3;
	d3 = d2 = d1;
	d2.show();
	d3.show();
}

void TestOperatorEqual() {
	TEST_HEADER;
	Date d1(2018, 3, 20);
	Date d2(1997, 12, 7);
	Date d3(2018, 3, 20);

	cout << "==" << endl;
	// 等于
	bool ret = (d1 == d2);
	cout << "ret  expert:  " << 0 << endl;
	cout << "ret  actual:  " << ret << endl;
	ret = (d1 == d3);
	cout << "ret  expert:  " << 1 << endl;
	cout << "ret  actual:  " << ret << endl;

	cout << '>' << endl;
	// 大于
	ret = (d1 > d2);
	cout << "ret  expert:  " << 1 << endl;
	cout << "ret  actual:  " << ret << endl;
	ret = (d2 > d1);
	cout << "ret  expert:  " << 0 << endl;
	cout << "ret  actual:  " << ret << endl;
	ret = (d1 > d3);
	cout << "ret  expert:  " << 0 << endl;
	cout << "ret  actual:  " << ret << endl;

	cout << "<=" << endl;
	// 小于等于
	ret = (d1 <= d2);
	cout << "ret  expert:  " << 0 << endl;
	cout << "ret  actual:  " << ret << endl;
	ret = (d2 <= d1);
	cout << "ret  expert:  " << 1 << endl;
	cout << "ret  actual:  " << ret << endl;
	ret = (d1 <= d3);
	cout << "ret  expert:  " << 1 << endl;
	cout << "ret  actual:  " << ret << endl;

	cout << ">=" << endl;
	// 大于等于
	ret = (d1 >= d2);
	cout << "ret  expert:  " << 1 << endl;
	cout << "ret  actual:  " << ret << endl;
	ret = (d2 >= d1);
	cout << "ret  expert:  " << 0 << endl;
	cout << "ret  actual:  " << ret << endl;
	ret = (d1 >= d3);
	cout << "ret  expert:  " << 1 << endl;
	cout << "ret  actual:  " << ret << endl;

	cout << '<' << endl;
	// 小于
	ret = (d1 < d2);
	cout << "ret  expert:  " << 0 << endl;
	cout << "ret  actual:  " << ret << endl;
	ret = (d2 < d1);
	cout << "ret  expert:  " << 1 << endl;
	cout << "ret  actual:  " << ret << endl;
	ret = (d1 < d3);
	cout << "ret  expert:  " << 0 << endl;
	cout << "ret  actual:  " << ret << endl;
	
	cout << "!=" << endl;
	// 不等于
	ret = (d1 != d2);
	cout << "ret  expert:  " << 1 << endl;
	cout << "ret  actual:  " << ret << endl;
	ret = (d1 != d3);
	cout << "ret  expert:  " << 0 << endl;
	cout << "ret  actual:  " << ret << endl;
}

void TestOperatorAdd1() {
	TEST_HEADER;
	Date d(1997, 12, 7);
	Date d2;
	d2 = d + 12;
	cout << "d2 expert : 1997-12-19" << endl << "actual :";
	d2.show();
	cout << "d1 expert : 1997-12-7" << endl << "actual :";
	d.show();

	d2 = d + 32;
	cout << "d2 expert : 1998-1-8" << endl << "actual :";
	d2.show();

	d2 = d + 1032;
	cout << "d2 expert : 2000-10-4" << endl << "actual :";
	d2.show();

	Date d1(1995, 8, 30);
	d2 = d1 + 8888;
	cout << "d2 expert : 2019-12-30" << endl << "actual :";
	d2.show();
	d += 1032;
	cout << "d expert : 2000-10-4" << endl << "actual :";
	d.show();
}

void TestOperatorSub1() {
	TEST_HEADER;
	Date d(2018, 3, 20);
	Date d2;
	d2 = d - 10;
	cout << "d2 expert : 2018-3-10" << endl << "actual :";
	d2.show();
	cout << "d1 expert : 2018-3-20" << endl << "actual :";
	d.show();

	d2 = d - 30;
	cout << "d2 expert : 2018-2-18" << endl << "actual :";
	d2.show();
	
	d2 = d - 3030;
	cout << "d2 expert : 2009-12-2" << endl << "actual :";
	d2.show();

	d -= 3030;
	cout << "d expert : 2009-12-2" << endl << "actual :";
	d.show();
}

void TestOperatorSub2() {
	TEST_HEADER;
	Date d1(1995, 8, 30);
	Date d2(1997, 12, 7);
	Date d3(2018, 3, 20);
	int ret = d1 - d2;
	cout << "ret expert : 830" << endl;
	cout << "ret actual : " << ret << endl;
	ret = d1 - d3;
	cout << "ret expert : 8238" << endl;
	cout << "ret actual : " << ret << endl;
	ret = d2 - d1;
	cout << "ret expert : -830" << endl;
	cout << "ret actual : " << ret << endl;
}

void TestOperatorAdd2() {
	TEST_HEADER;
	Date d1(2020, 12, 31);
	Date d2(2000, 2, 28);
	cout << "expert : 2021-1-1" << endl << "actual :";
	(++d1).show();
	cout << "expert : 2000-2-28" << endl << "actual :";
	(d2++).show();
	cout << "expert : 2000-2-29" << endl << "actual :";
	d2.show();
}

void TestOperatorSub3() {
	TEST_HEADER;
	Date d1(2020, 12, 31);
	Date d2(2000, 3, 1);
	cout << "expert : 2021-12-30" << endl << "actual :";
	(--d1).show();
	cout << "expert : 2000-3-1" << endl << "actual :";
	(d2--).show();
	cout << "expert : 2000-2-29" << endl << "actual :";
	d2.show();
}

void TestDate2() {
	TEST_HEADER;
	Date d(2018, 3, 20);
	cout << "expert : 1900-1-1" << endl << "actual :";
	
}

int main() {
	system("clear");
  TestDate();
	TestDateSet();
  TestCopy();
  TestOperatorEqual();
  TestOperatorAdd1();
  TestOperatorSub1();
  TestOperatorSub2();
  TestOperatorAdd2();
  TestOperatorSub3();
	TestDate2();



	return 0;
}
#endif
