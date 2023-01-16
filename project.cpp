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

bool validateUsername(const string &username, vector<User> &users)
{
    if (username.empty())
    {
        return false;
    }
    size_t found = username.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*");
    if (found != string::npos)
    {
        return false;
    }
    for (auto &user : users) // that username is already used
    {
        if (user.getUsername() == username)
        {
            return false;
        }
    }

    return true;
}

bool validatePassword(const string &password)
{
    if (password.empty() || password.size() < 5)
    {
        return false;
    }
    size_t found = password.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*");
    if (found != string::npos)
    {
        return false;
    }
    int hasUpper = 0, hasLower = 0, hasSymbol = 0;
    for (auto &character : password)
    {
        if (isupper(character))
        {
            hasUpper++;
        }
        else if (islower(character))
        {
            hasLower++;
        }
        else if (character == '!' || character == '@' || character == '#' || character == '%' || character == '^' || character == '&' || character == '*')
        {
            hasSymbol++;
        }
    }
    if (hasUpper < 1 || hasLower < 1 || hasSymbol < 1)
    {
        return false;
    }

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
            if (validateUsername(username, users) && validatePassword(password))
            {
                User user = Register(username, password);
                users.push_back(user);
                cout << "Successfully registered user" << endl;
                bankMenu(users, users.back());
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