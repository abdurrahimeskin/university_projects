//2016400387-Abdurrahim ESKİN
//CMPE322-PROJECT2
//STATUS:WORKING
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
   //to understand the semaphores emptiness i used an array and assigned false value to entire array
    bool semIsuseing[10];
    for(int i = 0; i < 10; i++){
            semIsuseing[i]=false;
    }
    //if a semaphore in usage it can also called by different processes at the same time, to keep the index information i used an array
    queue<ProcessInf> ifSemisusing[10];
    queue<ProcessInf> temp;
    //
    for(int i = 0; i < 10; i++){
        ifSemisusing[i]=temp;
    }

    // creates queue named in ProcessInf structure to keep information which have been read in the file
    queue<ProcessInf> v;

    /**
     * open the definition text file and read it all and assigns the values in an order to the object obj
     * and push the objects to the queue
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
     * create priority queue named pqueue after that assign the top of the process queue to the pqueue
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
     * until becomes totally empty while loop will work
     *

     */
    while (!pqueue.empty()) {

        int executionTime = 0;
        //i need the information while different processess called the same semaphore to keep time information i used semTime
        int semTime=0;
        ProcessInf front = pqueue.front();
        pqueue.pop();

        ifstream codeFile;
        codeFile.open( front.processCode);

        int counter=0;
        string a;
        int semcode;

        bool finished=true;

        bool isWait=false;

        /*
          * reads the code text file and controls the completion of an instruction according to 100 running time
          * execute the instruction until instruction running time becomes equal or bigger than 100ms
          * if an instruction is not completely executed save its place and while executing again in the same file's instruction continue the last instruction
          * first of all, the process will have been executed, but at the same time i controlled the situation of the semaphore whether it is using by another processes
          * if it is using by another processess the next process will be on another queue
          * while a process is executing if its gone to a semaphore initially i take the semaphore number to reach the index i keep the semaphore's usage information according to
          * its number at semIsuseing array and if a process get into a semaphore according to its number i changed the semIsuseing array index boolean situation
          * on the other hand if any process called a semaphore i controlled semaphore situation in semIsuseing array index if its true that means the semaphore is using by another
          * process or processes are waiting for the semaphore and i poped that processes the process from the ready queue, in that case i push the process or processes
          * according to semaphore number into ifSemisusing array that keep queues inside.
          * while that operations have been executing i controlled time line and whether a process exit the semaphore and controlled the emptiness of the semaphore waiting queue from
          * if ifSemisusing array is i changed the situation of the semIsuseing and pushed the process into readyqueue again
        */
        while (!codeFile.eof()) {
            counter++;
            codeFile >> instructionName >> instructionTime;

            if(front.instructionCount < counter ) {

                if (executionTime < 100 && !isWait) {
                    front.instructionCount++;
                    executionTime = executionTime + instructionTime;
                    if(instructionName.substr(0,1)=="w"){
                        semTime=time+executionTime;
                        a = instructionName.substr(instructionName.length()- 1);
                        semcode = stoi(a);
                        if(semIsuseing[semcode]==false){
                            semIsuseing[semcode]=true;
                        } else{
                            isWait=true;
                            ifSemisusing[semcode].push(front);


                            // copy the current situation in the ready to another queue
                            queue<ProcessInf> currReadyQueue = pqueue ;

                            // write to the output file
                            if(pqueue.empty()){
                                myfile << semTime << "::HEAD--TAIL" << endl ;
                            }else {
                                myfile << semTime << "::HEAD-" ;
                                while(!currReadyQueue.empty()){
                                    myfile << currReadyQueue.front().processName << "-" ;
                                    currReadyQueue.pop() ;
                                }
                                myfile << "TAIL"<< endl;
                            }


                            ofstream semFile;
                            semFile.open("output_"+ a+ ".txt", ofstream::app);
                            // copy the current situation in the ready to another queue
                            queue<ProcessInf> currSemQueue = ifSemisusing[semcode] ;

                            // write to the output file

                            semFile << semTime << "::HEAD-" ;
                            while(!currSemQueue.empty()){
                                semFile << currSemQueue.front().processName << "-" ;
                                currSemQueue.pop() ;
                            }
                            semFile << "TAIL"<< endl;



                        }

                    }
                    else if(instructionName.substr(0,1)=="s"){
                        a=instructionName.substr(instructionName.length()-1);
                        semcode=stoi(a);
                        semTime=time+executionTime;
                        if (!ifSemisusing[semcode].empty()){
                            ProcessInf waitQfront=ifSemisusing[semcode].front();
                            pqueue.push(waitQfront);

                            ifSemisusing[semcode].pop();



                            // copy the current situation in the ready to another queue
                            queue<ProcessInf> currReadyQueue = pqueue ;

                            // write to the output file
                            if(pqueue.empty()){
                                myfile << semTime << "::HEAD--TAIL" << endl ;
                            }else {
                                myfile << semTime << "::HEAD-" << front.processName<< "-";
                                while(!currReadyQueue.empty()){
                                    myfile << currReadyQueue.front().processName << "-" ;
                                    currReadyQueue.pop() ;
                                }
                                myfile << "TAIL"<< endl;
                            }


                            ofstream semFile;
                            semFile.open("output_"+ a+ ".txt", ofstream::app);
                            // copy the current situation in the ready to another queue
                            queue<ProcessInf> currSemQueue = ifSemisusing[semcode] ;

                            // write to the output file
                            if(ifSemisusing[semcode].empty()){
                                semFile<< semTime << "::HEAD--TAIL" << endl;
                            }else{
                                semFile << semTime << "::HEAD-" ;
                                while(!currSemQueue.empty()){
                                    semFile << currSemQueue.front().processName << "-" ;
                                    currSemQueue.pop() ;
                                }
                                semFile << "TAIL"<< endl;
                            }
                        } else{
                            semIsuseing[semcode]=false;
                        }
                    }
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
        if (!finished && !isWait) {
            pqueue.push(front) ;
        }

        if(!isWait){
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
              myfile << "TAIL"<< endl;
          }
        }
    }


    return 0;

}
