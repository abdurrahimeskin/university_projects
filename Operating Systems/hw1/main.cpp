//Abdurrahim ESKIN
//   2016400387

#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

/**
 * ProcessInf struct is a structure to provide information about processes
 * It includes process arrival time, process code and process name
 */
struct ProcessInf

{
    int arrivalTime;
    string processCode;
    string processName;
    int instructionCount=0;
    // constructor
    ProcessInf(int x1, string a, string b) {
        arrivalTime=x1;
        processCode=a;
        processName=b;
    }

    // Copy constructor
    ProcessInf(const ProcessInf &p2) {
        instructionCount = p2.instructionCount;
        arrivalTime=p2.arrivalTime;
        processCode=p2.processCode;
        processName=p2.processName;
    }

};

int main() {
    string processName;
    string processCode;
    int arrivalTime;
    int time = 0;
    // creates queue named v in ProcessInf structure to keep information which have been read in the file
    queue<ProcessInf> v;

    /**
     * open the definition text file and read it all and assign the values in an order to the object obj
     * and push the objects to the v queue
     */
    ifstream infile;
    infile.open("definition.txt");
    while (!infile.eof())
    {
        infile >> processName >> processCode >> arrivalTime;
        ProcessInf obj(arrivalTime, processCode, processName);
        v.push(obj);
    }
    // closes the file
    infile.close();

    /**
     * create priority queue named pqueue after that push the top of the processes queue to the pqueue
     */
    queue<ProcessInf> pqueue;
    ProcessInf first = v.front();
    v.pop();
    pqueue.push(first);

    string instructionName;
    int instructionTime;

    // open and write the top of the pqueue to the output file
    ofstream myfile;
    myfile.open("output.txt");
    myfile << time << "::HEAD-" << pqueue.front().processName << "-TAIL\n";

    /**
     * until becomes totally empty while loop will work it reads the code file and increase the time execution
     * after that controls the timeline limit, on the other hand saved the incompleted process' instruction and add it to the
     * queue, if a process completed exits the loop
     *

     */
    while (!pqueue.empty()) {

        int executionTime = 0;

        ProcessInf front = pqueue.front();
        pqueue.pop();

        ifstream codeFile;
        codeFile.open( front.processCode);

        int counter=0;

        bool finished=true;
        // reads the code text file and controls the completion of an instruction according to 100 running time
        // execute the instruction until instruction running time becomes equal or bigger tha 100ms
        // if an instruction is not completely executed save its place and while executing again in the same file's instruction continue the last instruction
        while (!codeFile.eof()) {
            counter++;
            codeFile >> instructionName >> instructionTime;
            if(front.instructionCount < counter ) {
                if (executionTime < 100) {
                    front.instructionCount++;
                    executionTime = executionTime + instructionTime;
                } else{
                    finished = false;
                }
            }


        }

        time = time + executionTime;
        //control the process which has came while another process executing
        while (!v.empty()) {
            ProcessInf tempProcess = v.front();
            if (tempProcess.arrivalTime <= time) {
                pqueue.push(tempProcess);
                v.pop();
            } else {
                break;
            }
        }
        //if current process is not completed add it the back of the raedy queue
        if (!finished) {
            pqueue.push(front) ;
        }
        // copy the current situation in the ready to another queue
        queue<ProcessInf> currentReadyQueue = pqueue ;

        // write to the output file
        if(pqueue.empty()){
            myfile << time << "::HEAD--TAIL" << endl ;
        }else {
            myfile << time << "::HEAD-" ;
            while(!currentReadyQueue.empty()){
                myfile << currentReadyQueue.front().processName << "-" ;
                currentReadyQueue.pop() ;
            }
            myfile << "TAIL" ;
        }
    }


    return 0;

}