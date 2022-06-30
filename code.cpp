#include <iostream>
#include <cstring>
#include <string>
#include <windows.h>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

template <class T>
void Disp(T t, int width)
{
    cout << left << setw(width) << setfill(' ') << t;
}

template <class t>
void copy(t a, t b)
{
    for (int i = 0; i < 3; ++i)
    {
        a[i] = b[i];
    }
}

template <class T>
void initial(T a)
{
    for (int i = 0; i < 3; ++i)
        a[i] = -1;
}

void delaydisp(string s, int t = 50)
{
    system("cls");
    cout << "\n"
         << s;
    for (int i = 0; i < 10; ++i)
    {
        cout << ".";
        Sleep(t);
    }
    cout << endl;
}
class METHODS
{
protected:
    int correct_ans[3], wrong_ans[3];
    float speed[3], percentage[3];
    int choice;

public:
    METHODS();
    void showpara();
    void shownum();
    void showrand();
    void accuracy(fstream &, fstream &);
    void typespeed(fstream &, fstream &);
};
METHODS::METHODS()
{
    choice = -1;
    initial(correct_ans);
    initial(wrong_ans);
    initial(speed);
    initial(percentage);
}
void METHODS::showpara()
{
    fstream f;
    f.open("para.txt", ios::in);
    if (!f)
    {
        cout << "\nFile doesnot exist.";
        return;
    }
    else
    {
        delaydisp("\nEnter the following text. Hit enter when you are done", 200);
        while (!f.eof())
        {
            string line;
            getline(f, line);
            cout << line;
        }
    }
    cout << "\n\nType below:\n";
    fstream test;
    test.open("test.txt", ios::out | ios::in);
    typespeed(test, f);
    f.close();
    test.close();
    delaydisp("Returning to main menu");
}
void METHODS::shownum()
{
    fstream f;
    f.open("num.txt", ios::in);
    if (!f)
    {
        cout << "\nFile doesnot exist.";
        return;
    }
    else
    {
        delaydisp("\nEnter the following text. Hit enter when you are done", 200);
        while (!f.eof())
        {
            string line;
            getline(f, line);
            cout << line;
        }
    }
    cout << "\n\nType below:\n";
    fstream test;
    test.open("test.txt", ios::out | ios::in);
    typespeed(test, f);
    test.close();
    f.close();
    delaydisp("Returning to main menu");
}
void METHODS::showrand()
{
    fstream f;
    f.open("rand.txt", ios::out | ios::in);
    if (!f)
    {
        cout << "\nFile doesnot exist.";
        return;
    }
    else
    {
        delaydisp("\nEnter the following text. Hit enter when you are done", 200);
        while (!f.eof())
        {
            string line;
            getline(f, line);
            cout << line;
        }
    }
    cout << "\n\nType below:\n";
    fstream test;
    test.open("test.txt", ios::out);
    typespeed(test, f);
    test.close();
    f.close();
    delaydisp("Returning to main menu");
}

void METHODS::accuracy(fstream &typed, fstream &actual)
{
    cout << endl;
    typed.seekg(0, ios::beg);
    actual.seekg(0, ios::beg);
    correct_ans[choice] = wrong_ans[choice] = 0;
    string t, a;
    while (!typed.eof() && !actual.eof())
    {
        typed >> t;
        actual >> a;
        if (t == a)
            correct_ans[choice]++;
        else
            wrong_ans[choice]++;
    }
    percentage[choice] = (correct_ans[choice] * 100) / (correct_ans[choice] + wrong_ans[choice]);
}

void METHODS::typespeed(fstream &typed, fstream &actual)
{
    cout << endl;
    string lines;
    fflush(stdin);
    high_resolution_clock::time_point start = high_resolution_clock::now();
    getline(cin, lines, '\n');
    typed << lines;
    high_resolution_clock::time_point end = high_resolution_clock::now();
    duration<double> total = duration_cast<duration<double>>(end - start);
    accuracy(typed, actual);
    speed[choice] = ((correct_ans[choice] + wrong_ans[choice]) / total.count()) * 60;
}

class USER : public METHODS
{
private:
    int age, flag;
    char name[30], year[10];

public:
    USER();
    void showuserdata();
    void showdetailed();
    void getuserdata();
    void search(char[]);
    void insertdata();
};
USER::USER() : flag(0){};
void USER::getuserdata()
{
    cout << "\nEnter your name: ";
    fflush(stdin);
    gets(name);
    search(name);
    if (flag == 1)
    {
        cout << "\nYour data already exists in our database.";
        cout << "\nDo you want to practice<p> or see your stats<s>?: ";
        char c;
        cin >> c;
        if (toupper(c) == 'S')
        {
            showdetailed();
            delaydisp("Returning to main menu");
            return;
        }
        goto here;
    }
    fflush(stdin);
    cout << "\nYour age: ";
    cin >> age;
    cout << "\nCurrent year in college: ";
    cin >> year;
here:
    cout << "\nWhich type of test do you want to give?\n "
         << endl
         << "1) PARAGRAPH TEST\n"
         << endl
         << "2) NUMERIC TEST\n"
         << endl
         << "3) RANDOM TEST\n"
         << endl;
    cin >> choice;
    choice--;
    switch (choice)
    {
    case 0:
        cout << "PARAGRAGH TEST.\n";
        showpara();
        insertdata();
        break;
    case 1:
        cout << "\nNUMERIC TEST.\n";
        shownum();
        insertdata();
        break;
    case 2:
        cout << "\nRANDOM TEST.\n";
        showrand();
        insertdata();
        break;
    default:
        cout << "\nInvalid choice.";
    }
}

