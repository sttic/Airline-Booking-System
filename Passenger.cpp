/****************************************************************
	FILE:		Passenger.cpp
	AUTHOR:		Tommy Deng
				s199762338

	PURPOSE:	CPP for the passenger object (Passenger.h).
****************************************************************/

#include "Passenger.h"

Passenger::Passenger()
{
	// initialize boarding pass
	economy = new Economy(false);
	business = new Business("", "", false);

	// initialize passenger variables
	int flightId = 0;
	int seatId = 0;

	string firstName = "_____";
	string lastName = "_____";
	string address = "__________";
	string phoneNumber = "__________";
}

Passenger::Passenger(string fn, string ln, string a, string p)
{
	firstName = fn;
	lastName = ln;
	address = a;
	phoneNumber = p;
}

Passenger::~Passenger()
{
}

int Passenger::getFlightId()
{
	return flightId;
}

int Passenger::getSeatId()
{
	return seatId;
}

string Passenger::getFirstName()
{
	return firstName;
}

string Passenger::getLastName()
{
	return lastName;
}

string Passenger::getAddress()
{
	return address;
}

string Passenger::getPhoneNumber()
{
	return phoneNumber;
}

void Passenger::setFlightId(int p)
{
	flightId = p;
}

void Passenger::setSeatId(int s)
{
	seatId = s;
}

void Passenger::setFirstName(string n)
{
	firstName = n;
}

void Passenger::setLastName(string n)
{
	lastName = n;
}

void Passenger::setAddress(string a)
{
	address = a;
}

void Passenger::setPhoneNumber(string p)
{
	phoneNumber = p;
}

Economy& Passenger::getEconomy()
{
	return *economy;
}

Business & Passenger::getBusiness()
{
	return *business;
}

