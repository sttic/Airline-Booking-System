/****************************************************************
	FILE:		FileInfo.cpp
	AUTHOR:		Tommy Deng
				s199762338

	PURPOSE:	CPP file for file handling object (FileInfo.h).
				Contains the "FileInfo.h" functions. This handles
				the reading and writing of data to and from text
				files.
****************************************************************/

#include "FileInfo.h"

FileInfo::FileInfo()
{
}

FileInfo::~FileInfo()
{
}

void FileInfo::readPassengers(const vector<Plane*> *plane)
{
	ifstream myFile;
	myFile.open("Passenger.txt");

	// check for error
	if (myFile.fail())
	{
		cerr << "Error opening file, \"Passenger.txt\"." << endl;
		exit(1);
	}

	if (myFile.is_open())
	{
		// standard info
		int flightId;
		int seatId;
		bool reserved;

		string firstName, lastName;
		string address1, address2, address3;
		string phone;

		// boarding pass info
		string passType;
		string from, toCity, toCountry;
		string drink, meal;

		while (!myFile.eof())
		{
			myFile >> flightId >> seatId >> reserved >> firstName >> lastName >> address1 >> address2 >> address3 >> phone;
			myFile>> passType >> from >> toCity >> toCountry >> drink >> meal;

			// processing input (connect address strings and remove underscores)
			stringstream address;
			address << address1 << " " << address2 << " " << address3;

			from = parseUnderscore(from);
			toCity = parseUnderscore(toCity);
			toCountry = parseUnderscore(toCountry);
			drink = parseUnderscore(drink);
			meal = parseUnderscore(meal);

			// assign passenger data
			setPassengerData(plane, flightId, seatId, reserved, firstName, lastName, address.str(), phone);

			// assign boarding pass data
			setBoardingPData(plane, flightId, seatId, passType, from, toCity, toCountry, drink, meal);
		}

		myFile.close();
	}
}

void FileInfo::readFlightSchedule(const vector<Plane*> *plane)
{
	ifstream myFile;
	myFile.open("FlightSchedule.txt");

	// check for error
	if (myFile.fail())
	{
		cerr << "Error opening file, \"FlightSchedule.txt\"." << endl;
		exit(1);
	}

	if (myFile.is_open())
	{
		int flightId;
		string depart, arrive, duration;

		while (!myFile.eof())
		{
			myFile >> flightId >> depart >> arrive >> duration;

			(*plane)[flightId]->setTimeDepart(depart);
			(*plane)[flightId]->setTimeArrive(arrive);
			(*plane)[flightId]->setDuration(duration);
		}
	}

	myFile.close();
}

void FileInfo::readDestination(const vector<Plane*>* plane)
{
	ifstream myFile;
	myFile.open("Destination.txt");

	// check for error
	if (myFile.fail())
	{
		cerr << "Error opening file, \"Destination.txt\"." << endl;
		exit(1);
	}

	if (myFile.is_open())
	{
		int flightId;
		string city, country;

		while (!myFile.eof())
		{
			myFile >> flightId >> city >> country;

			city = parseUnderscore(city);
			country = parseUnderscore(country);

			(*plane)[flightId]->setDestinationCity(city);
			(*plane)[flightId]->setDestinationCountry(country);
		}
	}

	myFile.close();
}

void FileInfo::writePassengers(const vector<Plane*> *plane, int FlightId, int seatId, bool append)
{
	ofstream myFile;
	myFile.open("Passenger.txt", ios::app);

	// check for error
	if (myFile.fail())
	{
		cerr << "Error opening file, \"Passenger.txt\"." << endl;
		exit(1);
	}

	if (myFile.is_open())
	{
		// add newlines only when appending to file (active file writing with prior entries)
		if (append)
			myFile << endl << endl;

		myFile << FlightId << " " << seatId << endl;
		myFile << (*plane)[FlightId]->getSeat(seatId).getReserved() << endl;
		myFile << (*plane)[FlightId]->getSeat(seatId).getPassenger().getFirstName() << " "
			<< (*plane)[FlightId]->getSeat(seatId).getPassenger().getLastName() << endl;
		myFile << (*plane)[FlightId]->getSeat(seatId).getPassenger().getAddress() << endl;
		myFile << (*plane)[FlightId]->getSeat(seatId).getPassenger().getPhoneNumber() << endl;

		if ((*plane)[FlightId]->getSeat(seatId).getPassenger().getEconomy().getHasEcon() == true)
		{
			myFile << "E" << " ";
			myFile << parseSpace((*plane)[FlightId]->getSeat(seatId).getPassenger().getEconomy().getFrom()) << " ";
			myFile << parseSpace((*plane)[FlightId]->getSeat(seatId).getPassenger().getEconomy().getToCity()) << " "
				<< parseSpace((*plane)[FlightId]->getSeat(seatId).getPassenger().getEconomy().getToCountry()) << " ";
			myFile << "_ _";
		}
		else if ((*plane)[FlightId]->getSeat(seatId).getPassenger().getBusiness().getHasBus() == true)
		{
			myFile << "B" << " ";
			myFile << parseSpace((*plane)[FlightId]->getSeat(seatId).getPassenger().getBusiness().getFrom()) << " ";
			myFile << parseSpace((*plane)[FlightId]->getSeat(seatId).getPassenger().getBusiness().getToCity()) << " "
				<< parseSpace((*plane)[FlightId]->getSeat(seatId).getPassenger().getBusiness().getToCountry()) << " ";

			myFile << parseSpace((*plane)[FlightId]->getSeat(seatId).getPassenger().getBusiness().getDrink()) << " ";
			myFile << parseSpace((*plane)[FlightId]->getSeat(seatId).getPassenger().getBusiness().getMeal());
		}


	}

	myFile.close();
}

