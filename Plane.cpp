/****************************************************************
	FILE:		Plane.cpp
	AUTHOR:		Tommy Deng
				s199762338

	PURPOSE:	CPP file for the plane object (Plane.h).
****************************************************************/

#include "Plane.h"

Plane::Plane()
{
	// initialize seats
	for (int i = 0; i < NUM_OF_SEATS; i++)
	{
		seat->push_back(new Seat(i));
		//(*(*seat)[i]) = Seat(i);
	}

	// to set, or not to set (the defaults/initial values)?
	int flightId = 0;
	string destinationCity;

	// redundant?
	int numOfPassengers = 0;

}

Plane::Plane(int id, string dest)
{
	// initialize seats
	for (int i = 0; i < NUM_OF_SEATS; i++)
	{
		seat->push_back(new Seat(i));
	}


	flightId = id;
	destinationCity = dest;
}

Plane::~Plane()
{
}

int Plane::getId()
{
	return flightId;
}

int Plane::getNumOfSeats()
{
	return NUM_OF_SEATS;
}

string Plane::getDestinationCity()
{
	return destinationCity;
}

string Plane::getDestinationCountry()
{
	return destinationCountry;
}

string Plane::getTimeDepart()
{
	return timeDepart;
}

string Plane::getTimeArrive()
{
	return timeArrive;
}

string Plane::getDuration()
{
	return duration;
}

int Plane::getNumOfPassengers()
{
	return numOfPassengers;
}

void Plane::setId(int id)
{
	flightId = id;
}

void Plane::setDestinationCity(string d)
{
	destinationCity = d;
}

void Plane::setDestinationCountry(string d)
{
	destinationCountry = d;
}

void Plane::setTimeDepart(string t)
{
	timeDepart = t;
}

void Plane::setTimeArrive(string t)
{
	timeArrive = t;
}

void Plane::setDuration(string d)
{
	duration = d;
}

void Plane::setNumOfPassengers(int n)
{
	numOfPassengers = n;
}

Seat& Plane::getSeat(int s)
{
	return (*(*seat)[s]);
}

void Plane::setSeat(int s, int id)
{
	//(*seat)[s] = new Seat(id);
	(*(*seat)[s]) = Seat(id);
}
