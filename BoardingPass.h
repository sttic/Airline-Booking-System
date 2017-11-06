/****************************************************************
	FILE:		BoardingPass.h
	AUTHOR:		Tommy Deng
				s199762338

	PURPOSE:	Header file for the boarding pass object. The file
				also contains the Economy and Business class for
				inheritance.
****************************************************************/

#ifndef BOARDINGPASS_H
#define BOARDINGPASS

#include <iostream>

using namespace std;

class BoardingPass
{
protected:
	string className;

	string from;
	string toCity, toCountry;
public:
	// Default constructor
	BoardingPass();

	// Parameterized contructor
	BoardingPass(string from, string toCity, string toCountry);

	// Destructor
	~BoardingPass();

	// Accessor functions
	string getClassName();

	string getFrom();
	string getToCity();
	string getToCountry();
	
	// Mutator functions
	void setFrom(string f);
	void setToCity(string t);
	void setToCountry(string t);

};

class Economy : public BoardingPass
{
protected:
	bool hasEconomy;
public:
	// Default constructor
	Economy();

	// Parameterized constructor
	Economy(bool hasEconomy);

	// Destructor
	~Economy();

	// Accessor functions
	bool getHasEcon();

	// Mutator functions
	void setHasEcon(bool e);
};

class Business : public BoardingPass
{
protected:
	bool hasBusiness;

	string preferredDrink;
	string preferredMeal;
public:
	// Default constructor
	Business();

	// Parameterized constructor
	Business(string drink, string meal, bool hasBusiness);

	// Destructor
	~Business();

	// Accessor functions
	bool getHasBus();
	string getDrink();
	string getMeal();

	// Mutator functions
	void setHasBus(bool b);
	void setDrink(string d);
	void setMeal(string m);

};
#endif // !BOARDINGPASS_H