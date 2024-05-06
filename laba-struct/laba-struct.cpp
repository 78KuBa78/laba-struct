using namespace std;

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

const int max_students = 30;

struct Profile
{
    string fullName;
    char sex;
    int group;
    int id;
    int grades[8];
    double averageGrade;
};

int countStudents()
{
    ifstream database("students.txt");
    if (database.is_open())
    {
        int temp = 0;
        string data;
        while (!database.eof())
        {
            getline(database, data);
            temp++;
        }
        database.close();
        int n;
        n = temp / 6;
        return n;
    }
    else return 0;
}

void createstudents(Profile students) {
    ofstream database;
    database.open("students.txt", ios::app);
    cout << "Создание записи о новом студенте:\n";
    cout << "Введите ФИО студента: \n";
    getline(cin >> ws, students.fullName, '\n');
    database << students.fullName << "\n";
    cout << "Введите пол студента(m/f): \n";
    cin >> students.sex;
    database << students.sex << "\n";
    cout << "Введите номер группы студента: \n";
    cin >> students.group;
    database << students.group << "\n";
    cout << "Введите номер студента в группе: \n";
    cin >> students.id;
    database << students.id << "\n";
    cout << "Введите оценки студента(8): \n";
    double sum = 0;
    for (int i = 0; i < 8; i++) {
        cin >> students.grades[i];
        database << students.grades[i] << " ";
        sum += students.grades[i];
    }
    students.averageGrade = sum / 8.0;
    database << "\n";
    database << students.averageGrade << "\n";
    database.close();
    cout << "Данные о студенте успешно записаны!\n";
}

void modifyStudent(Profile students[]) {
    ifstream database("students.txt");
    int count = 0, mod_id = 0;
    count = countStudents();
    for (int i = 0; i < count; i++) {
        getline(database >> ws, students[i].fullName);
        database >> students[i].sex;
        database >> students[i].group;
        database >> students[i].id;
        for (int j = 0; j < 8; j++) {
            database >> students[i].grades[j];
        }
        database >> students[i].averageGrade;
    }
    database.close();
    ofstream database1("students.txt", ios::trunc);
    cout << "Введите номер студента, данные которого необходимо изменить: ";
    cin >> mod_id;
    cout << "ФИО: ";
    getline(cin >> ws, students[mod_id].fullName, '\n');
    cout << "Пол: ";
    cin >> students[mod_id].sex;
    cout << "Номер группы: ";
    cin >> students[mod_id].group;
    cout << "Номер в списке: ";
    cin >> students[mod_id].id;
    cout << "Оценки за сессию: ";
    for (int i = 0; i < 8; ++i) {
        cin >> students[mod_id].grades[i];
    }
    double sum = 0;
    for (int i = 0; i < 8; ++i) {
        sum += students[mod_id].grades[i];
    }
    students[mod_id].averageGrade = sum / 8.0;
    for (int i = 0; i < count; i++) {
        database1 << students[i].fullName << "\n";
        database1 << students[i].sex << "\n";
        database1 << students[i].group << "\n";
        database1 << students[i].id << "\n";
        for (int j = 0; j < 8; j++) {
            database1 << students[i].grades[j] << " ";
        }
        database1 << "\n";
        database1 << students[i].averageGrade << "\n";
    }
    database1.close();
}

void showData() {
    setlocale(0, "");
    ifstream database("students.txt");
    if (!database.is_open())
        cout << "Ошибка открытия файла!\n";
    else
    {
        int temp = 10, count = 0;
        if (temp == 0)
            cout << "Файл пустой!";
        else
        {
            string data;
            cout << "Список всех студентов:\n";
            while (!database.eof())
            {
                getline(database, data);
                cout << data << '\n';
                count += 1;
                if (count == 6) {
                    count = 0;
                    cout << "---------------------------\n";
                }
            }
        }
        database.close();
    }
}

