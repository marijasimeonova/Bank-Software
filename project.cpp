// title

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

class User
{
private:
    string username;
    string password;
    double balance;

public:
    User(string username, string password)
    {
        this->username = username;
        this->password = password;
        this->balance = 0;
    }
    User(string username, string password, double balance)
    {
        this->username = username;
        this->password = password;
        balance = round(balance * 100) / 100; // round to 2 decimal places
        this->balance = balance;
    }
    string getUsername()
    {
        return username;
    }
    string getPassword()
    {
        return password;
    }
    double getBalance()
    {
        return balance;
    }
    void setBalance(double balance)
    {
        balance = round(balance * 100) / 100;
        this->balance = balance;
    }
};

string hashPassword(string password)
{
    hash<string> str_hash;
    size_t hashedPassword = str_hash(password);
    return to_string(hashedPassword);
}

vector<User> loadUsersFromFile(string filename)
{
    // to do implement loading from file
    vector<User> temp;
    temp.push_back(User("test1", hashPassword("test1")));
    temp.push_back(User("test2", hashPassword("test2"), 40.21));
    temp.push_back(User("test3", hashPassword("test3")));
    return temp;
}

void saveUsersToFile(string filename, vector<User> &users)
{
    // to do
}

void cancelAccount(vector<User> &users, User &user)
{
    string password;
    cout << "Enter password: ";
    cin >> password;
    string hashedPassword;
    hashedPassword = hashPassword(password);
    bool cancelAccount = false;
    for (vector<User>::iterator deleteUser = users.begin(); deleteUser != users.end(); ++deleteUser)
    {
        if (deleteUser->getUsername() == user.getUsername() && user.getPassword() == hashedPassword && user.getBalance() == 0)
        {
            deleteUser = users.erase(deleteUser);
            cancelAccount = true;
            break;
        }
    }
    if (cancelAccount)
    {
        cout << "Your account was canceled" << endl;
    }
    else
    {
        cout << "Your account cannot be canceled" << endl;
    }
}

void deposit(User &user)
{
    double deposit;
    cout << "Enter the amount you want to deposit: ";
    cin >> deposit;
    deposit = round(deposit * 100) / 100;
    user.setBalance(user.getBalance() + deposit);
}

void transfer(vector<User> &users, User &user)
{
    double transfer;
    string recipient;
    cout << "Enter the amount you want to transfer: ";
    cin >> transfer;
    transfer = round(transfer * 100) / 100;
    cout << "Enter the recipient's username: ";
    cin >> recipient;
    double overdraft = -10000;
    double newBalance = user.getBalance() - transfer;
    bool existingUser = false;
    if (newBalance >= overdraft)
    {
        for (auto &user2 : users)
        {
            if (user2.getUsername() == recipient)
            {
                existingUser = true;
                user2.setBalance(user2.getBalance() + transfer);
                user.setBalance(newBalance);
            }
        }
    }
    if (!existingUser)
    {
        cout << "Transaction declined" << endl;
    }
}

void withdraw(User &user)
{
    double withdraw;
    cout << "Enter the amount you want to withdraw: ";
    cin >> withdraw;
    withdraw = round(withdraw * 100) / 100;
    double overdraft = -10000;
    double newBalance = user.getBalance() - withdraw;
    if (newBalance >= overdraft)
    {
        user.setBalance(newBalance);
    }
    else
    {
        cout << "Withdrawal declined" << endl;
    }
}

void bankMenu(vector<User> &users, User &user)
{
    char command = ' ';
    while (command != 'L' && command != 'C')
    {
        cout << "You have " << user.getBalance() << " BGN. Choose one of the following options:" << endl;
        cout << "C - cancel account" << endl;
        cout << "D - deposit" << endl;
        cout << "L - logout" << endl;
        cout << "T - transfer" << endl;
        cout << "W - withdraw" << endl;
        cin >> command;
        switch (command)
        {
        case 'C':
            cancelAccount(users, user);
            break;
        case 'D':
            deposit(user);
            break;
        case 'T':
            transfer(users, user);
            break;
        case 'W':
            withdraw(user);
            break;
        case 'L':
            break;
        default:
            cout << "There is no such option" << endl;
            break;
        }
    }
}

void Login(vector<User> &users, const string username, const string password)
{
    string hashedPassword;
    hashedPassword = hashPassword(password);
    for (auto &user : users)
    {
        if (user.getUsername() == username && user.getPassword() == hashedPassword)
        {
            bankMenu(users, user);
            break;
        }
    }
}

User Register(const string username, const string password)
{
    string hashedPassword;
    hashedPassword = hashPassword(password);
    return User(username, hashedPassword);
}

bool validateUsername(string username)
{
    // to do implement logic
    return true;
}

bool validatePassword(string password)
{
    // to do implement logic
    return true;
}

int main()
{
    char command = ' ';
    string username, password, filename = "users.txt";
    vector<User> users = loadUsersFromFile(filename);

    while (command != 'Q')
    {
        cout << "Enter a command: " << endl;
        cout << "L - login" << endl;
        cout << "R - register" << endl;
        cout << "Q - quit" << endl;
        cin >> command;
        switch (command)
        {
        case 'L':
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            Login(users, username, password);
            break;
        case 'R':
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            if (validateUsername(username) && validatePassword(password))
            {
                User user = Register(username, password);
                users.push_back(user);
                cout << "Successfully registered user" << endl;
                bankMenu(users, user);
            }
            else
            {
                cout << "Invalid username or password" << endl;
            }
            break;
        case 'Q':
            saveUsersToFile(filename, users);
            break;
        default:
            cout << "Wrong command entered!" << endl;
            break;
        }
    }

    return 0;
}