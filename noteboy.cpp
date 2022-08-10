//noteboy.cpp by Evan Kamuf

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <stdio.h>
#include <math.h>
#include <istream>
#include "task.h"

void tapstate(){
    std::ofstream fs;
    fs.open("taskstate.csv");
    fs.close();
}

void savestatewrite(){

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
    }
}

char parentmost_menu(){
    //options
    char inprtn = getchar();
    return inprtn;
}
void loadfi(){
    std::ifstream fs;
    fs.open("taskstate.csv");
    if(!fs.is_open()){
        fs.close();
        tapstate();
    } else {
        fs.close();
        loadstate();
    }
}

int main(){
    //Startup options
    loadfi();

    //Menus, laterals, and exit saving

    //Exit
    return 0;
}