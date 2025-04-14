// account.h
#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
private:
    int accountNumber;
    char name[50];
    float balance;

public:
    void createAccount();
    void showAccount() const;
    void deposit(float amount);
    void withdraw(float amount);
    int getAccountNumber() const;
    float getBalance() const;
};

#endif
