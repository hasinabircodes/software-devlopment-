
#include <iostream>
#include <fstream>
#include <unordered_map>

#include <vector>
#include <algorithm>

using namespace std;

class University {
private:
    string RollNo, Name, Subject, Address;

public:
    University() : RollNo(""), Name(""), Subject(""), Address("") {}

    void setRollNo(string rollNo) { RollNo = rollNo; }
    void setName(string name) { Name = name; }
    void setSubject(string subject) { Subject = subject; }
    void setAddress(string address) { Address = address; }
    string getRollNo() { return RollNo; }
    string getName() { return Name; }
    string getSubject() { return Subject; }
    string getAddress() { return Address; }
};

unordered_map<string, string> readUserData(const string& filename) {
    unordered_map<string, string> um;
    fstream infile(filename, ios::in);
    string username, password;
    if (infile.is_open()) {
        while (infile >> username >> password) {
            um[username] = password;
        }
        infile.close();
    } else {
        cout << "Error opening file for reading!" << endl;
    }
    return um;
}

void writeUserData(const string& filename, const unordered_map<string, string>& um) {
    fstream outfile(filename, ios::out);
    if (outfile.is_open()) {
        for (const auto& pair : um) {
            outfile << pair.first << " " << pair.second << "\n";
        }
        outfile.close();
    } else {
        cout << "Error opening file for writing!" << endl;
    }
}

void pause() {
    cout << "\tPress any key to continue..." << endl;
    cin.ignore();
    cin.get();
}

void add(University &student) {
    string rollNo, name, subject, address;

    cout << "\tEnter RollNo Of Student: ";
    cin >> rollNo;
    student.setRollNo(rollNo);

    cout << "\tEnter Name Of Student: ";
    cin >> name;
    student.setName(name);

    cout << "\tEnter Subject Of Student: ";
    cin >> subject;
    student.setSubject(subject);

    cout << "\tEnter Address Of Student: ";
    cin >> address;
    student.setAddress(address);

    ofstream out("university.txt", ios::app);
    if (!out) {
        cout << "\tError: File Can't Open!" << endl;
    } else {
        out << student.getRollNo() << " : " << student.getName() << " : " << student.getSubject()
            << " : " << student.getAddress() << endl;
    }
    out.close();
    cout << "\tStudent Added Successfully!" << endl;
    pause();
}

