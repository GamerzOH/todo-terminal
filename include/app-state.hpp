#pragma once

#include <cstring>
#include <vector>
#include <string>

using namespace std;

enum task_status {
    PENDING,
    DONE,
};

struct Todo {
    char task[128];
    task_status status;

    bool operator==(Todo &todo) {
        if (!strcmp(this->task, todo.task) && this->status == todo.status) return true;
        else return false;
    }
};

struct AppState {
    string new_input = "";
    vector<Todo> todolist;

    AppState():todolist({}){

    }
};
