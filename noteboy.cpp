//noteboy.cpp (2022) Evan Kamuf
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include "conio.h"
#include <array>
#include <istream>

#include "task.h"


#define watch(x) return (#x)
task taskz;
std::vector<task> tasks;

int has_opened;

void tapstate(){
    std::ofstream fs;
    fs.open("taskstate.csv");
    fs.close();
    has_opened = 1;
}

void savestatewrite(){
    std::ofstream fs;
    fs.open("taskstate.csv");

    if(has_opened != 1){
        fs << "Task,Priority,Task Description,Associated Tasks,Assignees,Assigned Date,Due Date\n";
    }

    for(int i = 0; i < tasks.size(); i++){
        fs << tasks.at(i).getPiece("tName") << "," << tasks.at(i).getPiece("priority") << "," << tasks.at(i).getPiece("associated") << "," << 
        tasks.at(i).getPiece("assignee") << "," << tasks.at(i).getPiece("date_a") << "," << tasks.at(i).getPiece("date_d") << "\n";
    }

    //Before leaving
    fs.close();
}

void requestInterpret(std::string key, std::string value, int location){

}

std::string dirInterpreter(std::string inp){
    std::string to_ret;

    if(inp == "D" || inp == "d"){
        to_ret = "tDesc";

    }else if(inp == "P" || inp == "p"){
        to_ret = "priority";

    }else if(inp == "A" || inp == "a"){
        to_ret = "associated";

    }else if(inp == "B" || inp == "b"){
        to_ret = "assignee";

    }else if(inp == "S" || inp == "s"){
        to_ret = "date_a";

    }else if(inp == "X" || inp == "x"){
        to_ret = "date_d";

    }
    return to_ret;
}


void taskFiller(int location){
    std::string msg, temp, name, desc, aDate, dDate, priority, associated, assignee;
    std::string send_out [] = {temp, name, desc, aDate, dDate, priority, associated, assignee};
     while(temp != "done"){
        std::cout <<"Remaining fillable:\n";
        for(int i = 0; i < sizeof(send_out); i++){

            if(i + 1 == sizeof(send_out) && send_out[i] != ""){
                msg += std::string(send_out[i]) + ".\n";

            }
            if(send_out[i] != ""){
                msg += std::string(send_out[i]) + ", ";
            }
        }
    }

    std::cout << msg << "Enter a value/label for one of the following: ";
    std::cin >> temp;
    std::string move;
    std::cout << "What keys to '" << temp << "'? (D)escription, (P)riority, (A)ssociated Tasks\nAssignees use (B)oss, A(S)igned date, (X)Due Date:\n ";
    move = getchar();

    std::string chck = taskz.getPiece(dirInterpreter(move));

    if(chck != ""){
        return;
    }else{
        tasks.at(location).pieceTask(temp, move);
        //actually set
        return;
    }

}

void newTask(){
   /* std::string move, temp, name, desc, aDate, dDate, priority, associated, assignee;
    std::string send_out [] = {temp, name, desc, aDate, dDate, priority, associated, assignee};
    std::string remaining = "";*/
    std::string choice;
    std::string confirmation;
    std::string tName;
    std::cout << "Enter a task name: ";
    std::cin >> tName;
    std::cout << "Is " << tName << " correct? (y)es (n)o\n";
    confirmation = getchar();

    if(confirmation == "y"){
        taskz.createTask("", "", tName, "", "", "", "");
        std::cout << "Would you like to continue filling out task: " << tName << "?\n(y)es (n)o: ";
        choice = getchar();
        if(choice == "y" || choice == "Y"){
            taskFiller(int( sizeof(tasks) - 1 ));  //This passed int is supposed to represent the latest (currently being created/modified) task. If incorrect or unoptimal, please replace.
        }
    }
}


void loadstate(){
    std::string line;
    int count = 0;
    std::ifstream fs("taskstate.csv");
    while(std::getline(std::cin, line)){
        count += 1;
    }
    for(int x = 0; x < count; x++){
        //Cultivate a healthy write-to-file scheme first for this data before determining how to read it
        //This information pulled also has to be thrown back into the constructors and classes made in task.h  
    }
    fs.close();
}

int motion_interpret(char act){

    if(std::to_stringstd::to_string(act)) == "n"){
        to_ret = 1;
        return to_ret;

    }else ifstd::to_string(act) == "m"){
        to_ret = 2;
        return to_ret;

    }else ifstd::to_string(act) == "c"){
        to_ret = 3;
        return to_ret;

    }

    //Probably more options

    else ifstd::to_string(act) == "f"){
        to_ret = 4;
        return to_ret;
    }

    else ifstd::to_string(act) == "q"){
        to_ret == 9;
        return to_ret;
    }
    else {return 0;}
}

int parentmost_menu(){
    //function called to display tasks formatted
    //options
    std::cout << "Select: ";
    char inprtn = getch();
    int choice = motion_interpret(inprtn);

    if(choice == 0){
        std::cout << "!Invalid selection!";
        parentmost_menu;

    } else {

    }
        return choice;
}

void loadfi(){
    std::ifstream fs;
    fs.open("taskstate.csv");
    if(!fs.is_open()){
        fs.close();
        tapstate();
    } else {
        fs.close();
        has_opened = 1;
        loadstate();
    }
}

int main(){
    int option;
    std::string qConfirm = "";
    //Startup options
    loadfi();
    do{
        option = parentmost_menu();
        switch(option){
            case 1: newTask();
                break;

            case 2: //manage / modify / update
                break;

            case 3: //complete
                break;
            
            case 4: //filter
                break;

            case 9: std::cout<<"Press 'y' to confirm the quit: "; qConfirm = getchar(); break;

            default: "Not sure how you got here chief, but good going..\n";
        }

    }while(qConfirm != "y");
    //Menus, laterals, and exit saving

    //Exit
    return 0;
}