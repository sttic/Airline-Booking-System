/****************************************************************
	FILE:		Message.cpp
	AUTHOR:		Tommy Deng
				s199762338

	PURPOSE:	CPP file for the message object (Message.h).
				Contains commonly used text outputs and other
				text/formatting related functions.
****************************************************************/

#include "Message.h"

Message::Message()
{

}

Message::~Message()
{
}

string Message::menu()
{
	stringstream ss;

	ss << "Welcome to Fly-By-Night Airline's Booking System" << endl;
	ss << "Please pick an option from the menu below" << endl;
	ss << endl;
	ss << "\t1. Book reservation" << endl;
	ss << "\t2. Cancel reservation" << endl;
	ss << "\t3. Display the passenger manifest" << endl;
	ss << "\t4. Display the flight schedule" << endl;
	ss << "\t5. Display the destinations" << endl;
	ss << "\t6. Display flight reservations" << endl;
	ss << "\t7. Search for a customer's information" << endl;
	ss << "\t8. Cancel entire flight" << endl;
	ss << "\t9. Exit" << endl;
	ss << endl;
	ss << "Enter the number of a menu option: ";

	return ss.str();
}

string Message::invalid()
{
	return "Invalid input. Please try again.";
}

string Message::tabs(int numTabs)
{
	stringstream ss;

	if (numTabs > 0)
	{
		for (int i = 0; i < numTabs; i++)
			ss << "\t";

		return ss.str();
	}
	else
	{
		return "";
	}
	
}

string Message::exitProgram()
{
	return "Terminating program.";
}
