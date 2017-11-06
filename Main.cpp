/****************************************************************
	PROGRAM:	Airline Booking System
	AUTHOR:		Tommy Deng
				s199762338
	COURSE:		ICS4U-01
				Mr. Hudson

	FUNCTION:	A database for Fly-by-Night Airlines that keep
				track of their seat sales for each flight.

				The database contains:
					- plane id
					- seat number
					- seat availability
					- customer contact information
					- customer boarding pass information (economy
					and business class)

				Program functionalities inclue:
					- text file data storage (read and write)
					- adding passenger data
					- cancelling/removing reservations
					- cancelling entire flight
					- displaying customer information (sorted/
					alphabetical as a flight manifest)
					- reading flight scheduele from seperate file
					- reading flight destinations from seperate
					file
					- displaying flight reservations
					- searching for a specific customer's
					information
					- cancelling flight and outputting the flight's
					passenger contact information

	INPUT:	The inputs are done through the console and with text
			files, which include the following:
				"Destination.txt"
				"FlightSchedule.txt"
				"Passenger.txt"

	OUTPUT:	Like the inputs, the outputs are done through the
			console and with text files, which include the
			following:
				"Destination.txt"
				"FlightSchedule.txt"
				"Passenger.txt"

	NOTES:	There are two operating system dependent functions
			used. They are:
				system("cls") and,
				system("pause").
			These operate normally on a windows machine. Since they
			are purely for aesthetic purposes, alternate methods to
			perform the same tasks were not implemented to satisfy
			complete functionality on non-windows environments.
****************************************************************/

#include "Controller.h"

using namespace std;

int main()
{
	// create airline object and load current/past data from file
	Controller *airline = new Controller;

	airline->retrieveData();
	
	// display menu and console interaction
	while (airline->getRun())
	{
		airline->display();
	}
}