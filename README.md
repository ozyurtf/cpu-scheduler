**Note**: These are the notes that I took to prepare for the midterms of the Operating Systems class at New York University. I used the information from the course slides, Andrew Tanenbaum's Modern Operating Systems book and Claude when I prepare these notes. I tried to create a story and connect all the subtopics with each other as much as possible. And because I tried to write these notes based on my point of view as much as possible, there is no guarantee that every single information in here is correct.

# Processes and Threads 

## Process

In computer, there are programs that basically consist a set of instructions that are written to handle specific tasks. 

These **instructions/codes** are **stored** in the **disk or memory passively**. They need to be executed by the processor/CPU to do the tasks they are expected.

So, when these sets of instructions are executed by the CPU, we can call the `process of the execution of these instructions` as **process**. We can also say that **process** is an **abstraction of running program**. Or if we want to define in another way **process** is actually a program in execution but it is not as the same as program.

A **process** typically **includes** information like:

- **address space**
  - **text segment**
    - It contains code *(instructions or machine code that make up the program being executed by the process)*
  - **data segment**
    - Global and static variables are stored in here
  - **stack segment**
    - Local variables, function parameters, and return addresses are stored in stack segment.
  - **heap segment** *(used for dynamic memory allocation during the execution of the process)*
  
- **registers** *(hardware resource that are used to hold data during the execution of instructions)*
  - **general registers**: These registers are used to **hold variables**, and **results that are obtained during the execution of the program temporarily.**
  - **special registers**
    - **program counter**: This is one of the special registers that is **visible to the programmer**. It contains the **memory address of the next instruction**.
    - **stack pointer**: Another special register is stack pointer. It **points to the top of the current stack** in memory. This is **visible to the programmer** as well.
    - **condition registers**: These registers **store the outcome of arithmetic or logical operations** that are performed by the CPU. They contain **bits** that **represent the outcomes of the operations** (e.g., **whether the result of an operation is zero, positive, negative, too large**, etc.). These registers are **visible to the programmer.**
    - **program status word (PSW)**: These registers contain bits that indicate the operating mode of the CPU (e.g., kernel mode, user mode). Unlike the other 3 registers, they are **not visible to the programmer.**
- **process state** *(current activity of the process)*
- **open files**
- **resources held**

And these information are basically stored in physical memory. Each of these information has a physical address in the memory. So by using these addresses, we can access to a specific information in the memory indirectly. 

Hardware components such as CPU, for example, use these physical addresses directly when they store/fetch data in physical memory. But processes cannot access to the information located physical memory by using the information's physical address.

For processes, we virtualize the addresses in the memory. In other words, we translate the physical addresses into virtual addresses. These virtual addresses are typically represented as strings. And they point to the physical addresses in the memory. When a process wants to access to a specific information in the memory, it can use the virtual address of that information. And the information in the memory that is pointed by the virtual address is retrieved to the process. 

### Address Space 

Now, imagine a bunch of virtual addresses together. And that's what we call that **address space**. 

Address spaces typically can either be **flat** or **segmented**. In the flat address space, we store the virtual addresses consecutively, just like how we store data in array. Therefore, the entire virtual address space is treated as a **single, continuous region**.

In segmented address space, however, we **group** the virtual addresses **based on their properties**, divide them into segments, and store the virtual addresses in these segments. When we divide the virtual addresses into groups like these, the operationg system can treat these groups (segments) as a **region** that has the **same properties**. 

A good thing about the **segmented address** space is that we can **assign different access permissions** (e.g. read only, reaad write, execute only) to different segments. And this can **prevent unauthorized access to the critical memory regions.**

*Also one note is that if we have two same applications, their address space will be exactly the same.*

Okay we talked about the processes, how do they look like, how they access to the information in the memory, etc. But when these processes are actually created, implemented and terminated ? Let's talk a little bit about these.

### Process Creation 

Processes are created in many different time frames/conditions. In below, we can see some of the time frames/conditions when the processes are created:

- When a computer initializes hardware devices & operationg system and when it loads the operating system into the memory, new processes are created.
- During the system initialization, some processes are created to run in the foreground so that they can allow the users to interact with the computer. 
- And similarly during the system initialization, some processes are created to run in the background to perform tasks (e.g. an eaxmple of these tasks might be managing resources) without interacting with the user. 
- When processes are running, these processes typically create new processes as well. In those cases, we can represent the processes in a process tree:
```
      A
     / \
    /   \
   B     C
  / \
 D   F

In the process tree above, the process A created two child processes: process B and process C. And process B created two child processes: process D and process F.
```
- The user can execute some codes or open applications and these actions create processes.
- The operationg system can create processes to provide services *(e.g., network services, file system service, printing services, etc.)*
- When the user enters into a system interactively *(e.g through terminal, remote shell, graphical login screen, etc.)*, a new process is created to be able to handle the user's interactive session and to allow the user to interact with the system.

So these are some of the timeframes when processes are created. Now, after learning how/when the processes are created, the next thing that we might ask might be: how/when these processes are implemented and how/when they are terminated ? Let's explain how/when they are terminated first since process implementationo is fairly larger topic.  

### Process Termination 

Here are some of the distinct scenarios when processes are terminated:

- When a process completes its execution without any problem, it exits **voluntarily**. We can call this **normal exit**
- When a process encounters an **error/exception** during its execution, it exits **voluntarily**. We can call this **error exit**.
- When a process encounters a **severe error** that will cause the operating system to operate unsafely (e.g. by potentially damaging the system, causing data loss, etc.), the operating system terminates the process immediately. The process is not given a chance to take any action, that's why the exit is **involuntary** and the user may end up with losing the changes he made before the error. We can call this error type **fatal error**.
- Sometimes, a process may explicitly terminate another process. One example to this scenario might be terminating a process that has not been responding for a very long time. Like in the fatal error, the process is not given any chance to take action. That's why this is an **involuntary** termination as well.
- When a process has run longer than expected, they may be terminated as well. We can call this kind of error **time limit exceeded error**

Okay new we can discuss about how processes are implemented. 

### Process Implementation

In any given time, there might be many different processes that are in different states. 

State in here basically represents the current activity of the process. It is generally expressed with strings.

A process can have many different states depending on its current activity:

- When the process is created, its state becomes **New/Created**.
- When the process is executed by the CPU, its state becomes **Running**.
- Sometimes processes might wait for an external event such as an IO operation. If this happens, the state of the process becomes **Waiting/Blocked**.
- And when the process is ready to be executed by the CPU, its state becomes **Ready**.
- Lastly, when the process is terminated, the state becomes **Terminated**.

In addition to these states, processes deal with many other information (e.g. the priority of the process, program counter, pointers to memory, IO status information, etc.).  

Therefore, to be able to manage all the processes more easily, we can try to store all these information in a data structure. And then by using this data structure, we can manage processes more easily. 

So we call this data structure **process control block (PCB)** and it is **created and managed by the operating system**.

Let's say that there are two processes: process A and process B. And assume that CPU is currently executing the procss A. 

When the CPU switches from executing process A to executing process B, it would be very convenient to store all the information of the process A to somewhere. Because through this way, process A can continue its execution from where it lefts off without losing any important data and its progress. This is another place where **process control blocks** becomes very useful. Because they help us to **save the execution context of the processes** during the **context switch**. And through this way the **operating system** can **support/manage/deal with multiple processes**.

Because **each process** has a **distinct process control block**, we can assign a unique ID to these processes, which we call **process ID (PID)**. 

Process IDs are **handles** that are used to identify the processes. They help us to access the execution context of different processes. 

Handle in here means a reference to the resource and it is abstracted which means that it represents the resource in a way that it is not tied to the physical resource directly. And the reference to the resource can be represented in an abstract way by using an integer, pointer, pointer to pointer, pointer to integer, string, etc. 

To bea able to access to the process control block of a process more easily, we can **store** the **process ID** along with the **process control block** in a new data structure. And we call this data structure **process table**. 

When we pass the process ID, the kernel will basically look at that process ID in the process table and verify whether we have the right to access to the process control block or not. If we do, we will be able to access to the process control block. 

In addition to the process table, the **operating system maintains some other tables** **(e.g., memory table, IO table, file table)** to be able to **manage** the **resources** properly **when** the **processes** are **being executed**. 

In below, we can see the tables that are maintained by the operating system to manage the execution of processes and their accesses to the system resources.       

```
---------
Memory    -------------------> Memory Table (memory allocation and usage for each process)
---------
Devices   -------------------> IO Table (available IO devices, their status, associated processes)
---------
Files     -------------------> File Table (open files file descriptors, file access permissions)
---------
Processes -------------------> Process Table
----------                     -------------    
                               PID | PCB
                                1  |  x 
                                2  |  x 
                               ... | ...
                                n  |  x ⁻⁻⁻⁻⁻⁻|
                                              |
                                              |
                                              V
                                          ---------------
                                          Process State
                                          ---------------
                                          Priority
                                          ---------------
                                          Program Counter
                                          ---------------
                                          Memory Pointers
                                          ---------------
                                          IO Status Info
                                          ---------------
                                          Accounting Info
                                          ---------------
                                          ...
                                          ---------------

```

Okay after these definitions, now let's take a look at **process creation/implementation/termination steps in a real operating system.**

#### Linux Process Object 

In Linux, there is a data structure called **struct task**. This data structure is used to **represent processes as well as the threads** and it contains **all the information about the process/thread (e.g., state, program counter, open files, etc.)**.  

The size of this data structure is approximately 1.5KB. 

Along with the struct task, **each process** in the Linux **requires two stacks** (one for the **user space** and the other is for the **kernel space**). 

**User stack** is a region of memory allocated for user-level tasks. It is used to store information that will be used during the **execution of the code (e.g., function calls, local variables, function parameters, etc.) in the user space.** 

