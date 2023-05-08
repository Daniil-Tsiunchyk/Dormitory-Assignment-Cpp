#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <thread>
#include "HashSHA-256.h"
using namespace std;

struct User {
    string login;
    string password;
    int role;
};

const string USERS_FILE = "users.txt";

void loadAccounts(User users[], int& usersCount);
void registration(User users[], int& usersCount);
int authorisation(User users[], int usersCount, int& onlineUser);
void dormitoryFunctions();
void adminFunctions(User users[], int usersCount, int onlineUser);
void saveUsers(User users[], int usersCount);
void manageUsers(User users[], int usersCount, int onlineUser);
