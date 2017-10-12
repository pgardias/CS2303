/*
 * Doodlebug.h
 *
 *  Created on: Oct 8, 2017
 *      Author: etarthur
 */

#ifndef DOODLEBUG_H_
#define DOODLEBUG_H_

#include "Organism.h"

class Doodlebug: public Organism {
private:
	int hunger;
public:
	Doodlebug();
	virtual ~Doodlebug();
	Doodlebug(int x, int y);
	int getTime();
	void move();
	Doodlebug* breed();
	bool isMove(int x, int y);
	bool starve();
	void action();
	void simpleMove();
};

#endif /* DOODLEBUG_H_ */
