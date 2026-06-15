#include <fstream>
#include <io.hpp>
#include <iostream>
#include <filesystem>

using namespace std;

File::File() {

}
vector<Todo> File::readFile(const string filename = FILENAME) {
    if (!filesystem::exists(filename)) {
        writeFile({});
    }

    try {
        vector<Todo> todolist;
        ifstream datafile(filename, ios::binary | ios::in);
        if (datafile.is_open()) {
            Todo temp;
            while (datafile.read(reinterpret_cast<char*>(&temp), sizeof(Todo))) {
                todolist.push_back(temp);
            }
        } else throw("File could not be opened for reading! File does not exist!");
        datafile.close();
    }
    catch (const string e) {
        cerr<<e;
        return {};
    }
    return todolist;
}

bool File::writeFile(vector<Todo> todos) {
    todolist = todos;
    try {
        ofstream datafile(FILENAME, ios::out | ios::binary);
        if (datafile.is_open()) {
            for (Todo todo: todolist) {
                datafile.write(reinterpret_cast<char*>(&todo), sizeof(Todo));
            }
        } else throw("File could not be opened for writing!");
        datafile.close();
    }
    catch(const string e) {
        cerr<<e;
        return false;
    }
    return true;
}

bool File::appendTodo(const Todo todo) {
    try {
        ofstream datafile(FILENAME, ios::binary | ios::app);
        if (datafile.is_open()) {
            Todo temp = todo;
            datafile.write(reinterpret_cast<char*>(&temp), sizeof(temp));
        } else throw("Todo Could not be saved!");
        datafile.close();
    }
    catch(const string e) {
        cerr<<e;
        return false;
    }

    return true;
}
