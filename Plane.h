/****************************************************************
	FILE:		Plane.h
	AUTHOR:		Tommy Deng
				s199762338

	PURPOSE:	Header file for the plane object.
****************************************************************/

#ifndef PLANE_H
#define PLANE_H

#include <iostream>

#include "Seat.h"

using namespace std;

class Plane
{
protected:
	vector<Seat*> *seat = new vector<Seat*>;

	const int NUM_OF_SEATS = 10;

	int flightId;
	string destinationCity;
	string destinationCountry;
	string timeDepart;
	string timeArrive;
	string duration;


	int numOfPassengers;

public:
	// Default contructor
	Plane();

	// Parameterized contructor
	Plane(int id, string dest);

	// Decontructor
	~Plane();

	// Accessor functions
	int getId();
	int getNumOfSeats();
	string getDestinationCity();
	string getDestinationCountry();
	string getTimeDepart();
	string getTimeArrive();
	string getDuration();
	int getNumOfPassengers();

	// Mutator functions
	void setId(int id);
	void setDestinationCity(string d);
	void setDestinationCountry(string d);
	void setTimeDepart(string t);
	void setTimeArrive(string t);
	void setDuration(string d);
	void setNumOfPassengers(int n);


	Seat& getSeat(int s);
	void setSeat(int s, int id);
};

#endif // !PLANE_H
