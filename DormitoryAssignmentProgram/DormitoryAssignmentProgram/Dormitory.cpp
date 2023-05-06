#include "Dormitory.h"
#include "Protection.h"

void dormitoryFunctions() {
    int choice;
    const int Rooms = 100;
    int count = 0;
    Room rooms[Rooms];
    loadRooms(dormitoryFilename, rooms, count);

    do {
        system("cls");
        cout << "\n\tМеню:\n 1. Показать информацию о комнатах\n 2. Добавить новую комнату\n 3. Редактировать комнату\n 4. Удалить комнату\n 5. Поиск комнаты\n 6. Отсортировать комнаты\n 7. Выйти\n  Ваш выбор: ";
        choice = inputInt(1, 7);

        switch (choice) {
        case 1:
            showRooms(rooms, count);
            break;
        case 2:
            createRoom(rooms, count);
            break;
        case 3:
            editRoom(rooms, count);
            break;
        case 4:
            deleteRoom(rooms, count);
            break;
        case 5:
            searchRoom(rooms, count);
            break;
        case 6:
            sortRooms(rooms, count);
            break;
        case 7:
            cout << "Выход\n";
            break;
        default:
            cout << "  Неверный выбор, попробуйте еще раз\n";
        }
    } while (choice != 7);
}

void createRoom(Room rooms[], int& count) {
    Room newRoom;
    cout << "Введите номер комнаты: ";
    newRoom.roomNumber = inputInt(100, 1700);
    cout << "Введите этаж: ";
    newRoom.floor = inputInt(1, 16);
    for (int i = 0; i < 4; ++i) {
        cout << "\nВведите фамилию студента №" << i + 1 << ": ";
        getline(cin, newRoom.occupants[i].surname);
        cout << "Введите имя студента №" << i + 1 << ": ";
        getline(cin, newRoom.occupants[i].name);
        cout << "Введите Факультет студента №" << i + 1 << ": ";
        getline(cin, newRoom.occupants[i].faculty);
        cout << "Введите курс студента №" << i + 1 << ": ";
        newRoom.occupants[i].course = inputInt(1, 4);
    }

    rooms[count++] = newRoom;
    saveRooms(dormitoryFilename, rooms, count);
    cout << "Новая комната успешно добавлена\n";
}

void editRoom(Room room[], int count) {
    int roomNumber;
    cout << "Введите номер комнаты для редактирования: ";
    roomNumber = inputInt(99, 1700);
    for (int i = 0; i < count; ++i) {
        if (room[i].roomNumber == roomNumber) {

            cout << "Введите новый номер комнаты: ";
            cin.ignore();
            room[i].roomNumber = inputInt(100, 1700);
            cout << "Введите новый этаж: ";
            room[i].floor = inputInt(1, 16);
            cin.ignore();
            
            for (int i = 0; i < 5; ++i) {
                cout << "\nВведите имя студента №" << i + 1 << ": ";
                getline(cin, room[i].occupants[i].name);
                cout << "Введите фамилию студента №" << i + 1 << ": ";
                getline(cin, room[i].occupants[i].surname);
                cout << "Введите Факультет студента №" << i + 1 << ": ";
                getline(cin, room[i].occupants[i].faculty);
                cout << "Введите курс студента №" << i + 1 << ": ";
                room[i].occupants[i].course = inputInt(1, 4);
            }

            Sleep(2000);
            saveRooms(dormitoryFilename, room, count);
            cout << "Комната успешно отредактирована\n";
            return;
        }
    }

    cout << "Комната с указанным номером не найдена\n";
}

void deleteRoom(Room rooms[], int& count) {
    int roomNumber;
    cout << "Введите номер комнаты для удаления: ";
    roomNumber = inputInt(99, 1700);
    for (int i = 0; i < count; ++i) {
        if (rooms[i].roomNumber == roomNumber) {
            for (int j = i; j < count - 1; ++j) {
                rooms[j] = rooms[j + 1];
            }
            --count;
            saveRooms(dormitoryFilename, rooms, count);
            cout << "Комната успешно удалена\n";
            return;
        }
    }
    cout << "Комната с указанным номером не найдена\n";
}