void showDataGroup(Profile students[]) {
    setlocale(0, "");
    int n;
    cout << "Введите номер группы: ";
    cin >> n;
    ifstream database("students.txt");
    int count = 0;
    count = countStudents();
    for (int i = 0; i < count; i++) {
        getline(database >> ws, students[i].fullName);
        database >> students[i].sex;
        database >> students[i].group;
        database >> students[i].id;
        for (int j = 0; j < 8; j++) {
            database >> students[i].grades[j];
        }
        database >> students[i].averageGrade;
    }
    database.close();
    int temp = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].group == n) {
            cout << "\nФИО студента: " << students[i].fullName << "\n";
            cout << "Пол студента: " << students[i].sex << "\n";
            cout << "Номер студента в группе: " << students[i].id << "\n";
            cout << "Оценки за сессию:";
            for (int j = 0; j < 8; j++)
                cout << students[i].grades[j] << " ";
            temp++;
            cout << "\n\n";
        }
    }
    if (temp == 0) {
        cout << "Нет информации о группе № " << n << "\n";
    }
}

void showTopStudent(Profile students[]) {
    ifstream database("students.txt");
    int count = 0;
    count = countStudents();
    for (int i = 0; i < count; i++) {
        getline(database >> ws, students[i].fullName);
        database >> students[i].sex;
        database >> students[i].group;
        database >> students[i].id;
        for (int j = 0; j < 8; j++) {
            database >> students[i].grades[j];
        }
        database >> students[i].averageGrade;
    }
    database.close();
    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (students[j].averageGrade < students[j + 1].averageGrade) {
                swap(students[j], students[j + 1]);
            }
        }
    }
    cout << "Топ студентов по среднему баллу за сессию: \n";
    for (int i = 0; i < count; ++i) {
        cout << students[i].fullName << ": " << students[i].averageGrade << "\n";
    }
}

void showSex(Profile students[]) {
    ifstream database("students.txt");
    int count = 0;
    count = countStudents();
    for (int i = 0; i < count; i++) {
        getline(database >> ws, students[i].fullName);
        database >> students[i].sex;
        database >> students[i].group;
        database >> students[i].id;
        for (int j = 0; j < 8; j++) {
            database >> students[i].grades[j];
        }
        database >> students[i].averageGrade;
    }
    database.close();
    int maleCount = 0;
    int femaleCount = 0;
    for (int i = 0; i < count; ++i) {
        if (students[i].sex == 'm' || students[i].sex == 'M') {
            maleCount++;
        }
        else if (students[i].sex == 'F' || students[i].sex == 'f') {
            femaleCount++;
        }
    }

    cout << "Количество студентов мужского пола: " << maleCount << endl;
    cout << "Количество студентов женского пола: " << femaleCount << endl;
}

void showStipendia(Profile students[]) {
    ifstream database("students.txt");
    int count = 0;
    count = countStudents();
    for (int i = 0; i < count; i++) {
        getline(database >> ws, students[i].fullName);
        database >> students[i].sex;
        database >> students[i].group;
        database >> students[i].id;
        for (int j = 0; j < 8; j++) {
            database >> students[i].grades[j];
        }
        database >> students[i].averageGrade;
    }
    database.close();

    int array_3[max_students];
    int array_45[max_students];
    int array_5[max_students];
    for (int i = 0; i < count; ++i) {
        bool has_3 = false;
        bool has_4 = false;
        bool has_5 = false;
        for (int j = 0; j < 8; ++j) {
            if (students[i].grades[j] == 3) {
                has_3 = true;
            }
            if (students[i].grades[j] == 4) {
                has_4 = true;
            }
            if (students[i].grades[j] == 5) {
                has_5 = true;
            }
        }
        if (has_3 == true) {
            array_3[i] = 1;
        }
        else if (has_4 == true and has_5 == true) {
            array_45[i] = 1;
        }
        else if (has_4 == false and has_5 == true) {
            array_5[i] = 1;
        }
    }
    cout << "Студенты без стипендии: \n\n";
    for (int i = 0; i < count; ++i) {
        if (array_3[i] == 1) {
            cout << "ФИО: " << students[i].fullName << "\n";
            cout << "Оценки за сессию: ";
            for (int j = 0; j < 8; j++)
                cout << students[i].grades[j] << " ";
            cout << "\n\n";
        }
    }
    cout << "Студенты, которые учатся на 4 и 5: \n\n";
    for (int i = 0; i < count; ++i) {
        if (array_45[i] == 1) {
            cout << "ФИО: " << students[i].fullName << "\n";
            cout << "Оценки за сессию: ";
            for (int j = 0; j < 8; j++)
                cout << students[i].grades[j] << " ";
            cout << "\n\n";
        }
    }
    cout << "Студенты, которые учатся только на 5: \n\n";
    for (int i = 0; i < count; ++i) {
        if (array_5[i] == 1) {
            cout << "ФИО: " << students[i].fullName << "\n";
            cout << "Оценки за сессию: ";
            for (int j = 0; j < 8; j++)
                cout << students[i].grades[j] << " ";
            cout << "\n\n";
        }
    }
}

