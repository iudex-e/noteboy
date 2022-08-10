//task.h

class task {
    public:
        task();
        void createTask(std::string dateA, std::string dateD, std::string tName, std::string tDesc, std::string azikneez, std::string priority);
        void pieceTask(std::string temp, std::string where_to); //use val 1 of function to take in a piece of info, val 2 will be used to conditionally determine what the value is representing.
    private:
        std::string date_as;
        std::string date_due;
        std::string taskName;
        std::string taskDesc;
        std::string assignees;
        std::string priority;

};





void task::pieceTask(std::string temp, std::string where_to){

}