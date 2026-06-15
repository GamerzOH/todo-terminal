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
        Todo(const string task) {
            this->cont = task;
        }
        Todo(Task &task) {
            this->cont = task.cont;
        }
};

class TodoFile {
    Todo* head;
    Todo* curr;
    Todo* last;
    public:
        TodoFile() : head(nullptr), curr(nullptr), last(nullptr) {
            last = head;
            curr = head;
            readFile();
        }
        void readFile(const char* filename = "../testing/data.dat") {
            ifstream file(filename, ios::in|ios::binary);
            if (file.is_open()) {
                Task temp;
                curr = head;
                while (file.read(reinterpret_cast<char*>(&temp), sizeof(temp))) {
                    curr = new Todo(temp);
                    curr = curr->next;
                }
                last = curr;
            } else {
                cerr<<"Error reading file, file does not exist!";
            }
            file.close();
        }
        void saveToFile(const char* filename = "../testing/data.dat") {
            ofstream file(filename, ios::out|ios::binary);
            if (file.is_open()) {
                curr = head;
                while (curr!=nullptr) {
                    Task temp;
                    strcpy(temp.cont, curr->cont.c_str());
                    file.write(reinterpret_cast<char*>(&temp), sizeof(temp));
                    curr = curr->next;
                }
            } else {
                cerr<<"File opening for writing failed!";
            }
            file.close();
        }
        void addTodo(const char* todo) {
            if (head==nullptr) {
                head = new Todo;
                last = head;
            }
            last->next = new Todo(todo);
            last = last->next;
        }
        // void addTodo() {
        //     if (head == nullptr) {
        //         head = new Todo;
        //         last = head;
        //     }
        //     last->next = new Todo;
        //     last=last->next;
        //     cout<<"Enter Task: ";
        //     getline(cin, last->cont);
        // }
        void remTodo(const string todo) {
            curr = head;
            Todo* prev;
            while (curr!=NULL) {
                if (!strcmp(todo.c_str(), curr->cont.c_str())) {
                    if (curr==head) {
                        head = head->next;
                        delete curr;
                    } else if (curr==last) {
                        last = prev;
                        delete curr;
                        last->next = nullptr;
                    } else {
                        prev->next = curr->next;
                        delete curr;
                    }
                    break;
                } else {
                    prev = curr;
                    curr = curr->next;
                }
            }
        }
        void display() {
            curr = head;
            int count=1;
            while (curr!=NULL) {
                cout<<count<<": "<<curr->cont<<endl;
                curr = curr->next;
                count++;
            }
        }
};

int main() {
    TodoFile file;
    file.addTodo("Create something");
    // file.addTodo("Something is to be done");
    // file.saveToFile();
    // file.readFile();
    file.display();

    return 0;
}
