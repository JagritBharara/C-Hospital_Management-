#include <iostream>
#include <fstream>
#include <cstring>
#include <string>

using namespace std;

void menu();

class one {
public:
    virtual void get() = 0;
    virtual void show() = 0;
};

// Class to store patient data
class info : public one {
public:
    char name[50], time[50];
    int num, age;

    void get() {
        cout << "\nEnter The Patient Name: ";
        cin >> ws; // Clear any leading whitespace
        cin.getline(name, 50);

        cout << "Enter The Appointment Time: ";
        cin.getline(time, 50);

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Appointment No: ";
        cin >> num;
        cin.ignore(); // Ignore newline left in the buffer
    }

    void show() {
        cout << "\nName: " << name;
        cout << "\nAge: " << age;
        cout << "\nNo: " << num;
        cout << "\nTime: " << time << endl;
    }
};

// Class for Dr. Rana (a doctor)
class rana : public info {
public:
    info a1;

    void get() {
        cout << "[Debug] rana::get() called\n";
        ofstream out("Rana.txt", ios::app | ios::binary);
        a1.get();
        out.write((char*)&a1, sizeof(info));
        out.close();
        cout << "Your Entry Has been saved\n";
        menu();
    }

    void show() {
        cout << "[Debug] rana::show() called\n";
        ifstream in("Rana.txt", ios::binary);
        if (!in) {
            cout << "No Data In the File\n";
            menu();
        } else {
            while (in.read((char*)&a1, sizeof(info))) {
                a1.show();
            }
            in.close();
            menu();
        }
    }

    // Function to delete a patient appointment (by appointment number)
    void deleteAppointment() {
        ifstream in("Rana.txt", ios::binary);
        ofstream out("Temp_Rana.txt", ios::binary);

        if (!in) {
            cout << "No Data In the File\n";
            menu();
        } else {
            int numToDelete;
            cout << "Enter the appointment number to delete: ";
            cin >> numToDelete;

            while (in.read((char*)&a1, sizeof(info))) {
                if (a1.num != numToDelete) {
                    out.write((char*)&a1, sizeof(info));  // Write the appointment to temp file if it's not the one to delete
                }
            }
            in.close();
            out.close();

            // Remove the old file and rename the new file
            remove("Rana.txt");
            rename("Temp_Rana.txt", "Rana.txt");

            cout << "Appointment deleted if found.\n";
            menu();
        }
    }
};

// Class for staff management
class staff : public one {
public:
    char all[999];
    char name[50], age[20], sal[30], pos[20];

    void get() {
        cout << "\nEnter Name: ";
        cin >> ws;
        cin.getline(name, 50);
        cout << "Enter Age: ";
        cin.getline(age, 20);
        cout << "Enter Salary: ";
        cin.getline(sal, 30);
        cout << "Enter Working Position: ";
        cin.getline(pos, 20);

        ofstream out("Staff.txt", ios::app);
        out << "\nName: " << name << "\nAge: " << age << "\nSalary: " << sal << "\nPosition: " << pos << endl;
        out.close();
        cout << "\n\nYour Information has been saved\n";
        menu();
    }

    void show() {
        cout << "[Debug] staff::show() called\n";
        ifstream in("Staff.txt");
        if (!in) {
            cout << "File open error\n";
        } else {
            while (in.getline(all, 999)) {
                cout << all << endl;
            }
            in.close();
            menu();
        }
    }

    // Function to delete staff data by name
    void deleteStaff() {
        ifstream in("Staff.txt");
        ofstream out("Temp_Staff.txt");

        if (!in) {
            cout << "File open error\n";
            menu();
        } else {
            char nameToDelete[50];
            cout << "Enter the staff name to delete: ";
            cin >> ws; // Clear any leading whitespace
            cin.getline(nameToDelete, 50);

            while (in.getline(all, 999)) {
                // Skip writing the line if the name matches the one to delete
                if (strstr(all, nameToDelete) == nullptr) {
                    out << all << endl;
                }
            }

            in.close();
            out.close();

            // Remove the old file and rename the new file
            remove("Staff.txt");
            rename("Temp_Staff.txt", "Staff.txt");

            cout << "Staff data deleted if found.\n";
            menu();
        }
    }
};

void menu() {
    cout << "[Debug] menu() called\n";
    cout << "\nHospital Management System";
    cout << "\n=========================\n";
    cout << "1 - Available Doctor Information\n";
    cout << "2 - Doctor Appointment\n";
    cout << "3 - Save Staff Information\n";
    cout << "4 - Check Patient Appointment\n";
    cout << "5 - Check Staff Information\n";
    cout << "6 - Delete Patient Appointment\n";
    cout << "7 - Delete Staff Information\n";
    cout << "=========================\n";
    cout << "Please Enter Your Choice: ";

    int choice;
    cin >> choice;
    cin.ignore();

    one* ptr;
    rana s3;
    staff a2;

    if (choice == 1) {
        cout << "\nDr. Rana \nTiming: Monday to Friday 9 AM - 5 PM, Saturday 9 AM - 1 PM\n";
        menu();
    } else if (choice == 2) {
        s3.get();
        menu();
    } else if (choice == 3) {
        ptr = &a2;
        ptr->get();
        menu();
    } else if (choice == 4) {
        s3.show();
        menu();
    } else if (choice == 5) {
        ptr = &a2;
        ptr->show();
        menu();
    } else if (choice == 6) {
        s3.deleteAppointment(); // Delete patient appointment
        menu();
    } else if (choice == 7) {
        a2.deleteStaff(); // Delete staff data
        menu();
    } else {
        cout << "Sorry, invalid choice.\n";
        menu();
    }
}

int main() {
    menu();
}