void findId(Profile students[]) {
    ifstream database("students.txt");
    int count = 0, listNumber = 0;
    count = countStudents();
    for (int i = 0; i < count; i++) {
        getline(database >> ws, students[i].fullName);
        database >> students[i].sex;
        database >> students[i].group;
        database >> students[i].id;
        for (int j = 0; j < 8; j++) {
            database >> students[i].grades[j];
        }
        database >> students[i].averageGrade;
    }
    database.close();
    cout << "Введите номер в списке: ";
    cin >> listNumber;
    bool found = false;
    cout << "Студенты в списке с номером " << listNumber << ":" << endl;
    for (int i = 0; i < count; ++i) {
        if (students[i].id == listNumber) {
            found = true;
            cout << "ФИО: " << students[i].fullName << endl;
            cout << "Пол: " << students[i].sex << endl;
            cout << "Номер группы: " << students[i].group << endl;
            cout << "Оценки за сессию: ";
            for (int j = 0; j < 8; ++j) {
                cout << students[i].grades[j] << " ";
            }
            cout << endl << endl;
        }
    }
    if (!found) {
        cout << "Нет студентов в списке с номером   " << listNumber << "." << endl;
    }
}

struct Applicants {
    string fullName;
    char sex;
    int age;
    string city;
    int ege;
    string diplomOrig;
    double averageGrade;
};

