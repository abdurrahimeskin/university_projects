//Abdurrahim ESKİN
//2016400387
//STATUS:WORKING



#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <regex>


using namespace std;

//I have created ofstream to write
ofstream output("output.txt");
ofstream output10("output_10.txt");
ofstream outp11("output_11.txt");
ofstream output12("output_12.txt");

//I have defined program code structure for code.txt
class instruction {
public:
    string instructionName;
    int burstingTime;

    instruction() {} //Constructor
    instruction(string instructionName__, int burstingTime__) {
        instructionName = instructionName__;
        burstingTime = burstingTime__;

    }
};


//Defined process which include their attributes such as name,arrival time, instructions, program code etc
class ProcessInf {
public:
    string processName;
    string program_code_in_Usage;
    int arrivalTime;
    int totalBurstTime;
    queue<instruction> InstructionQ; // queue for Instruction

    ProcessInf() {}

    ProcessInf(string process_name__, string program_code_in_Usage__, int arrivalTime__, int burstingTime__,
               queue<instruction> ThrQ__) {
        processName = process_name__;
        program_code_in_Usage = program_code_in_Usage__;
        arrivalTime = arrivalTime__;
        totalBurstTime = burstingTime__;
        InstructionQ = ThrQ__;
    }


};

class InputOutput {
public:
    ProcessInf pro;
    int time;
};

queue<InputOutput> display0Q;
queue<InputOutput> display1Q;
queue<InputOutput> readyQu;
queue<string> duble_Que;


static queue<instruction> get_code(string codeTextNum) {
    //this function get code from txt file for example 1.code.txt

    ifstream file(codeTextNum);
    string instr_name;
    int burst_time;
    queue<instruction> tempQ;
    //parses file and splits it according to "TAB" sign

    while (file >> instr_name >> burst_time) {
        instruction tempCodeStructure(instr_name, burst_time);
        tempQ.push(tempCodeStructure);
    }

    return tempQ;
}

queue<ProcessInf> MakeProcessInfo(queue<ProcessInf> processQueue) {
//get info for process from definition text file
    ifstream myfile("definition.txt");

    string process_name;
    string program_Code_In_Usage;
    int arrival_time;


    //parses the file and splits it according to "TAB" sign

    while (myfile >> process_name >> program_Code_In_Usage >> arrival_time) {

        ProcessInf process_Inf;
        process_Inf.processName = process_name;
        process_Inf.program_code_in_Usage = program_Code_In_Usage;
        process_Inf.arrivalTime = arrival_time;

        process_Inf.InstructionQ = get_code(process_Inf.program_code_in_Usage);

        processQueue.push(process_Inf);

        //Add all attributes to processQueue
    }
    myfile.close();

    return processQueue;
}


