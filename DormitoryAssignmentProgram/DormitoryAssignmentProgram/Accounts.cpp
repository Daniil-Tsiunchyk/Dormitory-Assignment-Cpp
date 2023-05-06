#include "Accounts.h"
#include "Protection.h"


void registration(User users[], int& usersCount) {
    const int maxUsers = 100;
    User newUser;
    string confirmPassword;
    bool validInput;
    cout << "Регистрация нового пользователя\n";

    do {
        validInput = true;
        cout << "\nВведите логин: ";
        cin >> newUser.username;

        for (int i = 0; i < usersCount; ++i) {
            if (users[i].username == newUser.username) {
                cout << "Такой логин уже существует, попробуйте еще раз\n";
                validInput = false;
                break;
            }
        }
    } while (!validInput);

    do {
        cout << "Введите пароль: ";
        newUser.password = inputPassword();
        cout << "\nПодтвердите пароль: ";
        confirmPassword = inputPassword();

        if (newUser.password != confirmPassword) {
            cout << "Пароли не совпадают, попробуйте еще раз\n";
        }
    } while (newUser.password != confirmPassword);

    newUser.role = 1;
    newUser.password = doHashNow(newUser.password);

    users[usersCount++] = newUser;

    saveUsers(users, usersCount);

    cout << "\nПользователь успешно зарегистрирован\n";
    Sleep(2000);
    system("cls");
}

int authorisation(User users[], int usersCount, int& onlineUser) {
    string inputUsername, password;
    int loginAttempts = 3;
    while (loginAttempts > 0) {
        cout << "Введите логин: ";
        cin >> inputUsername;
        cout << "Введите пароль: ";
        password = inputPassword();
        password = doHashNow(password);
        for (int i = 0; i < usersCount; ++i) {
            if (users[i].username == inputUsername && users[i].password == password) {
                cout << "\nУспешная авторизация\n\n";
                onlineUser = i;
                return users[i].role;
            }
        }

        cout << "\nНеверный логин или пароль. Осталось попыток: " << --loginAttempts << endl;
    }
    cout << "Авторизация не удалась. Пожалуйста, попробуйте позже\n";
    return 0;
}

void saveUsers(User users[], int usersCount) {
    ofstream usersFile(usersFilename);
    if (!usersFile) {
        cerr << "Ошибка открытия файла пользователей\n";
        return;
    }

    for (int i = 0; i < usersCount; ++i) {
        usersFile << users[i].username << " " << users[i].password << " " << users[i].role << endl;
    }

    usersFile.close();
}

void loadAccounts(User users[], int& usersCount) {
    ifstream usersFile(usersFilename);
    if (!usersFile) {
        cerr << "Ошибка открытия файла пользователей. Создание нового файла...\n";
        ofstream newUsersFile(usersFilename);
        newUsersFile.close();
        usersCount = 0;
        return;
    }

    usersCount = 0;
    while (usersFile >> users[usersCount].username >> users[usersCount].password >> users[usersCount].role) {
        ++usersCount;
    }

    usersFile.close();
}

void adminFunctions(User users[], int usersCount, int onlineUser) {
    loadAccounts(users, usersCount);

    int choice;
    do {
        system("cls");
        cout << "\n\tМеню:\n 1. Работа с комнатами\n 2. Управление пользователями\n 3. Выйти\n  Ваш выбор: ";
        choice = inputInt(1, 3);
        switch (choice) {
        case 1:
            dormitoryFunctions();
            break;
        case 2:
            manageUsers(users, usersCount, onlineUser);
            break;
        case 3:
            cout << "Выход\n";
            break;
        default:
            cout << "Неверный выбор, попробуйте еще раз\n";
        }
    } while (choice != 3);
}

void manageUsers(User users[], int usersCount, int onlineUser) {
    int choice, userId;
    string newUsername, newPassword;
    int newRole;
    do {
        system("cls");
        cout << "\n\tСписок пользователей:\n"
            << " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n"
            << "| ID | Имя Пользователя | Роль в системе  |\n";

        for (int i = 0; i < usersCount; ++i) {
            cout << "|  " << i + 1 << " | " << setw(15) << users[i].username << "  | " << setw(15) << (users[i].role == 1 ? "пользователь" : "администратор") << " |\n";
        }
        cout << "|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n\n"
            << "\n\t\tМеню:\n\t1. Редактировать пользователя\n\t2. Удалить пользователя\n\t3. Выйти\n\t\t>>>";
        choice = inputInt(1, 3);

        switch (choice) {
        case 1:
            cout << "Введите ID пользователя для редактирования: ";
            userId = inputInt(1, 100);
            userId--;
            if (userId >= 0 && userId < usersCount) {
                cout << "Введите новое имя пользователя: ";
                cin >> newUsername;
                cout << "Введите новый пароль: ";
                cin >> newPassword;
                cout << "Введите новую роль (1 - пользователь, 2 - администратор): ";
                newRole = inputInt(1, 2);

                users[userId].username = newUsername;
                users[userId].password = newPassword;
                users[userId].role = newRole;
                saveUsers(users, usersCount);

                cout << "Пользователь успешно отредактирован\n";
                Sleep(2000);
                system("cls");
            }
            else {
                cout << "Пользователь с указанным ID не найден\n";
            }
            break;
        case 2:
            cout << "Введите ID пользователя для удаления: ";
            userId = inputInt(1, 100);
            userId--;
            if (onlineUser != userId) {
                if (userId >= 0 && userId < usersCount) {
                    for (int i = userId; i < usersCount - 1; ++i) {
                        users[i] = users[i + 1];
                    }
                    --usersCount;
                    saveUsers(users, usersCount);
                    cout << "Пользователь успешно удален\n";
                    Sleep(2000);
                }
                else {
                    cout << "Пользователь с указанным ID не найден\n";
                }
            }
            else {
                cout << "Вы не можете удалить себя\n";
                Sleep(2000);
            }
            break;
        case 3:
            break;
        default:
            cout << "Неверный выбор, попробуйте еще раз\n";
        }
    } while (choice != 3);
}
