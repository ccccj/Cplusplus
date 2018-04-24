#pragma once
#include <cstddef>

typedef int DataType;

class Vector {

public:
	Vector();
	Vector(const Vector& v);
	Vector& operator=(const Vector& v);
	~Vector();
	size_t Size() const;
	size_t Capacity() const;
	void Expand(size_t n);
	void PushBack(DataType x);
	void Reserve(size_t n);
	void PopBack();
	void Insert(size_t pos, DataType x);
	void Erase(size_t pos);
	size_t Find(DataType x);
	void Show();

private:
	DataType* _first;
	DataType* _finish;
	DataType* _endofstorage;
};
