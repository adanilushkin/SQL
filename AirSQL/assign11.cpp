#include <mysql.h>
#include <iostream>

using namespace:std;


int main ()
{

	//Creates a pointer to the MySQL instance
	MYSQL *connect, mysql;

	//Initialize the instance
	connect = mysql_init(&mysql);

	//Test to make sure the connection was successful
	if (mysql_real_connect(connect, courses, z1809166, 1995Jun03, z1809166, 0, NULL, 0)) {

		//Create a pointer to receive the return value
		MYSQL_RES *res_set;

		//Assign a variable for rows
		MYSQL_ROW row, checkRowNull;

/*
 *
 *	BELOW DISPLAYS THE ENTIRE FLIGHT TABLE
 *
 *
 */

		//Send the query to the databse (checks for flights first)
		mysql_query(connect, "select * from flight");

		//Receive the result and store it
		res_set = mysql_store_result(connect);

		checkRowNull = mysql_fetch_row(res_set);

		//If the query returns 'Empty Set', we don't have ANY flights in the database, which is a problem.
		//Error message is printed because airtraffic.sql needs to be rerun to repopulate the database.
		if (checkRowNull == 0) {
			cerr << endl << endl << "ERROR: There are no flights, which means this program won't work!";
			cerr << endl << "Please have the owner " << "'" << USER << "'" 
			             << " rerun 'airtraffic.sql' on MySQL to repopulate the database." 
			             << endl << endl << endl;



			return 0;
		}

		//Send the query to the databse (verified that we have flights)
		mysql_query(connect, "select * from flight");

		//Receive the result and store it
		res_set = mysql_store_result(connect);

		unsigned int num_rows = mysql_num_fields(res_set);

		//Makes sure that the header for flight listings is only printed once
		int flightCount = 0;

		while ((row = mysql_fetch_row(res_set))) {

			//Checks to make sure that the header hasn't been printed yet
			if (flightCount == 0) {

				//Prints out the header
				cout << endl << "\t\t\t\t\t  === FLIGHT LISTING ===" << endl << endl;
				cout << "\t----------------------------------------"
					 << "----------------------------------------------------" << endl;
				cout << "\t| flightnum |" << "  origination   |" << "  destination  |"
					 << "     miles     |" << "    maxcost     |" << "   mincost  |" << endl;
				cout << "\t---------------------------------------"
					 << "-----------------------------------------------------" << endl;
			}

			//Print each row from the select statement
			for (int i = 0; i < num_rows; i++)
					cout << right << setw(16) << row[i];

			cout << endl;

			flightCount++;
		}
		cout << "\t------------------------------------------------"
			 << "-------------------------------------------" << endl;
		cout << endl << endl;

/*
 *
 *	BELOW DISPLAYS THE FLIGHTS, THEIR PASSENGERS, AND THEIR APPROPRIATE SEAT NUMBERS
 *
 *
 */

		//Send the query to the databse. This displays the flights, their passengers, and their appropriate seating
		mysql_query(connect, "select manifest.flightnum, concat(passenger.lName, ',', passenger.fName), manifest.seatnum from manifest, passenger where manifest.passnum = passenger.passnum order by flightnum");

		//Receive the result and store it
		res_set = mysql_store_result(connect);
		num_rows = mysql_num_fields(res_set);

		int passCount = 0;

		//While we have rows to work with...
		while ((row = mysql_fetch_row(res_set))) {

			//Checks to make sure that the header hasn't been printed yet
			if (passCount == 0) {

				cout << endl << "\t\t  === FLIGHT LISTING WITH PASSENGERS ===" << endl << endl;
				cout << "\t---------------------------------------------------------" << endl;
				cout << "\t| flightnum |" << "       passenger           |" << "    seatnum    |" << endl;
				cout << "\t---------------------------------------------------------" << endl;
			}

			for (int i = 0; i < num_rows; i++) {

				//When i == 0, this is the first row (small numbers), so adject the setw
				if (i == 0)	
					cout << right << setw(15) << row[i];

				//Prints each row received from the select statement
				else
					cout << right << setw(22) << row[i];
			}

			passCount++;
			cout << endl;
		}

		cout << "\t---------------------------------------------------------" << endl << endl;

/*
 *
 *	BELOW DISPLAYS HOW MANY FLIGHTS ARE EMPTY
 *
 *
 */

		//Holds the assigned flight number from the flightNumbers vector
		std::string flightNum = "";

		//Vector that holds the flights without passengers
		std::vector<std::string> flightNumbers;

		bool haveFlightWithoutPassenger = false;

		//This query finds all of the flights in the database
		mysql_query(connect, "select flightnum from flight");

		res_set = mysql_store_result(connect);
		num_rows = mysql_num_fields(res_set);

		//While we have rows to read
		while ((row = mysql_fetch_row(res_set))) {

			//Insert the value of the row into the flightNumbers table
			for (int i = 0; i < num_rows; i++)
				flightNumbers.push_back(row[i]);
		}

		cout << endl << "\t\t  === FLIGHTS WITHOUT PASSENGERS ===" << endl << endl;

		
		//Loop through the flightNumbers vector
		for (int i = 0; i < flightNumbers.size(); i++) {

			//Assign the value stored in the flightNumbers vector ast pos[i] to flightNum
			flightNum = flightNumbers[i];
			
			/*This query is a little different as in order to receive the flights without passengers
			  without having to call the mysql_query for each flight, it needed to be stored in a 
			  vector<string>. mysql_query only takes char * as the second parameter, so the entire
	          statement has to be converted to a c_str for it to work. */
			mysql_query(connect, ("select * from manifest where flightnum =" + flightNum).c_str());

			res_set = mysql_store_result(connect);
			num_rows = mysql_num_fields(res_set);
			row = mysql_fetch_row(res_set);

			//This is entered when 'Empty set' is returned in MySQL
			if (row == 0) {

				cout << "\t\tFlight #: " << flightNum << " does not have any passengers" << endl;
				haveFlightWithoutPassenger = true;
			}
		}

		//An 'Empty set' was not returned
		if (!haveFlightWithoutPassenger)
			cout << "\t\t     All flights have passengers" << endl;

		cout << endl << endl;

		//Free up the cursor pointer
		mysql_free_result(res_set);

		//Close the connection to the database
		mysql_close(connect);
	}

	//The connection was NOT successful
	else {

		cerr << endl << "Error: Unable to connect to the database" << endl;
	}

	return 0;
}
