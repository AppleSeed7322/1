#include <iostream>
#include <limits>
using namespace std;

class CircularQueue {
private:
    int* arr;
    int front, rear, count, SIZE;

public:
    CircularQueue(int size) {
        SIZE = size;
        arr = new int[SIZE];
        front = rear = -1;
        count = 0;
    }

    ~CircularQueue() { delete[] arr; }

    bool isFull() { return count == SIZE; }
    bool isEmpty() { return count == 0; }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is FULL! Cannot insert " << value << endl;
            return;
        }
        if (front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        arr[rear] = value;
        count++;
        cout << "Inserted: " << value << endl;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue is EMPTY! Cannot delete.\n";
            return;
        }
        cout << "Deleted: " << arr[front] << endl;
        front = (front + 1) % SIZE;
        count--;
        if (count == 0) front = rear = -1;
    }

    void display() {
        if (isEmpty()) {
            cout << "Queue is EMPTY!\n";
            return;
        }
        cout << "Queue elements: ";
        for (int i = 0; i < count; i++)
            cout << arr[(front + i) % SIZE] << " ";
        cout << endl;
    }
};

int inputInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) break;
        else {
            cout << "Invalid input! Enter an integer.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    return value;
}

int main() {
    int size = inputInt("Enter size of the Circular Queue: ");
    CircularQueue q(size);

    int choice;
    do {
        cout << "\n--- Circular Queue Menu ---\n";
        cout << "1. Enqueue (Insert)\n";
        cout << "2. Dequeue (Delete)\n";
        cout << "3. Display\n";
        cout << "4. Exit\n";
        choice = inputInt("Enter your choice: ");

        switch (choice) {
        case 1: {
            int value = inputInt("Enter value to insert: ");
            q.enqueue(value);
            break;
        }
        case 2:
            q.dequeue();
            break;
        case 3:
            q.display();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