**Kernel stack** is another region of memory allocated for kernel-level tasks **(e.g., interrupts, system calls, and other kernel operations**. When we switch from the user mode to the kernel mode, kernel stack is used. 

Using **two separate stacks** for user space and kernel space helps us to **maintain isolation between user space and kernel space**. When system call is made or when we encounter an exception during the execution of a process, the operating system switches to the kernel mode, and handles the tasks in the kernel by using the kernel stack.

The size of the kernel stack is somewhere between 4KB and 8KB while the user stack can grow dynamically until the stack ran out of space. 

And when we want to **create a new process**, we can make a system call named **fork()**.

#### fork()

```
Before fork()
------------
|          |
| O parent |
|          |
------------

After fork()
------------
|          |
| O parent |
| |        |
| O child  |
|          |    
------------
```

When we want to create a new process, we use an existing process along with the fork() system call. After this, the **copy of the existing process** is created. We call the copy of the existing process **child process** and the existing process that we used to create a new process is called **parent process**. Therefore, child process' parent's process ID is the same as the parent process' process ID.

Note that child process is an exact duplicate of the process except the child process has its own unique process ID. In addition, child process does not inherit it's parent's memory locks, timers, IO operations etc.
  
When kernel is initialized, it manually creates one process. This can be called as **boot process** as well and its **process ID** is set to **0**.

And by using **boot process**, another process is created. This new process is called **init process** and its **process ID** is set to **1**.

All the other processes are created from this **init process** by using **fork()** system call.

In below, we can see the implementation of the fork(): 

```
#include <stdio.h>
#include <unistd.h>
intmain(intargc, char**argv) {
      pid_t pid = fork();
      if(pid == 0) {
            // child process
      }
      elseif(pid > 0) {
            // parent process
      }
      else {
            // fork failed
            printf("fork() failed!\n");
            return1;
      }
}

fork() is called once but it returns twice: once in the parent and once in the child. 
```

```                                                 
int main() {                                  a1  --- a1 --- a1 --- a1
      for (int i = 0; i < 3; i++) {                |      |
            fork();                   =====>       |      |- a1      
      }                                            |
}                                                  |- a1 --- a1
                                                   |- a1

```

```
int main() {
      for(;;) { 
            fork()
      }
}

forkbomb(): Recursively creating processes until system runs out of available resources.
```

Note that because we **don't make a full copy of the parent process' address space**, **fork()** is **quite fast**.

After a new process is created with fork(), the next step is executing that new process, right ? But how to do that ? 

#### execv()

execv() is a system call that is used to **execute a process**.

When we call execv() we provide the path for the executable file as well as some arguments just like below. 

```
#include <unistd.h>

int main() {
    char *args[] = {"ls", "-l", NULL}; // Command-line arguments for the new program
    execv("/bin/ls", args); // Execute 'ls -l' command
    return 0; // This line won't be executed because execv replaces the current process
}
```

When we run execv(), **new process is not created** because execv() **transforms the existing process into a new process**. And after we create a child process with fork(), execv() system call is made to execute a program in that child process.

In below, we can be able to see another use case of execv():

```
#include <stdio.h>
#include <unistd.h>
int main(intargc, char**argv) {
      pid_t pid = fork();
            // Creates new process control block and address space                   
      if (pid == 0) {
            // Checks if current process is child process 
            execv(path, executablename);
                  // Replaces the current process image with new process image.
                  // Image means all the code, data and resources that are necessary to run the process
      }
      elseif (pid > 0) {
            // Checks if current process is parent process
            // In the parent process, process ID is set to the
            // newly created child process.
            int status;
            waitpid(pid,&status,option);
                  // Parent waits for child process to finish.
                  // Because execution of the parent process
                  // might depend on the completion of the
                  // child process.
      }
      else {
            // fork failed
            printf("fork() failed: \n“, strerror(errno));
            return-1;
      }
}
```

#### clone()

We can see clone() as more flexible version of fork(). It allows more control when we create new process. For example, we can specify which resources (e.g., virtual address space, file descriptors, etc.) should be shared between the parent and child processes. 

That's why it is an ideal way to create threads within the processes after we create processes with fork(). 

#### signal()

Signals are events that are generated by the software after the execution of specific instructions/conditions. They are used for **inter-process communication**. In other words, they are **sent by the kernel** from one process to another to notify the process about a specific event. 

Signals can be **represented** in various ways **(e.g. constants, enumerated values, signal numbers that are basically integer values associated with specific signal types, etc.)**

When a program is being executed, if exceptions happen (e.g., division by zero, illegal memory access, segmentation faults, etc.) or if user enters an input, or if process is terminated, or if timer set by the process expires, etc., signals are sent to notify processes about these events. 

For example, let's say that the user presses CTRL + C. In that case, an **interrupt** is **created** by the **keyboard hardware** and this interrupt is handled by the interrupt handler. Then the interrupt handler **sends** a **signal** that is **created by the kernel** to the **right process** and notify that process about the user's action that will interrupt the process.

**Summary**: **fork(), exec(), wait()** and its variants are the operating system's system calls that are used to **create** and **manipulate processes**. 

So, after seeing that how processes are created, implemented, and terminated in Linux, we can turn back where we left off. 

During the process implementation step, we have talked about states (e.g. Running, Waiting, Terminated, etc.) 

And a process can transition from one state to another during its runtime. 

We can actually visualize the list of all possible states that we can assign to a process and all the possible transitions between these states by using some kind of flow diagram.

And this diagram, in other words, the representation of the all the possible states and all the possible transitions between these states is called **process state model**. 

### Process State Model 

There can be several possible state models depending on the system and our needs.

Sometimes, for example, it may be convenient for us to assign only two states such as **Not Running** or **Running** to a process. In those cases, we can implement two-State model.

#### Two-State Model

```
                 Pause
      --------------------------  
      |                        | 
      |                        |
      V        Dispatch*       |   
 Not Running -------------> Running 

```

**Dispatch is the action of assigning the process to the running state. In other words, when a process is dispatched, this means that it is selected by the CPU to be executed.*

The two-state model is relatively simple as we might see above. But the issue with this model is: if a process is not in the **running** state, there might be many reasons why it is not in the **running** state: maybe it is waiting for an IO operation, or maybe it is actually ready to be executed but CPU is still busy with executing another process. In the two-state model, we ignore these possibilities and simply label the process as **not running** if it is not running. 

Therefore, we can say that two-state model is **efficient** only if all the processes that are in **not running** state are **ready for execution**. But this may not be the case sometimes. In other words, some of the processes in the **not running** state might not be ready for execution like we mentioned in the previous paragraph. Therefore, the dispatcher cannot simply select a process that is in **not running** state in these cases. Because it doesn't know if the process in the **not running** state is **ready** to be executed, or if it is **blocked**. 

The best way to solve this problem is to split the **not running** state into two new states: **ready** and **blocked**. Since we will have three states after this split, we call this new model as **three-state model**.

#### Three-State Model

```
         Timeout
  -----------------------    
  |                     | 
  |                     |
  V     Dispatch        |   
 Ready -----------> Running 
  Ʌ                    /
  |                   / 
  |                  /
  |                 /    
  |                /
  |               /
  |              /
  |             /
  |            /
  |           /
  |          /
  |         /
  |        /
  |       /
  |      /
  |     /
  |    /
  |   /
  |  /      
  | V
Blocked
```

In the three-state model, now the process can transition to **blocked** state when it starts waiting for an external event such as IO operation. And when the external event the process was waiting for is completed, this means that the process is now ready to be executed again and therefore it can now transition from the **blocked** state into the **ready** state.

And if another process that has a higher priority than the currently running process arrives, or if the currently running process has run for a long time, the currently running process can transition from the **running** state into the **ready** state. And then we can execute another process that is ready to be executed and move that process from the **ready** state into **running** state. 

Okay these are all good updates but we still ignore the process creation step. In some systems, not having a state specifically for the process creation may cause the system to not being able to allocate resources to the newly created processes until they are ready to be executed. Similarly, not having a state specifically for the process termination may cause the system to not being able to manage the resources efficiently after the process finishes its execution. 

Therefore, if we are in those systems, it may be better to use another state model that can take these details into account.

#### Five State Model 

```
                     Timeout
              -----------------------    
              |                     | 
              |                     |
     Admit    V     Dispatch        |     Release
New -------> Ready -----------> Running -----------> Exit
              Ʌ                    /
              |                   / 
              |                  /
              |                 /    
              |                /
              |               /
              |              /
              |             /
              |            /
              |           /
              |          /
              |         /
              |        /
              |       /
              |      /
              |     /
              |    /
              |   /
              |  /      
              | V
           Blocked
```

So, in the five-state model, we introduced two different new states: **new** and **exit** to solve the issue that we mentioned in three-state model.  

But there is one major flaw in the five-state model: CPU is much faster than the IO devices. Therefore, if the CPU executes very fastly and as a result of this if all of the processes are moved to the **blocked** state, there will be no processes in the ready state anymore. 

In that case, all the processes will just wait for an IO event and CPU will sit idle and wait for at least one process to be ready to be executed. And this will lead to low CPU utilization. 

We don't want CPU to be idle. To prevent this, if all processes in the main memory are in **blocked** state, the operationg system can **suspend** a process that is in **blocked** state. It can then store the suspended processes in a queue named **suspend queue**, and move the **suspended processes** to the **disk** to **free up main memory**.

Through this way, CPU can now bring other processes to the main memory and start executing them. This prevents the CPU from staying idle. 

Therefore, we can add another state named **suspend** to the five-state model. After this update, we will have six states in total and we call this model **six-state model**.

#### Six-State Model 

```
                     Timeout
              -----------------------    
              |                     | 
              |                     |
     Admit    V     Dispatch        |     Release
New -------> Ready -----------> Running -----------> Exit
             Ʌ Ʌ                    /
            /  |                   / 
           /   |                  /
          /    |                 /    
         /     |                /
        /      |               /
       /       |              /
      /        |             /
     /         |            /
    /          |           /
   |           |          /
   |           |         /
   |           |        /
   |           |       /
   |           |      /
   |           |     /
   |           |    /
   |           |   /
   |           |  /      
   |           | V
Suspend <--- Blocked
```

In the six-state model, we fixed the issue that we mentioend in five-state model by adding the **Suspend** state. 

But how we can decide if we should bring a brand new process or if we should bring a process from the suspend queue to the main memory ? 

In addition, CPU doesn't know which processes in the suspend queue are ready for execution and which processes are not. Because it doesn't know this, it may try to take a process in suspend queue that is still not ready to be executed. 

To avoid this, we can divide the suspend state into two new states: **Ready - Suspend**, and **Blocked - Suspend** 

- **Ready - Suspend**: This state means that the process is currently in the disk and it is ready for execution.
- **Blocked - Suspend**: This state means that the process is currently in the disk but it is still waiting for an event completion. 

When we introduce these two states and remove the **Suspend** state, the new model will have seven states in total and we call this **seven-state model**.

So, in many of these state models, we introduced the idea of moving the CPU away from the currently running process (in other words stopping the currently running process), and giving it to another process. 

When we keep multiple processes in the main memory, and the CPU is switched between them, we call this **multiprogramming** beacuse we run multiple processes simultaneously on a single CPU. Let's now talk about multiprogramming more.  

### Multiprogramming

In an operating system that is capable of **multiprogramming**, there are **multiple processes that are residing in the main memory** and **sharing the resources**. And **CPU can switch from executing one process to another quickly**. 

Multiprogramming is beneficial because it **lets processes to use the CPU when the CPU would otherwise become idle**. Through this way, we can **increase the CPU utilization**, **resource utilization**, **ensure fairness** among the processes and obtain **higher throughput**. 

In a **multiprogramming** environment, because there are **multiple processes that are executed**, the **execution order** of all of these processes are **determined** based on the **system load and resources** at that moment. And since the **system load and resources might change from time to time**, when we **run** the **same program/application multiple time**s, we will **get different execution times**. 

One **another reason** why we get **different execution times** when we run the **same program/application** multiple times is **interrupts**.

If you don't know what the interrupt is: interrupt is basically a signal/notification that is sent by the hardware or software to the CPU to suspend the execution of a process temporarily. It indicates that an event happened and it requires attention. 

Therefore, **interrupts bring unpredictable delays** and if we **run** the **same program several times** and **interrupts** **occur** during the execution, we **won't** **get** the **same execution times** because of this. 

The interrupts can be generated by external devices such as keyboard, mouse, etc. or internal system components such as disk controller, timer, etc. One way to represent interrupts is using a vector of numerical values associated with a specific interrupt type. 

When an **interrupt** happens, the **execution context (e.g. registers, program counter, etc.) is saved** and the **control** is **transferred** to the **interrupt** **handler**, which is a software that is responsible from handling interrupts. And the **interrupt handler performs the necessary actions from there.** 

So, if we turn back to multiprogramming: we have mentioned that multiprogramming increses CPU utilization but how do we calculate the CPU utilization ?  

### CPU Utilization

Let's assume that there are "n" processes that are residing in the memory at once. 

And let's say that these processes spend p% of their time waiting for an IO event.

In that case, the probabiltiy of all "n" processes waiting for an IO event at the same time becomes p * p * p * ... p = p^n. 

But we don't want all the processes to be waiting for an IO event at the same time because in that case, there would be no job for the CPU and CPU becomes idle. And we don't want the CPU to be idle. We want it to work and be busy as much as possible so that more jobs can be done. 

Therefore, in this scenario, CPU utilization can be calculated as **1 - p^n**.

If there are 3 processes that are residing in the memory, for example, and the fraction of the time these processes spend waiting for an IO event is 80%, the probability of all of these 3 processes waiting for an IO event at the same time will be 80% * 80% * 80% = 51.2%. In other words, the probability that CPU won't be idle will be 100% - 51.2% = 48.8%. And this can be seen as CPU utilization as well.

But it should be noted that this model is just an approximation. A more accurate model can be constructed using queueing theory. 

Okay these are great information but another question we did not ask during the explanation of multiprogramming is: how we can do multiprogramming ? 

### How to Do Multiprogramming ? 

Multiprogramming is achieved through the operating system's ability to **start, run and complete multiple processes in overlapping time periods**. And we call this ability **concurrency**. 

Note that concurrency is not the same as **parallelism** in which the **processes are run at the same time in multicore processor**. In **concurrency**, the **processes are run in an interleaved manner** and they are **managed** at the same time. But they **don't have to run at the same time**. Multitasking on a single core processor can be given as an example of concurrency. 

And in **parallelism**, the **processes** are **run at the same time**.

Therefore, the question of **how to do multiprogramming** is actually a **question of how to increase concurrency**, in other words, **how to manage execution of multiple processes at the same time** and **how to switch from process A to process B if process A is waiting for an external event**.

Imagine that there is a web server that is handled by only one process. In this kind of system, whenever the process is blocked and starts waiting for an external event (e.g. reading from a socket, writing to disk, etc.), the entire web server is blocked as well because everything is handled with only one process. That's why the entire web server would wait for the external event to be done. This will obviously result in delays and reduced throughput. 

A solution to this problem might be using multiple processes instead of one process. Through that way, each process can handle different tasks and if one of them is blocked, the others can continue their executions. 

But the issue in here is that, if we create multiple processes, each of them will have its own address space (e.g. stack, heap, files, etc.) and this means that these multiple address spacess will consume memory and other resources more. This is resource-intensive.

Maybe what we need is **execution units** like **process** that can **execute** the **instructions** but that **doesn't require a separate address space** and that **shares** the **resources**. And this execution unit is called **thread**.

## Thread

**Threads** are **unit of executions** like processes. But they are **created within the processes** so that they share the jobs of the process, and work together with all the other threads to reach the goal/task that is expected from the process they are part of. 

And to be able **to work and communicate together efficiently**, **they share/use the same address space and the resources of the process** they are part of. The only exception in here is stack space. Each thread has its own stack so that it can store its own local variables, function parameters, return address, etc. 

A **thread** typically **has**: 
- a state *(current activity of the thread such as running, ready, blocked, etc.)*
- saved thread context when the thread is not running *(when CPU stops running thread A and starts running the thread B, the context of the thread A is saved so that the next time thread A is executed, it can start from where it lefts off)*
- execution stack
- storage for local variables
- access to the address space and resources of the process that it is part of

Items that are **shared by all the threads** in a process: 
- address space
- global variables
- open files
- process-level resources

Items that are **private to each thread**: 
- program counter
- register *(stores memory addresses for data retrieval, current instruction being executed by the CPU, data values that are used in arithmetic, logical and other operations performed by the CPU)*
- state
- stack *(stores return addresses, the values of the arguments that are passed to a function, local variables, etc.)*

### What Is The Difference Between Threads and Processes ?

Imagine a web browser. You can think of this **web browser** as a **process** because

- It **has its own memory space** and this memory space is **separate from other applications in your computer**.
- If it **crashes**, **nothing happens to other applications**.
- It **has its own ID** (Process ID) in the operating system.

So, **when you launch** this web browser, 

- **Memory** is **allocated**
- **Executable code** is **loaded**
- **Resources** are set up for that browswer (process)
- An **entry** is **created** **in** the **process table** 
- Program's entry point starts to be executed

**by the operating system.**

And **the tabs you open in this web browser operate as threads** because

- **Each tab (thread)** can **load** a **different** **website**
- **All tabs** (threads) **share the same memory** of the web browser
- **Tabs (threads) can be executed in parallel**
- E**ach tab doesn't appear separately**.

So, when you open a tab in the web browswer, the workflow can be summarized like this: 

- The **browser** (process) **creates** a **new** **tab** (thread)
- It **allocates** a **stack** for that thread
- It **shares** **access** to the **browser's** (process) **memory** and **resources**
- It **sets** **up** **execution** **context** for that tab (thread)
- It **begins executing of the page loading code**.

Okay, these are good to know but how do we create the threads ? 

### How Threads Are Created ? 

1) We first allocate a memory for the thread's stack using a memory allocation function. *(e.g. malloc())*
2) Then we create a new thread within the current process. *(by making a system call such as clone(). clone() creates a new execution context within the process and this execution context represents the new thread)*
3) We set the stack pointer of this thread to the thread's stack that we created in step 1.
4) Set the program counter (instruction pointer) to a function pointer. Function pointer in here points to the function the thread will start executing when it starts running. 
5) After setting up the execution context of the thread, we allow the scheduler to run this thread whenever it is appropriate to run by marking the thread schedulable.

Now, imagine that there is an application that wants to perform multiple tasks concurrently. If there are no threads, for example, execution units would be processes. Therefore each process would have to execute only one task at a time. As aresult, whenever we need to switch between different tasks, we would need to switch the entire processes. And we would have to save and restore all the information of these processes (e.g., state, variables, register values, program counter etc.) everytime we stop executing one task and start executing another. This would require **significant state management**. **Threads save us from this.**

In addition, **threads** **prevent** us from **creating new address spaces and managing separate memory regions**. They just need a **stack** and a hardware component that is responsible from executing instructions **(execution unit)** and they use the same address space and resources of the process they are part of. 

That's why **threads** are **faster to create/restore** and they **lighter than processes**. When the **number of execution units** that are **needed** **changes dynamically** and rapidly, **threads become useful**. 

In addition, the ability for parallel tasks to share an address space and all of its data among themselves is essential for certain applications. Tha's why having multiple processes (with their own separate address spaces that cannot be accessed by another process) will not work in those cases. 