void idz() {
    Applicants applicants[6];
    ifstream database("applicants.txt");
    for (int i = 0; i < 6; i++) {
        getline(database >> ws, applicants[i].fullName);
        database >> applicants[i].sex;
        database >> applicants[i].age;
        getline(database >> ws, applicants[i].city);
        database >> applicants[i].ege;
        getline(database >> ws, applicants[i].diplomOrig);
        database >> applicants[i].averageGrade;
    }
    database.close();
    cout << "Абитуриенты младше 18:\n";
    for (int i = 0; i < 4; ++i) {
        if (applicants[i].age < 18) {
            cout << "\nФИО: " << applicants[i].fullName << endl;
            cout << "Пол: " << applicants[i].sex << endl;
            cout << "Возраст: " << applicants[i].age << endl;
            cout << "Город: " << applicants[i].city << endl;
            cout << "Средний балл ЕГЭ: " << applicants[i].ege << endl;
            cout << "Наличие оригинала аттестата: " << applicants[i].diplomOrig << endl;
            cout << "Средний балл аттестата: " << applicants[i].averageGrade << endl;
            cout << "\n---------------------------------------\n";
        }
    }
    cout << "\nАбитуриенты, чей средний балл егэ выше 85:\n";
    for (int i = 0; i < 4; ++i) {
        if (applicants[i].ege > 85) {
            cout << "\nФИО: " << applicants[i].fullName << endl;
            cout << "Пол: " << applicants[i].sex << endl;
            cout << "Возраст: " << applicants[i].age << endl;
            cout << "Город: " << applicants[i].city << endl;
            cout << "Средний балл ЕГЭ: " << applicants[i].ege << endl;
            cout << "Наличие оригинала аттестата: " << applicants[i].diplomOrig << endl;
            cout << "Средний балл аттестата: " << applicants[i].averageGrade << endl;
            cout << "\n---------------------------------------\n";
        }
    }
    cout << "\nИногородние абитуриенты:\n";
    for (int i = 0; i < 4; ++i) {
        if (applicants[i].city != "SPB") {
            cout << "\nФИО: " << applicants[i].fullName << endl;
            cout << "Пол: " << applicants[i].sex << endl;
            cout << "Возраст: " << applicants[i].age << endl;
            cout << "Город: " << applicants[i].city << endl;
            cout << "Средний балл ЕГЭ: " << applicants[i].ege << endl;
            cout << "Наличие оригинала аттестата: " << applicants[i].diplomOrig << endl;
            cout << "Средний балл аттестата: " << applicants[i].averageGrade << endl;
            cout << "\n---------------------------------------\n";
        }
    }
    cout << "\nАбитуриенты с аттестатом с отличием:\n";
    for (int i = 0; i < 4; ++i) {
        if (applicants[i].averageGrade == 5.0) {
            cout << "\nФИО: " << applicants[i].fullName << endl;
            cout << "Пол: " << applicants[i].sex << endl;
            cout << "Возраст: " << applicants[i].age << endl;
            cout << "Город: " << applicants[i].city << endl;
            cout << "Средний балл ЕГЭ: " << applicants[i].ege << endl;
            cout << "Наличие оригинала аттестата: " << applicants[i].diplomOrig << endl;
            cout << "Средний балл аттестата: " << applicants[i].averageGrade << endl;
            cout << "\n---------------------------------------\n";
        }
    }
}

void menu() {
    setlocale(0, "");
    int numStudents = 0, x;
    Profile students[max_students];
    cout << "Какой пункт вы хотите запустить?:\n"
        << "1 - Создание новой записи о студенте\n"
        << "2 - Внесение изменений в уже имеющуюся запись\n"
        << "3 - Вывод всех данных о студентах\n"
        << "4 - Вывод информации обо всех студентах группы N\n"
        << "5 - Вывод топа самых успешных студентов\n"
        << "6 - Вывод количества студентов мужского и женского пола\n"
        << "7 - Вывод данных об успеваемости и стипендии студентов\n"
        << "8 - Вывод данных о студентах, имеющих номер в списке – k\n"
        << "9 - ИДЗ\n"
        << "0 - Выход\n\n";
    cin >> x;
    switch (x)
    {
    case 1:
        system("cls");
        createstudents(students[numStudents]);
        system("Pause");
        system("cls");
        menu();
        break;
    case 2:
        system("cls");
        modifyStudent(students);
        system("Pause");
        system("cls");
        menu();
        break;
    case 3:
        system("cls");
        showData();
        system("Pause");
        system("cls");
        menu();
        break;
    case 4:
        system("cls");
        showDataGroup(students);
        system("Pause");
        system("cls");
        menu();
        break;
    case 5:
        system("cls");
        showTopStudent(students);
        system("Pause");
        system("cls");
        menu();
        break;
    case 6:
        system("cls");
        showSex(students);
        system("Pause");
        system("cls");
        menu();
        break;
    case 7:
        system("cls");
        showStipendia(students);
        system("Pause");
        system("cls");
        menu();
        break;
    case 8:
        system("cls");
        findId(students);
        system("Pause");
        system("cls");
        menu();
        break;
    case 9:
        system("cls");
        idz();
        system("Pause");
        system("cls");
        menu();
        break;
    case 0:
        exit(1);
    default:
        cout << "Ошибка!\n";
        system("Pause");
        system("cls");
        menu();
        break;
    }
}

int main() {
    menu();
}
