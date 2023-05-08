#include "Accounts.h"
#include "Protection.h"

void registration(User users[], int& count) {
    const int maxUsers = 100;
    User newUser;
    string confirmPassword;
    bool validInput;
    cout << "Регистрация нового пользователя\n";

    do {
        validInput = true;
        cout << "\nВведите логин: ";
        cin >> newUser.login;

        for (int i = 0; i < count; ++i) {
            if (users[i].login == newUser.login) {
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
    newUser.password = makeHash(newUser.password);

    users[count++] = newUser;

    saveUsers(users, count);

    cout << "\nПользователь успешно зарегистрирован\n";
    this_thread::sleep_for(chrono::seconds(2));
    system("cls");
}

int authorisation(User users[], int count, int& onlineUser) {
    string inputUsername, password;
    int attempts = 3;
    while (attempts > 0) {
        cout << "Введите логин: ";
        cin >> inputUsername;
        cout << "Введите пароль: ";
        password = inputPassword();
        password = makeHash(password);
        for (int i = 0; i < count; ++i) {
            if (users[i].login == inputUsername && users[i].password == password) {
                cout << "\nУспешная авторизация\n\n";
                onlineUser = i;
                return users[i].role;
            }
        }

        cout << "\nНеверный логин или пароль. Осталось попыток: " << --attempts << endl;
    }
    cout << "Авторизация не удалась. Пожалуйста, попробуйте позже\n";
    return 0;
}

void saveUsers(User users[], int count) {
    ofstream usersFile(USERS_FILE);
    if (!usersFile) {
        cerr << "Ошибка открытия файла пользователей\n";
        return;
    }

    for (int i = 0; i < count; ++i) {
        usersFile << users[i].login << " " << users[i].password << " " << users[i].role << endl;
    }

    usersFile.close();
}

void loadAccounts(User users[], int& count) {
    ifstream usersFile(USERS_FILE);
    if (!usersFile) {
        cerr << "Ошибка открытия файла пользователей. Создание нового файла...\n";
        ofstream newUsersFile(USERS_FILE);
        newUsersFile.close();
        count = 0;
        return;
    }

    count = 0;
    while (usersFile >> users[count].login >> users[count].password >> users[count].role) {
        ++count;
    }

    usersFile.close();
}

void adminFunctions(User users[], int count, int onlineUser) {
    loadAccounts(users, count);

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
            manageUsers(users, count, onlineUser);
            break;
        case 3:
            cout << "Выход\n";
            break;
        default:
            cout << "Неверный выбор, попробуйте еще раз\n";
        }
    } while (choice != 3);
}

void manageUsers(User users[], int count, int onlineUser) {
    int choice, userId;
    string newUsername, newPassword;
    int newRole;
    do {
        system("cls");
        cout << "\n\tСписок пользователей:\n"
            << " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n"
            << "| ID | Имя Пользователя | Роль в системе  |\n";

        for (int i = 0; i < count; ++i) {
            cout << "|  " << i + 1 << " | " << setw(15) << users[i].login << "  | " << setw(15) << (users[i].role == 1 ? "пользователь" : "администратор") << " |\n";
        }
        cout << "|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n\n"
            << "\n\tМеню:\n 1. Редактировать пользователя\n 2. Удалить пользователя\n 3. Выйти\n Ваш выбор: ";
        choice = inputInt(1, 3);

        switch (choice) {
        case 1:
            cout << "Введите ID пользователя для редактирования: ";
            userId = inputInt(1, 100);
            userId--;
            if (userId >= 0 && userId < count) {
                cout << "Введите новое имя пользователя: ";
                cin >> newUsername;
                cout << "Введите новый пароль: ";
                newPassword = inputPassword();
                cout << "Введите новую роль (1 - пользователь, 2 - администратор): ";
                newRole = inputInt(1, 2);

                users[userId].login = newUsername;
                users[userId].password = makeHash(newPassword);
                users[userId].role = newRole;
                saveUsers(users, count);

                cout << "Пользователь успешно отредактирован\n";
                this_thread::sleep_for(chrono::seconds(2));
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
                if (userId >= 0 && userId < count) {
                    for (int i = userId; i < count - 1; ++i) {
                        users[i] = users[i + 1];
                    }
                    --count;
                    saveUsers(users, count);
                    cout << "Пользователь успешно удален\n";
                    this_thread::sleep_for(chrono::seconds(2));
                }
                else {
                    cout << "Пользователь с указанным ID не найден\n";
                }
            }
            else {
                cout << "Вы не можете удалить себя\n";
                this_thread::sleep_for(chrono::seconds(2));
            }
            break;
        case 3:
            break;
        default:
            cout << "Неверный выбор, попробуйте еще раз\n";
        }
    } while (choice != 3);
}