void Scheduling_Instructions(queue<ProcessInf> processQueue) {

    queue<ProcessInf> CPU_Q;
    //I take first element of processQueue
    //than I added to CPU and removed from processQueue

    ProcessInf temp = processQueue.front();
    CPU_Q.push(temp);
    int time = CPU_Q.front().arrivalTime;

    //I have added the first element to output.txt
    output << time << "- " << "HEAD -" << processQueue.front().processName << "- TAIL" << endl;
    //pop'ed first element
    processQueue.pop();


    //I checked if new process is include or CPU is not empty
    while (!processQueue.empty() || !CPU_Q.empty()) {

        int exececutionTime = 0;
        //This while loop  control timeslot  is equal or more than it
        //because we cannot divide intructor of any process

        while (exececutionTime < 100 && !CPU_Q.front().InstructionQ.empty()) {

            if (CPU_Q.front().InstructionQ.front().instructionName.find("dispM_0") != std::string::npos) {
                //region Description

                time += exececutionTime;


                InputOutput d;
                d.time = CPU_Q.front().InstructionQ.front().burstingTime;
                CPU_Q.front().InstructionQ.pop();
                d.pro = CPU_Q.front();

                display0Q.push(d);

                CPU_Q.pop();

                while (processQueue.front().arrivalTime <= time && !processQueue.empty()) {
                    ProcessInf temp = processQueue.front();
                    CPU_Q.push(temp);
                    processQueue.pop();
                    //check if any process comes or not according to arrival time info
                }

                output << time << "::" << "HEAD ";
                queue<ProcessInf> tempQueue = CPU_Q;
                // I created  a temporary file to print CPU;
                while (!tempQueue.empty()) {
                    output << "-" << tempQueue.front().processName;
                    tempQueue.pop();
                }
                output << "-TAIL " << endl;

                output10 << time << "::" << "HEAD ";
                queue<InputOutput> tempQueue0 = display0Q;
                // I have created a temporary file to print CPU;
                while (!tempQueue0.empty()) {
                    output10 << "-" << tempQueue0.front().pro.processName;
                    tempQueue0.pop();
                }
                output10 << "-TAIL " << endl;
                exececutionTime = 0;
                //end_of_region
            } else if (CPU_Q.front().InstructionQ.front().instructionName.find("dispM_1") != std::string::npos) {
                //region Description
                time += exececutionTime;


                InputOutput d;
                d.time = CPU_Q.front().InstructionQ.front().burstingTime;
                CPU_Q.front().InstructionQ.pop();
                d.pro = CPU_Q.front();

                display1Q.push(d);

                CPU_Q.pop();

                while (processQueue.front().arrivalTime <= time && !processQueue.empty()) {
                    ProcessInf temp = processQueue.front();
                    CPU_Q.push(temp);
                    processQueue.pop();
                    //check if any process comes or not according to arrival time information
                }

                output << time << "::" << "HEAD ";
                queue<ProcessInf> tempQueue = CPU_Q;
                // I created  a temporary file to print CPU_Q;
                while (!tempQueue.empty()) {
                    output << "-" << tempQueue.front().processName;
                    tempQueue.pop();
                }
                output << "-TAIL " << endl;

                outp11 << time << "::" << "HEAD ";
                queue<InputOutput> tempQueue1 = display1Q;
                // I created a temporary file to print CPU_Q;
                while (!tempQueue1.empty()) {
                    outp11 << "-" << tempQueue1.front().pro.processName;
                    tempQueue1.pop();
                }
                outp11 << "-TAIL " << endl;
                exececutionTime = 0;
                //end_of_region
            } else if (CPU_Q.front().InstructionQ.front().instructionName.find("readM_") != std::string::npos) {

                regex str(".+_(\\d+)");
                string str1 = CPU_Q.front().InstructionQ.front().instructionName;
                smatch m;
                regex_search(str1, m, str);
                cout << m[1].str() << endl;
                string read_Num=m[1].str();

                if (duble_Que.size() < 2) {
                    duble_Que.push(read_Num);
                    time += exececutionTime;

                    InputOutput d;
                    d.time = CPU_Q.front().InstructionQ.front().burstingTime;
                    CPU_Q.front().InstructionQ.pop();
                    d.pro = CPU_Q.front();

                    readyQu.push(d);
                    CPU_Q.pop();
                    while (processQueue.front().arrivalTime <= time && !processQueue.empty()) {
                        ProcessInf temp = processQueue.front();
                        CPU_Q.push(temp);
                        processQueue.pop();
                        //check if any process comes or not according to arrival time info
                    }

                    output << time << "::" << "HEAD ";
                    queue<ProcessInf> tempQueue = CPU_Q;
                    // I created  a temporary file to print CPU;
                    while (!tempQueue.empty()) {
                        output << "-" << tempQueue.front().processName;
                        tempQueue.pop();
                    }
                    output << "-TAIL " << endl;

                    output12 << time << "::" << "HEAD ";
                    queue<InputOutput> tempQueue1 = readyQu;
                    // I created  a temporary file to print CPU;
                    while (!tempQueue1.empty()) {
                        output12 << "-" << tempQueue1.front().pro.processName;
                        tempQueue1.pop();
                    }
                    output12 << "-TAIL " << endl;
                    exececutionTime = 0;



                } else {

                    queue<string> tempQue = duble_Que;
                    bool iF_before = false;
                    // I created  a temporary file to print CPU_Q;
                    while (!tempQue.empty()) {
                        if (duble_Que.front() == read_Num) {
                            CPU_Q.front().InstructionQ.pop();
                            duble_Que.pop();
                            duble_Que.push(read_Num);
                            iF_before = true;

                        }

                        tempQue.pop();
                    }

                    if (!iF_before) {
                        duble_Que.pop();
                        duble_Que.push(read_Num);

                        time += exececutionTime;


                        InputOutput d;
                        d.time = CPU_Q.front().InstructionQ.front().burstingTime;
                        CPU_Q.front().InstructionQ.pop();
                        d.pro = CPU_Q.front();

                        readyQu.push(d);

                        CPU_Q.pop();
                        while (processQueue.front().arrivalTime <= time && !processQueue.empty()) {
                            ProcessInf temp = processQueue.front();
                            CPU_Q.push(temp);
                            processQueue.pop();
                            //check if any process comes or not according to arrival time information
                        }

                        output << time << "::" << "HEAD ";
                        queue<ProcessInf> tempQueue = CPU_Q;
                        // I created  a temporary file to print CPU;
                        while (!tempQueue.empty()) {
                            output << "-" << tempQueue.front().processName;
                            tempQueue.pop();
                        }
                        output << "-TAIL " << endl;

                        output12 << time << "::" << "HEAD ";
                        queue<InputOutput> tempQueue1 = readyQu;
                        // I created  a temporary file to print CPU;
                        while (!tempQueue1.empty()) {
                            output12 << "-" << tempQueue1.front().pro.processName;
                            tempQueue1.pop();
                        }
                        output12 << "-TAIL " << endl;
                        exececutionTime = 0;

                    }
                }


            } else {
                exececutionTime = exececutionTime + CPU_Q.front().InstructionQ.front().burstingTime;
                if (!display0Q.empty()) {
                    display0Q.front().time -= CPU_Q.front().InstructionQ.front().burstingTime;
                    if (display0Q.front().time <= 0) {
                        CPU_Q.push(display0Q.front().pro);
                        display0Q.pop();

                        output10 << time + exececutionTime << "::" << "HEAD ";
                        queue<InputOutput> tempQueue0 = display0Q;
                        // I created  a temporary file to print CPU;
                        while (!tempQueue0.empty()) {
                            output10 << "-" << tempQueue0.front().pro.processName;
                            tempQueue0.pop();
                        }
                        output10 << "-TAIL " << endl;
                    }
                }
                if (!display1Q.empty()) {
                    display1Q.front().time -= CPU_Q.front().InstructionQ.front().burstingTime;
                    if (display1Q.front().time <= 0) {
                        CPU_Q.push(display1Q.front().pro);
                        display1Q.pop();

                        outp11 << time + exececutionTime << "::" << "HEAD ";
                        queue<InputOutput> tempQueue1 = display1Q;
                        // I created  a temporary file to print CPU;
                        while (!tempQueue1.empty()) {
                            outp11 << "-" << tempQueue1.front().pro.processName;
                            tempQueue1.pop();
                        }
                        outp11 << "-TAIL " << endl;
                    }
                }


                if (!readyQu.empty()) {
                    readyQu.front().time -= CPU_Q.front().InstructionQ.front().burstingTime;
                    if (readyQu.front().time <= 0) {
                        CPU_Q.push(readyQu.front().pro);
                        readyQu.pop();

                        output12 << time + exececutionTime << "::" << "HEAD ";
                        queue<InputOutput> tempQueue1 = readyQu;
                        // I created  a temporary file to print CPU_Q;
                        while (!tempQueue1.empty()) {
                            output12 << "-" << tempQueue1.front().pro.processName;
                            tempQueue1.pop();
                        }
                        output12 << "-TAIL " << endl;
                    }
                }
                CPU_Q.front().InstructionQ.pop();


            }

        }
        time += exececutionTime;


        while (processQueue.front().arrivalTime <= time && !processQueue.empty()) {
            ProcessInf temp = processQueue.front();
            CPU_Q.push(temp);
            processQueue.pop();
            //check if any process comes or not according to arrival time information
        }

        if (CPU_Q.front().InstructionQ.empty()) {
            CPU_Q.pop();
        } else {
            ProcessInf temp = CPU_Q.front();
            CPU_Q.pop();
            CPU_Q.push(temp);

        }


        //For writing output text

        output << time << "::" << "HEAD ";
        queue<ProcessInf> tempQueue = CPU_Q;
        // I created  a temporary file to print CPU_Q;
        while (!tempQueue.empty()) {
            output << "-" << tempQueue.front().processName;
            tempQueue.pop();
        }
        output << "-TAIL " << endl;
    }
}

int main() {

    //I have created instruction queue
    queue<ProcessInf> processQueue;

    //the function that take all information from files and assing process
    processQueue = MakeProcessInfo(processQueue);

    //This Schedule decide which process must execute according to Timeslot and readyqueue FIFO
    //Round Robin Algorithm
    Scheduling_Instructions(processQueue);


    return 0;
}
