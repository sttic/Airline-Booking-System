/****************************************************************
	FILE:		Controller.h
	AUTHOR:		Tommy Deng
				s199762338

	PURPOSE:	Header file for the controller (airline) object.
				Controls/handles the interaction of most objects
				and other program functionalities.
****************************************************************/

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "Message.h"
#include "Plane.h"
#include "FileInfo.h"
#include "Input.h"

using namespace std;

class Controller
{
protected:
	vector<Plane*> *plane = new vector<Plane*>;

	Message message;
	FileInfo file;
	Input input;

	int numPlanes;
	bool run;
public:
	// Default constructor
	Controller();

	// Destructor
	~Controller();

	// Accessor functions
	bool getRun();

	// Mutator functions
	void setRun(bool run);

	// load all initial/current data from file and assigns it to
	// the corresponding objects
	void retrieveData();

	// output display to console
	void display();


	// nested/isolated functions (individual 'steps')
	void OptionTree(string input);

	void bookReservation();
	void cancelReservation();
	void displayPassengerInfo();
	void displaySchedule();
	void displayDestinations();
	void displayReservations();
	void searchPassengerInfo();
	void cancelEntireFlight();
	void exitProgram();

	void outputManifest(vector<Passenger> pCopy);

	// initialize passenger copy (for displaying manifest)
	void initPassengerAll(vector<Passenger>& pCopy, const vector<Plane*> *plane);
	void initPassengerOne(vector<Passenger>& pCopy, const vector<Plane*>* plane, int flightId);

	// used when displaying passenger info.
	// returns the number of tabs needed for proper formatting when displaying passenger info
	int spacing(int size);

	// linear search of copied passenger object
	// TODO: binary search
	// returns vector of position(s) of search
	vector<int> linearSearch(vector<Passenger> pCopy, string search);

};

#endif // !CONTROLLER_H