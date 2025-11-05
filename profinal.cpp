#include <iostream>
#include <fstream>
using namespace std;

class hotel {
    struct node {
        int id;
        int date;
        string name, typeofroom;
        node* next;
    };

public:
    node* head = NULL;
    void input();
    void option();
    void update();
    void search();
    void remove();
    void record();
    void sort();
    void saveToFile();  //save records file
    void loadFromFile(); // load records from a file
};

void hotel::option() {
    int ch;
    // add yellow colour
    cout << "\n\n";
    cout << "\033[1;33m\t\t      WELCOME ";
    cout << "\n\t\t\t TO";
    cout << "\n\t\t   ROYAL RESORT \n";
    cout << "\033[0m"; //for discontinue colour

    cout << "\n\n MENU:";
    cout << "\n";
    cout << "1)\t Allot the room ";
    cout << "\n2)\t Search room ";
    cout << "\n3)\t Renew allotment ";
    cout << "\n4)\t Customer record ";
    cout << "\n5)\t Delete record ";
    cout << "\n6)\t Save records to file ";
    cout << "\n7)\t Load records from file ";
    cout << "\n8)\t Exit ";
    cout << "\n\n";
    cout << "Enter Your Choice :  ";
    cin >> ch;

    switch(ch) {
        case 1: input(); break;
        case 2: search(); break; 
        case 3: update(); break; 
        case 4: record(); break; 
        case 5: remove(); break; 
        case 6: saveToFile(); break; 
        case 7: loadFromFile(); break; 
        case 8: exit(0); break; 
        default: cout << " :: Invalid option ::"; break;
    }
}

void hotel::input() {
    cout << "\n\t > royal resort < ";
    node *newNode = new node; 
    cout << "\n Enter the room ID : ";
    cin >> newNode->id;
    cout << "\n Enter the customer name : ";
    cin >> newNode->name;
    cout << " Enter arrival date (DDMMYYYY) : ";
    cin >> newNode->date;
    cout << " Enter room (AC or Non-AC) : ";
    cin >> newNode->typeofroom;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        node *ptr = head;
        while (ptr->next != NULL) {
            ptr = ptr->next;
        }
        ptr->next = newNode;
    }
    cout << "\n\n\t\t :: Room allotted successfully ::" << endl;
}

void hotel::search() {
    cout << "\n\t > royal resort < ";
    int temp_id;   
    if (head == NULL) {
        cout << " \n\n NO record found " << endl;
        return;
    }
    
    cout << " \n\n\n Enter ROOM ID : ";
    cin >> temp_id;
    node* ptr = head;
    while (ptr != NULL) {
        if (temp_id == ptr->id) {
            cout << "\n\n ROOM ID is : " << ptr->id;
            cout << "\n Customer name : " << ptr->name;
            cout << "\n Arrival date : " << ptr->date;
            cout << "\n Room type : " << ptr->typeofroom;
            return;
        }
        ptr = ptr->next;
    }
    cout << " \n\n Room not found." << endl;
}

void hotel::update() {
    cout << "\n\t > royal resort < ";
    int temp_id;
    
    if (head == NULL) {
        cout << " \n\n NO record found " << endl;
        return;
    }
    
    cout << "\n\n Enter room ID : ";
    cin >> temp_id;
    node *ptr = head;
    while (ptr != NULL) {
        if (temp_id == ptr->id) {
            cout << "\n\n Enter new Room ID : ";
            cin >> ptr->id;
            cout << "\n Enter Customer name : ";
            cin >> ptr->name;
            cout << "\n Enter Arrival date (DDMMYYYY) : ";
            cin >> ptr->date;
            cout << "\n Enter room type (AC or Non-AC) : ";
            cin >> ptr->typeofroom;
            cout << "\n\t :: Record updated successfully ::" << endl;
            return;
        }
        ptr = ptr->next;
    }
    cout << " \n\n Room not found." << endl;
}

void hotel::remove() {
    cout << "\n\t > royal resort < ";
    int temp_id;
    
    if (head == NULL) {
        cout << " \n\n NO record found " << endl;
        return;
    }
    
    cout << "\n\n Enter room ID : ";
    cin >> temp_id;

    if (head->id == temp_id) {
        node* ptr = head; 
        head = head->next;
        delete ptr;
        cout << "\n\t :: Record is removed successfully ::" << endl;
        return;
    }

    node* ptr = head;
    node* pre = NULL;
    while (ptr != NULL) {
        if (temp_id == ptr->id) {
            pre->next = ptr->next;
            delete ptr;
            cout << "\n\t :: Record is removed successfully ::" << endl;
            return;
        }
        pre = ptr;
        ptr = ptr->next;
    }
    cout << " \n\n Room not found." << endl;
}

void hotel::record() {
    node* ptr = head;
    if ( ptr == NULL) {
        cout << "\n\n No records to display." << endl;
        return;
    }
    
    while (ptr != NULL) {
        cout << "\n\n\t\t\tRECORD OF THE CUSTOMER ";
        cout << "\n Room ID is : " << ptr->id;
        cout << "\n Customer name is : " << ptr->name;
        cout << "\n Arrival date : " << ptr->date;
        cout << "\n Room type : " << ptr->typeofroom;
        ptr = ptr->next;
    }
}

void hotel::saveToFile() {
    ofstream outFile("hotel_records.txt");
    if (!outFile) {
        cout << "Error opening file for writing!" << endl;
        return;
    }
    
    node* ptr = head;
    while (ptr != NULL) {
        outFile << ptr->id << " " << ptr->date << " " << ptr->name << " " << ptr->typeofroom << endl;
        ptr = ptr->next;
    }
    outFile.close();
    cout << "Records saved to file successfully." << endl;
}

void hotel::loadFromFile() {
    ifstream inFile("hotel_records.txt");
    if (!inFile) {
        cout << "Error opening file for reading!" << endl;
        return;
    }

    head = NULL;  // Reset the list before loading

    while (true) {
        node* newNode = new node;
        inFile >> newNode->id >> newNode->date >> newNode->name >> newNode->typeofroom;

        if (inFile.fail()) {
            delete newNode;  // Avoid memory leak
            break;  // Stop reading when reaching the end or encountering an error
        }

        newNode->next = NULL;

        if (head == NULL) {
            head = newNode;
        } else {
            node* ptr = head;
            while (ptr->next != NULL) {
                ptr = ptr->next;
            }
            ptr->next = newNode;
        }
    }

    inFile.close();
    cout << "Records loaded from file successfully." << endl;
}

void hotel::sort() {
    if (head == NULL) {
        cout << "\n\n\t ::No Record found ::" << endl;
        return;
    }

    
    node* ptr1, *ptr2;
    int swapped;
    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != NULL) {
            ptr2 = ptr1->next;
            if (ptr1->id > ptr2->id) {
               
                swap(ptr1->id, ptr2->id);
                swap(ptr1->name, ptr2->name);
                swap(ptr1->date, ptr2->date);
                swap(ptr1->typeofroom, ptr2->typeofroom);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
    } while (swapped);
}

int main() {
    hotel h1;
    while (true) {
        h1.option();
    }
    return 0;
}
