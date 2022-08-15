//task.h
#include <vector>
#include <iostream>
#include <string>

class task {
    public:
        task();
        void createTask(std::string dateA, std::string dateD, std::string tName, std::string tDesc, std::string azikneez, std::string priority, std::string associated);
        void pieceTask(std::string temp, std::string where_to); //use val 1 of function to take in a piece of info, val 2 will be used to conditionally determine what the value is representing.
        //void delTask(); //Maybe have this in main? As the vector or array for tasks will probably be initialized there?

        std::string getTask();
        std::string getPiece(std::string temp);
    private:
        std::string date_as, date_due, taskNam, taskDes, priority;
        std::vector<std::string> assignees, associated;
};