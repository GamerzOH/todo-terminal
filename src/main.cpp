<<<<<<< HEAD
#include <cstring>
#include <iostream>
#include <fstream>
#include <iterator>
#include <list>
#include <string>

using namespace std;

struct Task {
    char cont[128];

    bool operator==(const Task &task) {
        if (strcmp(cont, task.cont)) return false;
        else return true;
    }
};

class TodoApp {
    list<Task> taskList;
    public:
        TodoApp(): taskList(){
            readFile();
        }
        void readFile(const string filepath = "../testing/data.dat") {
            ifstream file(filepath, ios::in|ios::binary);
            if (file.is_open()) {
                Task temp;
                while(file.read(reinterpret_cast<char*>(&temp), sizeof(Task))) {
                    taskList.push_back(temp);
                }
                file.close();
            } else {
                cerr<<"Error Reading file!";
            }
        }
        void saveToFile(const string filepath = "../testing/data.dat") {
            ofstream file(filepath, ios::out|ios::binary);
            if (file.is_open()) {
                for (auto iter:taskList) {
                    file.write(reinterpret_cast<char*>(&iter), sizeof(Task));
                }
                file.close();
            } else {
                cerr<<"Error Writing to file!";
            }
        }
        void addTodo() {
            string cont;
            cout<<"Enter Task: ";
            getline(cin, cont);
            Task temp;
            strcpy(temp.cont, cont.c_str());
            taskList.push_back(temp);

            saveToFile();
            // this->display();
        }
        void addTodo(const char* cont) {
            Task temp;
            strcpy(temp.cont, cont);
            taskList.push_back(temp);

            saveToFile();
            // this->display();
        }
        void remTodo(const char* cont) {
            for (auto iter:taskList) {
                if (!strcmp(cont, iter.cont)) taskList.remove(iter);
            }

            saveToFile();
            // this->display();
        }
        void remTodo(const int index) {
            if (index<=taskList.size()&&index>=0) {
                auto iter = taskList.begin();
                advance(iter, index-1);
                taskList.erase(iter);

                saveToFile();
                // this->display();
            } else {
                cerr<<"Invalid index!"<<endl;
            }
        }
        void display() {
            int count=1;
            for (auto iter:taskList) {
                cout<<count<<": "<<iter.cont<<endl;
                count++;
            }
        }
};

int main() {
    TodoApp app;

    return 1;
}
=======
#include <app-state.hpp>
#include <io.hpp>
#include <ui-comp.hpp>
>>>>>>> 8f6ad69 (Added file handling and backend logic)
