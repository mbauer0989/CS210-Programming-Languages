/*
 * BankingApp.h
 *
 *  Created on: Aug 1, 2020
 *      Author: Michael Bauer
 */

#ifndef BANKINGAPP_H_
#define BANKINGAPP_H_

class BankingApp {
   public:
	  BankingApp ();
	  void setDeposit(int t_userDeposit); // sets initial deposit
	  void setMonthlyDeposit (int t_userMonDeposit); // sets monthly deposit
	  void setInterest (int t_userInterest); // sets annual interest
	  void setYears (int t_userYears); // sets number of years
      void getUserInput (); // collects user input for initial deposit, monthly deposit, interest, and years
	  void displayMenu (); // prints the menu
	  void displayStaticInitial (); // prints the static report without monthly deposits
	  void displayStaticMonthly (); // prints the static report with monthly deposits
	  void staticInitialBalance (); // calculates the total balance and interest for a year without monthly deposits
	  void staticMonthlyBalance (); // calculates the total balance and interest for a year with monthly deposits
	  static char getQuit (); // returns the quit value
	  static void setQuit (char t_userDecision); // sets quit

   private:
	  int m_initDeposit; // initial deposit
	  int m_monthlyDeposit; // monthly deposits
	  double m_interest; // annual interest
	  int m_totalYears; // number of years
	  double m_totalInitialInterest; // total interest per month without monthly deposits
	  double m_totalInitialBalance; // total balance per year without monthly deposits
	  double m_totalMonthlyInterest; // total interest per month with monthly deposits
	  double m_totalMonthlyBalance; // total balance per year with monthly deposits
	  double m_endOfYearInterest; // total interest per year without monthly deposits
	  double m_endOfYearInitialInterest; // total interest per year with monthly deposits
	  static char quit; // value used to quit program
};

void runAccount (); // runs the program
void border (); // outputs a border

#endif /* BANKINGAPP_H_ */
