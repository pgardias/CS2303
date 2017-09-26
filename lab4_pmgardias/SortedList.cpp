/*
 * SortedList.cpp
 *
 *  Created on: Aug 26, 2013
 *      Author: Hugh C. Lauer
 */

#include <cstdio>
#include <iostream>

#include "SortedList.h"

SortedList::SortedList() {
	head = NULL;
	sumOfItems = 0;
}	// SortedList::SortedList()

SortedList::~SortedList(void) {
	listItem *p = head;

	while (!p) {
		listItem *q = p -> next;
		delete p;
		p = q;
	}

	return;

}	//	SortedList::~sortedList(void)


void SortedList::InsertItem(long itemValue){

	listItem *p = new listItem(itemValue);

	if (!head) {
		head = p;
		sumOfItems = itemValue;
		return;
	}

	else if (itemValue < head -> payload) {
		p -> next = head;
		head = p;
	}

	else {
		listItem *q = head;
		while ((q -> next) && (q -> next -> payload < itemValue))
			q = q -> next;
		p -> next = q -> next;
		q -> next = p;
	}

	sumOfItems += itemValue;

}	//	void SortedList::InsertItem(long itemValue)

long SortedList::getSum(void) {
	long checkSum = 0;
	for (listItem *p = head; p; p = p -> next)
		checkSum += p -> payload;
	if (checkSum != sumOfItems)
		throw checkSum;

	return sumOfItems;
}	// long SortedList::getSum(void)

void SortedList::printReverseList(void){

	printLastItems(head);
	std::cout << std::endl;
}	// void SortedList::printReverseList(void)

void SortedList::printLastItems(listItem *p){

	if (p -> next)
		printLastItems(p -> next);
	std::cout << p -> payload << " ";
}	// void SortedList::printLastItems(listItem *p)
