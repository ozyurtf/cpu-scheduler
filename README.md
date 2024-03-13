**Concurrency**: Executing multiple instructions in an interleaved manner. 

**Parallelism**: Distributing multiple instructions into different resources and running them at the same time in parallel. 

**Inter-Process Communication**: In computer, there are programs that basically includes some set of instructions that can handle some specific task. 

These instructions/codes are stored in disk or memory and cannot help us to do what we want directly. Therefore, they should be executed by the processor. 

And these set of instructions are executed, and we can call the process of the execution of these instructions as **process**.

In a specific time window, there might be multiple processes that need to work with each other and share resources to be able to finish the execution of the instructions successfully. 

One note is that there might be some key points that need attention during this communication: 

1) The way these processes pass information to each others.
2) Ensuring that two processes don't interfere with each other.
3) Ordering the processes properly if there is dependency: If process A produces data and process B prints these data, process B has to wait untl process A produce data to print.

We have mentioned that sometimes multiple processes can share the same resource. And one of the resource they may share might be storage (e.g. main memory, shared file). 

Print spooler is a perfect example of multiple processes sharing the same storage. A print stooler is a program that queues the print jobs that are sent from an application to a printer. 
When a process wants to print a file, for example, it inters the name of the file into the spooler directory. And another process periodically checks if there is any file to be printed. 
If there is a file to be printed, it's file name is removed from the spooler directory and printed.

With this procedure, the print jobs do not need to be sent to the printer directly. The benefit of storing print jobs in this way is that 
sending print jobs to the printer directly may cause two print jobs to interfere with each other if multiple users are trying to use the printer simultaneously. And by storing the print jobs this way, 
we may prevent this kind of problem. 

Also, if we wouldn't use spooler directory, processes wouldn't be aware of each other at all.

But using a shared storage like this brings us another issue: **race condition**. 

**Race Condition**: When two or more processes read from the same resource and also write into the same resource at the same time, the final result
depends on the timing of these processes. And we call this condition as **race condition**.

To prevent t