Consider an example in which we need mutliple execution units that should work on the same document. In this case, having multiple separate processes would not work because what we want is for execution units to share a common memory and to access to the same document. That's why we should use threads instead of processes in situations like these.

Lastly, it is important to note that **threads** are especially **useful** when there is a **substantial computing + substantial IO operations** because in these cases while one thread is waiting for an IO event, other threads can continue their executions. But if none of the threads are waiting for an IO event, threads will not result in a significant performance gain. 

In summary, **processes** are essentially programs that **encapsulate various resources** that are **required** for **executing the instructions**. And these resoruces can be memory, files, etc. 

Therefore, **the resource ownership**, **the unit of resource allocation** can also be seen as **process** or **task**. Also, each process has its own address space that are isolated from other processes. That's why a process **cannot modify** the address space of another process because these address spaces are **independent**. Because of this, we can say that **address spaces** are **protected** from being modified/destroyed by another process and that's why **a process** can also be seen as **unit of protection**. 

**Threads** or **lightweight procss**, on the other hand, are the entitis within processes. They can be seen as **the unit of dispatching**. 

Because threads are scheduled for execution on CPUs, they can be in any of several states such as **Running, Blocked, Ready, Terminated** etc. like processes. 

And when there are **multiple threads** in a process, this means that the **operating system can support multiple concurrent paths of execution within a single process**. This is called **multithreading**. In below, we can see the difference between a single-thread process and multi-thread process better: 

```
Single-Threaded Process
----------   ----------
|Process |   | User   |
|Control |   | Stack  | 
|Block   |   |        | 
----------   |--------|
----------   |        |
|User    |   | Kernel | 
|Address |   | Stack  | 
|Space   |   |        |
----------   ----------
              Thread-1    
```

```
Multi-Threaded Process

             ----------   -----------
             | Thread  |  | Thread  |
             | Control |  | Control |
             | Block   |  | Block   |
             ----------   -----------          
----------   ----------   -----------
|Process |   | User    |  | User    |
|Control |   | Stack   |  | Stack   | 
|Block   |   |         |  |         |
----------   |---------|  |-------- |  ....
----------   |         |  |         | 
|User    |   | Kernel  |  | Kernel  |
|Address |   | Stack   |  | Stack   |
|Space   |   |         |  |         |
----------   -----------  -----------
              Thread-1     Thread-2
```

So, we talked about the difference between single-threading and multiple-threading but we didn't compare multiprograming and multithreading. 

**Multiprogramming** provides **concurrency** at the **process level**. It **allows multiple processes to run concurrently within the CPU**. 

**Multithreading** provides **concurrecny** at the **thread level**. It **allows multiple threads to run concurrently within a single process**.

Also note that because **threads** within the same process **share** the **same address space**, one **thread** **can completely modify** or even destroy **another thread's stack**. In other words, there is **no protection among threads**. 

Even though the lack of protection may seem negative, the factor that causes this lack of protection (**sharing address space and resources**) is actually what **allows efficient communication** between different threads.

But as we mentioned, sharing address space or resources also **introduces** the **risk of data corruption and race conditions** **if proper synchronization mechanisms** are not applied. Therefore, it is important to apply synchronization techniques such as **semaphores, lock variables, busy waiting** etc. to ensure data integrity. 

What **threads** **add** to the process is the **ability occupy multiple executions in the same (process) environment** to achieve a common goal. Having threads running in one process is analogue to the having processes running in one computer. In the former case, the threads share an address space and other resources in the process. In the latter case processes share physical memory, disks, printers, and other resources in the computer. 

Okay it is great to know all these but where do we implement these threads though ? 

### Where to Put Thread ? 

#### Implementing Threads in User-Space

There are two places to implement threads: 
- user space
- kernel space

We can put the threads entirely in the user space. But when we do this, the kernel won't know anything about these threads. The only execution unit it will see will be processes and it will see them kind of like single threaded and try to manage the processes directly since they will be the only execution units it is aware of.

The advantage of putting threads to the user space entirely is that through this way, we can implement threads in an operating system that does not support multithreading. With this approach, threads are implemented in the library/application and all the thread management is handled in there (user space). 

In addition, because kernel is not aware of the existence of threads, and it only recognizes the processes, only one thread of the process can be executed at a given time. 

When we implement the threads in the user space, each process needs its own private thread table in the userspace. This thread table basically contains thread ID, and thread control block pairs for each thread. Thread tables are analogous to the kernel's process table that we have mentioned previously. The difference is that thread tables keep track of the properties of each thread (e.g. thread ID, thread stack, thread state, register values, priority, etc.) rather than process. 

Also when threads are implemented in the user space, thread tables are managed by the runtime system that is provided by the programming language. Runtime means the instructions that are executed when your program is running. And runtime system provides the environment, necessary services and infrastructure for executing these instructions. It acts as a layer between the program code and the underlying operating system and hardware.

Like in all the other methods, there are both advantages and disadvantages of this method (implementing threads in the user space): 

Advantages: 
- When threads are switched, we don't need to enter into the kernel mode because threads are not located in kernel.
- Because threads are implemented by the user-level library, the scheduling system is handled in the user space as well. Therefore, we can implement application specific scheduling systems rather than relying on the general purpose scheduling system of the kernel.
- Because threads are implemented in the user space, we can run them in any operating system.
- User-level threads also scale better in terms of the number of thread creation. Because when we implement threads in the user-level space using a library, the library only needs to allocate memory from the process' heap, set up stack in the user space, and add the thread to a queue in the user-space. Because all of these happen in the user space without switching to the kernel mode, we can say that user-level threads scale better. In addition, the procedure of saving the thread's state and scheduling the next thread are just local procedures in user space when we implement the threads in the user space. So saving the thread's state nad scheduling the next thread in the user space is much more efficient because we don't need a kernel call, trap or context switch. These make thread scheduling very fast when we use user-level threads.

Disadvantages: 
- We have mentioned that the user level threads are located in the user space and kernel is not aware of their existence. The only thing kernel access is processes. That's why kernels are unaware of the activities of the threads in the user space. So, if a thread starts waiting for an external event, the whole process and as a result, all the threads in that process are blocked as well. Similarly when page fault happens, the entire process and all the threads are blocked as a result.
- Also, if threads are managed at the user-level, they are not aware of the underlying hardware architecture and therefore cannot be efficiently scheduled across multiple processors by the operating system. As a result, they may end up running on the same processor instead of being distributed across multiple processors for parallel execution.

What if we implement the threads in the kernel space ? 

#### Implementing Threads in Kernel-Space

As we might guess, when we implement the threads in the kernel space, they are managed by the kernel. No thread management is handled by an application/library.

Also because they are implemented in the kernel, kernel is aware of these threads and can be able to manage them. And creating / destroying or doing any other operations to threads requires us to do system call.

In addition, when threads are implemented in the kernel, which has already the right infrastructure (e.g., built-in data structures such as process & thread control blocks, algorithms for process & thread scheduling, synchronization systems, etc.), for managing threads, no runtime system is needed in each process. Because programs can directly interface with the services provided by the kernel without needing an additional runtime system. 

If the threads would be implemented in the user-space using a library, however, all these services that could normally be provided by the kernel would have to be implemented in the user-space. In that case, a runtime system would be be needed.

And the advantages of implementing threads in the kernel are: 

- Because the kernel is aware of the individual threads in the processes, and threads can access to the resources, kernel can simultaneously schedule/run multiple threads from the same process on multiple CPUs/cores/hardware threads.
- If one thread is blocked, the other threads can continue their execution.

Disadvantages: 
- If we want to switch from executing one thread to another within the same process, we need to switch to kernel mode. *(But note that if we would try to do the same thing in user-space implementation of the threads, we would have to send a signal which would be more expensive)*

#### Hybrid Approach

In the hybdrid approach, all the threads are created in the user-space. When we want to schedule and sycnhronize the threads, these are done in the user space in bulk. After these threads are implemented in user space, however, they are associated with smaller or equal number of threads in the kernel.

The benefit of creating all the threads in the user-space is that it is more efficient compared to creating them in the kernel space. Because when we implement threads in kernel space, the kernel will need to manage various data structures (e.g. thread control block, kernel stacks, etc.) and resources. We will also need to **switch from user mode to kernel mode when**

- the user requests services from the operating system *(e.g. IO operations)*
- **interrupts** *(e.g, timer interrupts, device interrupts)* occur
- **exceptions** *(e.g., page faults, division by zero)* occur.

And switching from user mode to kernel mode frequently is expensive. Because every time we switch from user mode to kernel mode, for example, the CPU has to save the current execution context (e.g., program counter, register values, etc.) of the currently running mode (either user or kernel) and then load the context of the mode it is switching to.

That's why creating threads in the user space involves less overhead. 

It is good to create the threads in the user space but one problem we need to solve is letting know the kernel about the existence of these threads since they are not located in the kernel. And we do this by first creating equal or smaller number of threads in the kernel and then associating the the threads that are implemented in the user space with these kernel level threads. By this way, kernel can use these kernel level threads to manage the user level threads. 

Also, one note is that when we want to refer different thread models, we can use the ratio of the user-level threads and kernel level threads.

- 1:1 *(1 user level thread, 1 kernel level thread -> each user thread = kernel thread)*
- M:1 *(M user level thread, 1 kernel level thread -> user level thread model)*
- 1:N *(1 user level thread, N kernel level thread -> kernel level thread model)*
- M:N *(hybrid model)*

So we explained the processes and threads, their similarities and differences but we didn't talk much about the differences between the storage of the execution contents of these two execution units: PCBs and TCBs

### PCB vs TCB

Process control block is responsible from managing resources that are shared among all threads within a process. This also means that **PCB handles global process resources.**

**Thread control block**, on the other hand, are primarly focusing on **managing resources that are needed for execution.**

Here is the information that is **carried by each process**:

- address space 
- global variables
- open files
- child processes
- pending alarms *(e.g., these alarms are created with system calls like setitimer() and allows the process to perform specific actions when the timer expires)*
- process state
- signals and signal handlers
- accounting information *(e.g., CPU usage, memory usage, IO operations that are performed, number of context switches, etc.)*

Here is the information that is **carried by each thread**:

