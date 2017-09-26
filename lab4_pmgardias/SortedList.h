/*
 * SortedList.h
 *
 *  Created on: Aug 26, 2013
 *      Author: Hugh C. Lauer
 */

#ifndef SORTEDLIST_H_
#define SORTEDLIST_H_

#include <cstdio>
#include <cstdlib>

class SortedList {
public:
	void InsertItem (long item);
	long getSum(void);
	void printReverseList(void);

	SortedList();	//	constructor
	~SortedList();	//	destructor

private:
	class listItem;
	listItem *head;
	long sumOfItems;

	void printLastItems(listItem *p);

	class listItem {	// an internal class
	public:

		const long payload;
		listItem *next;

		inline listItem(long item) : payload(item), next(NULL) {};

	};	// class listItem

};

#endif /* SORTEDLIST_H_ */
