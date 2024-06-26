#include <iostream>
#include <string>

using namespace std;

bool login() {
    string validUsername = "admin";
    string validPassword = "password123";

    string username, password;

    cout << "\tEnter Username: ";
    cin >> username;
    cout << "\tEnter Password: ";
    cin >> password;

    if (username == validUsername && password == validPassword) {
        cout << "\tLogin Successful!" << endl;
        return true;
    } else {
        cout << "\tInvalid username or password!" << endl;
        return false;
    }
}

int main() {
    if (!login()) {
        cout << "\tAccess Denied!" << endl;
        return 0;
    }



    return 0;
}
