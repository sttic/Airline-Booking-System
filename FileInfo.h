/****************************************************************
	FILE:		FileInfo.h
	AUTHOR:		Tommy Deng
				s199762338

	PURPOSE:	Handles the reading and writing of data to and from
				text files.
****************************************************************/

#ifndef FILEINFO_H
#define FILEINFO_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include "Plane.h"

using namespace std;

class FileInfo
{
public:
	// Default constructor
	FileInfo();

	// Destructor
	~FileInfo();

	// load data from file
	void readPassengers(const vector<Plane*> *plane);
	void readFlightSchedule(const vector<Plane*> *plane);
	void readDestination(const vector<Plane*> *plane);

	// write data to file
	void writePassengers(const vector<Plane*> *plane, int flightId, int seatId, bool append);

	void setPassengerData(const vector<Plane*> *plane, int flightId, int seatId, bool reserved, string firstName, string lastName, string address, string phone);
	void setBoardingPData(const vector<Plane*> *plane, int flightId, int seatId, string passType, string from, string toCity, string toCountry, string drink, string meal);

	// upon exiting the program, clear and then edit the passenger file (sorted)
	void updateFile(const vector<Plane*> *plane, int numPlanes);
	void clearFile();

	string parseUnderscore(string s);
	string parseSpace(string s);

};

#endif // !FILEINFO_H