void search() {
    string rollNo;
    cout << "\tEnter RollNo Of Student: ";
    cin >> rollNo;

    ifstream in("university.txt");
    if (!in) {
        cout << "\tError: File Can't Open!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(in, line)) {
        if (line.find(rollNo) != string::npos) {
            cout << "\t" << line << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "\tStudent Not Found!" << endl;
    }
    in.close();
    pause();
}

void update(University &student) {
    string rollNo;
    cout << "\tEnter RollNo Of Student: ";
    cin >> rollNo;

    ifstream infile("university.txt");
    ofstream outfile("university_temp.txt");
    if (!infile || !outfile) {
        cout << "\tError: File Can't Open!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(infile, line)) {
        if (line.find(rollNo) != string::npos) {
            cout << "\t" << line << endl;
            cout << "\tEnter New Address: ";
            string address;
            cin >> address;
            student.setAddress(address);

            int pos = line.find_last_of(':');
            line = line.substr(0, pos + 2) + student.getAddress();
            found = true;
        }
        outfile << line << endl;
    }
    if (!found) {
        cout << "\tStudent Not Found!" << endl;
    }
    infile.close();
    outfile.close();

    remove("university.txt");
    rename("university_temp.txt", "university.txt");
    if (found) {
        cout << "\tData Updated!" << endl;
    }
    pause();
}

void deleteStudent() {
    string rollNo;
    cout << "\tEnter RollNo Of Student to Delete: ";
    cin >> rollNo;

    ifstream infile("university.txt");
    ofstream outfile("university_temp.txt");
    if (!infile || !outfile) {
        cout << "\tError: File Can't Open!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(infile, line)) {
        if (line.find(rollNo) == string::npos) {
            outfile << line << endl;
        } else {
            found = true;
        }
    }
    infile.close();
    outfile.close();

    remove("university.txt");
    rename("university_temp.txt", "university.txt");

    if (found) {
        cout << "\tStudent Record Deleted!" << endl;
    } else {
        cout << "\tStudent Not Found!" << endl;
    }
    pause();
}

void listAllStudents() {
    ifstream infile("university.txt");
    if (!infile) {
        cout << "\tError: File Can't Open!" << endl;
        return;
    }

    string line;
    cout << "\tListing All Students:" << endl;
    while (getline(infile, line)) {
        cout << "\t" << line << endl;
    }
    infile.close();
    pause();
}

void sortStudentsByName() {
    ifstream infile("university.txt");
    if (!infile) {
        cout << "\tError: File Can't Open!" << endl;
        return;
    }

    vector<string> students;
    string line;
    while (getline(infile, line)) {
        students.push_back(line);
    }
    infile.close();

    sort(students.begin(), students.end(), [](const string &a, const string &b) {
        size_t posA = a.find(" : ");
        size_t posB = b.find(" : ");
        string nameA = a.substr(posA + 3, a.find(" : ", posA + 3) - (posA + 3));
        string nameB = b.substr(posB + 3, b.find(" : ", posB + 3) - (posB + 3));
        return nameA < nameB;
    });

    cout << "\tStudents Sorted by Name:" << endl;
    for (const string &student : students) {
        cout << "\t" << student << endl;
    }
    pause();
}

int main() {
    string filename = "userdata.txt";
    unordered_map<string, string> um = readUserData(filename);

    int attempt_count = 0;
    bool is_logged_in = false;

    while (!is_logged_in) {
        if (attempt_count >= 5) {
            cout << "You have tried 5 times and you cannot try anymore.\n";
            return 0;
        }

        cout << "1. Login\n2. Register\n3. Exit\nEnter option: ";
        string option;
        cin >> option;

        if (option == "1") {
            cout << "Enter username: ";
            string username;
            cin >> username;

            if (um.find(username) == um.end()) {
                cout << "Invalid username\n";
                attempt_count++;
                if (attempt_count >= 3 && attempt_count < 5) {
                    cout << "Attempt " << attempt_count << " failed. " << 5 - attempt_count << " attempt(s) left.\n";
                }
                continue;
            }

            cout << "Enter password: ";
            string password;
            cin >> password;

            if (um[username] == password) {
                cout << "Login successful\n";
                is_logged_in = true;
            } else {
                cout << "Invalid password\n";
                attempt_count++;
                if (attempt_count >= 3 && attempt_count < 5) {
                    cout << "Attempt " << attempt_count << " failed. " << 5 - attempt_count << " attempt(s) left.\n";
                }
            }
        } else if (option == "2") {
            cout << "Enter new username: ";
            string username;
            cin >> username;
            cout << "Enter new password: ";
            string password;
            cin >> password;

            if (um.find(username) == um.end()) {
                um[username] = password;
                writeUserData(filename, um);
                cout << "Registration successful\n";
            } else {
                cout << "Username already exists\n";
            }
        } else if (option == "3") {
            cout << "Exiting\n";
            return 0;
        } else {
            cout << "Invalid option, please try again\n";
        }
    }

    University student;
    bool exit = false;
    while (!exit) {
        system("cls");
        int val;
        cout << "\tWelcome To University Management System" << endl;
        cout << "\t*" << endl;
        cout << "\t1. Add Student." << endl;
        cout << "\t2. Search Student." << endl;
        cout << "\t3. Update Data Of Student." << endl;
        cout << "\t4. Delete Student Record." << endl;
        cout << "\t5. List All Students." << endl;
        cout << "\t6. Sort Students By Name." << endl;
        cout << "\t7. Exit." << endl;
        cout << "\tEnter Your Choice: ";
        cin >> val;

        switch (val) {
            case 1:
                system("cls");
                add(student);
                break;
            case 2:
                system("cls");
                search();
                break;
            case 3:
                system("cls");
                update(student);
                break;
            case 4:
                system("cls");
                deleteStudent();
                break;
            case 5:
                system("cls");
                listAllStudents();
                break;
            case 6:
                system("cls");
                sortStudentsByName();
                break;
            case 7:
                system("cls");
                exit = true;
                cout << "\tGood Luck!" << endl;
                pause();
                break;
            default:
                cout << "\tInvalid Choice!" << endl;
                pause();
        }
    }
    return 0;
}
