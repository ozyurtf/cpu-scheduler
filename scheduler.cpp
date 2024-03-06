#include <queue>
#include <iostream>
#include <list>
#include <fstream>
#include <vector> 
#include <iomanip>
#include <cstring>
#include <set> 
#include <algorithm>
using namespace std;

string inputFilePath;
string rfilePath;
string schedulerType = "FCFS";

int timeQuantum;
int maxPrio = 4;
bool printTransition = false;     
bool printAddRmEvent = false;     
bool printReadyQ = false;         
bool printPreemptProcess = false; 

int numDone = 0; 
int ofs = 1;
int IOBusy = 0;
int blockStart = 0;
int blockEnd = 0;

enum stateEnum { 
    READY = 0,
    PREEMPT = 1,
    RUNNG = 2,
    BLOCK = 3,
    Done = 4,
    CREATED = 5} ;

string getState(int stateEnum) {
    switch(stateEnum) {
        case READY:
            return "READY";
        case PREEMPT:
            return "PREEMPT";
        case RUNNG:
            return "RUNNG";
        case BLOCK:
            return "BLOCK";
        case Done:
            return "Done";
        case CREATED:
            return "CREATED";
        default: 
            return "Done";    
    }
};    

vector<int> readRandom(string rfilePath) {
    ifstream file(rfilePath);
    string line;
    vector<int> randVals;
    while (getline(file, line)) {
        randVals.push_back(stoi(line));
    }
    return randVals;
};

int assignRandom(int burst, vector<int> randVals) {
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
        stateEnum state;
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
        CPUWaitTime = 0;
    }
};

queue<PCB*> runQueue;

struct Event {
    public:
        PCB* evtProcess;
        stateEnum oldState;
        stateEnum newState;
        int evtTimeStamp;

    Event(PCB* process, stateEnum transition, int timeStamp) {
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
                 << newState
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
                 << newEvent.newState 
                 << ")" 
                 << ":"
                 << " ";

            printEvents();
            cout << " ==>   ";
        }
        
        if (eventQ.empty()) {
            eventQ.push_front(&newEvent);
        }

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

bool isEmpty(vector<queue<PCB*>> qVec) { 
    bool isEmpty = true;
    for (const auto& q : qVec) {
        if (!q.empty()) {
            isEmpty = false; 
            break;
        }
    }
        
    return isEmpty;
};

struct Scheduler { 
    virtual void addProcess(PCB* pcb) = 0;

    virtual PCB* getNextProcess() = 0;

    virtual bool testPreempt(PCB* unblockedPCB, 
                             PCB* runningPCB, 
                             int currentTime) = 0;

    virtual void printQueues() = 0;

};

struct FCFS: public Scheduler {
    public:
        deque<PCB*> runQ;

    FCFS() {
        deque<PCB*> runQ;
    }

    void addProcess(PCB* pcb) {
        runQ.push_back(pcb);
    };

    PCB* getNextProcess() {
        PCB* nextPCB = nullptr;
        if (!runQ.empty()) {
            nextPCB = runQ.front();
            runQ.pop_front();
        }
        return nextPCB;
    }

    bool testPreempt(PCB* unblockedPCB, PCB* runningPCB, int currentTime) { 
        return false;
    }  

    void printQueues() { 

    }  
};

struct LCFS: public Scheduler {
    public:
        deque<PCB*> runQ;

    LCFS() {
        deque<PCB*> runQ;
    }

    void addProcess(PCB* pcb) {
        runQ.push_back(pcb);
    };

    PCB* getNextProcess() {
        PCB* nextPCB = nullptr;
        if (!runQ.empty()) {
            nextPCB = runQ.back();
            runQ.pop_back();
        }
        return nextPCB;
    }

    bool testPreempt(PCB* unblockedPCB, PCB* runningPCB, int currentTime) { 
        return false;
    } 

    void printQueues() { 
        
    }        
};

struct SRTF: public Scheduler {
    public:
        set<PCB*> runQ;

    SRTF() {
        set<PCB*> runQ;
    }

    void addProcess(PCB* pcb) {
        runQ.insert(pcb);
    };

