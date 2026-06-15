#pragma once
#define FILENAME "../testing/data.txt"

#include <app-state.hpp>
#include <vector>

using namespace std;

class File {
    vector<Todo> todolist;
    public:
        File();
        vector<Todo> readFile(const string);
        bool writeFile(vector<Todo> todos);
        bool appendTodo(const Todo todo);
};
