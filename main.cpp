#include <iostream>
#include <fstream>
#include <cstdlib>
#include "account.h"

using namespace std;

void writeAccount();
void displayAccount(int);
void depositWithdraw(int, int); // 1: deposit, 2: withdraw
void deleteAccount(int);
void displayAll();

int main() {
    int choice, accNum;

    do {
        cout << "\n\n==== Bank Management System ====\n";
        cout << "1. Create Account\n";
        cout << "2. View Account Details\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Delete Account\n";
        cout << "6. List All Accounts\n";
        cout << "7. Exit\n";
        cout << "Enter your choice (1-7): ";
        cin >> choice;

        switch (choice) {
        case 1:
            writeAccount();
            break;
        case 2:
            cout << "Enter account number: ";
            cin >> accNum;
            displayAccount(accNum);
            break;
        case 3:
            cout << "Enter account number: ";
            cin >> accNum;
            depositWithdraw(accNum, 1);
            break;
        case 4:
            cout << "Enter account number: ";
            cin >> accNum;
            depositWithdraw(accNum, 2);
            break;
        case 5:
            cout << "Enter account number: ";
            cin >> accNum;
            deleteAccount(accNum);
            break;
        case 6:
            displayAll();
            break;
        case 7:
            cout << "Thank you for using the system!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

        cin.ignore();
        cin.get(); // Pause

    } while (choice != 7);

    return 0;
}
void writeAccount() {
    Account acc;
    ofstream outFile("accounts.dat", ios::binary | ios::app);
    acc.createAccount();
    outFile.write(reinterpret_cast<char *>(&acc), sizeof(Account));
    outFile.close();
    cout << "Account created successfully.\n";
}

void displayAccount(int num) {
    Account acc;
    bool found = false;
    ifstream inFile("accounts.dat", ios::binary);

    while (inFile.read(reinterpret_cast<char *>(&acc), sizeof(Account))) {
        if (acc.getAccountNumber() == num) {
            acc.showAccount();
            found = true;
        }
    }

    inFile.close();
    if (!found) cout << "Account not found.\n";
}

void depositWithdraw(int num, int option) {
    Account acc;
    fstream file("accounts.dat", ios::binary | ios::in | ios::out);
    bool found = false;

    while (!file.eof() && !found) {
        streampos pos = file.tellg();
        file.read(reinterpret_cast<char *>(&acc), sizeof(Account));
        if (acc.getAccountNumber() == num) {
            acc.showAccount();

            float amount;
            if (option == 1) {
                cout << "Enter amount to deposit: ";
                cin >> amount;
                acc.deposit(amount);
            } else {
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                acc.withdraw(amount);
            }

            file.seekp(pos);
            file.write(reinterpret_cast<char *>(&acc), sizeof(Account));
            cout << "Transaction successful.\n";
            found = true;
        }
    }

    file.close();
    if (!found) cout << "Account not found.\n";
}

void deleteAccount(int num) {
    Account acc;
    ifstream inFile("accounts.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    bool found = false;

    while (inFile.read(reinterpret_cast<char *>(&acc), sizeof(Account))) {
        if (acc.getAccountNumber() != num) {
            outFile.write(reinterpret_cast<char *>(&acc), sizeof(Account));
        } else {
            found = true;
        }
    }

    inFile.close();
    outFile.close();

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    if (found) cout << "Account deleted successfully.\n";
    else cout << "Account not found.\n";
}

void displayAll() {
    Account acc;
    ifstream inFile("accounts.dat", ios::binary);
    cout << "\n\n=== All Accounts ===\n";

    while (inFile.read(reinterpret_cast<char *>(&acc), sizeof(Account))) {
        acc.showAccount();
        cout << "---------------------------\n";
    }

    inFile.close();
}