- program counter
- registers
- stack/stack pointer *(points to the thread's stack in the process)*
- thread state

So, we are already be familiar with the program counter, register, and stack. But how about thread state ? Are the states that are assigned to threads different from the states that are assigned to the processes ? 

### Thread State

Just like the processes, threads can get the same states: **New/Created**, **Running**, **Blocked**, **Terminated**, etc. 

And we can create a thread state model just like how we created the process state model. There is really no difference in terms of how state models are implemented and what types of states can be assigned. 

Note that the instructions and registers are not virtualized in some systems by their nature. In these systems, real physical instructions and registers are used. In addition, CPU can execute instructions sequentially. That's why a processor, or core, or hardware thread can only run one process/thread (these can also be called as unit of execution) at a time in these cases. 

And because processor can only run one process/thread at a time, it would be more efficient if we could be able to switch among multiple processes/threads even if these execution units will all look like progressing but at a slower speed. And this among the execution units is called **context switching**. 

### Context Switching

Context switching **happens** **when**
- current process/thread **blocks** OR 
- **preemption** occurs via interrupt

When **context switching occurs**: 
- the **CPU resources** must be **released** so that they can be used by other execution unit.
- all **registers** should be **stored** in the **PCB** or **TCB**.

All these procedures are written in **assembler**.

But why do we need to save registers to the PCB or TCB ? What kind of information registers contain ?: Registers are storage locations within the CPU. **They hold data and addresses for the instructions that are being executed currently**. That's why storing/saving the registers in a data structure like PCB or TCB is crucial because it helps us to preserve the execution context of a process or thread during the context switching. Through this way the process or thread can resume its execuiton from where it lefts off properly the next time it will be executed. So, let's turn back to context switching.

The benefit of context switching is that when a process performs IO operation, instead of forcing the CPU to wait for that process to finish its IO operation, we can just direct that CPU to another process during that time. And as result, we can finish more tasks.

So, if context switching is switching from executing one process/thread to executing another process/thread, what is the mechanism that decides when and which process should be executed at the moment. The answer to that question is **scheduler** and we will cover that now.

# Process & Thread Scheduling 

**Scheduling** is a **mechanism** that **decides** **which process/thread** should be **executed/run** by the CPU **within a group of ready processes/threads**. During this decision, **multiple factors** are taken into account: 

- When these processes/threads should be scheduled ?
- Do we want the ability to stop executing the currently running process in the middle (preemptive) and start executing another process or not (nonpreemptive) ?
- The operating system we are currently in *(e.g., batch, interactive, real-time, etc.)*
- The goals we want achieve and the metrics we use to achieve that goal. These metrics can be
  - The time between the process/thread arrival/creation and process/thread termination
  - The number of completed processes/threads in a time unit
  - The time between user's request and system's response to this request.
  - How long the processes/threads wait to be executed on average ? 

**Whether scheduling is made based on processes or threads** **depend on** whether the **operating system** is **capable** of **multithreading** or not. Because in a single-threaded operating system, the unit of execution is basically process. Therefore, the operating system schedules and switches between **processes**. In an operating system that is capable of **multithreading**, the **operating system can manage individual threads** within the processes. Because the execution unit is thread, the **operating system can schedule threads.**

So, let's take a look at when processes/threads should be scheduled. 

## When Processes/Threads Should be Scheduled ? 

- Whenever a process is created and ready to be executed. 
- Whenever a process is terminated. Because whenever the execution of a process is finished, CPU becomes idle. So we should pick another process to execute.
- Whenever a process blocks. This means the process cannot be able to proceed its execution because of the reasons like waiting for an IO operation, lock, semaphore, or maybe for a timer to expire. When that happens, we should pick another process to execute.
- Whenever an IO interrupt occurs. This is another time the process cannot be able to proceed its execution. But now the reason is because it is interrupted by some IO device. Nevertheless, the CPU becomes idle when this happens and therefore we should pick another process to execute.

In summary, we should schedule process or thread in the cases above but there are many decisions we should make when we schedule processes or threads. For example, how long we should let processes to run without stopping them ? Should we just execute them until they are finished ? If so, what if they enter a very long IO operation ? Should we wait for that process to finish its IO operation or should we just start executing another process or thread during this time period ? The answers to these questions depend on that kind of operating system we are currently in.

## What Kind of Scheduling Algorithm Do We Want to Use ?

Well, like we mentioned, it depends on the operating system and our needs.

### Interactive System

In interactive systems, the ability of taking away the CPU from the process and giving it to another process **(preemption)** is essential. Because in the interactive systems, there are users whose jobs need to be done urgently. Whenever a task comes from the user, we should prioritize the user request over many of the processes that are currently running. That's why we should have the ability to take the CPU away from a process and give it to another one.

### Batch System

In batch systems, there is **no user** who is **waiting impatiently**. In these systems, the **jobs** are **grouped together** and **executed in batches** in a **predetermined order** rather than being executed individually, immediately or interactively. 

Because **human intervention does not occur** when processes are executed, when we use a scheduling algorithm in these systems, it **doesn't have to be preemptive** most of the times. Even if preemption feature is used, it has long preemption period for each process so switching from one process to another is not the case in these systems. 

### Real-Time System

Real time systems are used when we want to provide predictable and timely responses with **strict timing constraints**. That's why the deadlines are important to take into account when we use a scheduling algorithm in these systems. This doesn't mean that it has to be fast though. It just means there has to be deadlines. 

In chemical operations, for example, we can see the application of real-time systems. The real time could mean minutes, hours, days, etc. to initiate an event. 

## Measures of the Scheduling Algorithms

**Turnaround Time**: The length of time from the process creation to process termination. In other words, this measures **how long it took for the process to be completed**.

It is a **good metric to use in batch systems** because the goal of the batch systems is to **minimize the average turnaround time for all processes/threads**. The **lower turnaround time** means that the **less time it took for the processes to be completed on average**. 

**Throughput**: **The rate of processes/threads that are completed per unit of time.** The **higher throughput** means the **higer number of processes/threads are completed in a specified time unit**. A scheduling algorithm that tries to maximize throughput may not necessarily minimize turnaround time. For example, given a mix of short jobs and long jobs, a **scheduler** that **always ran short jobs** and **never ran long jobs** might achieve **great throughput** but at the expense of **bad turnaround time** for the long jobs. If short jobs keep arriving at a steady rate, the **long jobs might never run**. And this makes the **average turnaround time infinite** while achieving **high throughput**. 

**Response Time**: The **time between** the **user's request** and the **system's response to the user's request**. It is the time between the arrival of a process and the first time it starts running.

As we might guess, the goal of the **interactive systems** is to **reduce the average response time** to **minimize the response time experienced by the users**. It is a good metric to use in interactive systems.

**Average Wait Time**: **Average time the processes/threads spend waiting to be executed by the CPU in total**. Note that the response time and wait time are different. In response time, we measure the time between process arrival and the first time the process starts running. In wait time, we measure the total amount of time the process waited for the CPU. And by averaging this across all the processes, we calculate average wait time. The less average wait time is better for us. 

**CPU Burst**: Sequence of instructions a process/thread runs without requesting for an IO operation. This is mostly **dependent** on the **programs' behavior.**

**IO Burst**: The length of time required to finish an IO event while the process cannot run any code. This is mostly **dependent** on the **system's behavior**. Because **the number of other IO events, the speed of device, etc. can change the IO Burst.** 

**CPU Burst and IO Burst are the behaviors of the applications when they are running. They continuously change.**

## Goals of the Scheduling 

The goals of the scheduling generally change from systems to systems. 

In **batch** systems, for example, the goal might be 
- **maximizing the number of processes that are completed per hour** (throughput) (all things considered, finishing 50 jobs per hour is better than finishing 40 jobs per hour. But this might not be the case in other systems that has other priorities other than the number of completed processes in a time unit)
- **minimizing the time between process creation/submission and process termination** (turnaround time)
- **increasing CPU utilization** (keeping CPU busy as much as possible)

In **interactive systems**, the goal might be 
- **minimizing response time** so that the system can be able to respond to users quickly
- **meeting users' expectations** as much as possible

In **real-time systems**, the goal might be 
- **meeting deadlines** (avoid losing data)
- predictability **(the ability of the system to provide reliable and consistent performance)**

And the **goals** that are important for **all of the systems** in general
- **fairness** (giving each process a fair share of CPU execution)
- **balance** (keeping all parts of the system busy)
- **policy enforcement** 

But what do we mean by policy ?: **Policy** in here means a **set of predefined rules** that **specify how processes should be scheduled and executed**. These policies can be **priority assignment, resource allocation, preemption rules, scheduling criteria, etc.** 

And an **implementation** that **enforces the policy** is called **mechanism**. 

It is important to discriminate these two from each other: **Policy is deciding what should be done** while **mechanism is an implementation that enforces the policy.** 

An example of policy might be a scheduling algorithm. And a mechanism, in this case, might be a data structure. If we have a state model like below, for example,

```
                 x
             Interrupt 
      ----------------------
      |                    |
      |                    |
 x    V                    |      x
---> Ready -----------> Running ---->
       Ʌ                 /
        \               /
    IO   \             / IO Called
Completed \           /      x    
    x      \         /
            \       V
             Blocked

```

when the process becomes ready to be executed *(either because this process is recently created or this process completed its IO operation or some other process has run long enough and the CPU was given to the this process or the priority of this process is higher than the currently running process and therefore the CPU is given to this process)*, when it starts waiting for an IO event, or when it stops running, scheduler is called to make a scheduling decision and to potentially switch the CPU from one process/thread to another. 

And to enfore the policy (specified the predetermined scheduling algorithm), we can create a queue data structure to store all the processes that are ready to be run. This queue is called **ready queue** or **run queue** and the scheduler picks a process from this data structure and the selected process is executed by the CPU.
This **ready queue** is called **mechanism** because it helps to **enforce the policy** (scheduling algorithm).

Okay, if we turn back to the scheduling, after explaining the goals of the scheduling in different systems, now the question we want to ask might be: what are the different types of scheduling algorithms ? What kind of scheduling algorithm we should use to reach our goals ?: Well that depends on the system and our needs. The list of scheduling algorithms that are suitable for batch systems is quite different from the scheduling algorithms that are suitable for interactive systems for example. Because the priorities are different in those systems. 

## Scheduling in Batch Systems 

### First-Come First-Served (FCFS/FIFO) 

In FCFS scheduling, when a new process enters the system and becomes ready for execution, or when a process stops its IO operation and becomes ready for execution, it is added to the **end** of the ready queue. And the FCFS scheduler selects a process from the ready queue based on its arrival time without taking any other factors (e.g. priority, user group, time limit) into account. Then the selected process is executed on the CPU without any interruption. So there is no preemption in this scheduler.

FCFS scheduler can be seen fair only if we look at from arrival time perspective.

**If long processes come first**, they are **executed first** based on their arrival time. And **if short processes come later**, they will **have to wait** until the long processes are finished their CPU execution. This means that the **time between the arrival time and completion time might be large for especially short processes** in this kind of scenario. 

That's why we might encounter
- **high wait time**
- **high turnaround time**
- **low throughput**
- **poor response time**

in some cases (e.g. frequent and/or long IO operations, long processes coming first frequently) when we use FCFS. 

### Shortest Job First (SJF)

In SJF, when a new process enters the system and becomes ready for execution, it is added to the ready queue. When we use this scheduler, we assume that we already know the burst time of each process in advance. We can try to estimate the burst time based on the execution histories of the processes for example. 

Once the processes are in the ready queue, we **pick the process with shortest burst time (the time that is required by the process to finish its execution)**. Then the selected process is executed by the CPU. Like FCFS, this scheduler is **not preemptive** as well, in other words, once we start running a process, we cannot take the CPU away from that process. 

This scheduler is **only optimal when all the processes are available simultaneously** and **we have a good idea about their burst times in advance**. Because through this way, it can arrange the processes ensuring that no process that has shorter burst time arrives later and disrupts the scheduling order.

When all the processes are available simultaneously, in other words when they all arrive to the ready queue at the same time, **the scheduler can schedule these processes optimally by picking the shortest job first and then picking the next shortest job etc.**

```
     8      4    4    4
________________________
|A       | B  | C  | D  |
------------------------

Ready queue in original order

Average Wait Time = (0 + 8 + 12 + 16) / 4 = 9
```

```
  4    4    4      8
________________________
|B  | C  | D  | A      | 
------------------------

Ready queue in shortest job first

Average Wait Time = (0 + 4 + 8 + 12) / 4 = 6
```

That's why the **average turnaround time and the average waiting time is smaller, and overall throughput is higher in comparison with the FCFS scheduler.**

But when we use shortest job first scheduler, long processes may experience starvation if short prcoesses keep coming. In addition, the requirement of knowing burst times in advance can be seen as negative as well. Also, we can say that **response time is poor for interactive processes because of the lack of preemption**. 

### Shortest Remaining Time Next 

In here, scheduler always **chooses the process whose remaining time is the shortest**. 

In the first step, processes are added to the ready queue after they become ready to be executed. The **burst time required for each process is assumed to be known in advance**. Then the **process with the shortest remaining time is selected by the scheduler** and executed by the CPU. We can set this scheduler **either preemptive or nonpreemptive**. 

When a process that has remaining time shorter than the remaining time of the currently running process arrives, **if** our scheduler is **preemptive**, the **currently running process stops its execution**, and the **CPU is given to the newly arrived process that has shorter remaining time**. 

**If** our scheduler is **not preemptive**, this **preemption does not happen** and the **selected processes are run until their burst time are finsihed**. 

And since **we are always prioritizing the processes that are closest to their completion**, **we minimize the amount of time processes spend waiting to be executed in the ready queue**. As we **choose the processes that has the shortest remaining time**, **processes are completed more quickly** and **this allows choosing a new process from the ready queue more quickly**. And that makes the **overall waiting time smaller**. And we can say that **processes are completed faster on average and the average turnaround time is shorter with this scheduler**.

But **if** a stream of **processes that are very close to be finished keep arriving continuously**, **processes that have long remaining time may not be given a chance** to be executed with this scheduler and this would cause **starvation for these processes**. 

Also, assuming that the **burst time of the processes are known is another negative side** of this scheduler because in real life it is very hard to estimate the CPU burst time in advance.

In addition, this scheduler does **not consider the priorities of the processes**. Sometimes when a process is running, another process with higher priority might arrive. But when we use this scheduler, the newly arrived process with higher priority is not executed directly unless its remaining time is shorter than the currently running process. This might be okay for some systems but not an ideal solution in interactive systems.  

## Scheduling in Interactive Systems 

### Round Robin

In Round Robin, each process is assigned a **time limit**. After the process starts being executed, if it reaches this time limit, the CPU simply stops executing this process and starts executing another one (**preemption**) in the queue (The processes can be picked based on their arrival times). This time limit is also known as **time quantum**.

When the **time quantum** is **too short**, this means that **processes are given very short time frame to be executed**. And once they reach these short time limits, they are preempted. That's why if the time quantum is too short, **preemption occurs more frequently** and this means **too many context switches** and that means **lower CPU efficiency**. 

When the **time quantum is too large**, this means that **processes are given a very long time frame** to be executed. In that case, **long processes are given a chance to be executed for an extended period of time**. As a result, **short processes may have to wait to be executed for a long time**. 

That's why if we choose a time quantum that is larger than the typical CPU burst, preemption and context switch does not occur very frequently. In addition, short processes does not have to be wait too much. That's why **choosing a time quantum larger then the typical CPU burst is ideal**.

**Round Robin** can be seen as **First Come First Served scheduler with preemption**. Or we can also say that **First Come First Served** can be seen as **Round Robin with a very large time quantum**. 

Because there is a **time limit** for each process and the scheduler is used **with preemption**, we can say that **CPU time is allocated among processes/threads fairly** and **this prevents starvation**. Also because each process gets a turn to be executed, we can say that it has a **good response time** and **processes/threads don't experience starvation wait indefinitely to be executed**.  

But **if there are many processes that have high CPU burst**, these processes will likely be **preempted frequently** and **this causes inefficiency** because each time context switching happens, the operating system needs to save the the context of the current process and load the context of the next process. This context switching causes inefficiencies. 

In addition, **Round Robin** does **not take the priority of the processes into account like** previous schedulers. 

### Priority Scheduling 

In Priority Scheduling, **each process is assigned priority**. And a **process that is ready to be executed** and that **has the highest priority** is **selected** by the scheduler and then **CPU starts executing that process**.

**Priorities** in here **can be assigned either statically or dynamically**. 

Static priorities are generally assigned based on the type of application, its importance, etc. 

And dynamic priorities are assigned/updated based on the current state of the process, time quantum and how long the process ran, whether the process is preempted or not, whether the process returned back from the IO operation or not, etc.

**By using time quantum and decreasing the priority of the currently running process dynamically, we can prevent the process from running for a long time.**

### Multi Level Queue (MLQ) Scheduling

```
Priority Level     Runnable Processes
--------------     --------------------------------------------
| Priority 4 |---- Process 8, Process 9, Process 10, Process 11 ----- Highest Priority    (System)
--------------    

--------------
| Priority 3 |---- Process 5, Process 6, Process 7
--------------
                                                                ----- Medium Priority  (Interactive)
--------------
| Priority 2 |---- Process 4
--------------

--------------
| Priority 1 |---- Process 1, Process 2, Process 3              ----- Lowest Priority    (Batch)
--------------

```

In Multi Level Queue Scheduling, **processes are basically divided into different groups based on their priorities**. And these **processes** are **stored in queues**. And **each of these queues that have different priority level can use a different scheduling algorithm**. For instance, Priority Scheduling may be used for intearctive process while FCFS may be used for batch processes 

The **system processes** (e.g. kernel processes that are responsible from memory management, task scheduling, interrupt handling, etc.) **have the highest priority** **over the other processes**. 

The **interactive processes** (e.g. graphical user interface processes, processes that are used in interactive applications such as web browsers, text editors, etc.) have **lower priority compared to system processes** but **higher priority over batch processes**. 

And the **batch processes** (e.g. processes that are used for large scale data processing, automated system maintenance such as backups, system updates, virus scans, et.) have the **lowest priorities**.

But the issue with multi level queue scheduling is that **starvation might happen if there is always a process to run in the highest priority queues.** 

## Multi Level Feedback Queue (MLFQ) Scheduler / Priority Decay Scheduler

**Processes** are **divided** into different **groups** based on their priorities and these processes are **stored** in **different queues** just like multi level queue scheduling. 

**The difference is that processes are assigned dynamic priorities** as well and **these dynamic priorities are updated depending on some circumstances.**

When the processes are created, their dynamic priorities are assigned within the range of static priority depending on their importances. 

If the process **consumes too much CPU time**, or if a **process with higher priority arrives**, it might be **preempted**, in other words, its execution stops to give the CPU to another process. In those cases, **the dynamic priority of this process is decreased by 1**. The reason is to **prevent the processes to be executed for a very long time and ensure fairness**. And **if the dynamic priority reaches to 0 and if the process is preempted again**, the **dynamic priority is reset to the static priority**. 

If **a process performs an IO operation**, it is **preempted as well** but **once IO operation is done**, it is **put into a higher priority queue instead of lower one because IO operations, especially if they are done frequently, are a strong signal that the process is interactive**. Since **interactive processes often directly impact user** experience (keyboard input, clicks, UI updates), they should usually have **higher priority** to prevent the users to experience delays. **So, it is best practice to assign higher priority to IO bound tasks, and lower priority to CPU bound tasks** 

## Lottery Scheduling 

Lottery Scheduler is a mechanism that assigns something like integer variable to the processes/threads and increases this variable by 1 in certain conditions. If we see these variables as tickets in a bowl, and the person who picks these tickets from the bowl as scheduler, it is obvious that the higher number of tickets a process has, the more likely it is picked up by the scheduler. And once the process is picked by the scheduler, it is executed by the CPU.  

Imagine that there are two processes: process A and process B and let's assume that the integer value (the number of tickets) is 50 for both of them. If we pick process from the queue first time randomly, we will get process A with 50% probability and process B with 50% probability. 

But if the integer value assigned to process A is 70 and the integer value assigned to process B is 0, this means that whenever we pick a process from the queue randomly, we will always pick process A.  

## Fair Share Scheduler

Until now, we talked about distribution of CPU among **different processes**, and we were trying to be **fair** to **processes**. If user 1 starts up with 9 processes, and user 2 starts up with 1 process, user 1 would get 90% of the CPU and user 2 would get only 10% of it if we would use round robin, for example.

But we can also try to be fair to the **users** instead of **processes**. 

Fair Share Scheduler is a scheduling algorithm which its goal is to distribute the CPU among **different users** or **different process groups** equally/fairly. In Fair Share Scheduler, the schedule is not only based on individual processes but also the process' owner/user.

## Scheduling in Real-Time

As we mentioned earlier, in real-time systems, meeting deadlines is important. The importance level of it depends on whether the system is hard real-time or soft real-time. In **hard real-time systems, responding to an event within a deadline is crucial**. In **soft real-time systems, meeting deadlines is very important as well but missing the deadlines once in a while is tolerable** unlike hard real-time systems. 

The **events** in the real-time system can be **periodic or aperiodic**. As we might guess, periodic events occur periodically (e.g., sensor readings every 10 seconds) and aperiodic events occur in unpredictable time frames (e.g. user input). 

In addition, the scheduling algorithms that we use in real-time systems can be **static** or **dynamic**. 

If the scheduling algorithm is **static, this means that the order and timing of the processes that will be executed is predetermined and strict, and they don't change during the runtime.**

In **static** scheduling algorithms, a **scheduling table** is created in advance and the **order and timing of the processes execution is stored in this table**.  The static scheduling algorithms are preferred in **hard real-time systems**.

If the scheduling algorithm is **dynamic**, this means that **the order of the processes that will be executed is not prdetermined** and **it can change** during the runtime **based on current system state, durations and urgency of the tasks, etc**. **Dynamic scheduling algorithms is commonly used in soft real-time systems.**

Let's now dive into different types of scheduling algorithms used in real-time systems. 

### Earliest Deadline First (EDF) 

In EDF, **the processes are prioritized based on their deadlines**. The process that has the **earliest deadline is assigned the highest priority** and therefore, it is **executed first**. The **deadlines to the processes are typically assigned by**:

- **System designers/developers** during the design phase of a real-time system
- **Application programmers** who code real-time applications
- **Predefined rules**
- **Higher-level scheduling algorithms**

Here is how EDF works: 

1) **After the processes are assigned a deadline**, the **scheduler maintains a priority queue of processes that are ready to be executed**.
2) Then **processes are sorted by their deadline** (As we mentioned earlier, earlier deadlines are assigned higher priority)
3) The **CPU executes the highest priority** (earliest deadline) task
4) **When a new process arrives**, the **scheduler evalutes the priorities again** 

