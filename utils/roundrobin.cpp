#include <queue>
#include <iostream>
#include <list>
#include <fstream>
#include <vector> 
#include <iomanip>
#include <cstring>

using namespace std;

string inputFilePath = "/Users/ozyurtf/Documents/ms-cs/spring-2024/operating-systems/labs/lab2/lab2_assign/input7";

// ATTENTION: MAX PRIO IS 4 BY DEFAULT. CHECK THE OTHER DEFAULTS PARAMETERS.
string schedulerType = "RR";
int timeQuantum = 10;
int maxPrio = 4;
bool printTransition = true;
bool printAddRmEvent = true; 
bool printReadyQ = true;
bool printPreemptProcess = true;

int numDone = 0;
int ofs = 0;
int IOBusy = 0;
int blockStart = 0;
int blockEnd = 0;

// ATTENTION: USE THIS IN A BETTER WAY.
enum stateEnum { 
    READY = 0,
    PREEMPT = 1,
    RUNNG = 2,
    BLOCK = 3,
    DONE = 4,
    CREATED = 5} ;

string getState(int stateEnum) {
    switch(stateEnum) {
        case 0:
            return "READY";
        case 1:
            return "PREEMPT";
        case 2:
            return "RUNNG";
        case 3:
            return "BLOCK";
        case 4:
            return "DONE";
        case 5:
            return "CREATED";
        default: 
            return "DONE";    
    }
};    

vector<int> readRandom(string rfilePath) {
    ifstream file(rfilePath);
    string line;
    bool firstLineSkipped = false;
    vector<int> randVals;
    while (getline(file, line)) {
        if (!firstLineSkipped) {
            firstLineSkipped = true;
            continue;
        }
        randVals.push_back(stoi(line));
    }
    return randVals;
};

string rfilePath = "/Users/ozyurtf/Documents/ms-cs/spring-2024/operating-systems/labs/lab2/lab2_assign/rfile";
vector<int> randVals = readRandom(rfilePath);

// ATTENTION: Don’t assume that the rfiles have a well-known length → test with different, 
// there is reason why the first number in rfile is the total number of randfiles so you can dynamically allocate the array/vector 
int assignRandom(int burst) {
    // cout << "~~~~~ ASSIGNED: " << randVals[ofs] << " is used! ~~~~~~"  << endl;
    // ATTENTION: BE SURE THAT THE THIS IS RESET CORRECTLY.
    if (ofs > randVals[0]) { 
        ofs = 1;
    }

    int randVal = 1 + (randVals[ofs] % burst);
    ofs++;
    return randVal;
}


struct PCB {
    public:
        int PID;
        int AT;
        int TC;
        int TCInit;
        int CB;
        int CPUBurst;
        int IB;
        int IOBurst;
        int staticPriority;
        int dynamicPriority;
        int state;
        int stateTimeStamp;
        int nextEventTime;
        int runStart;
        int startTime;
        int finishTime;
        int turnAroundTime;
        int IOTime;
        int CPUWaitTime;

    PCB(int processID, int arrivalTime, int totalCPU, int CPB, int IOB, int staticPrio) {
        PID = processID;
        AT = arrivalTime;
        TC = totalCPU;
        TCInit = totalCPU;
        CB = CPB;
        CPUBurst = 0;
        IB = IOB;
        IOBurst = 0;
        staticPriority = staticPrio;
        dynamicPriority = staticPrio - 1;
        state = CREATED;
        stateTimeStamp = arrivalTime;
        nextEventTime = 0;
        IOTime = 0;
    }
};

queue<PCB*> runQueue;

struct Event {
    public:
        PCB* evtProcess;
        int oldState;
        int newState;
        int evtTimeStamp;

    Event(PCB* process, int transition, int timeStamp) {
        evtProcess = process;
        oldState = process->state;
        newState = transition;
        evtTimeStamp = timeStamp;
    }
};

struct DESLayer {

    public:
        list<Event*> eventQ;

    DESLayer(list<Event*>& evtQ) {
        eventQ = evtQ;
    }

