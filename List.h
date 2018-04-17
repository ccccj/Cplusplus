#pragma once

typedef int DataType; 

struct ListNode { 

	ListNode(DataType x) 
		:_data(x) 
		,_next(NULL) 
		,_prev(NULL)
	{}

	DataType _data; 
	ListNode* _next; 
	ListNode* _prev; 
}; 

class List { 

	typedef ListNode Node; 

public: 
	
	List() 
		:_head(new Node(DataType())) 
	{ 
		_head->_next = _head; 
		_head->_prev = _head; 
	} 

	List(const List& l); 
	List& operator=(List l); 
	~List(); 

	void PushBack(DataType x);
	void PushFront(DataType x); 
	void PopBack(); 
	void PopFront(); 
	Node* Find(DataType x); 
	void Insert(Node* pos, DataType x); 
	void Erase(Node* pos); 
	void Show();

private: 
	Node* _head; 

}; 