If the **deadline of the new process is higher than the deadline of the currently running process**, **current process is stopped** and the **new process starts being executed.** In other words, EDF is preemptive. 

## Thread Scheduling

### Thread Scheduling vs Process Scheduling 

There are some advantages of threads scheduling over process scheduling. 

Because threads are lightweight processes, and they share the same address space unlike processes, **thread switching is faster and cheaper** compared to the process switching. In addition, **sharing the same address space makes the communication/synchronization between the threads easier compared to the processes.**

Like we do in process scheduling, **we can also execute multiple threads in parallel if there are multiple cores.**

So in thread scheduling, we have **two levels of parallelism:**
- **processes**
- **threads within these processes**

If threads are **implemented** in the **kernel**, **thread management** is handled by the **kernel**. If the **threads are implemented** in the **user-space**, **thread management** is **handled by thread libraries**. 

Until this point, we talked about the scenarios in in which there is one CPU. But what if there are multiple CPUs ? How we can handle scheduling in that case ? 

## SMP (Symmetric Multi Process) Scheduling

Modern computers can have 100s of CPUs. And **SMP** refers to a **computer architecture in which multiple CPUs are connected to a shared main memory**. In SMP systems, **each process has equal level of access to the memory and IO devices.**

And **each CPU has its own scheduler** which is responsible from **scheduling the threads in that CPU**. That's why **each CPU is triggered by its own timer interrupt when a process/thread reaches its time limit of execution (time quantum).** Because each CPU is responsible from scheduling the processes/threads in it, the scheduling algorithm in each CPU might be called as **local scheduler** as well.

**New processes**, which are created with fork(), **or threads**, which are created with clone(), are **generally assigned to the local CPU where the process/thread creation request is made**. And **if the process/thread load vary across different CPUs, the workload becomes imbalanced across different CPUs**.

And **when imbalances occur in the workloads of different CPUs**, **the resources in the CPUs that have small amount of workloads might be idle for a long time while some other CPUs might be overloaded**. 

**This is not the situation we want because we don't want the resources to be idle**. In addition to this, **when imbalances happen**, **some proceses/threads receive more CPU time compared to others and this decreases fairness**, **reduce overall responsiveness**, and **user experience**. 

Therefore, we should find a way to solve this problem.

### Load Balancing

One way to solve this problem is **letting the CPUs to steal work from other CPUs occasionally**. 

**Each scheduler maintains an average workload history** so that **it can see how stable workload it had until now**. This helps it to make **informed decisions about whether** or not it should **steal** **work** from other CPUs and what kind of **processes it should execute from other CPUs**. And when a CPU is idle and decides to steal work from other CPUs, **small jobs** are **preferred** over the long ones. 

After covering the execution units (processes, threads), what kind of information they carry, their differences and similarities, how these execution units are created, how they are implemented, how they are scheduled, when they are executed, and  when they are terminated, etc., now this might be a good time to explain how these execution units work with each other. 

# Communication Between Execution Units

## Inter-Process Communication

Sometimes there might be **multiple processes** that **need to work with each other and share resources to be able to finish their executions** successfully and efficiently.

But when they work together,

1) **How these processes will pass information** to each others ? 
2) **How will they ensure that they don't interfere** with each other.
3) **How to order the processes properly if there is a dependency between them** ? *(e.g., If process A produces data and process B prints these data, process B has to wait until process A produce data to print.)*

We have mentioned that **multiple processes may share** the same resources. And one of the resources they may share might be **storage** (e.g. main memory, shared file). 

Print spooler is a perfect example to this. A print spooler is basically a program/software that puts the print jobs that are sent from an application to a spooler directory (which can be seen as temporary data storage). When a process wants to print a file, for example, it enters the name of the file into the spooler directory which is where the information about the file is stored. And another separate process (printer daemon) periodically checks if there is any file in spooler directory to be printed. If there is a file to be printed, it's printed and then it's file name is removed from the spooler directory.

**With this procedure, the print jobs do not need to be sent to the printer directly**. The benefit of applying this procedure is that sending print jobs to the printer directly could cause two print jobs to interfere with each other if multiple users would try to use the printer simultaneously. And by **storing the print jobs in a temporary place** this way, **extracting a print job from that temporary place**, and **giving the resource to it whenever the resource becomes available**, we can **prevent this kind of interference between processes**. 

Also, **if we wouldn't use spooler directory, processes wouldn't be aware of each other at all.**

Okay, using a shared storage like this is cool but it actually brings an important issue: **race condition**. 

**Race Condition**: It is a situation in which **two or more processes attempts to do their operatings at the same time.** When **two or more processes read from the same resource and also write into the same resource at the same time, a race condition occurs.** Because **processes are kind of racing with each other to do their tasks.**

## Intra-Process Communication

Until this point, we have mentioned about the processes as well as the inter-process communication. And one thing to note is that in processes, there might be multiple smaller units of execution and we call these units **threads**. If there are multiple threads in a process, these threads work together and share the same address space and other resources. Therefore, there should be some kind of communication between them as well. 

And before we handle the communication between the threads, the 3 key points that need to be considered and that we emphasized in inter-process communication are valid in here as well:

1) How these threads will pass information to each others ? 
2) Ensuring that two threads don't interfere with each other.
3) Ordering the threads properly if there is a dependency.

So, the ability of the multiple processes/threads to access/modify the shared resources simultaneously is cool but it is important to note that this situation may (and will) end up with many problems if it is not handled properly.

For instance, when multiple processes or threads are accessing/sharing/modifying the shared data, a specific sequence of operations is performed. This sequence of operations is what we call **Read-Modify-Write Cycle**. 

## Read-Modify-Write Cycles

- **Read**: Reading the current value of a memory location from the memory is called **read**.
- **Modify**: Some operation is performed on the value that was read from a memory location and this is called **modify**. 
- **Write**: The modified value is written back to the same memory location from where the value was read in the first step.

But if the code is executed by multiple processes/threads that access to the same data concurrently, we may end up with race conditions and data inconsistency. 

This is not what we want because our expectation is that processes/threads access to same data consistently. So how we can prevent race conditions ? 

## Preventing Race Conditions

One simple way to prevent race conditions is to prevent more than one process or thread from reading and modifying the shared resource at the same time. In other words, when one process or thread accesses to a shared resource, all the other processes or threads should be excluded from doing the same thing during that time and we call this **mutual exclusion**.

And the section of the program/codes in which shared resources are accessed is called **critical region**. 

If we can develop a system in which two or more processes would never be within their critical regions at the same time, we can prevent race conditions. 

But the issue is that if we develop only this rule (in other words if we only try to prevent multiple processes from being in their critical regions at the same time) that may still not be very efficient. 

For example, preventing multiple processes to be within their critical regions at the same time does not prevent a process that is **running outside of its critical region** to **block another process** that is running in its **critical region**. This kind of block is unnecessary because it may cause delays and does not bring any benefit. Therefore, we should add additional rules to prevent the race conditions in an efficient way: 

1) We shouldn't take the speed or the number of CPUs into account. *(Not relying on assumptions about the speed of processors or the number of them helps us to develop methods that can be used in different systems)*
2) If there is a process running outside its critical region, it shouldn't block any process. *(This will ensure that processes do not block each other unnecessarily when they are **not** accessing shared resources)*
3) There should be no process that is waiting to enter its critical region forever. *(This will prevent starvation)*

In addition to the first condition that we defined previously

4) Two processes should not be in their critical regions at the same time.

Now let's try to find a method that can meet all of these four rules. 

### Mutual Exclusion with Busy Waiting

Let's say that there is a process that is currently in it's critical region. And let's call it process A. One of the conditions of preventing race conditions was to prevent other processes from entering their critical regions that access the same shared resources if process A is in it's critical region. 

The simplest way to do this is using **interrupts**. 

Interrupt is basically a signal/notification that is sent by hardware or software to the CPU. It indicates that an event happened that requires attention. 

Interrupts can be generated by external devices such as keyboard, mouse, etc. or internal system components such as disk controller, timer, etc. One way to represent interrupts is using a vector of numerical values associated with a specific interrupt type. 

Context switches are triggered by either time interrupts or IO or other types of interrupts. When an interrupt happens, the information of the currently running execution unit (e.g. registers, program counter, etc.) is saved, the control is transferred to the interrupt handler, which is a software that is responsible from handling interrupts. And the interrupt handler performs the necessary actions. 

So, if process A disables all the interrupts just after it enters it's critical region and then re-enable these interrupts just before leaving the critical region, only one process can be in its critical region and therefore process A can access/modify the shared memory exclusively without the fear of intervention. 

But using only this approach is not the best option because it is not a good practice to give the process in the user space the ability to turn on/off the interrupts since the process may forget to turn on the interrupt after leaving its critical region and that would cause many problems. In addition, disabling interrupts from the user space will affect only the CPU that executes the process A. In this case, we actually don't prevent the processes **in other CPUs** entering their own critical regions that access the same shared resources with the process A.

So, using interrupts is not the best way to provide mutual exclusion. Let's look at another way to provide mutual exclusion.

**Lock Variables:** Another way to apply mutual exclusion is using **lock variables**. Instead of interrupts, we can use a variable that takes a value of 0 or 1. And we call this lock variable. 

For example, if the process A enter its critical region, it can set this lock variable to 1, which basically means that the critical section is occupied at this moment. And if other processes try to enter their critical regions after the lock variable is set to 1 by the process A, they will see that lock variable is 1 and they will have to wait until the lock variable is set to 0 by the process A (which means that process A stopped accessing to the shared resource, left its critical region and one process can now enter its own critical region and access to the shared resource).

But the thing is: when we use just lock variables, we might encounter with the same problem that we encounter in read-modify-write cycle: if multiple processes perform this cycle, and tries to access the shared data/resources simultaneously, race condition may occur. For example two processes may read the lock variable as 0 simultaneously, both modify it to 1, and then write back the value 1. This would allow both processes to enter the critical section at the same time, and maybe modify the shared data/resources simultaneously. And this results in data inconsistency which is not something we want. 

In addition, when we implement only lock variables, a process that is running outside its critical region may block another process. For example, let's say that there are two processes: 

```
Process A:

while (TRUE) {
  while (turn != 0) {} // Wait until turn = 0
  critical_region();   // If turn = 0, enter to critical region.
  turn = 1;        
  noncritical_region();
}
```

```
Process B:

while (TRUE) {
  while (turn != 1) {} // Wait until turn = 1
  critical_region();   // If turn = 1, enter to critical region.
  turn = 0;
  noncritical_region();
}
```

In the example above, when process A leaves the critical region, it sets the turn variable to 1 to allow the process B to enter its critical region. Suppose that process B finishes its critical region quickly and set the turn variable to 0. At that moment, both process A and process B will be in their non critical regions. 

Later, if process A executes its loop again, enters its critical region, sets the turn variable to 1, and then enters its non critical region, both process A and B will be in their non critical regions and turn variable will be equal to 1. 

