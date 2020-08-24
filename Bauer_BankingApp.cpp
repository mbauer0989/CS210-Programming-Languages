/*
 * Bauer_BankingApp.cpp
 *
 *  Created on: Aug 1, 2020
 *      Author: Michael Bauer
 */

#include <iostream>
#include <exception>
#include <cctype>
#include <iomanip>
#include "BankingApp.h"
using namespace std;

BankingApp::BankingApp () { // default constructor
   m_initDeposit = 0;
   m_monthlyDeposit = 0;
   m_interest = 0;
   m_totalYears = 0;
   m_totalInitialInterest = 0.0;
   m_totalInitialBalance = 0.0;
   m_totalMonthlyInterest = 0.0;
   m_totalMonthlyBalance = 0.0;
   m_endOfYearInterest = 0.0;
   m_endOfYearInitialInterest = 0.0;
}

char BankingApp::quit = 'N'; // sets quit to 'N'

void BankingApp::setDeposit(int t_userDeposit) { // sets initial deposit equal to parameter passed in
	m_initDeposit = t_userDeposit;
}

void BankingApp::setMonthlyDeposit (int t_userMonDeposit) { // sets monthly deposit equal to parameter passed in
	m_monthlyDeposit = t_userMonDeposit;
}
void BankingApp::setInterest (int t_userInterest) { // sets interest equal to parameter passed in
	m_interest = t_userInterest;
}

void BankingApp::setYears (int t_userYears) { // sets total years equal to parameter passed in
	m_totalYears = t_userYears;
}

void BankingApp::getUserInput () {
	int temp = 0;
	double userInterest = 0;
	char finished = 'n';

	while (finished != 'Y') { // checks if all input was collected
		try {
			cout << "Please Enter Initial Deposit Amount:\n" << ">>";
			cin >> temp;

			if (temp <= 0 || cin.fail()) { // checks if user enters an invalid value, throws a 1 if the user does
				throw 1;
			}
			else {
				setDeposit(temp);
				temp = 0;
			}

			cout << "Please Enter Monthly Deposit:\n" << ">>";
			cin >> temp;

			if (temp <= 0 || cin.fail()) { // checks if user enters an invalid value, throws a 2 if the user does
				throw 2;
			}
			else {
				setMonthlyDeposit(temp);
				temp = 0;
			}

			cout << "Please Enter Annual Interest:\n" << ">>";
			cin >> userInterest;

			if (userInterest <= 0 || cin.fail()) { // checks if user enters an invalid value, throws the variable if the user does
				throw userInterest;
			}
			else {
				setInterest(userInterest);
				userInterest = 0;
			}

			cout << "Please Enter Number of Years For Investment:\n" << ">>";
			cin >> temp;

			if (temp <= 0 || cin.fail()) { // checks if user enters an invalid value, throws a 3 if the user does
				throw 3;
			}
			else {
				setYears(temp);
				temp = 0;
			}

			finished = 'Y';
		}
			catch (int temp) { // depending on what was thrown it catches and prints the response related to the error
				switch (temp) {
				case 1:
					cout << "Invalid Deposit " << endl;
					cin.clear();
					cin.ignore();
					continue;
				case 2:
					cout << "Invalid Monthly Deposit" << endl;
					cin.clear();
					cin.ignore();
					continue;
				case 3:
					cout << "Invalid Number of Years" << endl;
					cin.clear();
					cin.ignore();
					continue;
				}
			}
			catch (double userInterest) { // prints the response related to the error
				cout << "Invalid Interest" << endl;
				cin.clear();
				cin.ignore();
				continue;
			}
	}
}

void BankingApp::displayMenu () { // prints the menu blank if there is no user input otherwise prints menu with user input
	border();

	cout << "\t" << "Account" << endl;
	cout << "Initial Deposit Amount: ";

	if (m_initDeposit > 0) {
		cout << "$" << m_initDeposit << endl;
		cout << "Monthly Deposit: $";
	}
	else {
	   cout << "\nMonthly Deposit: ";
	}

	if (m_monthlyDeposit > 0) {
		cout << m_monthlyDeposit << endl;
		cout << "Annual Interest: %";
	}
	else {
		cout << "\nAnnual Interest: ";
	}

	if (m_interest > 0) {
		cout << m_interest << endl;
		cout << "Number of Years: ";
	}
	else {
		cout << "\nNumber of Years: ";
	}

	if (m_totalYears > 0) {
		cout << m_totalYears << endl;
		cout << "Press 'Enter' to continue" << endl;
	}
	else {
		cout << "\nPress 'Enter' to continue" << endl;
	}

	border();
	cout << endl;
}

