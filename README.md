**Concurrency**: Executing multiple instructions in an interleaved manner. 

**Parallelism**: Distributing multiple instructions into different resources and running them at the same time in parallel. 

## Inter-Process Communication

In computer, there are programs that basically includes some set of instructions that can handle some specific task. 

These instructions/codes are stored in disk or memory and cannot help us to do what we want directly. Therefore, they should be executed by the processor. 

When these set of instructions are executed, we can call the process of the execution of these instructions as **process**.

In a specific time window, there might be multiple processes that need to work with each other and share resources to be able to finish their executions successfully and efficiently.

In addition, there might be some key points that need attention during this inter-process communication: 

1) The way these processes pass information to each others.
2) Ensuring that two processes don't interfere with each other.
3) Ordering the processes properly if there is a dependency: If process A produces data and process B prints these data, process B has to wait until process A produce data to print.

We have mentioned that sometimes multiple processes can share the same resource. And one of the resource they may share might be the storage (e.g. main memory, shared file). 

Print spooler is a perfect example to this situation. A print stooler is a program that queues the print jobs that are sent from an application to a printer. 
When a process wants to print a file, for example, it enters the name of the file into the spooler directory which is where the information about the file is stored. And another separate process periodically checks if there is any file in spooler directory to be printed. 
If there is a file to be printed, it's printed and then it's file name is removed from the spooler directory.

With this procedure, the print jobs do not need to be sent to the printer directly. The benefit of applying this procedure is that sending print jobs to the printer directly may cause two print jobs to interfere with each other if multiple users are trying to use the printer simultaneously. And by storing the print jobs this way, we may prevent this kind of problem. 

Also, if we wouldn't use spooler directory, processes wouldn't be aware of each other at all.

Using a shared storage like this is cool but it brings another issue: **race condition**. 

**Race Condition**: When two or more processes read from the same resource and also write into the same resource at the same time, the final result depends on the running time of these processes. And we call this condition as **race condition** since the processes are kind of racing with each other to do their tasks.


## Intra-Process Communication

We have mentioned about the processes and inter-process communication. One thing to note is that in processes, there might be multiple smaller units of execution and we call these units **threads**. In a process, if there are multiple threads, these threads work together and share the same resources. Therefore, there should be some kind of communication between them as well. 

And the three key points that we emphasized in inter-process communications and that need attention are valid in here as well: 

1) The way these threads pass information to each others.
2) Ensuring that two threads don't interfere with each other.
3) Ordering the threads properly if there is a dependency.

Until now we have talked about scenarios in which multiple entities access/share/modify the shared resources simultaneously. This situation may (and will) end up with many problems if it is not handled properly.

And the **Read-Modify-Write Cycles** is a concept that are useful to explain before going through different solutions for preventing these problems. 

## Read-Modify-Write Cycles

When multiple processes or threads are accessing/sharing/modifying the shared data, a specific sequence of operations must be performed in order to ensure data consistency and integrity. This sequence of operations is what we call **Read-Modify-Write Cycle**. The goal is for the code to reach consistent/same view of the data. 

**Read**: Reading the current value of a memory location from the memory is called **read**.
**Modify**: Some operation is performed on the value that was read from a memory location and this is called **modify**. 
**Write**: The modified value is written back to the same memory location from where the value was read in the first step before modification.

One note is that some parts of this cycle should be atomic. Otherwise, we may end up with race conditions and data inconsistency.

The main way to prevent race conditions is to prevent more than one process or thread from reading and writing the shared data at the same time. In other words, if one process or thread uses a shared variable or file, the other processs or threads should be excluded from doing the same thing and we call this **mutual exclusion**.

And the section of the program/codes in which shared resources are accessed is called **critical region**. 

If can develop a system in which two or more processes never be within their critical regions at the same time, we can prevent races. But the issue is that if we develop the system with this way (in other words if we only try to prevent multiple processes from being in their critical regions at the same time) we prevent races but this also prevents parallel processes to cooperate correctly and to use shared resources efficiently. 

So to prevent the races in a more efficient and better way, we should have these additional 3 conditions: 

1) We shouldn't take the speed or the number of CPUs into account. (Not relying on assumptions about the speed of processors or the number of them helps us to develop a system that can be used in different configurations)
2) If there is a process running outside its critical region, it shouldn't block any process. (This will ensure that processes do not block each other unnecessarily when they are not accessing shared resources)
3) There should be no process that is waiting to enter its critical region forever. (This will prevent starvation)

in addition to the first condition that we defined previously 

4) Two processes should not be in their critical regions at the same time.

Now let's try to find a method that can meet all of these four conditions. 

## Mutual Exclusion with Busy Waiting