void FileInfo::setPassengerData(const vector<Plane*> *plane, int flightId, int seatId, bool reserved, string firstName, string lastName, string address, string phone)
{
	(*plane)[flightId]->getSeat(seatId).getPassenger().setFlightId(flightId);
	(*plane)[flightId]->getSeat(seatId).getPassenger().setSeatId(seatId);
	(*plane)[flightId]->getSeat(seatId).setReserved(reserved);
	(*plane)[flightId]->getSeat(seatId).getPassenger().setFirstName(firstName);
	(*plane)[flightId]->getSeat(seatId).getPassenger().setLastName(lastName);
	(*plane)[flightId]->getSeat(seatId).getPassenger().setAddress(address);
	(*plane)[flightId]->getSeat(seatId).getPassenger().setPhoneNumber(phone);
}

void FileInfo::setBoardingPData(const vector<Plane*> *plane, int flightId, int seatId, string passType, string from, string toCity, string toCountry, string drink, string meal)
{
	// economy boarding pass
	if (passType == "E")
	{
		(*plane)[flightId]->getSeat(seatId).getPassenger().getEconomy().setFrom(from);
		(*plane)[flightId]->getSeat(seatId).getPassenger().getEconomy().setToCity(toCity);
		(*plane)[flightId]->getSeat(seatId).getPassenger().getEconomy().setToCountry(toCountry);

		(*plane)[flightId]->getSeat(seatId).getPassenger().getEconomy().setHasEcon(true);
	}
	// business boarding pass
	else if (passType == "B")
	{
		(*plane)[flightId]->getSeat(seatId).getPassenger().getBusiness().setFrom(from);
		(*plane)[flightId]->getSeat(seatId).getPassenger().getBusiness().setToCity(toCity);
		(*plane)[flightId]->getSeat(seatId).getPassenger().getBusiness().setToCountry(toCountry);

		(*plane)[flightId]->getSeat(seatId).getPassenger().getBusiness().setHasBus(true);
		(*plane)[flightId]->getSeat(seatId).getPassenger().getBusiness().setDrink(drink);
		(*plane)[flightId]->getSeat(seatId).getPassenger().getBusiness().setMeal(meal);
	}
}

void FileInfo::updateFile(const vector<Plane*> *plane, int numPlanes)
{

	// ID's of flight/seat that are occupied
	vector<int> flightId;
	vector<int> seatId;

	int count = 0;

	for (int i = 0; i < numPlanes; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if ((*plane)[i]->getSeat(j).getReserved())
			{
				flightId.push_back(i);
				seatId.push_back(j);

				count++;
			}
		}
	}

	clearFile();

	// write to file (will be sorted by flight and seat id)
	FileInfo file;

	// first entry is different (no newline spacing prior entry)
	for (int i = 0; i < count; i++)
		file.writePassengers(plane, flightId[i], seatId[i], i != 0);
	
}

void FileInfo::clearFile()
{
	ofstream myFile;
	myFile.open("Passenger.txt");

	// check for error
	if (myFile.fail())
	{
		cerr << "Error opening file, \"Passenger.txt\"." << endl;
		exit(1);
	}

	myFile.clear();
}

string FileInfo::parseUnderscore(string s)
{
	string str = s;

	for (unsigned int i = 0; i < str.size(); i++)
		if (str.substr(i, 1) == "_")
			str.replace(i, 1, " ");

	return str;
}

string FileInfo::parseSpace(string s)
{
	string str = s;

	for (unsigned int i = 0; i < str.size(); i++)
		if (str.substr(i, 1) == " ")
			str.replace(i, 1, "_");

	return str;
}