At that time, if process A finishes its non critical region and goes back to the top of it's loop, it won't be permitted to enter its critical region because turn = 1. 

That's why, this kind of procedure is not a good solution because it violates the 2nd condition that we defined previously: 

1) We shouldn't take the speed or the number of CPUs into account. (Not relying on assumptions about the speed of processors or the number of them helps us to develop a system that can be used in different configurations)
2) **If there is a process running outside its critical region, it shouldn't block any process. (This will ensure that processes do not block each other unnecessarily when they are not accessing shared resources)**
3) There should be no process that is waiting to enter its critical region forever. (This will prevent starvation)
4) Two processes should not be in their critical regions at the same time.

So we can conclude that using lock variables solely is not the best method to prevent race conditions. Let's take a look at other methods.

### Peterson's Solution for Achieving Mutual Exclusion

```
#define FALSE 0
#define TRUE 1
#define N 2
int turn;          
int interested[N] = {FALSE, FALSE};  // Initially no process is interested

void enter_region(int process) {
  int other = 1 - process;
  
  interested[process] = TRUE;  // Indicate interest in entering critical section
  turn = process;              // Set turn to this process
  
  // Wait if other process is interested AND it's their turn
  while (interested[other] == TRUE && turn == process) {}
}

void leave_region(int process) {
  interested[process] = FALSE;  // No longer interested
}
```

In this method, here is how the workflow looks like: 

1) The process A shows its interest in entering its own critical region.
2) It sets the turn variable to itself.
3) If another process (let's call it process B) is also interested, this means that it is already in its critical region. In that case, if it's the turn of the process A, the process waits until the other process leaves its critical region (in other words until `interested[other] = FALSE`) and/or it becomes the another process's turn. When this condition is met, the process A enters its critical region.
4) The process A leaves its critical region after doing what it should do and sets interested[process] as FALSE to show that it is not in its critical region anymore.

The other methods that are used to do ensure mutual exclusion are called **Test and Set Lock** and **XCHG**.

### TSL (Test and Set Lock)

```
enter_region:

  TSL REGISTER, LOCK
    | Copies the value in the lock into the register and sets the lock to 1.

  CMP REGISTER, #0
    | Compares the value in the register with 0.

  JNE enter_region
    | If the value in the register is not 0,
    | this means that critical region is occupied.
    | So keep waiting until the value in the register is set to 0, in other words,
    | until the critical region becomes vacant.
    | If the value in the register is 0,
    | this means that the critical region is vacant.
    | In that case, jump into the RET.

  RET
    | Returns, allowing the process to acquire the lock and enter its critical region.

leave_region:

  MOVE_LOCK, #0
    | Releases the lock, and stores the value of 0 in the lock variable.

  RET
    | Returns, allowing other threads to attempt to acquire the lock.
```  
  
### XCHG

```
enter_region:

  MOVE REGISTER, #1
    | Load the value of 1 into the register.

  XCHG REGISTER, LOCK
    | Let's say that the current value of the lock is 0.
    | This means that the lock is available and there is no process
    | that is in its critical region right now. 
    | So, the processor reads this value in the lock.
    | And then it writes the current value of the register (1) to lock,
    | and writes the value of the lock (0) into the register simultaneously.
    | After this, the register is now equal to 0 (which means the lock is acquired)
    | and the lock is now equal to 1 (which represents a locked state)
    | So, by storing the initial value of the lock (0) in the register
    | and using the swap operation,
    | we can check the initial value of the lock and set the lock variable
    | to a desired state in an atomic way.
    | And this atomic operation prevents the situation in which
    | one process (e.g. process A) checks the lock variable and
    | another process (e.g. process B) acquires the lock
    | before the process A sets the lock variable.

  CMP REGISTER, #0
    | Compares the value in the register with 0.

  JNE enter_region
    | If the value in the register is not 0,
    | this means that critical region is occupied.
    | So keep waiting until the value in the register is set to 0, in other words,
    | until the critical region becomes vacant.
    | If the value in the register is 0,
    | this means that the critical region is vacant.
    | In that case, jump into the RET.
    
  RET
    | Returns, allowing the process to acquire the lock and enter its critical region.

leave_region:

  MOVE_LOCK, #0
    | Releases the lock, and stores the value of 0 in the lock variable.

  RET
    | Returns, allowing other threads to attempt to acquire the lock.
```  

So, the solutions we tried until now, **Peterson's solution**, **TSL**, and **XCHG**, to achieve mutual exclusion were correct. But the thing is they had some issues. 

For instance, they had the defect of **busy waiting**. In other words, when a process wants to enter its critical region, it checks to see whether it is allowed to enter. If this is not the case, the process just waits until its entry is allowed. And the problem is that this waiting process wastes the CPU time. That's why it should be avoided.

In addition, suppose  that there are two processes: process A and process B and the priority of process A is higher than the priority of process B. When we use methods like **Peterson's solution**, **TSL**, or **XCHG**, there is a chance that process A can be prevented from entering its critical region when process B is in its critical region and holding the lock variable. And this is called **priority inversion**. 

So in the next steps, we will try to find a way to **eliminate the busy waiting and priority inversion** problems as much as possible. 

Let's try to do the lock implementation by reducing the busy waiting. 

### Lock Implementation with Semi-Busy Waiting 

```
mutex_lock: 
  TSL REGISTER, MUTEX
    | A mutex is a variable that acts like a lock.
    | It is typically a binary value:
    | 0 = Unlocked
    | 1 = Locked
    | The code above copies the value in the mutex (mutual exclusion) lock
    | into the register and sets the mutex lock to 1.
    | This allows the code to know the previous state
    | of the lock while simultaneously attempting to acquire it. 

  CMP REGISTER, #0
    | Compares the value in the register with 0.

  JZE ok
    | If the value in the register is 0, this means that critical region is vacant.
    | In that case, jump into RET.
    | If the value of the register is not 0,
    | this means that the critical region is occupied.
    | In that case, go to the next code.

  CALL thread_yield
    | Instead of checking the status of the lock repeatedly (busy-waiting),
    | and wasting CPU time, we can allow another process/thread to run.
    | So, if critical region is currently occupied,
    | schedule another process/thread and go to the next code.

  JMP mutex_lock
    | Runs the mutex_lock again with a new process/thread.

  RET
    | Returns. This allows the process to acquire the lock and enter its critical region.

mutex_unlock:

  MOVE_MUTEX, #0
    | Releases the lock, and stores the value of 0 in the mutex lock variable.

  RET
    | Returns. This allows other threads to attempt to acquire the lock.
```

Okay with this new method, we now reduced the **busy waiting** by scheduling another process/thread instead when the lock is not available for a process.

Note that when a process/thread tries to acquire a lock, if the lock is not available for that process, we call this **lock contention**

## Lock Contention

Lock contention depends on 

1) The frequency of attempts to acquire the lock      *(as the number of attempts to acquire the lock increases, the probability of lock contention increases)*
2) The amount of time a process/thread holds the lock *(if a process hold the lock very short time, the probability of lock contention decreases)*
3) The number of processes/threads that acquired the lock *(as the number of processes that want to acquire the lock increases, the probability of lock contention increases)*

**If** the **lock contention** is **low**, this means that the **length of time a process/thread spends to wait for the lock variable to be available is low**. In other words, **processes/threads don't wait too much** and in that kind of scenario, **TSL might be a solution** because in TSL, **we just check if the lock is available or not**. If it is available, **it is locked and the process enters its critical region.** If it is not, **the process waits until the lock variable becomes available.**

Until now, **we used the lock variable to ensure that only one process can occupy the critical region at a time**. We can do this with methods other than a simple lock variable as well. 

Let's explain this in a new problem that is called **producer-consumer problem**.

## Producer-Consumer Problem

In producer-consumer problem, there are **two processes**. And they **share a common buffer** (temporary data storage) which it's size is fixed. 

**One** of these two processes **produces information** and **puts** that **information** into this **buffer**. We can call this process **producer**. 

**Another** process **takes** this information **from** the **buffer** and **uses** it. We can call this process **consumer**. 

Now **imagine** that the **buffer is full** and there is no empty space. In that case, **if** the **producer** wants to **put** a **new information** into this buffer, that would cause a **problem**. 

One **solution** for the producer might be **being forced to sleep** until being awakened. And when the **consumer** **removes** one or more items **from the buffer** and **buffer has empty slot(s),** it can wake up the producer as well so that it can put its information into the buffer. 

Similarly, if the **buffer is completely empty**, and if the **consumer wants to remove an item** from that buffer, that's a **problem** too since there is **nothing to remove**. 

And again one solution for the consumer might be **being forced to sleep** until being awakened. And **when the producer puts information** to the buffer and **buffer has a non-empty slot**, **the producer can wake up the consumer** as well so that it can **extract the information from the buffer and use (consume) it.** 

But there are some issues in these solution.

If we look at from the **producer's perspective:**

**1) How can the producer know if a slot is free or not ?
2) If the slot is not free, how can the producer know if it/when it will become free ?**

And if we look at from the **consumer's perspective:** 

**1) How can the consumer know if an information is available in the buffer ?
2) If there is nothing available to consume in the buffer, how can the consumer know if/when an information will become available ?**

To answer these questions, we should first introduce a new concept named **Pipe**. 

## Pipe 

**Pipe** is basically an **inter-process communication mechanism** that **provides temporary storage between processes**. They can be created by **applications**. 

A pipe is basically implemented with a **buffer data structure** in the kernel. And in the produer-consumer problem, the **output of the producer is passed to this buffer** and the **consumer takes the information from the same buffer**. So, **a pipe allows data flow from one process to another in FIFO manner.**

When the **buffer** is **full**, **pipe blocks the producer** to put a new information to it. Similarly, **when the buffer is empty**, **pipe blocks the consumer** to prevent it to attempt consuming an information from an empty buffer. 

And **when a space becomes available in the buffer**, **pipe unblocks the producer**. Similarly, **when some data becomes available in the buffer**, **pipe unblocks the consumer**. 

So, in summary **pipe** is a **unidirectional data channel** that can be **used for inter-process communication**. You can create pipes between two processes or threads to ensure smooth data flow between processes/threads. 

So, now let's turn back to the producer-consumer problem. You can see a simple implementation of this problem in below:

```
#define N 100
  // The length of buffer

int count = 0;
  // Number of items in the buffer

void producer(void) {

  int item = produce_item();
    // Produce the next item

  if (count == N) {
    sleep(producer);
      // If the buffer is full, don't put the item into the buffer
      // and sleep until being awakened by the consumer.
  }

  insert_item();
    // Now put the item into the buffer

  count++;
    // Increase the number of items in the buffer by 1.

  if (count == 1) {
    wakeup(consumer);
      // If an item is available in the buffer,
      // wake up the consumer and let it know about this
  }
}

void consumer(void) {
  if (count == 0) {      
    sleep(consumer);
      // If the buffer is empty, don't attempt to extract item from the buffer and
      // sleep until being awakened.
  }

  int item = remove_item();
    // Now extract an item from the buffer

  count--;
    // Decrease the number of items in the buffer by 1

  if (count == N-1) {

    wakeup(producer);
      // If the buffer was full before extracting an item,
      // this means that an empty slot became available in the buffer.
      // In that case, wake up the producer and let it know about this so that
      // it can put a new item into the buffer if it is waiting. 
  }

  consume_item(item);
}
    
```

Okay, we explained the producer-consumer problem, brought a new method **(sleep() and wakeup() operations) to prevent multiple processes to access to their critical regions at the same time.** But there are still some issues. 

In the producer-consumer problem above, **the access to the count variable is not constrained**. And as a result of this, **we may encounter with a race condition.** 

## Fatal Race Condition

For instance, **let's assume that the buffer is empty** and **the consumer reads the count variable as 0.** But before the consumer executes `sleep(consumer)`, the scheduler interrupts (preempts) the consumer process. At that moment, **consumer does not start sleeping.** 

**Then let's say that a scheduler starts running the producer**. **Producer produces an item and inserts it into the buffer, increments the value of the count from 0 to 1**, and lastly **wakes up the consumer** which is technically **not sleeping**. 

The main issue in this scenario is that the **wakeup() call that was sent to a process that is not sleeping is lost**. 

So, we need to develop a **new mechanism that prevents this issue** and that also **allows multiple processes to access to the shared resources in a sycnhronized way** **on the basis of some shared resource (buffer)**.

We call this new mechanism **semaphore**.

## Semaphores 

A semaphore is a data type like integer just like mutex. But the only way to **access** it is through **two separate operations** that are called **wait()** and **signal()**.

- **wait():**  **Decrements the value of the semaphore by 1** which means that the **resource is acquired**. **Before** this **decrementation**, if the **value** of the **semaphore** was **0** or **negative**, this means that **resource(s)** controlled by the semaphore was/were **already being used**. **After** wait() operation **decreases** the value of the semaphore **by 1**, the value of the semaphore **will be lower than 0**. In that case, **we add the current thread into the wait queue**, because of the **lack of available resources**, **block** it (since it cannot access to the shared resource at this moment), and **schedule another thread** and **run the wait() operation again to avoid spinning and wasting CPU time**.

- **signal():** **Increments the value of the semaphore by 1** which means that the **process/thread** that was **using a resource** **left its critical region** and **stopped accessing to that resource**. If the **semaphore** value **was negative before this increment**, this means that **there were waiting processes/threads in the wait queue**. And **after we release the resource and increment the value of semaphore by 1**, **one of these waiting processes/threads can now start using that resource**. So in that condition, **we pick one thread from the wait queue** and **add it to the scheduler.**

You can see the implementation of Semaphore below:

```
class Semaphore {

  int value;
    // The value of semaphore

  queue<Thread*> waitQ;
    // Queue that holds threads that are blocked (waiting) because of the lack of resources.

  void Init(int v);

  void wait();
    // This operation is called by a thread/process when it wants to acquire a resource.

  void signal();
    // This operation is called by a thread/process when it wants to release a resource.
}

void Semaphore::Init(int v) {

  value = v;

  waitQ.init();
    // Initialize an empty queue to hold threads
    // that are blocked (waiting) because of the lack of resources.                         
}

void Semaphore::wait() {                  
  value--;
      // Decrement the value of semaphore by 1.

  if (value < 0) {

    waitQ.add(current_thread);
      // If the new value of the semaphore is negative,
      // this means that resource(s) controlled by the semaphore was already being used.
      // In that case, add current thread into the wait queue
      // because of the lack of available resources.

    current_thread->status = blocked;
      // Update the status of the thread as "blocked"
      // because it cannot access to the shared resource at this moment

    schedule();
      // Schedule another thread to avoid spinning and wasting CPU time.
  }
}

void Semaphore::signal() {                   
  value++;
    // Increment the value of the semaphore by 1.
    // This means that the process/thread that was using a resource left its critical region
    // and stopped accessing to that resource.

  if (value <= 0) {

    Thread *thd= waitQ.getNextThread();
      // If the semaphore value was negative before this increment,
      // this means that there were waiting processes/threads in the wait queue.
      // In that case, after the shared resource is being released in the previous steps,
      // one of these waiting processes/threads can now start using that resource.
      // In that condition, we pick one thread from the wait queue.

    scheduler->add(thd);
      // And then add the tread to the scheduler.
  }
}
```

