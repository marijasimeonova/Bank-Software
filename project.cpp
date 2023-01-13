// dodaj od dokumento !!! pred da predades

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// hashed_password ?
struct User
{
    string username;
    string password;
    int balance;
};

vector<User> loadUsersFromFile(string filename)
{
}

void saveUsersToFile(string filename, vector<User> users)
{
}

void Login(vector<User> users, const string username, const string password)
{
    // кара потребителят да въведе име, а след това и парола
    cout << "LOG";
}

User Register(const string username, const string password)
{
    // кара потребителят да въведе свободно име, което съдържа само латински букви или символи  и парола, която трябва да се потвърди и да съдържа само латински букви,
    // числа и символите !@#$%^&* като трябва да има поне 1 малка буква, 1 главна и 1 символ, а паролата трябва да е поне 5 символа.
    // Паролата трябва да се съхранява в хеширан вид
}

bool validateUsername(string username)
{
}

bool validatePassword(string password)
{
}

string hashPassword(string password)
{
}

int main()
{
    // open and read from  “users.txt”
    char command = ' '; // za da moze da se uleze u while cikla
    string username, password, filename = "users.txt";
    vector<User> users = loadUsersFromFile(filename);
    while (command != 'Q')
    { // quit - излиза от програмата и презаписва файла “users.txt” с новото състояние на данните
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