void USER::showdetailed()
{
    delaydisp("Fetching data");
    cout << "\nName: " << name << endl
         << "Age: " << age << endl
         << "Year: " << year << endl;
    cout << "\nPARAGRAPH\n";
    cout << "Accuracy: " << percentage[0] << endl
         << "WPM: " << speed[0] << endl;
    cout << "\nNUMBERS\n";
    cout << "Accuracy: " << percentage[1] << endl
         << "WPM: " << speed[1] << endl;
    cout << "\nRANDOM\n";
    cout << "Accuracy: " << percentage[2] << endl
         << "WPM: " << speed[2] << endl;
}

void USER::search(char n[])
{
    fstream f;
    f.open("basics.txt", ios::in);
    if (!f)
    {
        cout << "\nerror.";
    }
    else
    {
        USER temp;
        while (f.read((char *)&temp, sizeof(USER)))
        {
            if (!strcmp(n, temp.name))
            {
                flag = 1;
                choice = temp.choice;
                strcpy(year, temp.year);
                age = temp.age;
                copy(correct_ans, temp.correct_ans);
                copy(wrong_ans, temp.wrong_ans);
                copy(speed, temp.speed);
                copy(percentage, temp.percentage);
                break;
            }
        }
    }
    f.close();
}

void USER::showuserdata()
{

    Disp(name, 20);
    Disp(age, 5);
    Disp(year, 10);
    for (int i = 0; i < 3; ++i)
        Disp(percentage[i], 20);
}

void USER::insertdata()
{
    fstream f;
    f.open("basics.txt", ios::in | ios::app);
    if (!f)
    {
        cout << "\nerror";
        return;
    }

    USER temp;
    if (flag == 1)
    {
        fstream t;
        t.open("temp.txt", ios::out);
        while (f.read((char *)&temp, sizeof(USER)))
        {
            int done = 0;
            if (!strcmp(name, temp.name))
            {
                if (correct_ans[choice] > temp.correct_ans[choice])
                {
                    t.write((char *)this, sizeof(USER));
                    done = 1;
                }
            }
            if (done == 0)
                t.write((char *)&temp, sizeof(USER));
        }
        f.close();
        t.close();
        remove("basics.txt");
        rename("temp.txt", "basics.txt");
    }
    else
    {
        f.write((char *)this, sizeof(USER));
        f.close();
    }
}

void showall()
{
    delaydisp("Processing");
    ifstream f;
    f.open("basics.txt");
    if (!f)
    {
        cout << "\nSome error occured while accessing the file.";
        delaydisp("Returning to main menu");
        return;
    }
    int length;
    f.seekg(0, ios::end);
    length = f.tellg();
    if (length)
    {
        f.seekg(0, ios::beg);
        USER u;
        Disp("NAME", 20);
        Disp("AGE", 5);
        Disp("YEAR", 10);
        Disp("PARAGRAPH ACCURACY", 20);
        Disp("NUMBER ACCURACY", 20);
        Disp("RANDOM ACCURACY", 20);
        vector<USER> saved;
        while (f.read((char *)&u, sizeof(USER)))
        {
            cout << "\n\n";
            saved.push_back(u);
            u.showuserdata();
        }
        cout << "\n\nEnter the serial for his/her detailed result, otherwise type -1: ";
        int choice;
        cin >> choice;
        if (choice != -1)
            saved[choice - 1].showdetailed();
    }
    else
    {
        cout << "\nNo records to display.\n";
    }
    f.close();
}

void deleteall()
{
    cout << "\nAre you sure you want to DELETE all the data? Yes(y)/No(n): ";
    char choice;
    cin >> choice;
    if (toupper(choice) == 'Y')
    {
        if (!remove("basics.txt"))
            cout << "\nFile deleted successfully.";
        else
            cout << "\nFile already deleted.";
            fstream f;
    f.open("basics.txt", ios::out);
    f.close(); ////////////////
    }
    
}

int main()
{
    for (int i = 0; i < 70; ++i)
    {
        cout << "_";
        Sleep(10);
    }
    cout << endl
         << endl;
    string title = "MY TYPING STATS ...... by ABHAY";
    for (int i = 0; i < title.length(); ++i)
    {
        cout << title[i];
        Sleep(20);
    }
    cout << endl;
    for (int i = 0; i < 70; ++i)
    {
        cout << "_";
        Sleep(10);
    }
    char choice;
    while (1)
    {
        USER u;
        cout << "\n\nWelcome...\n"
             << endl
             << "1) SHOW ALL USERS STATS\n"
             << endl
             << "2) NEW USER\n"
             << endl
             << "3) DELETE ALL FILES AND DATA.\n"
             << endl
             << "4) QUIT\n"
             << endl
             << "Enter your choice: ";
        cin >> choice;
        system("cls");
        switch (choice)
        {
        case '1':
            cout << "\nALL DATA\n\n";
            showall();
            break;
        case '2':
            cout << "\nUSER DATA\n\n";
            u.getuserdata();
            break;

        case '3':
            cout << "\nDELETE ALL DATA\n\n";
            deleteall();
            break;
        case '4':
            cout << "THANK YOU !!!";
            return 0;
        default:
            cout << "PLEASE ENTER A VALID INPUT !!!\n";
        }
    }
    return 0;
}