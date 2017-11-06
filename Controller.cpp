/****************************************************************
	FILE:		Controller.cpp
	AUTHOR:		Tommy Deng
				s199762338

	PURPOSE:	CPP file for the controller (airline) object
				(Controller.h).	Controls/handles the interaction
				of most objects and other program functionalities.
****************************************************************/

#include "Controller.h"
#include <algorithm>

// used with sorting algo., compares values and returns if the first one is lesser than the second
bool cmd(Passenger p1, Passenger p2);



Controller::Controller()
{
	numPlanes = 3;
	run = true;

	// initialize planes
	for (int i = 0; i < numPlanes; i++)
	{
		plane->push_back(new Plane(i, "CITY, COUNTRY"));
	}

	// initialize message
	message = Message();

	// note: these appear to do the same thing
	//cout << (*plane)[0]->getDestination() << endl;
	//cout << (*(*plane)[0]).getDestination() << endl;
}

Controller::~Controller()
{
}

bool Controller::getRun()
{
	return run;
}

void Controller::setRun(bool run)
{
	this->run = run;
}

void Controller::retrieveData()
{
	file.readPassengers(plane);
	file.readFlightSchedule(plane);
	file.readDestination(plane);
}

void Controller::display()
{
	cout << message.menu();

	string input;
	cin >> input;
	cout << endl;

	OptionTree(input);
}

void Controller::OptionTree(string input)
{
	// clear screen
	system("cls");

	if (input.size() == 1)
	{
		switch (input[0])
		{
		case '1':
			bookReservation();
			break;
		case '2':
			cancelReservation();
			break;
		case '3':
			displayPassengerInfo();
			break;
		case '4':
			displaySchedule();
			break;
		case '5':
			displayDestinations();
			break;
		case '6':
			displayReservations();
			break;
		case '7':
			searchPassengerInfo();
			break;
		case '8':
			cancelEntireFlight();
			break;
		case '9':
			exitProgram();
			break;
		default:
			cout << message.invalid() << endl;
			break;
		}
	}
	else
	{
		cout << message.invalid() << endl;
	}

	system("pause");
	system("cls");
}

void Controller::bookReservation()
{
	// display reservation availability when booking
	displayReservations();

	// get flight id input and checks validity
	int flightId = input.flightId(numPlanes);
	// get seat id input and checks validity
	int seatId = input.seatId(plane, flightId);

	if ((*plane)[flightId]->getSeat(seatId).getReserved())
	{
		cout << "The seat is unavailable. Consider cancelling it first." << endl;
	}
	else
	{
		string firstName, lastName;
		string streetNum, streetName, streetType;
		string phone;

		string classType;
		string from, toCity, toCountry;
		string drink, meal;

		cout << "First and last name: ";
		cin >> firstName >> lastName;
		cout << "Address (format: ### Address St.): ";
		cin >> streetNum >> streetName >> streetType;
		cout << "Phone number: ";
		cin >> phone;

		// get pass type input and checks validity
		cout << "Boarding pass type, E or B (economy or business): ";
		classType = input.boardingPass();

		from = "Ottawa";	// determined by airline location
		cout << endl;

		cout << "The destination for this flight is " << (*plane)[flightId]->getDestinationCity()
			<< ", " << (*plane)[flightId]->getDestinationCountry() << endl;
		cout << "See the flight schedule and destination board for more detail" << endl;

		toCity = (*plane)[flightId]->getDestinationCity();
		toCountry = (*plane)[flightId]->getDestinationCountry();

		if (classType == "B")
		{
			drink = input.drink();
			meal = input.meal();
		}
		else
		{
			drink = "_";
			meal = "_";
		}

		// combining strings
		stringstream ssStreet;
		ssStreet << streetNum << " " << streetName << " " << streetType;

		// assign information to objects
		input.setReservation(plane, flightId, seatId, firstName, lastName, ssStreet.str(), phone, classType, from, toCity, toCountry, drink, meal);

		// write to file as entries are made (appends entry to end)
		file.writePassengers(plane, flightId, seatId, true);

		// actively updates the file
		// it's not really necessary to do this (doesn't impact anything and file already updates as program is closing)
		file.updateFile(plane, numPlanes);
	}

	cout << endl;
}

void Controller::cancelReservation()
{
	// display reservation availability when canceling
	displayReservations();

	cout << "Cancel a reservation." << endl;

	int flightId = input.flightId(numPlanes);
	int seatId = input.seatId(plane, flightId);

	cout << endl;

	if ((*(*plane)[flightId]).getSeat(seatId).getReserved() == true)
	{
		cout << "Cancelling " << (*plane)[flightId]->getSeat(seatId).getPassenger().getFirstName() << "'s flight" << endl;
		(*plane)[flightId]->getSeat(seatId).setPassenger("_____", "_____", "__________", "__________");
		(*plane)[flightId]->getSeat(seatId).setReserved(false);
		cout << "Seat " << seatId << " of plane " << flightId << " is now available" << endl;

		// actively updates the file
		// it's not really necessary to do this (doesn't impact anything and file already updates as program is closing)
		file.updateFile(plane, numPlanes);
	}
	else
	{
		cout << "The seat was already not reserved" << endl;
	}

	cout << endl;
}

