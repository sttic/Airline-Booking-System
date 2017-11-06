/****************************************************************
	FILE:		Passenger.h
	AUTHOR:		Tommy Deng
				s199762338

	PURPOSE:	Header file for the passenger object.
****************************************************************/

#ifndef PASSENGER_H
#define PASSENGER_H

#include <iostream>
#include <sstream>
#include <vector>

#include "BoardingPass.h"

using namespace std;

class Passenger
{
protected:
	Economy *economy = new Economy;
	Business *business = new Business;

	int flightId;
	int seatId;

	string firstName;
	string lastName;
	string address;
	string phoneNumber;

public:
	// Default contructor
	Passenger();

	// Parametized contructor
	Passenger(string fn, string ln, string a, string p);

	// Destructor
	~Passenger();

	// Accessor functions
	int getFlightId();
	int getSeatId();
	string getFirstName();
	string getLastName();
	string getAddress();
	string getPhoneNumber();

	// Mutator functions
	void setFlightId(int p);
	void setSeatId(int s);
	void setFirstName(string n);
	void setLastName(string n);
	void setAddress(string a);
	void setPhoneNumber(string p);

	Economy& getEconomy();
	Business& getBusiness();
};

#endif // !PASSENGER_H
