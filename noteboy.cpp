//noteboy.cpp (2022) Evan Kamuf

//lib
#include <iterator>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <array>
#include <limits>
#include <istream>
#include <sstream>
#include <regex>

/*using namespace conmanip;*/

//Host-specific includes
#include <windows.h>

//External Includes
#include <conmanip.h>

//in-house include
#include "task.h"

//macros
#define watch(x) return (#x)

//globals
task taskz;
std::vector<task> tasks;
int has_opened;
conmanip::console_out_context ctxout;
conmanip::console_out conout(ctxout);

void showAll(){
    //Display this information formatted with conmanip
    for(int i = 0; i < sizeof(taskz); i++){
    std::cout
      << settextcolor(conmanip::console_text_colors::light_yellow)
      << setbgcolor(conmanip::console_bg_colors::black)
      << tasks.at(i).getPiece("tName")
      << "\n"
      << settextcolor(conmanip::console_text_colors::light_blue)
      << setbgcolor(conmanip::console_bg_colors::white) << std::endl;
      std::cout
      << "\"" << tasks.at(i).getPiece("date_d") << "\"" << tasks.at(i)getPiece("priority");
      //Finish - incomplete
    }
}


int dimensionSpecficiation(){
    //24 pixels per row
    //11~ pixels per column

        CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return rows, columns;
}


std::fstream& GotoLine(std::fstream& file, unsigned int num){
    file.seekg(std::ios::beg);
    for(int i=0; i < num - 1; ++i){
        file.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return file;
}

void disAll(){
    //This guy needs to be formatted better  --- More longitudenal involvement? Viewport based display?

    for(int i=0; i < sizeof(tasks); i++){
        std::cout << tasks.at(i).getTask() << std::endl;
    }
}

void tapstate(){
    std::ofstream fs;
    fs.open("taskstate.csv");
    fs.close();
    has_opened = 1;
}

int delFromFile(int location){
    
    std::string t_line;
    int lncount = 0;
    bool alter = false;

    try {
        std::ifstream fs("taskstate.csv");
        std::ofstream ofs;
        if(!fs.is_open()){
            throw(1);   

        }
        fs.close();

        while (std::getline(fs, t_line))
        {
                if(t_line.find(tasks.at(location).getPiece("tName")) == true){

                    ofs.open("taskstate.csv");
                    t_line.replace(t_line.find(lncount), sizeof(t_line.find(lncount)), "");
                    ofs << t_line << std::endl;
                    alter = true;
            lncount += 1;
        }
         ofs.close();
        
        if(alter == false){
            throw(1);
        }
        std::cout <<"Deletion of task in file: successful\n";
        }
    }

    catch (int exc){
        if(exc == 1){
            std::cout << "Trouble initializing to read?!\n";
        }
        if(exc == 2){
            std::cout << "Deletion of task in file: failed\n";
        }
    }
}

void deltask(int location){
    try {
        tasks.erase(tasks.begin() + location);
    }
    catch (int d_code){
        if(d_code == 0){
            std::cout << "Deletion of task in session: succesful\n";
        }
        if(d_code == 1){
            std::cout << "Deletion of task in session: failed\n";
        }
    }
}

std::string fCheck(std::string target, std::string options){
    std::string result = "false";
    std::string line;
    int counter = 0;
    std::ifstream fs("taskstate.csv");
    while(std::getline(fs, line)){
        if(line.find(target)){
            result = "true";
        }
         counter += 1;
    }
    if(options == "u"){
        return std::to_string(counter);
    }else if(options == "n"){
        return result;
    }
}

void fUpdate(std::string target, std::string key, std::string replaceStr, int location){
    std::string prebuff;
    int lnum = std::stoi(fCheck(target, "u"));
    std::ofstream fs("taskstate.csv");
    std::stringstream buffer_in;
    buffer_in << fs.rdbuf();
    fs.close();
    std::fstream wfs("taskstate.csv");
    std::string bufferConv = buffer_in.str();
    std::string t_grab = tasks.at(location).getTask();

    //bufferConv.replace(buffer_in.str().find(tasks.at(location).getPiece(key)), tasks.at(location).getPiece(key).size(), replaceStr);
    
    std::regex_replace(bufferConv, std::regex(fileExpr(keyToDir(key))), replaceStr);    //Uses regex_replace to run-through file. Replaces matched string with 'replaceStr'
    wfs.write(bufferConv.c_str(), bufferConv.size());                                   //Overwrites entire file with the change. This DOES NOT make isolated changes/re-writes.
    wfs.close();
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

std::string keyToDir(std::string key){
       std::string to_ret;

    if(key == "tDesc"){
        to_ret = "tDesc";

    }else if(key == "priority"){
        to_ret = "priority";

    }else if(key == "associated"){
        to_ret = "";

    }else if(key == "assignee"){
        to_ret = "assignee";

    }else if(key == "date_a"){
        to_ret = "date_a";

    }else if(key == "date_d"){
        to_ret = "date_d";

    }
    return to_ret;
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

std::string fileExpr(std::string directed){
    
    std::string proper;

    //These regular expression represnetations need to utilize the 'match' not the group. The match contains references to GET TO the match

    if(directed == "tDesc"){

        proper = "ion:.(.*)";

    }else if(directed =="tName"){

        proper = "\\)(.*)";

    }else if(directed == "priority"){

        std::string prpoer = "\\((.*)\\)";

    }else if(directed == "associated"){

        proper = "sks:.(.*)";

    }else if(directed == "assignee"){

        proper = "ees:.(.*)";

    }else if(directed == "date_a"){
    
        proper = "ned:.(.*)";

    }else if(directed == "date_d"){
        proper = "ue:.(.*)";
    }else {
        std::cout << "Issue at 'fileExpr'~~ a direction is not conditionally exppresed or passed properly in this function. You are not meant to see this message.\n"
        << "Please diagnose this and recompile.\n";
    }

    return proper;

}

void interWrite(std::string taskName, std::string key, std::string replaceStr, int location){
    std::string wType;
    wType = fCheck(taskName, "n");

    if(wType == "true"){

        fUpdate(taskName, key, replaceStr, location);

    }else if(wType == "false"){

        //Function to append at end

    } else{
        std::cout << "on iterWrite()~~ conditional exception occured (this is manually documented.\nThis message is not supposed to be visible.\n" <<
        "If you see this output, please diagnose this and recompile." << std::endl;
    }
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
        interWrite(tasks.at(location).getPiece("tName"), tasks.at(location).getPiece(dirInterpreter(move)), temp, location);
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
    int to_ret;

    if(std::to_string(act) == "n"){
        to_ret = 1;
        return to_ret;

    }else if(std::to_string(act) == "m"){
        to_ret = 2;
        return to_ret;

    }else if(std::to_string(act) == "c"){
        to_ret = 3;
        return to_ret;

    }

    //Probably more options

    else if(std::to_string(act) == "f"){
        to_ret = 4;
        return to_ret;
    }

    else if(std::to_string(act) == "q"){
        to_ret == 9;
        return to_ret;
    }
    else {return 0;}
}

int parentmost_menu(){
    //function called to display tasks formatted
    disAll();
    //options
    std::cout << "Select: ";
    char inprtn = getchar();
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

int main(int argc, char *argv[]){

    conout.settitle("Noteboy");

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