    void printEvents() { 
        for (Event* event : eventQ) {
            int evtTimeStamp = event->evtTimeStamp;
            int PID = event->evtProcess->PID;
            int newState = event->newState;

            cout << evtTimeStamp 
                 << ":" 
                 << PID 
                 << ":" 
                 << getState(newState) 
                 << " ";
        }
    }    

    void addEvent(Event& newEvent) { 
        if (printAddRmEvent) {
            cout << "  " 
                << "AddEvent" 
                << "("
                << newEvent.evtTimeStamp 
                << ":" 
                << newEvent.evtProcess->PID 
                << ":" 
                << getState(newEvent.newState) 
                << ")" 
                << ":"
                << " ";

            printEvents();
            cout << " ==>   ";
        }
        
        if (eventQ.empty()) {
            eventQ.push_front(&newEvent);
        }

        // ATTENTION: BE SURE THAT THE EVENTS ARE PROCESSED IN CORRECT ORDER
        else if (!eventQ.empty()) {
            for (list<Event*>::iterator it = eventQ.begin(); it != eventQ.end(); it++) {

                if (newEvent.evtTimeStamp > (*it)->evtTimeStamp) {

                    if (next(it) != eventQ.end()) {
                        continue;
                    }

                    else if (next(it) == eventQ.end()) {
                        eventQ.push_back(&newEvent);
                    }
                    
                    break;
                }

                else if (newEvent.evtTimeStamp == (*it)->evtTimeStamp) {

                    if (next(it) == eventQ.end()) { 
                        eventQ.insert(next(it), &newEvent);
                        break;
                    }
                    else { 
                        continue;
                    }

                }
                
                else if (newEvent.evtTimeStamp < (*it)->evtTimeStamp) {
                    eventQ.insert(it, &newEvent);
                    break;
                }
            }
        }

        if (printAddRmEvent) { 
            printEvents();
            cout << endl; 
        }
    }

    Event* getEvent() {
        Event* event = eventQ.front();
        eventQ.pop_front();
        return event;
    }

    void rmEvent(PCB* pcb) {

        for (Event* event: eventQ) { 

            if (event->evtProcess->PID == pcb->PID) { 
                
                if (printAddRmEvent) {
                    cout << "RemoveEvent"
                        << "(" 
                        << event->evtProcess->PID 
                        << ")" 
                        << ": ";

                    printEvents();
                }

                eventQ.remove(event);

                if (printAddRmEvent) { 
                    cout << " ==> ";
                    printEvents();
                    cout << endl;
                }
                
                break;
            }
        }
    }

    int getNextEventTime() {
        if (!eventQ.empty()) { 
            return eventQ.front()->evtTimeStamp;
        }
        else { 
            return -1;
        }
    }

};

struct Scheduler {
    public:
        // ATTENTION: BE SURE THAT THESE WON'T TAKE TO MUCH TIME AND 
        // IT WAS RIGHT TO USE VECTOR. 
        // ALSO CHECK THE OTHER CONTAINERS TO BE SURE THAT 
        // THEY ARE THE CORRECT ONES.
        queue<PCB*> runQ;

    Scheduler() {
        queue<PCB*> runQ;
    }

    void addProcess(PCB* pcb) {
        runQ.push(pcb);

    };

    bool isEmpty(vector<queue<PCB*>> qVec) { 
        return false;

    };

    PCB* getNextProcess() {

        PCB* nextPCB = nullptr;
        
        if (!runQ.empty()) {
            nextPCB = runQ.front();
            runQ.pop();
        }
        
        return nextPCB;
    }

    bool testPreempt(PCB* unblockedPCB, PCB* runningPCB, int currentTime) { 
        return false;
    }

    void printQueues() { 
    }
};