Let's give another implementation of semaphores. Imagine that there are two processes: process A and process B: 

```
process A             process B 
----------            ----------
A1                    B1
A2                    B2
signal(s)
A3        \           B3
           \
            \
             \
              \
               \
                \
                 \
                  \
                   \
                     wait(s)
A4                   B4
A5                   B5 
```

And assume that we want the statement A2 in process A to be completed before statement B4 begins in process B. How we can do this ? 

We can put the **signal()** call after A2, and **wait()** call before B4. Through that way, after B1, B2, and B3 are executed, we wait the signal coming from the signal() operation. And that signal only comes after A2 is completed. Through this way, we can ensure that statement A2 is completed before statement B4 begins.

So if we want to summarize: semaphores are elegant solutions for sycnhronization of the processes/threads. But a **race condition** can **occur** like in the other methods if multiple processes/threads try to **execute the wait() and signal() operations simultaneously**. 

For instance, **if one thread** is in the middle of **decrementing the semaphore value** by using **wait()** operation and **another thread** tries to **increment** the same value with **signal()** operation at the same time, that will **cause race condition.**

Therefore, we must **impement the wait() and signal()** operations in **atomic** way so that they should be executed exclusively.

We can make the wait() and signal() operations atomic by using **lock variable** 

```
class Semaphore {
  int lockvar;
    // The lock variable

  int value;
    // The value of semaphore

  queue<Thread*> waitQ;
    // Queue that holds threads that are blocked (waiting) because of the lack of resources.

  void Init(int v);

  void wait();
    // This operation is called by a thread/process when it wants to acquire a resource.

  void signal();
    // This operation is called by a thread/process when it wants to release a resource.
}

void Semaphore::Init(int v) {

  value = v;

  waitQ.init();
    // Initialize an empty queue to hold threads
    // that are blocked (waiting) because of the lack of resources.                         
}

void Semaphore::wait() {
  lock(&lockvar);
    // Lock the lock variable so that when a process/thread acquires resources,
    // no other process/threads can interfere with this.
    // This ensures no two threads can simultaneously modify the semaphore state

  value--;
    // Decrement the value of semaphore by 1.

  if (value < 0) {

    waitQ.add(current_thread);
      // If the new value of the semaphore is negative,
      // this means that resource(s) controlled by the semaphore was already being used.
      // In that case, add current thread into the wait queue because of the lack of available resources.

    current_thread->status = blocked;
      // Update the status of the thread as "blocked"
      // because it cannot access to the shared resource at this moment

    unlock(&lockvar);
      // Unlock the lock variable so that another process/thread can start it's operations.

    schedule();
      // Schedule another thread to avoid spinning and wasting CPU time.
  }
  else {
    unlock(&lockvar);
      // Unlock the lock variable so that another process/thread can start it's operations.
  }
}

void Semaphore::signal() {

  lock(&lockvar);
    // Lock the lock variable so that when a process/thread release resources,
    // no other process/threads can interfere with this.

  value++;
    // Increment the value of the semaphore by 1.
    // This means that the process/thread that was using a resource left its critical region
    // and stopped accessing to that resource.

  if (value <= 0) {

    Thread *thd= waitQ.getNextThread();
      // If the semaphore value was negative before this increment,
      // this means that there were waiting processes/threads in the wait queue.
      // In that case, after the shared resource is being released in the previous steps,
      // one of these waiting processes/threads can now start using that resource.
      // In that condition, we pick one thread from the wait queue.

    scheduler->add(thd);
      // And then add the tread to the scheduler.
  }
  unlock(&lockvar);
    // Unlock the lock variable so that another process/thread can start it's operations.
}

// When a thread is executing the codes above in wait() or signal(),
// it first acquires the lockvar. Any other thread that is trying to call
// wait() or signal() will be blocked.
// So, only one thread at a time can be inside
// its critical region and modfying the semaphore.
```

In the examples above, we used **binary/mutex semaphores**. These semaphores can be seen as lock. They are ideal for mutual exclusion problems. In these problems, when the semaphore value is initialized to 1, this means that the lock is available. 

There is also another type of semaphores that is called **counting semaphores**. This is a type of semaphore that represents the number of processes/threads that are allowed to be in their critical regions at the same time. In cases when we want multiple processes/threads to enter their critical regions simultaenously, we can use counting semaphores. But in these cases, mutual exclusion is not guaranteed. 

Let's review the use case of both **binary/mutex semaphores** and **counting semaphores** in the producer-consumer problem. 

```
#define N 100               // Define the size of the buffer

Semaphore empty = N;        // Define a semaphore to manage the number of emtpy slots in the buffer
Semaphore full = 0;         // Define a semaphore to manage the number of full slots in the buffer
Semaphore mutex = 1;        // Define a semaphore to manage the lock/unlock process and to make operations atomic

T buffer[N];                // Define an empty buffer that has N elements
int widx = 0,               // Define an integer value to write items into the buffer
int ridx = 0;               // Define an integer value to read items from the buffer

Producer(T item) {
    wait(&empty); // Decrement the value of the empty semaphore by one.
                  // If the value of the empty semaphore was 0 before this decrementation,
                  // this means that there is no empty slot in the buffer.
                  // In this case, the producer process will be blocked and
                  // added to the empty semaphore's wait queue.

    wait(&mutex); // Lock the mutex to ensure exclusive access to
                  // the shared buffer before putting a new item to it.
                  // Without this mutex lock,
                  // - Two producers might write to the same position.
                  // - A producer might write to a certain location in the buffer
                  // while the consumer is reading from that location.
                  // - Race conditions would corrupt the data in the buffer. 

    buffer[widx] = item;   // Put an item into the next available empty slot in the buffer
    widx = (widx + 1) % N; // Update the index of the next available empty slot (using modulo to wrap around)

    signal(&mutex); // Unlock the mutex after putting an item into the buffer.

    signal(&full); // Increment the value of the full semaphore by 1.
                   // This indicates "one more filled slot in the buffer"
                   // If the value of the full semaphore was larger than
                   // or equal to N before this incrementation, this means
                   // that the buffer was full, and a consumer waiting on
                   // the full semaphore will be unblocked and added to the ready queue.
}

Consumer(T &item) {
    wait(&full); // Decrement the value of the full semaphore by 1.
                 // If the value of the full semaphore was 0 before this decrementation,
                 // this means that there is no data available in the buffer.
                 // In this case, the consumer process will be blocked
                 // (because there is nothing to consume) and
                 // added to the full semaphore's wait queue.

    wait(&mutex); // Lock the mutex to ensure exclusive access to the shared buffer.

    item = buffer[ridx];   // Read an item from the next available full slot in the buffer
    ridx = (ridx + 1) % N; // Update the index of the next available full slot (using modulo to wrap around)

    signal(&mutex); // Unlock the mutex after reading an item from the buffer.

    signal(&empty); // Increment the value of the empty semaphore by one.
                    // If the value of the empty semaphore was larger than or equal to N
                    // before this incrementation, this means that the buffer was empty,
                    // and a producer process waiting on the empty semaphore will be unblocked
                    // and added to the ready queue.
}
```
At this point, we can see that semaphore is a great way to prevent the race conditions. But we can also use mutex locks to do this. How to decide which one to use ? 

## Binary Semaphores vs Mutex Locks 

In binary semaphores, there is a variable that indicates whether a resource is currently available. In addition, binary semaphores provide a signaling mechanism that enables communication between processes. For instance, Process A may signal Process B to indicate that it added data to a shared buffer. This allows Process B to begin consuming that data immediately. Similarly, a binary semaphore can be used to notify another process that a shared resource is now free. This enables coordination without continuous checking.

In mutex locks, the primary goal is to provide mutual exclusion by allowing only one thread to access a critical section at a time. While mutexes do not expose a user-level signaling mechanism like semaphores, they are designed to block and wake up threads efficiently without busy waiting. Unlike spinlocks, standard mutex implementations rely on the operating system to handle blocking. This ensures that CPU time is not wasted.

In addition, in mutex locks, only the thread that locks the mutex can release it. This prevents other threads releasing the mutex accidentally. In semaphores, however, the resources can be released by any thread after they are locked by a specific thread.

Although **semaphores are great**, like all the other methods, they **have some downsides** as well:

- It is **not** always **easy to write** the codes with semaphores.
- If **a thread dies while holding a semaphore**, the **permit to access to a shared resource is basically lost**. And **this can cause other threads to be blocked from accessing shared resource**. That's why we need to be extra careful when constructing the semaphores.

In addition, they **may cause a situation in which the processes had to wait for resources(s) forever**. **To avoid this** situation, we should

- **acquire the multiple locks in the same order.**
- **release the locks in reverse order ideally.**

And we can show how these solutions work in an example. In below, we can see two very similar but different codes: 

**1st Scenario:**
```
typedef int semaphore;
  semaphore resource_1;
  semaphore resource_2;

  void process_A(void) {
    down(&resource_1);
    down(&resource_2);

    use_both_resources();

    up(&resource_2);
    up(&resource_1);
  }

  void process_B(void) {
    down(&resource_2);
    down(&resource_1);

    use_both_resources();

    up(&resource_1);
    up(&resource_2);
  }

```
In the second case, **process A can acquire the resource 1**, and **process B can acquire the resource 2**. Then **process A will attempt to acquire the resource 2** but **it won't be able to** because the **resource 2 is hold by the process B**. 

Similarly, **process B will attempt to acquire the resource 1** but **it won't be able to because the resource 1 is hold by the process A**. This is called **deadlock** and both processes will wait to hold a resource forever.

But by **acquiring locks in the same order** and **releasing them in the reverse order we can avoid deadlock.**

**2nd Scenario:**
```
typedef int semaphore;   
  semaphore resource_1;
  semaphore resource_2;

  void process_A(void) {
    down(&resource_1);
    down(&resource_2);

    use_both_resources();

    up(&resource_2);
    up(&resource_1);
  }

  void process_B(void) {
    down(&resource_1);
    down(&resource_2);

    use_both_resources();

    up(&resource_2);
    up(&resource_1);
  }

```

In the second case, both process A and process B acquire resources in the same order. In addition, the semaphores ensure that only one of these processes can use a resource at a time. Also, after the resources are used by the processes, they are released. Lastly, the resources are released in reverse order of acquisition. Because of these reasons, we won't see a deadlock in this scenario.

Okay we have mentioned about the deadlock above but one note is that sometimes people can get confused about **deadlock** and **starvation**. That's why it may be useful to define both of them to see the differences between them.

## Deadlock vs Starvation

- **Deadlock**: This occurs when the **processes wait for a resource that will never be available**. 
- **Starvation** The **resource can become available at some point** but **if a process cannot get access to that resource**, **that process will experience starvation**. In other words, **the process waits for its turn but its turn never comes even if there is an available resource**.

**Deadlock occurs** when **none** of the processes are able to **move ahead** while **starvation occurs when a process waits for indefinite period of time to get the resource it needs to move forward**. 

If we want to give an example, **let's say that you submit a large document to printer**. But **if other people keep submitting small documents continuously**, this means that **when one small document is printed, another one starts and your document won't get a chance to be printed** because the resources for printing are continuously being used by some other processes. This is where we see starvation. There is **no deadlock in here because we don't see dependency between processes to move forward**. Deadlock occurs among processes that are **waiting to acquire resources in order to progress forever**.

Okay we compared the deadlock and starvation and explained their differences but we also talked about the resources. What are the things that we call **resource** in general ? 

## Resources

If we want to explain simply, we call **anything** that **needs** to be 

1) **acquired**
2) **used**
3) **released**

 **resource**. 

So, a **printer**, **lock variable**, or **semaphore**, for instance, can be seen as resources because they all need to be acquired, used, and then released.

The resource can be **preemptable** or **nonpreemptable** as well. In other words, sometimes, you can take away some resources from the process while the process is actively using that resource. These resources are preemptable. But not all the resources are like this. There are also other resources that cannot/should not be taken away from the process if it is actively using it. 

We can also divide the resources into two categories: **Reusable**, and **Consumable**. 

**Reusable Resources**: We call a resource reusable if it is/can be used by **ONLY ONE** process at a time **over and over again**. **CPU, I/O channels, memory, data structures such as files, databases, semaphores can be given as an example of reusable resources**. 

**Consumable Resources**: These are the resources that can be created and then destroyed/consumed and once we consume these resources, they are not going to be available to be used anymore. **Interrupts, signals, messages, information in I/O buffers can be given as an example of consumable resources**. 

One thing to note is that when we explained the deadlocks, we have made some **assumptions**. And these are: 

- If a process requests a resource and that resource is unavailable, the process is suspended and put into waiting (sleep) state until the requested resource becomes available for it.
- Once the process is put into the waiting state because of the lack of resources, no interrupt can wake up that process from the sleeping/waiting state. If you can send the signal externally, you can break the deadlock but that is not the definition of the deadlock. That is the definition of how we can recover from a deadlock.

And now, let's explain the **conditions of a deadlock**

- **Each resource is either available or assigned to exactly one process**. Because if resources could be shared, processes would not need to wait for exclusive access to them. 
- **Only one process can use the resource at a time. In other words, the resources cannot be used by multiple processes at the same time.** If multiple processes could use a resource at the same time, they would not need to wait for each other.
- **Processes that are holding resources can request new resources.** In other words, **a process should not release all resources it holds before requesting new resources**. Because if a process holding resources requests new resources, which are held by other processes, this will cause circular dependency which is one of the other conditions of deadlock. Let's say that process A holds resource 1 and it wants resource 2 while process B holds resource 2 and it wants resource 1. If both of these processes hold their resources and want the other resources, neither of them can proceed and this results in a deadlock. However, if process A releases the resource 1 before requesting resource 2 and process B releases the resource 2 before requesting resource 1, this won't result in a deadlock.
- **Granted resources cannot be taken away from a process. They must be explicitly released by the process that is holding them.** Because if resources could be taken away, the system could resolve resource conflicts and avoid deadlocks.
- **There must be a circular chain of 2 or more processes. And each of these processes should be waiting a resource that will be released by the next member (process) of the chain** The circular chain is a fundamental characteristic of a deadlock, as it creates a situation where no process can make progress.

