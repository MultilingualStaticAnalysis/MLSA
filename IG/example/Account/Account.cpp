/* Implementation for the Account class (Account.cpp) */
#include <iostream>
#include <iomanip>
#include "Account.h"
using namespace std;
 
// Constructor
Account::Account(int no, double b) : accountNumber(no), balance(b) { }
 
// Public getter for private data member accountNumber
int Account::getAccountNumber() const {
   return accountNumber;
}
 
// Public getter for private data member balance
double Account::getBalance() const {
   return balance;
}
 
// Public setter for private data member balance
void Account::setBalance(double b) {
   balance = b;
}
 
// Adds the given amount to the balance
void Account::credit(double amount) {
   setBalance(balance+amount);
}
 
// Subtract the given amount from the balance
void Account::debit(double amount) {
   if (amount <= balance) {
      setBalance(balance-amount);
   } else {
      cout << "Amount withdrawn exceeds the current balance!" << endl;
   }
}
 
// Print description for this Account instance
void Account::print() const {
   cout << fixed << setprecision(2);
   cout << "A/C no: " << accountNumber << " Balance=$" << balance << endl;
}