// account.cpp
#include <iostream>
#include <cstring>
#include "account.h"

using namespace std;

void Account::createAccount() {
    cout << "Enter account number: ";
    cin >> accountNumber;
    cin.ignore();
    cout << "Enter account holder name: ";
    cin.getline(name, 50);
    cout << "Enter initial balance: ";
    cin >> balance;
}

void Account::showAccount() const {
    cout << "Account Number: " << accountNumber << endl;
    cout << "Account Holder: " << name << endl;
    cout << "Balance: $" << balance << endl;
}

void Account::deposit(float amount) {
    balance += amount;
}

void Account::withdraw(float amount) {
    if (amount > balance)
        cout << "Insufficient balance.\n";
    else
        balance -= amount;
}

int Account::getAccountNumber() const {
    return accountNumber;
}

float Account::getBalance() const {
    return balance;
}
