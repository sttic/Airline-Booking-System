/****************************************************************
	FILE:		Input.h
	AUTHOR:		Tommy Deng
				s199762338

	PURPOSE:	Handles getting user input for common variables.
****************************************************************/

#ifndef INPUT_H
#define INPUT_H

#include <iostream>

#include "Plane.h"

using namespace std;

class Input
{
public:
	// Default constructor
	Input();

	// Destructor
	~Input();

	// sets reservation data
	void setReservation(vector<Plane*> *plane,
						int flightId,
						int seatId,
						string firstName,
						string lastName,
						string ssStreet,
						string phone,
						string classType,
						string from,
						string toCity,
						string toCountry,
						string drink,
						string meal);

	// get common user inputs
	// prompts the user to a value and verifies validity
	int flightId(int numPlanes);
	int seatId(const vector<Plane*> *plane, int flightId);
	string drink();
	string meal();

	string boardingPass();
	int destinationChoice(int numPlanes);

};

#endif // !INPUT_H
