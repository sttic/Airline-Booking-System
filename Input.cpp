/****************************************************************
	FILE:		Input.cpp
	AUTHOR:		Tommy Deng
				s199762338

	PURPOSE:	Handles getting user input for common variables.
****************************************************************/

#include "Input.h"

Input::Input()
{
}

Input::~Input()
{
}

void Input::setReservation(	vector<Plane*> *plane,
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
							string meal)
{
	// assign information to objects

	(*plane)[flightId]->getSeat(seatId).setPassenger(firstName, lastName, ssStreet, phone);
	(*plane)[flightId]->getSeat(seatId).getPassenger().setFlightId(flightId);
	(*plane)[flightId]->getSeat(seatId).getPassenger().setSeatId(seatId);
	(*plane)[flightId]->getSeat(seatId).setReserved(true);

	if (classType == "E")
	{
		(*plane)[flightId]->getSeat(seatId).getPassenger().getEconomy().setHasEcon(true);
		(*plane)[flightId]->getSeat(seatId).getPassenger().getEconomy().setFrom(from);
		(*plane)[flightId]->getSeat(seatId).getPassenger().getEconomy().setToCity(toCity);
		(*plane)[flightId]->getSeat(seatId).getPassenger().getEconomy().setToCountry(toCountry);
	}
	else if (classType == "B")
	{
		(*plane)[flightId]->getSeat(seatId).getPassenger().getBusiness().setHasBus(true);
		(*plane)[flightId]->getSeat(seatId).getPassenger().getBusiness().setFrom(from);
		(*plane)[flightId]->getSeat(seatId).getPassenger().getBusiness().setToCity(toCity);
		(*plane)[flightId]->getSeat(seatId).getPassenger().getBusiness().setToCountry(toCountry);

		(*plane)[flightId]->getSeat(seatId).getPassenger().getBusiness().setDrink(drink);
		(*plane)[flightId]->getSeat(seatId).getPassenger().getBusiness().setMeal(meal);
	}
}

int Input::flightId(int numPlanes)
{
	int flightId;

	cout << "Flight number: ";
	cin >> flightId;
	while (flightId < 0 || flightId > numPlanes - 1)
	{
		cout << "Invalid input. Enter numbers 0 to " << numPlanes - 1 << endl;
		cin >> flightId;
	}

	return flightId;
}

int Input::seatId(const vector<Plane*>* plane, int flightId)
{
	int seatId;

	cout << "Seat number: ";
	cin >> seatId;
	while (seatId < 0 || seatId >(*plane)[flightId]->getNumOfSeats() - 1)
	{
		cout << "Invalid input. Enter numbers 0 to " << (*plane)[flightId]->getNumOfSeats() - 1 << endl;
		cin >> seatId;
	}

	return seatId;
}

string Input::drink()
{
	string drink;

	cout << "Preferred drink: ";
	cin >> drink;

	return drink;
}

string Input::meal()
{
	string meal;

	cout << "Preferred meal: ";
	cin >> meal;

	return meal;
}

string Input::boardingPass()
{
	string classType;

	cin >> classType;
	while (classType != "E" && classType != "B")
	{
		cout << "Invalid input. Enter letters \"E\" or \"B\"" << endl;
		cin >> classType;
	}

	return classType;
}

int Input::destinationChoice(int numPlanes)
{
	int destinationChoice;

	cin >> destinationChoice;
	while (destinationChoice < 1 || destinationChoice > numPlanes)
	{
		cout << "Invalid input. Select destinations from 1 to " << numPlanes << endl;
		cin >> destinationChoice;
	}

	return destinationChoice;
}
