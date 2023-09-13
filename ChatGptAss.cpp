/*Assignment: Student Record Management using Linked Lists
Objective:
Create a simple Student Record Management System that allows you to add, delete, and display student records using singly linked lists. 
Additionally, save the student records to a file and load them when the program starts.

Data Structure: Use a singly linked list to store student records. Each node should contain the following fields:

Add a new student record.
Delete a student record by Student ID.
Display all student records.
Save records to a file.
Load records from a file.
File I/O: Use file input/output operations to save and load student records.

When the program starts, it should load student records from a file (if it exists).
Whenever a new record is added or deleted, the file should be updated accordingly.
*/


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

struct Student
{
    int studentID;
    string name;
    float gpa;
};
struct Node
{
    Student data;
    Node *next;
};

// func declare
void addStudent(Node *&head, int id, const string &name, float gpa);
void deleteStudent(Node *&head, int id);
void displayStudents(const Node *head);
void saveToFile(const Node *head, const string &filename, int lastUsedID);
void loadFromFile(Node *&head, const string &filename, int &lastUsedID);

int main()
{
    Node *head = nullptr;
    char end = 'i';
    int choice = 0;
    int lastUsedID = 0;
    int id;
    string name;
    string fileName = "students.txt";
    // string fileType = ".txt";
    loadFromFile(head, fileName, lastUsedID);
    cout << "Last used ID after loading: " << lastUsedID << endl;

    while (end != 'q' && end != 'Q')
    {
        cout << "Menu:" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Delete Student" << endl;
        cout << "3. Display Students" << endl;
        cout << "4. Save Students to file" << endl;
        cout << "Enter your choice (1/2/3/4): ";
        cin >> choice;
        cin.ignore(); // Clear the input buffer

        switch (choice)
        {
        case 1:
        {
            int newID = lastUsedID + 1; // Generate new unique ID
            lastUsedID = newID;         // Update last used ID
            cout << "Enter student's name: ";
            getline(cin, name);
            cout << "Enter student's GPA: ";
            float gpa = 0;
            cin >> gpa;
            addStudent(head, newID, name, gpa);
            break;
        }
        case 2:
        {
            if (head == nullptr)
            {
                cout << "No student in the system" << endl;
                break;
            }
            cout << "Enter student ID to delete: ";
            cin >> id;
            deleteStudent(head, id);
            break;
        }
        case 3:
        {
            displayStudents(head);
            break;
        }
        case 4:
        {
            // cout << "enter file name";
            // cin >> fileName;
            // fileName += fileType;
            saveToFile(head, fileName, lastUsedID);
            cout << "File saved as students.txt" << endl
                 << endl;
            break;
        }
        }
        cout << "Quit? (q/Q): ";
        cin >> end;
    }
    return 0;
}

void addStudent(Node *&head, int id, const string &name, float gpa)
{
    Node *newNode = new Node;
    newNode->data.studentID = id;
    newNode->data.name = name;
    newNode->data.gpa = gpa;
    newNode->next = head;
    head = newNode;
}

void deleteStudent(Node *&head, int id)
{
    Node *prev = head;

    if (head->data.studentID == id)
    {
        head = head->next;
        delete prev;
        return;
    }
    Node *current = head;
    while (current != nullptr)
    {
        if (current->data.studentID == id)
        {
            prev->next = current->next;
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void displayStudents(const Node *head)
{
    cout << "Student ID|    Name|    GPA" << endl;
    const Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->data.studentID << ",   ";
        cout << temp->data.name << ",   ";
        // cout << temp->data.gpa << "   ";
        cout << fixed << setprecision(2) << temp->data.gpa << " ";
        cout << endl; // Move to the next line for the next student
        temp = temp->next;
    }
}
void saveToFile(const Node *head, const string &filename, int lastUsedID)
{
    const Node *temp = head;
    ofstream stuFile;
    stuFile.open(filename);
    if (!stuFile.is_open())
    {
        cerr << "Failed to open the file.";
        return;
    }
    stuFile << "LastUsedID: " << lastUsedID << endl; // Add this line
    stuFile << "Student ID|    Name|    GPA" << endl;

    while (temp != nullptr)
    {
        stuFile << temp->data.studentID << "|   ";
        stuFile << temp->data.name << "|   ";
        stuFile << fixed << setprecision(2) << temp->data.gpa << " ";
        stuFile << endl; // Move to the next line for the next student
        temp = temp->next;
    }
    stuFile.close();
}
void loadFromFile(Node *&head, const string &filename, int &lastUsedID)
{
    ifstream stuFile(filename);
    if (!stuFile.is_open())
    {
        cerr << "Failed to open the file.";
        return;
    }

    string line, name;
    int id;
    float gpa;
    int maxID = 0; // Variable to hold the maximum Student ID

    // Read the LastUsedID line from the file.
    getline(stuFile, line);
    sscanf(line.c_str(), "LastUsedID: %d", &lastUsedID);

    // Skip the header line ("Student ID| Name| GPA").
    getline(stuFile, line);

    while (stuFile >> id)
    {
        stuFile.ignore(3);           // Skip the "|  " characters after the ID
        getline(stuFile, name, '|'); // Read until the next '|'
        stuFile >> gpa;
        stuFile.ignore(2); // Skip the "  " or "\n" at the end of the line

        // Remove trailing spaces from the name
        name.erase(name.find_last_not_of(" ") + 1);

        // Add the student to the linked list
        addStudent(head, id, name, gpa);

        // Update maxID if the current ID is greater than maxID
        if (id > maxID)
        {
            maxID = id;
        }
    }
    stuFile.close();

    // Set lastUsedID to maxID
    lastUsedID = maxID;

    cout << "Last used ID after loading: " << lastUsedID << endl; // Debugging print
}
