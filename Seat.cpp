/****************************************************************
	FILE:		Seat.cpp
	AUTHOR:		Tommy Deng
				s199762338

	PURPOSE:	CPP file for the seat object (Seat.h).
****************************************************************/

#include "Seat.h"

Seat::Seat()
{
	// initialize passenger
	*passenger = new Passenger("_____", "_____", "__________", "__________");

	int seatId = 0;
	bool reserved = false;

}

Seat::Seat(int id)
{
	// initialize passenger
	*passenger = new Passenger("_____", "_____", "__________", "__________");

	seatId = id;
}

Seat::~Seat()
{
}

bool Seat::getReserved()
{
	return reserved;
}

void Seat::setReserved(bool r)
{
	reserved = r;
}

Passenger& Seat::getPassenger()
{
	return **passenger;
}

void Seat::setPassenger(string fn, string ln, string a, string p)
{
	// put passenger information within Passenger parameters
	*passenger = new Passenger(fn, ln, a, p);
}
