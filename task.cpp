//task.cpp

#include <vector>
#include <iostream>
#include <string>

#include "task.h"


task::task(){
    this -> date_as = "";
    this -> date_due = "";
    this -> date_com = "";
    this -> taskNam = "";
    this -> taskDes = "";
    this -> priority = "";
    this -> assignees = std::vector<std::string>();
    this -> associated = std::vector<std::string>();
}


void task::createTask(std::string d_a, std::string d_d, std::string date_c, std::string t_n, std::string t_d, std::string asi, std::string pri, std::string aso){
    if(date_as.empty() && d_a != ""){
        date_as = d_a;

    }else if(date_due.empty() && d_d != ""){
        date_due = d_d;

    }else if(date_com.empty() && date_c != ""){
        date_com = date_c;

    }else if(taskNam.empty() && t_n != ""){
        taskNam = t_n;

    }else if(taskDes.empty() && t_d != ""){
        taskDes = t_d;

    }else if(assignees.size() == 0 && asi != ""){
        assignees.push_back(asi);

    }else if(priority.empty() && pri != ""){
        priority = pri;

    }
    else if(associated.size() == 0 && aso != ""){
        associated.push_back(aso);
    }
}

void task::pieceTask(std::string temp, std::string where_to){
    if(where_to == "date_a"){
        date_as = temp;

    }else if(where_to == "date_d"){
        date_due = temp;

    }else if(where_to == "date_c"){
        date_com = temp;

    }else if(where_to == "tName"){
        taskNam = temp;

    }else if(where_to == "tDesc"){
        taskDes = temp;

    }else if(where_to == "assignee"){
        assignees.push_back(temp);

    }else if(where_to == "priority"){
        priority = temp;
    }else if(where_to == "status"){

    }
}

std::string task::getPiece(std::string temp){
    if(temp == "date_a"){
        return date_as;

    }else if(temp == "date_d"){
        return date_due;

    }else if(temp == "date_c"){
        return date_com;

    }else if(temp == "tName"){
        return taskNam;
        
    }else if(temp == "tDesc"){
        return taskDes;

    }else if(temp == "priority"){
        return priority;

    }else if(temp == "assignee"){
        std::string to_ret = "";
        if(assignees.size() == 0){
            return "";

        } else {
            for(int i = 0; i < assignees.size(); i++){
                to_ret += std::to_string(i + 1) + ": " + assignees.at(i) + "\n";

            }
        }
        return to_ret;

    }else if(temp == "associated"){
        std::string to_ret = "";

        if(associated.size() == 0){
            return "";

        } else {
            for(int i = 0; i < associated.size(); i++){
                to_ret += std::to_string(i + 1) + ": " + associated.at(i) + "\n";

            }
        }
        return to_ret;
    }
    return "";
}

std::string task::getTask(){
    std::string aso_comp = "";
    for(int i = 0; i < associated.size(); i++){
        if(i + 1 == associated.size()){
            aso_comp += associated.at(i);
        } else {
            aso_comp += associated.at(i) + ", ";
        }
    }

    std::string asi_comp = "";
    for(int i = 0; i < assignees.size(); i++){
        if(i + 1 == assignees.size()){
            asi_comp += assignees.at(i);
        } else{
            asi_comp += assignees.at(i) + ", ";
        }
    }

    std::string to_ret = "(" + priority + ")" + taskNam + " :\n" + "Description: " + taskDes + "\nAssoc. Tasks: " + 
    aso_comp + "\nAssignees: " + asi_comp +  "\nAssigned: " + date_as + "\nDue: " + date_due + "\n";

    return to_ret;
}