void transition(PCB* pcb, int currentTime, string oldState, string newState) { 
    
    if (oldState == "RUNNG" && newState == "READY") { 
        runQueue.pop();
        pcb->CPUBurst = pcb->CPUBurst - (currentTime - pcb->runStart);
        pcb->TC = pcb->TC - (currentTime - pcb->runStart);     
        
        cout << currentTime 
             << " " 
             << pcb->PID 
             << " " 
             << currentTime - pcb->stateTimeStamp 
             << ": " 
             << oldState
             << " -> " 
             << newState;             
        
        cout << " " 
             << "cb=" << pcb->CPUBurst 
             << " " 
             << "rem=" << pcb->TC 
             << " " 
             << "prio=" << pcb->dynamicPriority 
             << endl;
             
        pcb->dynamicPriority--;
        pcb->dynamicPriority = pcb->staticPriority - 1;   
    }

    else if (oldState == "READY" && newState == "RUNNG") {  

        pcb->CPUWaitTime = pcb->CPUWaitTime + currentTime - pcb->stateTimeStamp;

        if (pcb->TC <= pcb->CPUBurst) { 
            pcb->CPUBurst = pcb->TC;
        }        

        else if (pcb->CPUBurst == 0) { 
            pcb->CPUBurst = assignRandom(pcb->CB); 
        }  

        if (pcb->CPUBurst > pcb->TC) { 
            pcb->CPUBurst = pcb->TC;
        }     

        cout << currentTime 
             << " " 
             << pcb->PID 
             << " " 
             << currentTime - pcb->stateTimeStamp 
             << ": " 
             << oldState
             << " -> " 
             << newState;    

        cout << " " 
             << "cb=" << pcb->CPUBurst
             << " " 
             << "rem=" << pcb->TC
             << " " 
             << "prio=" << pcb->dynamicPriority
             << endl;             
    }

    else if (oldState == "RUNNG" && newState == "BLOCK") {       
        pcb->CPUBurst = pcb->CPUBurst - (currentTime - pcb->runStart);
        pcb->TC = pcb->TC - (currentTime - pcb->runStart);
        runQueue.pop();

        if (pcb->TC != 0) {  

            if (pcb->IOBurst == 0) { 
                pcb->IOBurst = assignRandom(pcb->IB); 
            }               

            cout << currentTime 
                 << " " 
                 << pcb->PID 
                 << " " 
                 << currentTime - pcb->stateTimeStamp 
                 << ": " 
                 << oldState
                 << " -> " 
                 << newState;             
            
            cout << " " 
                 << "ib=" << pcb->IOBurst 
                 << " " 
                 << "rem=" << pcb->TC
                 << endl;

            if (currentTime > blockEnd) { 
                blockStart = currentTime;
                blockEnd = currentTime + pcb->IOBurst;   
                IOBusy = IOBusy + blockEnd - blockStart;
            }

            else if (currentTime <= blockEnd && currentTime + pcb->IOBurst > blockEnd) { 
                IOBusy = IOBusy + currentTime + pcb->IOBurst - blockEnd;
                blockStart = currentTime; 
                blockEnd = currentTime + pcb->IOBurst;                
            }                   
        }

        else if (pcb->TC == 0) { 
            cout << currentTime 
                 << " " 
                 << pcb->PID 
                 << " " 
                 << currentTime - pcb->stateTimeStamp 
                 << ": " 
                 << "DONE"
                 << endl;              
        }
    }

    else if (oldState == "BLOCK" && newState == "READY") {  

        cout << currentTime 
             << " " 
             << pcb->PID 
             << " " 
             << currentTime - pcb->stateTimeStamp 
             << ": " 
             << oldState
             << " -> " 
             << newState
             << endl;  

        pcb->IOTime = pcb->IOTime + currentTime - pcb->stateTimeStamp;
        pcb->dynamicPriority = pcb->staticPriority - 1;
        pcb->IOBurst = 0;
    }

    else if (newState != "DONE") { 

       cout << currentTime 
            << " " 
            << pcb->PID 
            << " " 
            << currentTime - pcb->stateTimeStamp 
            << ": " 
            << oldState
            << " -> " 
            << newState
            << endl;          
    }
};

