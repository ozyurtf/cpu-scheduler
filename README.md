**Concurrency**: Executing multiple instructions in an interleaved manner. 

**Parallelism**: Distributing multiple instructions into different resources and running them at the same time in parallel. 

**Inter-Process Communication**: In computer, there are programs that basically includes some set of instructions that can handle some specific task. 

These instructions/codes are stored in disk or memory and cannot help us to do what we want directly. Therefore, they should be executed by the processor. 

And these set of instructions are executed, and we can call the process of the execution of these instructions as **process**.

In a specific time window, there might be multiple processes that need to work with each other and share resources to be able to finish the execution of the instructions successfully. 

One note is that there might be some key points that need attention during this inter-process communication: 

1) The way these processes pass information to each others.
2) Ensuring that two processes don't interfere with each other.
3) Ordering the processes properly if there is a dependency: If process A produces data and process B prints these data, process B has to wait untl process A produce data to print.

We have mentioned that sometimes multiple processes can share the same resource. And one of the resource they may share might be storage (e.g. main memory, shared file). 

Print spooler is a perfect example to this situation. A print stooler is a program that queues the print jobs that are sent from an application to a printer. 
When a process wants to print a file, for example, it inters the name of the file into the spooler directory. And another separate process periodically checks if there is any file in spooler directory to be printed. 
If there is a file to be printed, it's file name is removed from the spooler directory and printed.

With this procedure, the print jobs do not need to be sent to the printer directly. The benefit of applying this procedure is that 
sending print jobs to the printer directly may cause two print jobs to interfere with each other if multiple users are trying to use the printer simultaneously. And by storing the print jobs this way, 
we may prevent this kind of problem. 

Also, if we wouldn't use spooler directory, processes wouldn't be aware of each other at all.

One note is that using a shared storage like this brings another issue: **race condition**. 

**Race Condition**: When two or more processes read from the same resource and also write into the same resource at the same time, the final result depends on the running time of these processes. And we call this condition as **race condition**.

**Intra-Process Communication:** We have mentioned about the processes and inter-process communication. One thing to note is that in processes, there might be multiple smaller units of execution and we call these units **threads**. In a process, if there are multiple threads, these threads work together and share the same resources. Therefore, there should be some kind of communication between them as well. 

And the three key points that we emphasized in inter-process communications and that need attention are valid in here as well: 

1) The way these threads pass information to each others.
2) Ensuring that two threads don't interfere with each other.
3) Ordering the threads properly if there is dependency.

Until now we have talked about scenarios in which multiple entities access/share/modify the shared resources simultaneously. This situation may (and will) end up with many problems it is not handled properly.

And the **Read-Modify-Write Cycles** is a concept that are useful to address these potential problems. 

**Read-Modify-Write Cycles:** When multiple processes or threads are accessing/sharing/modifying the shared data, a specific sequence of operations must be performed in order to ensure data consistency and integrity. This sequence of operations is what we call **Read-Modify-Write Cycle**. The goal is for the code to reach consistent/same view of the data. 

**Read**: Reading the current value of a memory location from the memory is called **read**.
**Modify**: Some operation is performed on the value that was read from a memory location and this is called **modify**. 
**Write**: The modified value is written back to the same memory location from where the value was read in the first step before modification.

One note is that some parts of this cycle should be atomic. Otherwise, we may end up with race conditions and data inconsistency.

The main way to prevent race conditions is to prevent more than one process or thread from reading and writing the shared data at the same time. In other words, if one process or thread uses a shared variable or file, the other processs or threads should be excluded from doing the same thing and we call this **mutual exclusion**.

And the section of the program in which shared resources are accessed is called **critical region**. 

If can develop a system in which two or more processes never be within their critical regions at the same time, we can prevent races. 

But the issue is that if we develop the system with this way (in other words if we only prevent multiple processes to be not in their critical regions at the same time) we prevent races but we also prevent parallel processes cooperating correctly and using shared resources efficiently. 

So to prevent the races in a more efficient and better way, we should have these additional 3 conditions: 

1) We shouldn't take the speed or the number of CPUs into account. (Not relying on assumptions about the speed of processors or the number of them helps us to develop a system that can be used in different configurations)
2) If there is a process running outside its critical region, it shouldn't block any process. (This will ensure that processes do not block each other unnecessarily when they are not accessing shared resources)
3) There should be no process that is waiting to enter its critical region forever. (This will prevent starvation)

in addition to the first condition that we defined previously 

4) Two processes should not be in their critical regions at the same time.

Now let's try to find a method that can meet all of these four conditions. 

**Mutual Exclusion with Busy Waiting:**

Let's say that there is a process A that is currently in it's critical region. One of the conditions of preventing races was to exclude all other processes to enter their critical regions while process A is in it's critical region. The simplest way to do this is using interrupts. So, if process A disables all the interrupts just after it enters it's critical region and then re-enable these interrupts just before leaving the critical region, it can access/modify the shared memory without the fear of intervention. 

But using only this approach is not a good option because disabling interrupts will only affect the CPU that executed the process A in our case (because process A was the one that disabled interrupts in our example). In this case, there is no reason for the processes in other CPUs to intervene the process A and enter their own critical regions while the process A is in it's critical region. 

**Lock Variables:**




















