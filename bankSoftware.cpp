#include <iostream>
#include <fstream>
#include <sstream>
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
        // round to 2 decimal places
        balance = round(balance * 100) / 100;
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
        // round to 2 decimal places
        balance = round(balance * 100) / 100;
        this->balance = balance;
    }
};

string hashPassword(string password)
{
    // hash user's password
    hash<string> str_hash;
    size_t hashedPassword = str_hash(password);
    return to_string(hashedPassword);
}

vector<User> loadUsersFromFile(string filename)
{
    ifstream file;
    file.open("users.txt");
    vector<User> users;
    if (file.is_open())
    {
        // read a complete line and store it here
        string line;
        // read all lines of the file
        while (getline(file, line))
        {
            // read a complete line into the string line
            // put it into a istringstream to be able to extract it with iostream functions
            istringstream iss(line);

            // vector to store the substrings
            string substring;
            vector<string> substrings;

            // get the substrings from the istringstream
            while (getline(iss, substring, ':'))
            {
                // Add the substring to the vector
                substrings.push_back(substring);
            }
            // insert user to file
            User user(substrings[0], substrings[1], stoi(substrings[2]));
            users.push_back(user);
        }
    }
    else
    {
        cout << "Could not open file!" << endl;
    }

    return users;
}

void saveUsersToFile(string filename, vector<User> &users)
{
    // delete previous data
    fstream file;
    file.open(filename, ofstream::out | ofstream::trunc);
    file.close();
    // open the file to perform write operation using file object
    file.open(filename, ios::out);
    if (file.is_open())
    {
        // insert users
        for (auto &user : users)
        {
            file << user.getUsername() << ':' << user.getPassword() << ':' << user.getBalance() << endl;
        }

        file.close();
    }
    else
    {
        cout << "Could not open file!" << endl;
    }
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
        // check if that user is existing and his balance is zero
        if (deleteUser->getUsername() == user.getUsername() && user.getPassword() == hashedPassword && user.getBalance() == 0)
        {
            // cancel(delete) user's account
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
    // add the wanted deposit to the user's balance
    user.setBalance(user.getBalance() + deposit);
}

void transfer(vector<User> &users, User &user)
{
    double transfer;
    string recipient;
    cout << "Enter the amount you want to transfer: ";
    cin >> transfer;
    cout << "Enter the recipient's username: ";
    cin >> recipient;
    double overdraft = -10000;
    double newBalance = user.getBalance() - transfer;
    bool existingUser = false;
    if (newBalance >= overdraft)
    {
        for (auto &receivingUser : users)
        {
            // check if there is existing user to recieve the money
            if (receivingUser.getUsername() == recipient)
            {
                existingUser = true;
                // add the wanted transfer to the recieving user's balance
                receivingUser.setBalance(receivingUser.getBalance() + transfer);
                // subtract the wanted transfer from current user
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
    double overdraft = -10000;
    double newBalance = user.getBalance() - withdraw;
    if (newBalance >= overdraft)
    {
        // subtract the wanted withdraw from the user's balance
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
    bool existingUser = false;
    for (auto &user : users)
    {
        // check if that user is existing
        if (user.getUsername() == username && user.getPassword() == hashedPassword)
        {
            // take user to bankMenu
            existingUser = true;
            bankMenu(users, user);
            break;
        }
    }
    if (!existingUser)
    {
        cout << "No user found!" << endl;
    }
}

User Register(const string username, const string password)
{
    string hashedPassword;
    hashedPassword = hashPassword(password);
    // create new user
    return User(username, hashedPassword);
}

bool validateUsername(const string &username, vector<User> &users)
{
    if (username.empty())
    {
        return false;
    }
    // check if the username contains only latin letters or symbols
    size_t found = username.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!@#$%^&*-_.,");
    if (found != string::npos)
    {
        return false;
    }
    // check if that username is already used
    for (auto &user : users)
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
    // check if password consists at least 5 characters
    if (password.empty() || password.size() < 5)
    {
        return false;
    }
    // check if the password contains only latin letters, numbers or specific symbols
    size_t found = password.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*");
    if (found != string::npos)
    {
        return false;
    }
    // check if the password contains at least one upper letter, lower letter and symbol
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
    // load user profiles from "users.txt" and store them in the vector users
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
            cin.ignore();
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
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