void Controller::displayPassengerInfo()
{
	// copy reserved passengers to passenger vector
	vector<Passenger> pCopy;
	initPassengerAll(pCopy, plane);

	cout << "Manifest of all passengers of all flights:" << endl << endl;
	cout << "Flight and seat number order" << endl;
	outputManifest(pCopy);
	cout << endl << endl;

	// sort algorithm from library
	sort(pCopy.begin(), pCopy.end(), cmd);

	cout << "Alphabetical order (Lastname, Firstname)" << endl;
	outputManifest(pCopy);
	cout << endl << endl;
	

	cout << "Enter a flight (0 - " << numPlanes - 1 << ") to display the manifest for a particular flight." << endl;
	int flightId = input.flightId(numPlanes);

	// clear vector copy and replace with a single flight
	pCopy.clear();
	initPassengerOne(pCopy, plane, flightId);

	cout << "Manifest of passengers of flight " << flightId << ":" << endl << endl;
	cout << "Seat number order" << endl;
	outputManifest(pCopy);
	cout << endl << endl;

	// sort algorithm from library
	sort(pCopy.begin(), pCopy.end(), cmd);

	cout << "Alphabetical order (Lastname, Firstname)" << endl;
	outputManifest(pCopy);

	cout << endl;
}

void Controller::displaySchedule()
{
	cout << "Plane\tDepart Time\tArrive Time\tDuration" << endl;

	for (int i = 0; i < numPlanes; i++)
	{
		cout << i << "\t" << (*plane)[i]->getTimeDepart() << "\t\t" << (*plane)[i]->getTimeArrive();
		cout << "\t\t" << (*plane)[i]->getDuration() << endl;
	}

	cout << endl;
}

void Controller::displayDestinations()
{
	cout << "Plane\tDestinations" << endl;

	for (int i = 0; i < numPlanes; i++)
	{
		cout << i << "\t" << (*plane)[i]->getDestinationCity() << ", " << (*plane)[i]->getDestinationCountry() << endl;
	}
		
	cout << endl;
}

void Controller::displayReservations()
{
	cout << "Plane\tSeat\tReserved\tName" << endl;

	for (int i = 0; i < numPlanes; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			int numTabs = 0;

			cout << i << "\t" << j << "\t";

			if ((*plane)[i]->getSeat(j).getReserved() == true)
				cout << "Yes";
			else if ((*plane)[i]->getSeat(j).getReserved() == false)
				cout << "No";

			cout << "\t\t" << (*plane)[i]->getSeat(j).getPassenger().getFirstName();
			cout << " " << (*plane)[i]->getSeat(j).getPassenger().getLastName();

			cout << endl;
		}
	}

	cout << endl;
}

void Controller::searchPassengerInfo()
{
	vector<Passenger> pCopy;

	// copy reserved passengers to passenger vector
	initPassengerAll(pCopy, plane);

	// sort algorithm from library
	// not needed, used linear search (opposed to binary)
	//sort(pCopy.begin(), pCopy.end(), cmd);

	cout << "Search for a passenger." << endl;

	string firstName, lastName;

	cout << "Enter the first and last name: ";
	cin >> firstName >> lastName;
	cout << endl;

	stringstream name;
	name << firstName << " " << lastName;

	// copy returned search vector which contains search result
	vector<int> pos = linearSearch(pCopy, name.str());

	if (pos.size() != 0)
	{
		cout << "Number of search result(s): " << pos.size() << endl << endl;

		// output all search result(s)
		for (unsigned int i = 0; i < pos.size(); i++)
		{
			// alternatively output the search input
			cout << "Name: " << pCopy[pos[i]].getFirstName() << " " << pCopy[pos[i]].getLastName() << endl;
			cout << "Address: " << pCopy[pos[i]].getAddress() << endl;
			cout << "Phone number: " << pCopy[pos[i]].getPhoneNumber() << endl;
			cout << "Flight ID: " << pCopy[pos[i]].getFlightId() << endl;
			cout << "Seat ID: " << pCopy[pos[i]].getSeatId() << endl;

			// boarding pass information
			if (pCopy[pos[i]].getEconomy().getHasEcon())
			{
				cout << "Pass Type: " << pCopy[pos[i]].getEconomy().getClassName() << endl;
				cout << "From: " << pCopy[pos[i]].getEconomy().getFrom() << endl;
				cout << "To: " << pCopy[pos[i]].getEconomy().getToCity() << ", " << pCopy[pos[i]].getEconomy().getToCountry() << endl;
			}
			else if (pCopy[pos[i]].getBusiness().getHasBus())
			{
				cout << "Pass type: " << pCopy[pos[i]].getBusiness().getClassName() << endl;
				cout << "From: " << pCopy[pos[i]].getBusiness().getFrom() << endl;
				cout << "To: " << pCopy[pos[i]].getBusiness().getToCity() << ", " << pCopy[pos[i]].getBusiness().getToCountry() << endl;

				cout << "Preferred drink: " << pCopy[pos[i]].getBusiness().getDrink() << endl;
				cout << "Preferred meal: " << pCopy[pos[i]].getBusiness().getMeal() << endl;
			}

			cout << endl;
		}

	}
	else
	{
		cout << "Passenger " << name.str() << " was not found." << endl;
	}

	cout << endl;
}

