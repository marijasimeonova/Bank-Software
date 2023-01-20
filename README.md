# Bank-Software

Bank Software is a program that simulates a basic set of activities in a bank.

When starting the program, user profiles are loaded from the "users.txt" file, which are stored in the following format:
username:hashed_password:balance

In the start menu, the user can choose one of the following three options (the program waits for the user to enter a command, using one of the letters listed below):
L - login - prompts the user to enter a name and then a password
R - register - prompts the user to enter a free name that contains only Latin letters or symbols and a password that must be confirmed and contain only Latin letters, numbers and the symbols !@#$%^&* and must have at least 1 lowercase letter, 1 uppercase and 1 character, and the password must be at least 5 characters. The password must be stored in hashed form
Q - quit - exits the program and overwrites the file “users.txt” with the new state of the data

Upon successful registration/login, the user receives the following menu, where X is the amount available to the user (at registration, the amount is equal to 0):
You have X BGN. Choose one of the following options:
C - cancel account (prompts the user to enter his password and if it is correct and his account balance is zero, deletes his account from the system and returns him to the home menu)
D - deposit (successfully deposited a positive number with no more than 2 decimal places. If a number with more than 2 digits after the comma is entered, they should be cut off. (1.234 -> 1.23))
L - logout (returns the user to the home menu)
T - transfer (transfer an amount (a positive number with no more than 2 digits after the decimal point) from the current account to another account, if the second account exists and if there is enough money in the current account, and an overdraft of at most 10,000 can be reached BGN)
W - withdraw (reduces the current account by a number entered by the user (positive, with no more than 2 digits after the decimal point), and can reach a credit (overdraft) of a maximum of BGN 10,000)
