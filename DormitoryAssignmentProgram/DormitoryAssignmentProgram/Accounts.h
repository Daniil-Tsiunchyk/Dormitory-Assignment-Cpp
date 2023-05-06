#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <Windows.h>
#include "makeHash.h"
using namespace std;

struct User {
	string username;
	string password;
	int role;
};

const string usersFilename = "users.txt";


void loadAccounts(User users[], int& usersCount);
void registration(User users[], int& usersCount);
int authorisation(User users[], int usersCount, int& onlineUser);
void dormitoryFunctions();
void adminFunctions(User users[], int usersCount, int onlineUser);
void saveUsers(User users[], int usersCount);
void manageUsers(User users[], int usersCount, int onlineUser);