    PCB* getNextProcess() {
        PCB* nextPCB = nullptr;
        if (!runQ.empty()) {
            
            auto prioritize = [](const PCB* pcb1, const PCB* pcb2) {
                if (pcb1->TC < pcb2->TC) { 
                    return true;
                }

                else if (pcb1->TC == pcb2->TC) { 
                    if (pcb1->stateTimeStamp < pcb2->stateTimeStamp) { 
                        return true;
                    }
                }
                return false;
            };

            nextPCB = *min_element(runQ.begin(), runQ.end(), prioritize);
            runQ.erase(nextPCB);
        }

        return nextPCB;
    }

    bool testPreempt(PCB* unblockedPCB, PCB* runningPCB, int currentTime) { 
        return false;
    }    

    void printQueues() { 
        cout << "SCHED" 
             << " "
             << "(" 
             << runQ.size()
             << ")" 
             << ":" 
             << " ";
        for (PCB* pcb: runQ) { 
            cout << pcb->PID 
                 << ":" 
                 << pcb->stateTimeStamp 
                 << " ";
        };
        cout << endl;
    }
};

struct RR: public Scheduler {
    public:
        queue<PCB*> runQ;

    RR() {
        queue<PCB*> runQ;
    }

    void addProcess(PCB* pcb) {
        runQ.push(pcb);
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

struct PRIO: public Scheduler {
    public:
        vector<queue<PCB*>> activeQVec;
        vector<queue<PCB*>> expiredQVec;

    PRIO() {
        activeQVec = vector<queue<PCB*>>(maxPrio);
        expiredQVec = vector<queue<PCB*>>(maxPrio);
    }

    void addProcess(PCB* pcb) {

        if (pcb->dynamicPriority >= 0) {
            int activeQInd = (maxPrio - 1) - pcb->dynamicPriority;
            activeQVec.at(activeQInd).push(pcb);
        }

        else if (pcb->dynamicPriority < 0) {
            pcb->dynamicPriority = pcb->staticPriority - 1;
            int expiredQInd = (maxPrio - 1) - pcb->dynamicPriority;
            expiredQVec.at(expiredQInd).push(pcb);
        }

    };


    PCB* getNextProcess() {
        PCB* nextPCB = nullptr;

        if (isEmpty(activeQVec)) { 
            activeQVec.swap(expiredQVec);
            if (printReadyQ) { 
                cout << "switched queues" << endl;
            }
        }
        
        if (!isEmpty(activeQVec)) {
            for (queue<PCB*>& activeQ: activeQVec) { 
                if (!activeQ.empty()) { 
                    nextPCB = activeQ.front();
                    activeQ.pop();
                    break;
                }
            }
        }
        return nextPCB;
    }

    bool testPreempt(PCB* unblockedPCB, PCB* runningPCB, int currentTime) { 
        return false;
    }    

    void printQueues() { 
        cout << "{ ";
        
        for (queue<PCB*> activeQ: activeQVec) { 

            if (activeQ.empty()) { 
                cout << "[" 
                     << ""
                     << "]";
            }
            else {    
                queue<PCB*> copyQ = activeQ;

                cout << "[";
                while(!copyQ.empty()) { 
                    cout << copyQ.front()->PID;
                    copyQ.pop();
                    if (!copyQ.empty()){
                        cout << ",";    
                    }                     
                }
                cout << "]";
            }
        }    
        cout << "}" 
             << ": "
             << "{ ";

        for (queue<PCB*> expiredQ: expiredQVec) { 

            if (expiredQ.empty()) { 
                cout << "[" 
                     << ""
                     << "]";
            }
            else { 
                cout << "[" 
                     << expiredQ.front()->PID 
                     << "]";
            }
        }  
        cout << "}"  
             << " " 
             << ":" 
             << endl;          
    }; 
};

struct PREPRIO: public Scheduler {
    public:
        vector<queue<PCB*>> activeQVec;
        vector<queue<PCB*>> expiredQVec;

    PREPRIO() {
        activeQVec = vector<queue<PCB*>>(maxPrio);
        expiredQVec = vector<queue<PCB*>>(maxPrio);
    }

    void addProcess(PCB* pcb) {

        if (pcb->dynamicPriority >= 0) {
            int activeQInd = (maxPrio - 1) - pcb->dynamicPriority;
            activeQVec.at(activeQInd).push(pcb);
        }

        else if (pcb->dynamicPriority < 0) {
            pcb->dynamicPriority = pcb->staticPriority - 1;
            int expiredQInd = (maxPrio - 1) - pcb->dynamicPriority;
            expiredQVec.at(expiredQInd).push(pcb);
        }
    };

    PCB* getNextProcess() {

        PCB* nextPCB = nullptr;
        
        if (isEmpty(activeQVec)) { 
            activeQVec.swap(expiredQVec);
            if (printReadyQ) { 
                cout << "switched queues" << endl;
            }
        }
        
        if (!isEmpty(activeQVec)) {
            for (queue<PCB*>& activeQ: activeQVec) { 
                if (!activeQ.empty()) { 
                    nextPCB = activeQ.front();
                    activeQ.pop();
                    break;
                }
            }
        }
        return nextPCB;
    }

    bool testPreempt(PCB* unblockedPCB, PCB* runningPCB, int currentTime) { 
        int cond1 = 0;
        int cond2 = 0;
        int runningDynamicPriority = runningPCB->dynamicPriority;
        int nextEventTime = runningPCB->nextEventTime;
        bool preemptRunningPCB = false;
        int timeUntilNextEvent = nextEventTime - currentTime;

        if (unblockedPCB->dynamicPriority > runningDynamicPriority) { 
            cond1 = 1;
        }

        if (nextEventTime > currentTime) { 
            cond2 = 1;
        }

        if (cond1 == 1 && cond2 == 1) { 
            preemptRunningPCB = true;
        }

        if (printPreemptProcess) { 
            cout << "    " 
                 << "-->"
                 << " " 
                 << "PrioPreempt" 
                 << " "
                 << "Cond1=" << cond1 
                 << " "
                 << "Cond2=" << cond2 
                 << " "
                 << "(" 
                 << timeUntilNextEvent 
                 << ")" 
                 << " --> ";   

            if (preemptRunningPCB == true) { 
                cout << "YES" << endl;
            }
            
            else if (preemptRunningPCB == false) { 
                cout << "NO" << endl;
            }
        }

        return preemptRunningPCB;
    }

    void printQueues() { 
        cout << "{ ";
        
        for (queue<PCB*> activeQ: activeQVec) { 

            if (activeQ.empty()) { 
                cout << "[" 
                     << ""
                     << "]";
            }
            else {    
                queue<PCB*> copyQ = activeQ;

                cout << "[";
                while(!copyQ.empty()) { 
                    cout << copyQ.front()->PID;
                    copyQ.pop();
                    if (!copyQ.empty()){
                        cout << ",";    
                    }                     
                }
                cout << "]";
            }
        }    
        cout << "}" 
             << ": "
             << "{ ";

        for (queue<PCB*> expiredQ: expiredQVec) { 

            if (expiredQ.empty()) { 
                cout << "[" 
                     << ""
                     << "]";
            }
            else { 
                cout << "[" 
                     << expiredQ.front()->PID 
                     << "]";
            }
        }  
        cout << "}"  
             << " " 
             << ":" 
             << endl;          
    }; 
};

void transition(PCB* pcb, int currentTime, stateEnum oldState, stateEnum newState, 
                vector<int> randVals, string schedulerType) { 
    
    if (oldState == RUNNG && newState == READY) { 
        runQueue.pop();
        pcb->CPUBurst = pcb->CPUBurst - (currentTime - pcb->runStart);
        pcb->TC = pcb->TC - (currentTime - pcb->runStart);  

        if (printTransition)  {    
            
            cout << currentTime 
                 << " " 
                 << pcb->PID 
                 << " " 
                 << currentTime - pcb->runStart
                 << ": " 
                 << getState(oldState)
                 << " -> " 
                 << getState(newState)
                 << " " 
                 << " "
                 << "cb=" << pcb->CPUBurst 
                 << " " 
                 << "rem=" << pcb->TC 
                 << " " 
                 << "prio=" << pcb->dynamicPriority 
                 << endl;
        }
             
        pcb->dynamicPriority--;   
        if (schedulerType == "RR") { 
            pcb->dynamicPriority = pcb->staticPriority - 1;          
        }
    }

    else if (oldState == READY && newState == RUNNG) {  

        pcb->CPUWaitTime = pcb->CPUWaitTime + currentTime - pcb->stateTimeStamp;

        if (pcb->TC <= pcb->CPUBurst) { 
            pcb->CPUBurst = pcb->TC;
        }        

        else if (pcb->CPUBurst == 0) { 
            pcb->CPUBurst = assignRandom(pcb->CB, randVals); 
        }  

        if (pcb->CPUBurst > pcb->TC) { 
            pcb->CPUBurst = pcb->TC;
        }             

        if (printTransition) { 
            cout << currentTime 
                 << " " 
                 << pcb->PID 
                 << " " 
                 << currentTime - pcb->stateTimeStamp 
                 << ": " 
                 << getState(oldState)
                 << " -> " 
                 << getState(newState)
                 << " " 
                 << "cb=" << pcb->CPUBurst
                 << " " 
                 << "rem=" << pcb->TC
                 << " " 
                 << "prio=" << pcb->dynamicPriority
                 << endl;  
        }           
    }

    else if (oldState == RUNNG && newState == BLOCK) {       
        pcb->CPUBurst = pcb->CPUBurst - (currentTime - pcb->runStart);
        pcb->TC = pcb->TC - (currentTime - pcb->runStart);
        runQueue.pop();

        if (pcb->TC != 0) {  

            if (pcb->IOBurst == 0) { 
                pcb->IOBurst = assignRandom(pcb->IB, randVals); 
            }               

            if (printTransition) {
                cout << currentTime 
                     << " " 
                     << pcb->PID 
                     << " " 
                     << currentTime - pcb->stateTimeStamp 
                     << ": " 
                     << getState(oldState)
                     << " -> " 
                     << getState(newState)            
                     << " " 
                     << " "
                     << "ib=" << pcb->IOBurst 
                     << " " 
                     << "rem=" << pcb->TC
                     << endl;
            }

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
            if (printTransition) { 
                cout << currentTime 
                     << " " 
                     << pcb->PID 
                     << " " 
                     << currentTime - pcb->stateTimeStamp 
                     << ": " 
                     << getState(Done)
                     << endl;  
            }            
        }
    }

    else if (oldState == BLOCK && newState == READY) {  

        if (printTransition) { 
            cout << currentTime 
                 << " " 
                 << pcb->PID 
                 << " " 
                 << currentTime - pcb->stateTimeStamp 
                 << ": " 
                 << getState(oldState)
                 << " -> " 
                 << getState(newState)
                 << endl;  
        }

        pcb->IOTime = pcb->IOTime + currentTime - pcb->stateTimeStamp;
        pcb->dynamicPriority = pcb->staticPriority - 1;
        pcb->IOBurst = 0;                          
    }

    else if (newState != Done) { 
        if (printTransition) { 
            cout << currentTime 
                 << " " 
                 << pcb->PID 
                 << " " 
                 << currentTime - pcb->stateTimeStamp 
                 << ": " 
                 << getState(oldState)
                 << " -> " 
                 << getState(newState)
                 << endl; 
        }         
    }
};

int main(int argc, char* argv[]) {
 
    for (int i = 0; i < argc; i++) { 

        string userOption = argv[i];

        if (userOption == "-v") { 
            printTransition = true;
            continue;
        }
            
        else if (userOption == "-t") { 
            printReadyQ = true; 
            continue;
        }  
            
        else if (userOption == "-e") { 
            printAddRmEvent = true;
            continue;
        }    

        else if (userOption == "-p") { 
            printPreemptProcess = true;
            continue;
        }  

        else if (userOption == "-s") { 
            continue;
        }

        else if (userOption.substr(0, 2) == "-s") { 
            size_t sPos = userOption.find("-s");
            userOption.erase(sPos, 2);
        }
        
        if (userOption[0] == 'F') { 
            schedulerType = "FCFS";
            timeQuantum = 10000;
            continue;
        }

        else if (userOption[0] == 'L') { 
            schedulerType = "LCFS";
            timeQuantum = 10000;
            continue;
        }

        else if (userOption[0]  == 'S') { 
            schedulerType = "SRTF";
            timeQuantum = 10000;
            continue;
        }

        else if (userOption[0] == 'R') {
            schedulerType = "RR";
            size_t RPos = userOption.find('R');
            userOption.erase(RPos, 1);

            if (!userOption.empty()) { 
                timeQuantum = stoi(userOption);
            }
            continue;
        }

        else if (userOption[0] == 'P' || userOption[0] == 'E') { 

            if (userOption[0] == 'P'){ 
                schedulerType = "PRIO";
                size_t PPos = userOption.find('P'); 
                userOption.erase(PPos, 1);                
            }

            else if (userOption[0] == 'E') {
                schedulerType = "PREPRIO";
                size_t EPos = userOption.find('E'); 
                userOption.erase(EPos, 1);
            }


            if (!userOption.empty()) { 
                size_t colonPos = userOption.find(':');

                if (colonPos == string::npos) { 
                    timeQuantum = stoi(userOption);
                }   

                else if (colonPos != string::npos) { 
                    timeQuantum = stoi(userOption.substr(0, colonPos));
                    maxPrio = stoi(userOption.substr(colonPos + 1));
                }
            }
            continue;
        }  

        size_t inputPos = userOption.find("input");

        if (inputPos != string::npos) { 
            inputFilePath = userOption;
            continue;
        }

        size_t rfilePos = userOption.find("rfile");

        if (rfilePos != string::npos) { 
            rfilePath = userOption;
            
            continue;
        }
    }

    vector<int> randVals = readRandom(rfilePath);

    queue<PCB*> readyQueue;

    Scheduler* scheduler;

    if (schedulerType == "FCFS") { 
        scheduler = new FCFS();
    }
    else if (schedulerType == "LCFS") { 
        scheduler = new LCFS(); 
    }
    else if (schedulerType == "SRTF") { 
        scheduler = new SRTF();
    }
    else if (schedulerType == "RR") { 
        scheduler = new RR(); 
    }
    else if (schedulerType == "PRIO") { 
        scheduler = new PRIO();
    }
    else if (schedulerType == "PREPRIO") { 
        scheduler = new PREPRIO();
    }


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
        int prio = assignRandom(maxPrio, randVals);
        
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

    while (evt = DES.getEvent()) { 
        PCB* pcb = evt->evtProcess; 
        int currentTime = evt->evtTimeStamp;
        stateEnum oldState = pcb->state;
        stateEnum newState = evt->newState; 
        bool preemptRunningPCB = false;

        if (oldState == PREEMPT) { 
            oldState = READY;
        }

        if (newState == PREEMPT) { 
            newState = READY;
        }
     
        transition(pcb, currentTime, oldState, newState, randVals, schedulerType);
        
        switch(newState) { 

            case READY: {  

                if (oldState == CREATED) { 
                    pcb->startTime = evt->evtTimeStamp;
                }                
                
                if (oldState == CREATED || oldState == BLOCK) { 
                
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
                            
                            continue;              
                        }

                        else if (!preemptRunningPCB) { 
                            pcb->state = READY;
                            pcb->stateTimeStamp = currentTime;
                            scheduler->addProcess(pcb);
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
                    pcb->state = Done;
                    pcb->stateTimeStamp = currentTime;
                    pcb->finishTime = currentTime;
                    pcb->turnAroundTime = pcb->finishTime - pcb->startTime;
                    transition(pcb, currentTime, oldState, Done, randVals, schedulerType);
                    numDone++;
                } 
            }

            case Done: { 
                callScheduler = true;
            }
        };       

        if (callScheduler == true) {

            if (DES.getNextEventTime() == currentTime) {    
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
    
        if (numDone == processNum) { 
            totalSimTime = currentTime;
            break;
        }       
    };

    if (schedulerType == "RR" || schedulerType == "PREPRIO" || schedulerType == "PRIO"){ 
        cout << schedulerType
             << " "
             << timeQuantum
             << endl;
    }
    else { 
        cout << schedulerType
             << endl;        
    }      

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
    double throughput = 100*(double(processNum)/totalSimTime);

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