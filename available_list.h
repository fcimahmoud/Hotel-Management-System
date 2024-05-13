#pragma once
#include<iostream>
#include<string>
using namespace std;

struct Node {
	int offset;
	int size;
	Node* next;
};
 
class availableLinkedlist {
	Node* head;
	Node* rear;
public:


	availableLinkedlist();
	void addDeletedNodeToList(int offset,int size);
	void printLinkedList();
	bool isEmpty();
	int searchAndDeleteNode(int size_record);

};

availableLinkedlist::availableLinkedlist()
{
	head = NULL;
	rear = NULL;
}

void availableLinkedlist::addDeletedNodeToList(int offset, int size)
{
	Node* newnode = new Node;

	newnode->offset = offset;
	newnode->size = size;

	if (head == NULL && rear == NULL)
	{
		head = newnode;

		rear = newnode;
		newnode->next = NULL;
	}
	else {
		rear->next = newnode;
		newnode->next = NULL;
		rear = newnode;
	}
}

bool availableLinkedlist::isEmpty()
{
	return (head == NULL);
}

void availableLinkedlist::printLinkedList()
 {
	 Node* current = head;
	 while (current != nullptr) {
		 cout << "offset = " << current->offset << " "
			 << "size = " << current->size << endl;
		 current = current->next;
	 }
	 cout << endl;
 }

int availableLinkedlist::searchAndDeleteNode(int size_record)
 {
	 Node* current = head;
	 Node* previous = NULL;

	 while (current != NULL && current->size != size_record) {///---------------------
		 previous = current;
		 current = current->next;
	 }

	 if (current == NULL) {
		 return -1; 
		 // or any other value that indicates the size record value was not found
	 }

	 if (previous == NULL) {
		 head = current->next;
	 }
	 else {
		 previous->next = current->next;
	 }

	 int offset = current->offset;
	 delete current;
	 return offset;
 }




 

