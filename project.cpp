// dodaj od dokumento !!! pred da predades

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


class User
{
private:
    string username;
    string password;
    float balance;
public:
    User(string username, string password){
        this->username = username;
        this->password = password;
        this->balance  = 0;
    }
    User(string username, string password, float balance){
        this->username = username;
        this->password = password;
        this->balance  = balance;
    }
    string getUsername(){
        return username;
    }
    string getPassword(){
        return password;
    }
    float getBalance(){
        return balance;
    }
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
}

User Register(const string username, const string password)
{
    string hashedPassword;
    hashedPassword = hashPassword(password);
    return User(username, hashedPassword);
}

bool validateUsername(string username)
{
}

bool validatePassword(string password)
{
}

string hashPassword(string password)
{
    hash<string> str_hash;
    size_t hashedPassword = str_hash(password);
    return to_string(hashedPassword);
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