int main() {

    queue<PCB*> readyQueue;
    Scheduler* scheduler = new Scheduler;

    list<Event*> eventQ;
    DESLayer DES(eventQ);

    Event* evt; 
    
    bool callScheduler = false;    
    double totalSimTime;
    int processNum = 0; 

    ifstream inputFile(inputFilePath);
    string line;

    queue<PCB*> processQ;

    while (getline(inputFile, line)) {
        vector<int> PCBInputs;

        PCBInputs.push_back(processNum);
        int prio = assignRandom(maxPrio);
        
        char * lineChar = new char[line.length() + 1];
        strcpy(lineChar, line.c_str());
        char * token = strtok(lineChar, " \t");
        while (token != NULL) {
            PCBInputs.push_back(stoi(token));
            token = strtok(NULL, " \t");
            continue;
        }

        delete lineChar;
        
        PCBInputs.push_back(prio);

        PCB* pcb = new PCB(PCBInputs[0], PCBInputs[1], PCBInputs[2], PCBInputs[3], PCBInputs[4], PCBInputs[5]);
        processQ.push(pcb);

        Event* event = new Event(pcb, READY, PCBInputs[1]); 
        DES.addEvent(*event);
        processNum++;
    }

    int iter = 0;

    while (evt = DES.getEvent()) { 
        PCB* pcb = evt->evtProcess; 
        int currentTime = evt->evtTimeStamp;
        int oldState = pcb->state;
        int newState = evt->newState; 
        bool preemptRunningPCB = false;
        
        if (oldState == 1) { 
            oldState = 0;
        }

        if (newState == 1) { 
            newState = 0;
        }
     
        transition(pcb, currentTime, getState(oldState), getState(newState));
        
        switch(newState) { 

            case READY: {  

                if (getState(oldState) == "CREATED") { 
                    pcb->startTime = evt->evtTimeStamp;
                }                
                
                if (getState(oldState) == "CREATED" || getState(oldState) == "BLOCK") { 
                
                    if (!runQueue.empty()) { 

                        PCB* runningPCB = runQueue.front();
                        preemptRunningPCB = scheduler->testPreempt(pcb, 
                                                                   runningPCB,
                                                                   currentTime); 

                        if (preemptRunningPCB) { 
                            
                            pcb->state = READY;
                            pcb->stateTimeStamp = currentTime;
                            scheduler->addProcess(pcb);                            

                            DES.rmEvent(runningPCB); 
                            
                            runningPCB->stateTimeStamp = currentTime;
                            runningPCB->nextEventTime = currentTime;  
                            
                            Event* event = new Event(runningPCB, PREEMPT, currentTime);
                            DES.addEvent(*event);   
                            
                            cout << endl;
                            continue;              
                        }

                        else if (!preemptRunningPCB) { 
                            pcb->state = READY;
                            pcb->stateTimeStamp = currentTime;
                            scheduler->addProcess(pcb);
                            cout << endl;
                            continue;
                        }
                    }
                }                  

                pcb->state = READY;
                pcb->stateTimeStamp = currentTime;    
                
                scheduler->addProcess(pcb);
                callScheduler = true; 
                break;
            }

            case PREEMPT: { 
                runQueue.pop();
                
                pcb->state = READY;
                pcb->stateTimeStamp = currentTime;                  
                
                scheduler->addProcess(pcb);                           
                callScheduler = true;
                break;
            }

            case RUNNG: {  
 
                int minRemaining = min(timeQuantum, pcb->CPUBurst);
                int nextEventTime = currentTime + minRemaining;

                pcb->state = RUNNG;
                pcb->stateTimeStamp = currentTime;
                pcb->runStart = currentTime;
                pcb->nextEventTime = nextEventTime;

                runQueue.push(pcb);                

                if (pcb->CPUBurst > minRemaining && pcb->TC > timeQuantum) {      
                    Event* event = new Event(pcb, PREEMPT, nextEventTime);
                    DES.addEvent(*event);
                }

                else if (pcb->CPUBurst == minRemaining || pcb->TC <= timeQuantum) {
                    Event* event = new Event(pcb, BLOCK, nextEventTime);
                    DES.addEvent(*event);                                                        
                }
                break; 
            } 

            case BLOCK: {   

                if (pcb->TC != 0){

                    pcb->state = BLOCK;
                    pcb->stateTimeStamp = currentTime;  
                    
                    Event* event = new Event(pcb, READY, currentTime + pcb->IOBurst);
                    DES.addEvent(*event);     

                    callScheduler = true;                 
                    break;
                }

                else if (pcb->TC == 0) { 
                    pcb->state = DONE;
                    pcb->stateTimeStamp = currentTime;
                    pcb->finishTime = currentTime;
                    pcb->turnAroundTime = pcb->finishTime - pcb->startTime;
                    transition(pcb, currentTime, getState(oldState), getState(DONE));
                    numDone++;
                } 
            }

            case DONE: { 
                callScheduler = true;
            }
        };       

        if (callScheduler == true) {

            if (DES.getNextEventTime() == currentTime) {    
                cout << endl;
                continue; 
            }

            callScheduler = false;

            if (pcb == nullptr) {
                pcb = scheduler->getNextProcess();
                if (pcb == nullptr) {
                    continue;
                }
            }
 
            if (printReadyQ) { 
                scheduler->printQueues();
            }
    
            PCB* nextPCB = scheduler->getNextProcess();

            if (nextPCB!=nullptr) { 
                Event* event = new Event(nextPCB, RUNNG, currentTime); 
                DES.addEvent(*event);  
                nextPCB = nullptr;  
            }            
        }

        iter++;
    
        if (numDone == processNum) { 
            totalSimTime = currentTime;
            break;
        }   

        cout << endl;     
    };

    cout << schedulerType 
         << " "
         << timeQuantum
         << endl;

    vector<vector<int>> summary;
    vector<double> sum(6);

    int CPUBusy = 0; 
    int totalTAT = 0;
    int totalWait = 0;    

    while (!processQ.empty()) { 
        summary.push_back({processQ.front()->AT,
                           processQ.front()->TCInit,
                           processQ.front()->CB,
                           processQ.front()->IB,
                           processQ.front()->staticPriority,
                           processQ.front()->finishTime,
                           processQ.front()->turnAroundTime,
                           processQ.front()->IOTime,
                           processQ.front()->CPUWaitTime
        });

        CPUBusy += processQ.front()->TCInit;
        totalTAT += processQ.front()->turnAroundTime;
        totalWait += processQ.front()->CPUWaitTime;
 
        delete processQ.front();
        processQ.pop();
    }

    double CPUtil = 100*(CPUBusy)/totalSimTime;
    double IOUtil = 100*(IOBusy)/totalSimTime;
    double avgTAT = totalTAT/double(processNum);
    double avgWait = totalWait/double(processNum);
    double throughput = 100*(processNum/totalSimTime);

    sum = {totalSimTime, 
           CPUtil,
           IOUtil,
           avgTAT, 
           avgWait,                 
           throughput};    

    for (int i = 0; i < processNum; ++i) {
        int zerosToAdd = 4 - to_string(i).length();
        cout << string(zerosToAdd, '0') << i << ": ";
        for (int j = 0; j < 4; ++j) {
            cout << setw(4) 
                 << summary[i][j] 
                 << " ";
        }

        cout << setw(1) 
             << summary[i][4] 
             << " ";        

        cout << "|";
        
        for (int j = 5; j < 9; ++j) {
            cout << setw(6) 
                 << summary[i][j];
        }
        cout << endl;
    }

    cout << "SUM: ";
    for (int i = 0; i < 6; ++i) {
        if (i == 0) {
            cout << sum[i] 
                 << " ";
        } 
        
        else if (i != 5) { 
            printf("%.2f ", sum[i]);
        }

        else if (i == 5) { 
            printf("%.3f\n", sum[i]);
        }

    }
              
    delete scheduler;
    while (!eventQ.empty()) { 
        delete eventQ.front();
        eventQ.pop_front();
    }

    return 0;
}