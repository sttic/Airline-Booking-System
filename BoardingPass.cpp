/****************************************************************
	FILE:		BoardingPass.cpp
	AUTHOR:		Tommy Deng
				s199762338

	PURPOSE:	CPP file for the boarding pass object
				(BoardingPass.h). The file also contains the
				Economy and Business class for inheritance.
****************************************************************/

#include "BoardingPass.h"

BoardingPass::BoardingPass()
{
	className = "";
}

BoardingPass::BoardingPass(string from, string toCity, string toCountry)
{
	this->from = from;
	this->toCity = toCity;
	this->toCountry = toCountry;
}

BoardingPass::~BoardingPass()
{
}

string BoardingPass::getClassName()
{
	return className;
}

string BoardingPass::getFrom()
{
	return from;
}

string BoardingPass::getToCity()
{
	return toCity;
}

string BoardingPass::getToCountry()
{
	return toCountry;
}

void BoardingPass::setFrom(string f)
{
	from = f;
}

void BoardingPass::setToCity(string t)
{
	toCity = t;
}

void BoardingPass::setToCountry(string t)
{
	toCountry = t;
}



Economy::Economy()
{
	className = "Economy";

	hasEconomy = false;
}

Economy::Economy(bool hasEconomy)
{
	Economy();

	this->hasEconomy = hasEconomy;
}

Economy::~Economy()
{
}

bool Economy::getHasEcon()
{
	return hasEconomy;
}

void Economy::setHasEcon(bool e)
{
	hasEconomy = e;
}



Business::Business()
{
	className = "Business";

	hasBusiness = false;

	preferredDrink = "";
	preferredMeal = "";
}

Business::Business(string drink, string meal, bool hasBusiness)
{
	preferredDrink = drink;
	preferredMeal = meal;

	this->hasBusiness = hasBusiness;
}

Business::~Business()
{
}

bool Business::getHasBus()
{
	return hasBusiness;
}

string Business::getDrink()
{
	return preferredDrink;
}

string Business::getMeal()
{
	return preferredMeal;
}

void Business::setHasBus(bool b)
{
	hasBusiness = b;
}

void Business::setDrink(string d)
{
	preferredDrink = d;
}

void Business::setMeal(string m)
{
	preferredMeal = m;
}
