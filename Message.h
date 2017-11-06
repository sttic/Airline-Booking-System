/****************************************************************
	FILE:		Message.h
	AUTHOR:		Tommy Deng
				s199762338

	PURPOSE:	Header file for the message object. Contains commonly
				used text outputs and other text/formatting related
				functions.
****************************************************************/

#ifndef MESSAGE_H
#define MESSAGE_H

#include <iostream>
#include <sstream>

using namespace std;

class Message
{
public:
	// Default constructor
	Message();

	// Destructor
	~Message();

	// consider between making these function return a string (like
	// it is now). Or have them output the string itself. The
	// slight difference in usage would be that you wouldn't have
	// to write the "cout << ..." in your main code, instead you
	// would have something like "message.____()"

	string menu();
	string invalid();
	string tabs(int numTabs);
	string exitProgram();

};

#endif // !MESSAGE_H
