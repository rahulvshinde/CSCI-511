/*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NAME: RAHUL VISHWANATH SHINDE
CHICO STATE ID #006948956
ASSIGNMENT: Various operations on Files and Directories
CHANGE LOG:
INITIALS						DATE									CHANGE
RVS							 10/10/2014							Study of File Handling
RVS							 10/15/2014							Implementation of get System Date and Time Functions
RVS                          10/17/2014							Implementation of change directory code
RVS					         10/20/2014							Implementation of read list of files and print them on console window
RVS							 10/22/2014							Implementation of Backup to a file
RVS							 10/23/2014							Implementation of modifying file size
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////*/

#include"Header1.h"
#include<iostream>

using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Function: Main Function
//Input: None
//Output: Int
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main(){

	int choice1;

	while (true){
		system("cls");
		cout << endl << "MENU" << endl << "*********************" << endl
			<< "1. Call A" << endl << "2. Call B" << endl << "0. Exit" << endl 
			<< "*********************" << endl << "Enter your choice: ";
		cin >> choice1;

		while (!cin){		// If user enters a character, ask for the choice again.
			cin.clear();
			cin.ignore();

			cout << endl << "   ERROR - Choice should be a number..." << endl
				<< endl << "Enter choice again: ";
			cin >> choice1;
		}
		switch (choice1)
		{
		case 1: PartA();
			break;

		case 2:  PartB();
			system("pause");
			break;

		case 0: cout << endl << endl;
			exit(0);
			break;

		default:
			cout << endl << "   ERROR - Invalid choice.." << endl;
			break;

		}
	}
	cout << endl << endl;
	return 0;
}


