#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct Task {
    char cont[128];
};

class Todo {
    public:
        string cont;
        Todo* next;
        Todo() {
            cout<<"Enter Todo: ";
            getline(cin, this->cont);
        }
        Todo(Task &task) {
            this->cont = task.cont;
        }
};

class TodoFile {
    Todo* head;
    public:
        TodoFile() {
            saveToFile();
            readFile();
        }
        void readFile(const char* filename = "../testing/data.dat") {
            ifstream file(filename, ios::in|ios::binary);
            if (file.is_open()) {

            } else {
                cerr<<"Error reading file, file does not exist!";
            }
            file.close();
        }
        void saveToFile(const char* filename = "../testing/data.dat") {
            ofstream file(filename, ios::out|ios::binary);
            if (file.is_open()) {
                Todo* curr = head;
                while (curr->next!=nullptr) {
                    Task temp;
                    strcpy(temp.cont, curr->cont.c_str());
                    file.write(reinterpret_cast<char*>(&temp), sizeof(Task));
                    curr = curr->next;
                }
            } else {
                cerr<<"File opening for writing failed!";
            }
            file.close();
        }
};

int main() {
    TodoFile file;

    return 0;
}
