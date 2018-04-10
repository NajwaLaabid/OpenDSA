#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class ErrorRec { // Queue class ADT
	public:
		// Hold the number of errors
		int numErr = 0;
		// Print error messages in a text file
		ofstream error;
		// Added at the beginning of error messages
		const string DEFAULT_MSG = "* ***OpenDSA Error*** *\n";
		// Added at the beginning of the name of error log file
		const string FILE_NAME = "error log.";

		/* Constructor. Creates a new new PrintWriter object if asked to use files */
		ErrorRec(bool useFile, string className) {
			if (useFile)
				error.open(FILE_NAME + className);
		}

		/* Prints out an error message in an error log or a console 
		 * and increases the number of errors by 1.
		*/
		void printError(string message) {
			if (error.is_open())
				error << DEFAULT_MSG << message << endl;
			else
				cout << DEFAULT_MSG << message << endl;

			numErr++;
		}

		/* Tells if there exist errors and, if any, prints out the number of errors. */
		void feedback(){
			// If there are no errors, create a success file and print out success. If
			// not, report the number of errors
			if (numErr == 0) {
				ofstream output;
				output.open("success");
				output << "Success" << endl;
				output.flush();
				output.close();
				cout << "Success!" << endl;
			} else 
				cout << "Testing failed. There are (is) " << numErr << " error(s) in your code." << endl;
			
			if (error.is_open()) {
				error.flush();
				error.close();
			}
		}
};