void Controller::cancelEntireFlight()
{
	cout << "Are you sure you want to cancel an entire flight? ('Y' or 'N')" << endl;
	string in;
	cin >> in;

	while (in != "Y" && in != "N")
	{
		cout << "Invalid input. Enter \"Y\" for yes, or \"N\" for no." << endl;
		cin >> in;
	}

	if (in == "Y")
	{
		int flightId = input.flightId(numPlanes);

		cout << endl;
		cout << "Contact information:" << endl;

		// output flight data
		// copy all passengers of that flight
		vector<Passenger> pCopy;
		initPassengerOne(pCopy, plane, flightId);
		outputManifest(pCopy);

		for (int i = 0; i < (*plane)[flightId]->getNumOfSeats(); i++)
		{
			if ((*(*plane)[flightId]).getSeat(i).getReserved() == true)
			{
				(*plane)[flightId]->getSeat(i).setPassenger("_____", "_____", "__________", "__________");
				(*plane)[flightId]->getSeat(i).setReserved(false);
			}
		}

		cout << endl << "Flight " << flightId << " was cancelled" << endl;
	}
	else
	{
		cout << "No flight was cancelled." << endl;
	}
}

void Controller::exitProgram()
{
	setRun(false);
	cout << message.exitProgram() << endl;
	file.updateFile(plane, numPlanes);
	exit(0);
}

void Controller::outputManifest(vector<Passenger> pCopy)
{
	cout << "Name\t\t\tAddress\t\t\tPhone number\t\tPlane\tSeat" << endl;

	for (unsigned int i = 0; i < pCopy.size(); i++)
	{
		int numTabs = 0;
		// for formatting purposes; so that the vertical columns line up
		int nameSize, addressSize, phoneSize;

		// output name
		cout << pCopy[i].getLastName() << ", " << pCopy[i].getFirstName();

		// output address
		nameSize = pCopy[i].getFirstName().size() + pCopy[i].getLastName().size() + 2;	// +2 for added space and comma
		cout << message.tabs(spacing(nameSize)) << pCopy[i].getAddress();

		// output phone number
		addressSize = pCopy[i].getAddress().size();
		cout << message.tabs(spacing(addressSize)) << pCopy[i].getPhoneNumber();

		// output flight and seating numbers
		phoneSize = pCopy[i].getPhoneNumber().size();
		cout << message.tabs(spacing(phoneSize)) << pCopy[i].getFlightId() << "\t" << pCopy[i].getSeatId();

		cout << endl;
	}
}



void Controller::initPassengerAll(vector<Passenger>& pCopy, const vector<Plane*> *plane)
{
	for (int i = 0; i < numPlanes; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if ((*plane)[i]->getSeat(j).getReserved())
			{
				pCopy.push_back((*plane)[i]->getSeat(j).getPassenger());
			}
		}
	}
}

void Controller::initPassengerOne(vector<Passenger>& pCopy, const vector<Plane*>* plane, int flightId)
{
	for (int i = 0; i < 10; i++)
	{
		if ((*plane)[flightId]->getSeat(i).getReserved())
		{
			pCopy.push_back((*plane)[flightId]->getSeat(i).getPassenger());
		}
	}
}

int Controller::spacing(int size)
{
	int numTabs = 0;
	
	if (size < 4)
		numTabs = 3;
	else if (size < 8)
		numTabs = 3;
	else if (size < 12)
		numTabs = 2;
	else if (size < 16)
		numTabs = 2;
	else
		numTabs = 1;
	
	return numTabs;
}

vector<int> Controller::linearSearch(vector<Passenger> pCopy, string search)
{
	// array of full names, the first and last name combined
	string *fullName = new string[pCopy.size()];
	for (unsigned int i = 0; i < pCopy.size(); i++)
	{
		stringstream name;
		name << pCopy[i].getFirstName() << " " << pCopy[i].getLastName();

		fullName[i] = name.str();
	}

	// linear search algorithm (handles people with identical names)
	vector<int> pos;
	int i = 0;

	while (i < pCopy.size())
	{
		if (fullName[i] == search)
			pos.push_back(i);
		i++;
	}

	return pos;
}



bool cmd(Passenger p1, Passenger p2)
{
	if (p1.getLastName() != p2.getLastName())
		return p1.getLastName() < p2.getLastName();

	return p1.getFirstName() < p2.getFirstName();
}