void showRooms(const Room rooms[], int count) {
    cout << "\n\t\t\tСписок комнат:\n";
    cout << " _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _\n";
    cout << "| Номер комнаты " << " | " << setw(30) << left << " Этаж " << " | " << setw(15) << " Заселённые студенты                 | \n";
    cout << "| _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _|\n";

    for (int i = 0; i < count; ++i) {
        cout << "| №" << rooms[i].roomNumber << " |     " << setw(30) << left << rooms[i].floor << "|   Имя   |   Фамилия   |    Факультет    | Курс        |\n";
        for (int j = 0; j < 4; ++j) {
            cout << "| Студент №" << setw(30) << j + 1 << ": " << setw(15) << left
                << rooms[i].occupants[j].name << setw(15) << left
                << rooms[i].occupants[j].surname << setw(15) << left
                << rooms[i].occupants[j].faculty << setw(10) << left
                << rooms[i].occupants[j].course << " |\n";
        }
        cout << "|_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ |\n\n";
    }
    system("pause");
}


void searchRoom(const Room rooms[], int count) {
    int roomNumber;
    cout << "Введите номер комнаты для поиска: ";
    roomNumber = inputInt(99, 1700);
    bool found = false;
    for (int i = 0; i < count; ++i) {
        if (rooms[i].roomNumber == roomNumber) {
            found = true;
            cout << "| " << setw(15) << left << "№" << rooms[i].roomNumber << " | " << setw(15) << left << rooms[i].floor << "|\n";
            for (int j = 0; j < 4; ++j) {
                cout << endl
                    << "| Студент №" << j + 1 << ": " << setw(15) << left
                    << rooms[i].occupants[j].name << setw(15) << left
                    << rooms[i].occupants[j].surname << setw(15) << left
                    << rooms[i].occupants[j].faculty << setw(15) << left
                    << rooms[i].occupants[j].course << endl;
            }
        }
    }

    if (!found) {
        cout << "Комната с указанным номером не найдена\n";
    }
    system("pause");
}
void sortRooms(Room rooms[], int count) {
    int choice;
    do {
        system("cls");
        cout << "\n\tМеню сортировок:\n"
            << " 1. Сортировка по номеру комнаты\n"
            << " 2. Сортировка по этажу\n"
            << " 3. Выйти\n  Ваш выбор: ";
        choice = inputInt(1, 3);

        switch (choice) {
        case 1:
            for (int i = 0; i < count - 1; ++i) {
                for (int j = 0; j < count - i - 1; ++j) {
                    if (rooms[j].roomNumber > rooms[j + 1].roomNumber) {
                        Room temp = rooms[j];
                        rooms[j] = rooms[j + 1];
                        rooms[j + 1] = temp;
                    }
                }
            }
            showRooms(rooms, count);
            break;
        case 2:
            for (int i = 0; i < count - 1; ++i) {
                for (int j = 0; j < count - i - 1; ++j) {
                    if (rooms[j].floor > rooms[j + 1].floor) {
                        Room temp = rooms[j];
                        rooms[j] = rooms[j + 1];
                        rooms[j + 1] = temp;
                    }
                }
            }
            showRooms(rooms, count);
            break;
        case 3:
            cout << "Выход\n";
            break;
        default:
            cout << "Неверный выбор, попробуйте еще раз\n";
        }
    } while (choice != 3);

    system("pause");
}

void writeStudent(ofstream& out, const Student& students) {
    out << students.name << endl;
    out << students.surname << endl;
    out << students.faculty << endl;
    out << students.course << endl;
}

void readStudents(ifstream& in, Student& students) {
    getline(in, students.name);
    getline(in, students.surname);
    getline(in, students.faculty);
    in >> students.course;
    in.ignore();
}

void writeRoom(ofstream& out, const Room& room) {
    out << room.roomNumber << endl;
    out << room.floor << endl;
    for (const Student& student : room.occupants) {
        writeStudent(out, student);
    }
}

void readRoom(ifstream& in, Room& room) {
    in >> room.roomNumber;
    in >> room.floor;
    in.ignore();
    for (Student& student : room.occupants) {
        readStudents(in, student);
    }
}

void saveRooms(const string& filename, Room rooms[], int count) {
    ofstream out(filename);
    if (!out.is_open()) {
        cerr << "Не удалось открыть файл для записи: " << filename << endl;
        return;
    }

    out << count << endl;
    for (int i = 0; i < count; ++i) {
        writeRoom(out, rooms[i]);
    }

    out.close();
}

void loadRooms(const string& filename, Room rooms[], int& count) {
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Не удалось открыть файл для чтения: " << filename << endl;
        return;
    }

    in >> count;
    in.ignore();
    for (int i = 0; i < count; ++i) {
        readRoom(in, rooms[i]);
    }

    in.close();
}