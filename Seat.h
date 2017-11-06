/****************************************************************
	FILE:		Seat.h
	AUTHOR:		Tommy Deng
				s199762338

	PURPOSE:	Header file for the seat object.
****************************************************************/

#ifndef SEAT_H
#define SEAT_H

#include <iostream>
#include "Passenger.h"
#include <sstream>

using namespace std;

class Seat
{
protected:
	Passenger* *passenger = new Passenger*;

	int seatId;
	bool reserved;

public:
	// Default constructor
	Seat();

	// Parameterized contructor
	Seat(int id);

	// Destructor
	~Seat();

	// Accessor functions
	bool getReserved();

	// Mutator functions
	void setReserved(bool r);

	Passenger& getPassenger();
	void setPassenger(string fn, string ln, string a, string p);
};

#endif // !SEAT_H