void BankingApp::displayStaticInitial () { // prints static report without monthly deposits
	cout << "Balance and Interest With Only Initial Deposit" << endl;
	cout << setfill('-') << setw(60) << "\n";
	cout << "Year\t" << "End of Year Balance\t" << "End of Year Earned Interest" << endl;

	m_totalInitialBalance = static_cast <double>(m_initDeposit);

	cout << setprecision(2) << fixed;

	for (int i = 0; i < m_totalYears; ++i) { // loops depending upon total years
		staticInitialBalance(); // calls this function for each year of the total years
		cout << i + 1 << "\t\t$" << m_totalInitialBalance << "\t\t\t$" << m_endOfYearInitialInterest << endl;; // prints total balance and total interest per year
	}
}

void BankingApp::staticInitialBalance () {
	m_totalInitialInterest = 0;
	m_endOfYearInitialInterest = 0;

	for (int i = 0; i < 12; ++i) { // loops 12 times, for each month
		m_totalInitialInterest = (m_totalInitialBalance * ((m_interest/100)/12)); // gets interest in a decimal per month and multiplies it by the balance
		m_totalInitialBalance = m_totalInitialBalance + m_totalInitialInterest; // adds the interest per month to the balance
		m_endOfYearInitialInterest = m_endOfYearInitialInterest + m_totalInitialInterest; // adds the interest per month to the total interest
	}
}

void BankingApp::displayStaticMonthly () { // prints static report with monthly deposits
	cout << "Balance and Interest With Monthly Deposits" << endl;
	cout << setfill('-') << setw(60) << "\n";
	cout << "Year\t" << "End of Year Balance\t" << "End of Year Earned Interest" << endl;

	m_totalMonthlyBalance = static_cast <double>(m_initDeposit);

	cout << setprecision(2) << fixed;
	cout << setfill(' ');

	for (int i = 0; i < m_totalYears; ++i) { // loops depending upon total years
		staticMonthlyBalance(); // calls this function for each year of the total years
		cout << i + 1;
		cout.width(14);
		cout << "$" << m_totalMonthlyBalance;
		cout.width(20);
		cout << "$" << m_endOfYearInterest << endl;
	}
}

void BankingApp::staticMonthlyBalance () {
	m_totalMonthlyInterest = 0;
	m_endOfYearInterest = 0;

	for (int i = 0; i < 12; ++i) { // loops 12 times, for each month
		m_totalMonthlyInterest = ((m_totalMonthlyBalance + m_monthlyDeposit) * ((m_interest/100)/12)); // gets interest in a decimal per month and multiplies it by the balance plus the monthly deposit
		m_totalMonthlyBalance = (m_totalMonthlyBalance + m_monthlyDeposit) + m_totalMonthlyInterest; // adds the interest per month and monthly deposits to the balance
		m_endOfYearInterest = m_endOfYearInterest + m_totalMonthlyInterest; // adds the interest per month to the total interest
	}
}

char BankingApp::getQuit () { // returns value of quit
	return quit;
}

void BankingApp::setQuit (char t_userDecision) { // sets quit equal to parameter passed in
	quit = t_userDecision;
}
void runAccount () { // calls the other functions to run the program
	char temp = ' ';
	BankingApp* account = new BankingApp ();

	while (toupper(account->getQuit()) != 'Y') { // checks if user wants to quit
		account->displayMenu();
		getchar(); // a way to wait for user input
		account->getUserInput();
		account->displayMenu();
		cin.clear();
		cin.ignore();
		getchar(); // a way to wait for user input
		account->displayStaticInitial();
		account->displayStaticMonthly();

		cout << "Would you like to: Quit or Start Over?" << endl;
		cout << "Enter Y to Quit or N to Start Over" << endl;
		cout << ">>";
		cin >> temp;
		account->setQuit(toupper(temp));

		while (account->getQuit() != 'Y' && account->getQuit() != 'N') {
			cout << "Invalid Entry" << endl;
			cout << "Would you like to: Quit or Start Over?" << endl;
			cout << "Enter Y to Quit or N to Start Over" << endl;
			cout << ">>";
			cin >> temp;
			account->setQuit(toupper(temp));
		}
		account = new BankingApp ();
		cin.clear();
		cin.ignore();
	}
}
void border () {
	cout << "_________________________" << endl;

}