Continuously waiting and testing to see if a condition is met is called **busy waiting**. And this waiting process wastes the CPU time. That's why it should be avoided if possible. 

**Interrupts:** Let's say that there is a process A that is currently in it's critical region. One of the conditions of preventing races was to exclude all other processes to enter their critical regions while process A is in it's critical region. The simplest way to do this is using interrupts. So, if process A disables all the interrupts just after it enters it's critical region and then re-enable these interrupts just before leaving the critical region, it can access/modify the shared memory without the fear of intervention. 

But using only this approach is not a good option because disabling interrupts will affect only the CPU that executed the process A (because process A was the one that disabled interrupts in our example). In this case, there is no reason for the processes in other CPUs to intervene the process A and enter their own critical regions while the process A is in it's critical region. 

**Lock Variables:** This is another way to handle mutual exclusion. Instead of interrupts, we use a variable, which we call lock variable, that takes a value of 0 or 1. 

If the process A enter it's critical region, it sets this lock variable as 1 which basically means that the critical section is occupied at this moment. And if other processes try to enter their critical regions, they will see that lock variable is 1 and they will have to wait until it is set to 0 (which means the critical region is left and one process can now enter it's own critical region).

But when we use just lock variables, we might encounter with the problem that we observe with print spooler. Sometimes two processes can see the lock variable as 0 at the same time and as a result, they can both enter their critical regions simultaneously. 

**Peterson's Solution for Achieving Mutual Exclusion**: Let's say that there are two processes: 

```
Process A:

while (TRUE) {
  while (turn!=0) {} // Wait until turn = 0
  critical_region();
  turn = 1;
  noncritical_region();
}
```

```
Process B:

while (TRUE) {
  while (turn!=1) {} // Wait until turn = 1
  critical_region();
  turn = 0;
  noncritical_region();
}
```

When process A leaves the critical region, it sets turn variable to allow the process B to enter it's critical region. 
Suppose that process B finishes its critical region quickly. After that, the turn variable will be set to 0 and both process A and process B will be in their non critical regions. 
If process A executes it's loop again, enters the critical region, and sets the turn variable as 1, and enters it's non critical region, both process A and B will be in their 
non critical regions and turn variable will  equal to 1. At that moment, if process A finishes it's non-critical region and goes back to the top of it's loop, 
it won't be permitted to enter it's critical region because turn=1. 

That's why, this kind of procedure is not a good solution because it violates the 3rd condition that we defined previously: 

1) We shouldn't take the speed or the number of CPUs into account. (Not relying on assumptions about the speed of processors or the number of them helps us to develop a system that can be used in different configurations)
2) **If there is a process running outside its critical region, it shouldn't block any process. (This will ensure that processes do not block each other unnecessarily when they are not accessing shared resources)**
3) There should be no process that is waiting to enter its critical region forever. (This will prevent starvation)
4) Two processes should not be in their critical regions at the same time.

So, let's take a look at the **Peterson's solution** for achieving mutual exclusion:

```
#define FALSE 0
#define TRUE 1
#define N 2

int turn;          
int interested[N]; // interested = [. , .]

void enter_region(int process) {
  int other;

  other = 1 - process; // Other process. If the current process is 0, other process will be 1. If current process is 1, other process will be 0.

  turn = process;      // Which process' turn to enter it's critical region ?

  while (turn == process && interested[other] == TRUE) {} // If it's current process turn and and the other process is in it's critical region, keep waiting until the other process leaves it's critical region.

}

void leave_region(int process) {
  interested[process] = FALSE;  
}

```

The other methods that are used to do ensure mutual exclusion and prevent race condition are called Test and Set Lock and XCHG:

**TSL (Test and Set Lock)**: 

```
enter_region:
  TSL REGISTER, LOCK | Reads the value of the lock into the register and sets the lock variable to 1 
  CMP REGISTER, #0   | Compares the value in the register with 0. 
  JNE enter_region   | If the value in the register is not 0, this means that the another process already locked the variable and it is currently in it's critical region. That's why this process keeps waiting until the other process that locked the variable unlock it and leaves it's critical region.
  RET                | If the value in register is 0, this means that the lock is available, and no other process is in it's critical region right now. And therefore this function returns allowing the process to enter it's critical region.

leave_region:
  MOVE_LOCK, #0      | Stores the value of 0 in the lock variable and releases the lock.
  RET                | Returns, allowing other threads to attempt to acquire the lock.
```  
  
**XCHG**: 

```
enter_region:
  MOVE REGISTER, #1
  XCHG REGISTER, LOCK  
  JNE enter_region   
  RET                

leave_region:
  MOVE_LOCK, #0      
  RET                
```  












