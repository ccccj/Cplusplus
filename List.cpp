#include <iostream>
#include "List.h"

using namespace std;

List::List(const List& l)
	:_head(new Node(DataType()))
{
	_head->_next = _head; 
	_head->_prev = _head; 
	Node* cur = l._head->_next;
	while (cur != l._head) {
		PushBack(cur->_data);
		cur = cur->_next;
	}
}

void List::PushBack(DataType x) {
	Node* prev = _head->_prev;
	Node* new_Node = new Node(x);
	// prev new_Node _head
	prev->_next = new_Node;
	new_Node->_prev = prev;
	new_Node->_next = _head;
	_head->_prev = new_Node;
}

List& List::operator=(List l) {
	swap(_head, l._head);
}

List::~List() {
	Node* cur = _head->_next;
	while (cur != _head) {
		Erase(cur);
		cur = cur->_next;
	}
}

void List::PushFront(DataType x) {
	Node* next = _head->_next;
	Node* new_Node = new Node(x);
	// _head new_Node next
	_head->_next = new_Node;
	new_Node->_prev = _head;
	new_Node->_next = next;
	next->_prev = new_Node;
}

void List::PopBack() {
	if (_head->_next == _head) {
		return;
	}
	Node* to_delete = _head->_prev;
	Node* prev = to_delete->_prev;
	// prev to_delete _head
	prev->_next = _head;
	_head->_prev = prev;
	delete to_delete;
}

void List::PopFront() {
	if (_head->_next == _head) {
		return;
	}
	Node* to_delete = _head->_next;
	Node* next = to_delete->_next;
	// _head to_delete next
	_head->_next = next;
	next->_prev = _head;
	delete to_delete;
}

ListNode* List::Find(DataType x) {
	Node* cur = _head->_next;
	while (cur != _head) {
		if (cur->_data == x) {
			return cur;
		}
		cur = cur->_next;
	}
}

void List::Insert(Node* pos, DataType x) {
	if (pos == NULL) {
		return;
	}
	Node* next = pos->_next;
	Node* new_Node = new Node(x);
	// pos new_Node next
	pos->_next = new_Node;
	new_Node->_prev = pos;
	new_Node->_next = next;
	next->_prev = new_Node;
}
	
void List::Erase(Node* pos) {
	if (pos == _head) {
		return;
	}
	Node* prev = pos->_prev;
	Node* next = pos->_next;
	// prev pos next
	prev->_next = next;
	next->_prev = prev;
	delete pos;
}

void List::Show() {
	Node* cur = _head->_next;
	while (cur != _head) {
		cout << cur->_data << " ";
		cur = cur->_next;
	}
	cout << endl;
}

//////////////////////
// 测试代码
//////////////////////
#if 1
#include <cstdio>
#include <cstdlib>
#define TEST_HEADER printf("\n=========%s========\n", __FUNCTION__)

void Test() {
	TEST_HEADER;
	List l;
	l.PushBack(1);
	l.Show();

	l.PopBack();
	l.Show();
	
	l.PushBack(2);
	l.PushBack(3);
	l.PushBack(4);
	l.PushBack(5);
	l.Show();

	l.PopBack();
	l.Show();
	
	List l2(l);
	l2.Show();
	l2.PopFront();
	l2.Show();

	List l3;
	l3 = l;
	l3.Show();

	l3.PushFront(1);
	l3.Show();
	ListNode* pos = l3.Find(2);
	l3.Erase(pos);
	l3.Show();

	pos = l3.Find(3);
	l3.Insert(pos, 100);
	l3.Show();
}

int main() {
	system("clear");
	Test();
	return 0;
}


#endif

