#include <iostream>
#include <cstring>
#include <cstdlib>
#include <chrono>
using namespace std;
using namespace std::chrono;

struct Student {
    int rollNo;
    char name[30];
    float CGPA;
};

Student* students = nullptr;
int count = 0;

void addStudent() {
    int n;
    cout << "How many students do you want to add? ";
    cin >> n;

    students = (Student*)realloc(students, (count + n) * sizeof(Student));
    if (!students) {
        cout << "Memory allocation failed.\n";
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        cout << "\nEnter details for Student " << (count + 1) << ":\n";
        cout << "Roll No: "; cin >> students[count].rollNo;
        cout << "Name: "; cin >> students[count].name;
        cout << "CGPA: "; cin >> students[count].CGPA;
        count++;
    }
}

void displayStudents() {
    if (count == 0) {
        cout << "No student records available.\n";
        return;
    }

    cout << "\nRoll No\tName\t\tCGPA\n";
    for (int i = 0; i < count; i++) {
        cout << students[i].rollNo << "\t" << students[i].name << "\t\t" << students[i].CGPA << endl;
    }
}

void sortByName() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(students[j].name, students[j + 1].name) > 0) {
                swap(students[j], students[j + 1]);
            }
        }
    }
    cout << "Sorted by Name.\n";
}

void sortByCGPA(bool ascending = true) {
    for (int i = 0; i < count - 1; i++) {
        int idx = i;
        for (int j = i + 1; j < count; j++) {
            if ((ascending && students[j].CGPA < students[idx].CGPA) ||
                (!ascending && students[j].CGPA > students[idx].CGPA)) {
                idx = j;
            }
        }
        swap(students[i], students[idx]);
    }
    cout << "Sorted by CGPA (" << (ascending ? "Ascending" : "Descending") << ").\n";
}

void sortByRollNo() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].rollNo > students[j + 1].rollNo) {
                swap(students[j], students[j + 1]);
            }
        }
    }
}

void linearSearch(int key) {
    auto start = high_resolution_clock::now();
    for (int i = 0; i < count; i++) {
        if (students[i].rollNo == key) {
            auto end = high_resolution_clock::now();
            cout << "Student Found: " << students[i].name << ", CGPA: " << students[i].CGPA << endl;
            cout << "Linear Search Time: "
                 << duration_cast<nanoseconds>(end - start).count() << " ns\n";
            return;
        }
    }
    auto end = high_resolution_clock::now();
    cout << "Student not found (Linear Search).\n";
    cout << "Linear Search Time: "
         << duration_cast<nanoseconds>(end - start).count() << " ns\n";
}

void binarySearch(int key) {
    sortByRollNo();
    int low = 0, high = count - 1;

    auto start = high_resolution_clock::now();
    while (low <= high) {
        int mid = (low + high) / 2;
        if (students[mid].rollNo == key) {
            auto end = high_resolution_clock::now();
            cout << "Student Found: " << students[mid].name << ", CGPA: " << students[mid].CGPA << endl;
            cout << "Binary Search Time: "
                 << duration_cast<nanoseconds>(end - start).count() << " ns\n";
            return;
        } else if (key < students[mid].rollNo) high = mid - 1;
        else low = mid + 1;
    }
    auto end = high_resolution_clock::now();
    cout << "Student not found (Binary Search).\n";
    cout << "Binary Search Time: "
         << duration_cast<nanoseconds>(end - start).count() << " ns\n";
}

int main() {
    int choice;
    do {
        cout << "\n========== STUDENT DATABASE MENU ==========\n";
        cout << "1. Add Student(s)\n2. Display Students\n3. Sort by Name\n";
        cout << "4. Sort by CGPA (Ascending)\n5. Sort by CGPA (Descending)\n";
        cout << "6. Linear Search by Roll No\n7. Binary Search by Roll No\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: sortByName(); displayStudents(); break;
            case 4: sortByCGPA(true); displayStudents(); break;
            case 5: sortByCGPA(false); displayStudents(); break;
            case 6: {
                int key; cout << "Enter Roll No (Linear): "; cin >> key;
                linearSearch(key); break;
            }
            case 7: {
                int key; cout << "Enter Roll No (Binary): "; cin >> key;
                binarySearch(key); break;
            }
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);
    free(students);
    return 0;
}