Well, it is good to know the conditions of a deadlock but another important question that we should answer is: when the deadlock happens, how can we deal with them ? 

## How to Deal with Deadlocks ? 

- You can **ignore** them.
- **Let** the deadlock **occurs**, **detect** it, and **take** an **action**.
  -  We can **dynamically manage the resources** to avoid deadlock. **(Deadlock Avoidance)**
  -  We can also **break one of the conditions of the deadlock** and **prevent the deadlock**. **(Deadlock Prevention)**

## Deadlock Detection and Recovery

The **system** actually **does not attempt to prevent the deadlock**. It **just detects the deadlock as it happens**. And **once** it **detects** the deadlock, **it takes actions to recover**.

But the question is: **how we can detect the deadlock ?**
 
### Deadlock Detection with One Resource of Each Type

If there is only 1 resource for each type, in other words if the resources that are used by the processes are unique, constructing a resource graph is a good way to detect the deadlock. Because **if we detect a cycle in that graph, this means that there is a deadlock.**

We can give a system that has one scanner, one plotter, one tape-drive as an example of a system in which there is one resource of eacy type. Having two printers, however, would break the rule. 

Okay now the question is: how to detect cycles ? We can detect it by simply looking at it but how a computer can detect a cycle in a graph ? 

### Formal Algorithm to Detect Cycles

For each node in the graph: 

1) Initialize an empty list L.
2) Add current node to the end of L.
   - If the node appears twice, this means that there is a deadlock and we terminate the algorithm
3) Search for an unmarked outgoing and arc.
   - If there is an unmarked and outgoing arc, jump into the step 4.
   - If there is no unmarked and outgoing arc, jump into the step 5.
4) Pick an unmarked and outgoing arc randomly and mark it. Then follow it to the new node and jump into step 2.
5) If the current node is visited first time, this means that there is no cycle and we terminate the algorithm. Otherwise, we are in dead end and we remove the node and go back to the previous node. Then we jump into the 2nd step.

Okay we have mentioned about the deadlocks, conditions of the deadlock, and how to teach the computer to detect them but one another question is: **when to check for deadlocks ?** 

## When to Check Deadlocks ? 

- We can check **when a resource is requested**.
- We can check **periodically** (e.g. every x minutes)
- We can also **check when CPU utilization drops to a level that is lower than a specific threshold**. Because **if** the **CPU utilization** is **low**, this means that the **amount of time spent for idle tasks** is **high**. And this means that **some processes or threads** are **not making enough progress** and it may be because they are **endlessly waiting for a resource** and **cannot be able to progress** which means a **deadlock**.

Okay let's say that we checked the deadlocks, and detected one. Now the question is: how we can recover from the deadlock ? 

### 1) Recovering from Deadlock Through Preemption

When a deadlock happens, we can **take the resource away from its owner** and give that resource to another process temporarily. And this requires **manual intervention**. We can recover from the deadlock through this way but it is important to note that the decision of whether we should take away the resource from the process or not is **highly dependent on the nature of resource.**

Also, this method is **often not possible** because taking the resource away from the process would cause unpredictable and nonoptimal behavior.  

### 2) Recovering from Deadlock Through Rollback 

We can also **save the state of the processes periodically** (e.g. every x minutes). And **when** a **deadlock** happens, we can **roll the process back to its previous checkpoint.**

But this method may **cause significant delays.**

### 3) Recovering from Deadlock Through Killing Process 

Another simple way to recover from deadlock is **killing process(es).** And we can **continue killing processes until the deadlock is resolved.**

One note is that **killing a process outside of the cycle can release resources that can be used to fix the deadlock**. So we can **kill process(es) outside of the cycle as well**. 

So, until now, we covered deadlocks, its conditions, how to detect them, and how we can recover from them, but we didn't mention about how to **avoid** them **before they happen.**

## Deadlock Avoidance

Most of the times, the resources are requested one at a time and we don't see many cases in which process(es) request(s) mutliple resources at the same time.

One main way to avoid deadlock is granting the resource **only if** it it is **safe** to grant the resource. But what do we mean by **safe** ? 

### Safe and Unsafe States

If there is a sequence of order in which each process in the sequence can run and can be completed, that state is called **safe**. Even if every process requests the maximum number of resources immediately, as long as each process can run and finish without a problem, then the state is safe. 

And an **unsafe** state is a state that will **potentially** result in deadlock in some period. 

In the example below, we see 3 processes: A, B, and C. Process A has 3 resources, B has 2 resources and C has 2 resources. All together, they have 7 resources in total. 

And process A needs 9 resources to be finished while prcoess B needs 4 resources, and process C needs 7 resources. And let's assume that there are 10 instances of resources available in total. 

```
A | 3 | 9
B | 2 | 4
C | 2 | 7

Free: 3
```

So in this example, since we have 10 instances of resources available and all the processes has 7 resources at this moment, there are 3 resources available. We can give 2 of these resources to B and in that case process B will be completed. So we can call this state as **safe** state. 

Once we give 2 of the resources to process B 

```
A | 3 | 9
B | 4 | 4
C | 2 | 7

Free: 1
```

process B will be completed and release all of the resources it was using back.

```
A | 3 | 9
B | 0 | -
C | 2 | 7

Free: 5
```

So now, we have 5 resources. If we give these 5 resources to process A, it won't be enough for it because it needs 6 resources to complete. In that case, we end up with **unsafe** state. So we give these 5 resources to process C. 

```
A | 3 | 9
B | 0 | -
C | 7 | 7

Free: 0
```

and once process C is completed, it will release its resources

```
A | 3 | 9
B | 0 | -
C | 0 | -

Free: 7
```

and we will have 7 resources available. Now we can use 6 resources in process A

```
A | 9 | 9
B | 0 | -
C | 0 | -

Free: 1
```

and complete all the processes.

```
A | 0 | -
B | 0 | -
C | 0 | -

Free: 9
```

In this example, all of these states were **safe** because in each of them, there was a scheduling order in which each process can run and can be completed. 

In another example, let's say that we have a state like this: 

```
A | 3 | 9
B | 2 | 4
C | 2 | 7

Free: 3
```

This is a **safe** safe. Because we can give the 3 resources to the process B. Then process B will return 4 resources and at that moment we will have 5 resources in total and we can give these 5 resources to the process C. Once the process C finishes its execution and releases its 7 resources, we will have 7 resources in total which is enough for the process A. So from this state, there is a guarantee that all processes will finish their execution. That's why this is called **safe state**. 

The difference between a safe and unsafe state is that from a safe state the system can guarantee that all processes will finish; from an unsafe state, no such guarantee can be given

But now let's say that process A acquires one resource in this state. 

```
A | 4 | 9
B | 2 | 4
C | 2 | 7

Free: 2
```

Once that happens, this state becomes **unsafe** because the system cannot guarantee that all processes will finish from here unlike a **safe** state. Because at this step, we can give the available 2 resources only to process B,

```
A | 3 | 9
B | 4 | 4
C | 2 | 7

Free: 0
```

and after process B is completed and it releases all the resources, the total number of resources that is available won't be enough for neither process A or process B.

```
A | 3 | 9
B | 0 | -
C | 2 | 7

Free: 4
```

So in these examples, we tried to avoid the deadlock by using the concepts of **safe** and **unsafe** states. And avoiding the deadlock through this is the basis of a common resource allocation algorithm that is called **Banker's Algorithm**. 

## Banker's Algorithm

The main idea behind this algorithm is checking if granting a resource will lead to an **unsafe** state. If it won't, we just release the resource.

### Applying Banker Algorithm to Single Resource

```
A | 0 | 6
B | 0 | 5
C | 0 | 4
D | 0 | 7

Free: 10

(Safe)
```

```
A | 1 | 6
B | 1 | 5
C | 2 | 4
D | 4 | 7

Free: 2

(Safe)
```

```
A | 1 | 6
B | 2 | 5
C | 2 | 4
D | 4 | 7

Free: 1

(Unsafe)
```

### Applying Banker Algorithm to Multiple Resources

As in the single-resource case, processes must state their total resource needs before executing.


```
Process | Tape Drives | Plotters | Printers | CD ROMs
A       | 3           | 0        | 1        | 1
B       | 0           | 1        | 0        | 0
C       | 1           | 1        | 1        | 0
D       | 1           | 1        | 0        | 1
E       | 0           | 0        | 0        | 0

(How many resources are currently assigned to each process)

```

```
Process | Tape Drives | Plotters | Printers | CD ROMs
A       | 1           | 1        | 0        | 0
B       | 0           | 1        | 1        | 2
C       | 3           | 1        | 0        | 0
D       | 0           | 0        | 1        | 0
E       | 2           | 1        | 1        | 0

(How many resources each process still needs in order to be finished)

Existing Resources: 6 tape drives, 3 plotters, 4 printers, 2 CD ROMs
Allocated Resources: 5 tape drives, 3 plotters, 2 printers, 2 CD ROMs
Available Resources: 1 tape drive, 0 plotters, 2 printers, 0 CD ROMs

```

To find the deadlock, we can

1) look for a row whose unmet resource needs are all smaller than or equal to the values in available resources. If there is no that kind of row, this means that there is a deadlock and terminate.
2) assume the process of the chosen row requests all resources it needs, finishes, mark that process as terminated and release its resources back to the available resources.
3) repeat steps 1 and 2 until either all the processes are terminated or no process is left.

The **Banker Algorithm** looks nice in theory but it is practically **not useful** because 

- **prcoesses don't know the maximum number of resources they will need in advance.**
- the number of processes is not fixed. We can start with process A, B, and C and then other processes might come or some of the existing processes might vanish. In those scenarios, Banker Algorithm is not a good solution.
- resources can vanish.

So checking the safety of states this way is a method of deadlock avoidance which basically means analyzing the resources dynamically and trying to make decisions that will help us to avoid deadlocks beforehand. We can see deadlock avoidance as a more indirect way to prevent deadlocks before they happen.

But we can also try to **prevent the system entering into deadlock directly** by **violating at least one of the conditions of deadlocks**. And this is called **deadlock prevention**

## Deadlock Prevention 

We have mentioned about the conditions of the deadlock. For a deadlock to happen, all of those conditions were suppposed to be met simultaneously. And by violating at least one of these conditions, we can directly prevent the deadlock. Let's start with the first condition.

### 1) Deadlock Prevention: Attacking the Mutual Exclusion

One of the conditions of the deadlock was the mutual exclusion. In other words, if one process is accessing to the resource, no other process is allowed to use that resource until it is released. If we violate this rule, this means that the resources will become sharable among multiple processes simultaneously and these processes can access to the shared resource without waiting another process to release it. 

Spooling can be a way to violate the mutual exclusion rule. A spooler is a program/software that puts the tasks into a queue temporarily. If multiple processes arrives to the spooler simultaneously, instead of giving the resource to one of them and excluding the others, it simply puts all of these processes into the queue in the first come first served manner. And when the resource becomes available, a job is extracted from the queue and the resource is given to that job. In this kind of example, it is impossible to observe deadlock because we don't give the resource to one process and restrict the other processes using that resource until it becomes available. We just put all of the processes into a queue. 

So, attacking the mutual exclusion condition prevents the deadlock directly. But **we cannot apply this procedure in all cases**. **Some resources should be exclusively accessed by one process at a time** and in those cases, this solution cannot be used for those cases. 

### 2) Deadlock Prevention: Attacking the Hold and Wait Condition

Another condition of the deadlock was having process(es) that hold(s) a resource and that wait(s) a new resource to make progress. If we prevent this, in other words, if we prevent processes from waiting for new resources if they are currently holding resources, we can prevent the deadlock as well. 

One way to do this is to make processes to **request all of the resources at the same time before starting the execution.**

Imagine that there is a process named process A. **If all the resources that process A needs are available**, they can be **allocated to the process A** directly and process A can begin execution. But even **if one the requested resources** is **not available**, process A is **not granted any of the resources** and must **wait until all the resources become available**. And once the resources it needs are available to use, it can start. Through this way, **we prevent incremental acquisition of the resources which is the potential cause of the deadlocks**.

**Another way** is to make the process to **release all the resources it holds** **when** it wants to **acquire new resources**. **After releasing all the resources**, now it can try to **acquire all the resources it needs at the same time**. 

### 3) Deadlock Prevention: Attacking No Preemption Condition

The third condition of the deadlock was not allowing preemption. So we can **prevent the deadlock by preempting a resource from a process when the same resource is required by another process**. 

A good strategy to do this is **virtualization**. 

**Virtualization allows multiple virtual machines/containers/etc. to share the same resources**. 

Spooling, for instance, can be seen as virtualization. We can create an abstract layer that separates the logical view of the printer from the physical printer istelf. And after that, processes can interact with spooler instead of directly interacting with the physical printer. 

If a **process** has been **assigned** the **printer** and it is in the **middle** of **printing** its output, **taking away** the **printer** would be **tricky** and sometimes **impossible** **without this abstract layer**. **By** using **spooler**, in other words **virtualizing** the **resources**, spooling printer outputs to disk and allowing only printer daemon to access to the real printer, we can now **preempt** the **resources** and as a result of this we can **prevent deadlocks**. 

However, one thing to note is that **not all resources are eligible to be virtualized.** 

### 4) Deadlock Prevention: Attacking The Circular Wait Condition 

**Method 1:** For us to **observe** the **circular chain of dependencies**, a process should **hold one resource** and **wait another resource**. So, if we have a **rule forcing the processes** to be **entitled to a single** resource at a moment, **we can violate the circular wait condition** and as a result **prevent the deadlock**. According to this rule, **if** a **process** **needs** a **second source while holding another resource**, it must **first release the first resource**. 

**Method 2:** **Another way** to **violate** the **circular wait condition** is having a rule **forcing the processes to request resources in numerical order**. They can **request resources whenever they want** as long as they request **in numerical order**. 

Let's say that we have these resources: 

1) Imagesetter
2) Printer
3) Plotter
4) Tape Drive
5) Blu-ray Drive

So if we apply this method, a **process** may **request** **printer** first and then a **tape** **driver** second but it **can never request a plotter first and then printer second**. 

If we have the **process A and process B**, and the **resources are i and j**, for instance, 

```
A   B
|   | 
i   j
```

**at every instant**, **one of the assigned resources** (i or j) will have the **highest number**. 

**The process** that is **holding that resource** **will never ask for another resource that was already assigned**. **It will either be completed** (if it doesn't require any other source) or **request even higher numbered resources** (and all of them will be available). This way, **circular wait condition won't occur** and as a result we **prevent deadlock**.
