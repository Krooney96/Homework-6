// Kyle Rooney COP2000 Homework 6 Techi Gadgets Account
// This program will display a welcome message, determine the users access level, display their initial membership year, and their tech level if they are a general user.
// If the user is an admin, a list of all users information will be displayed and will be placed in a file called "sortedBackup.txt".

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <fstream>
#include <string>

using namespace std;

void showAll(string theAccounts[5][7]);
void sortInput(string theAccounts[5][7]);
bool readFile(string theAccounts[5][7]);
bool validateUser(string theAccounts[5][7], string, string, int*);

int main()
{
	cout << setprecision(2) << fixed << showpoint;   
	bool userSuccess;						             
	bool fileSuccess;						             
	int saveRow;					                 
	string username;                                 
	string password;                                
	string accountData[5][7] = { " " };             

	fileSuccess = readFile(accountData); 

	{
		if (fileSuccess == true)	// The file was opened successfully. If not, display error and exit the program.
			cout << "The file was read successfully\n\n"; 
		else
		{
			cout << " The file was not read successfully, exiting program.\n\n";
			return 0;
		}
	}

	sortInput(accountData);  

	do
	{
		
		username = "";
		password = "";

		cout << "Enter the following information, or press 0 to exit anytime" << endl;
		cout << "Please enter your username :";
		cin >> username;

		if (username == "0")
		{
			cout << "\nGoodbye!\n\n";
			return 0;
		}

		cout << "Please enter your password :";
		cin >> password;

		if (password == "0")
		{
			cout << "\nGoodbye!\n\n";
			return 0;
		}

		userSuccess = validateUser(accountData, username, password, &saveRow); 

		{
			if (userSuccess == true) 
			{
				if (accountData[saveRow][5] == "A")	// If the user has admin status, display all users and will output to backup file.
				{
					showAll(accountData);
				}

				else
				{
					cout << "\nWelcome Back " << accountData[saveRow][1] << "!\n\n";
					cout << setw(8) << left << accountData[saveRow][1];
					cout << setw(8) << left << accountData[saveRow][2];
					cout << setw(6) << left << accountData[saveRow][4];
					cout << setw(4) << left << accountData[saveRow][5];
					cout << setw(15) << left << accountData[saveRow][6];
					cout << endl << endl;
				}
			}

			else   
			{
				cout << "Username and password do not match, please try again \n" << endl;	// Username or password was incorrect.
			}
		}


	} while (password != "0" || username != "0");


	return 0;

}

void showAll(string theAccounts[5][7])
{
	
	ofstream outputFile;
	outputFile.open("sortedBackup.txt");
	int row = 5;

	cout << "\n";

	for (int index = 0; index < row; index++)
		
	{
		cout << setw(20) << right << theAccounts[index][0];
		cout << setw(8) << right << theAccounts[index][1];
		cout << setw(8) << right << theAccounts[index][2];
		cout << setw(10) << right << theAccounts[index][3];
		cout << setw(6) << right << theAccounts[index][4];
		cout << setw(4) << right << theAccounts[index][5];
		cout << setw(15) << right << theAccounts[index][6];
		cout << endl;

		outputFile << setw(20) << right << theAccounts[index][0];
		outputFile << setw(8) << right << theAccounts[index][1];
		outputFile << setw(8) << right << theAccounts[index][2];
		outputFile << setw(10) << right << theAccounts[index][3];
		outputFile << setw(6) << right << theAccounts[index][4];
		outputFile << setw(4) << right << theAccounts[index][5];
		outputFile << setw(15) << right << theAccounts[index][6];
		outputFile << endl;
	}

	cout << "Backup file created. \n " << endl;

	outputFile.close();

}

void sortInput(string theAccounts[5][7])
{
	
	bool sorted = false;
	string temp;

	while (!sorted) {
		sorted = true;
		for (int index = 0; index < 4; ++index) {
			if (theAccounts[index][2] > theAccounts[index + 1][2]) {
				sorted = false;
				for (int last = 0; last < 7; ++last) {
					temp = theAccounts[index][last];
					theAccounts[index][last] = theAccounts[index + 1][last];
					theAccounts[index + 1][last] = temp;
				}
			}
		}
	}
}



bool readFile(string theAccounts[5][7])   
{
	bool fileRead = false;
	int row = 5;
	int col = 7;
	ifstream inputFile;                 
	inputFile.open("AccountData.txt");  

	if (inputFile)
	{
		fileRead = true;
		
		for (int index = 0; index < row; index++)
			for (int index2 = 0; index2 < col; index2++)
				inputFile >> theAccounts[index][index2];
	}

	inputFile.close();

	return fileRead;
}

bool validateUser(string theAccounts[5][7], string username, string password, int *saveRow)

{
	bool passed = false;
	int user = 0;
	int pass = 3;
	int row = 0;

	for (int row = 0; row <= 4; row++)
	{
		if ((username == theAccounts[row][user]) && (password == theAccounts[row][pass]))
		{
			passed = true;
			*saveRow = row;
		}
	}
	system("pause");
	return passed; 
}