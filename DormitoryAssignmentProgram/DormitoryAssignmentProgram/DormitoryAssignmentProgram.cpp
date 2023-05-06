#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <iomanip>
#include <sstream>
#include "makeHash.h"
#include <Windows.h>
#include "Dormitory.h"
#include "Accounts.h"
#include "Protection.h"


using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    const int maxUsers = 100;
    User accounts[maxUsers];
    int count = 0;

    int choice, ind, loginedUser = 0;
    do {
        system("cls");
        cout << "\n\tМеню\n 1. Регистрация\n 2. Вход\n 3. Выход\n  Ваш выбор: ";
        choice = inputInt(1, 3);
        loadAccounts(accounts, count);
        switch (choice) {
        case 1:
            registration(accounts, count);
            break;
        case 2:
            ind = authorisation(accounts, count, loginedUser);
            if (ind == 1) dormitoryFunctions();
            if (ind == 2) adminFunctions(accounts, count, loginedUser);

            break;
        case 3:
            break;
        default:
            cout << "  Неверный выбор, попробуйте еще раз\n\n";
        }
    } while (choice != 3);

    return 0;
}
