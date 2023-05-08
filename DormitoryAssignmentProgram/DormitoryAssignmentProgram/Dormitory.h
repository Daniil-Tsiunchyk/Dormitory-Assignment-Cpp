#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <Windows.h>

using namespace std;

const string DORMITORY_FILE = "dormitory.txt";


struct Student {
    string name;
    string surname;
    string faculty;
    int course;
};

struct Room {
    int roomNumber;
    int floor;
    Student occupants[4];
};

void saveRooms(const string& filename, Room rooms[], int roomsCount);
void loadRooms(const string& filename, Room rooms[], int& roomsCount);
void dormitoryFunctions();
void createRoom(Room rooms[], int& roomsCount);
void editRoom(Room rooms[], int roomsCount);
void deleteRoom(Room rooms[], int& roomsCount);
void showRooms(const Room rooms[], int roomsCount);
void searchRoom(const Room rooms[], int roomsCount);
void sortRooms(Room rooms[], int roomsCount);
