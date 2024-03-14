**Concurrency**: Executing multiple instructions in an interleaved manner. 

**Parallelism**: Distributing multiple instructions into different resources and running them at the same time in parallel. 

# Inter-Process Communication

In computer, there are programs that basically includes set of instructions that can handle some specific task. 

These instructions/codes are stored in disk or memory and cannot help us to do what we want directly. Therefore, they should be executed by the CPU. 

When these set of instructions are executed, we can call the process of the execution of these instructions as **process**.

In a specific time window, there might be multiple processes that need to work with each other and share resources to be able to finish their executions successfully and efficiently.

In addition, there might be some key points that need attention during this inter-process communication: 

1) The way these processes pass information to each others.
2) Ensuring that two processes don't interfere with each other.
3) Ordering the processes properly if there is a dependency: *If process A produces data and process B prints these data, process B has to wait until process A produce data to print.*

We have mentioned that sometimes multiple processes can share the same resource. And one of the resource they may share might be the storage (e.g. main memory, shared file). 

Print spooler is a perfect example to this. A print stooler is basically a program that queues the print jobs that are sent from an application to a printer. 
When a process wants to print a file, for example, it enters the name of the file into the spooler directory which is where the information about the file is stored. And another separate process (printer daemon) periodically checks if there is any file in spooler directory to be printed. 
If there is a file to be printed, it's printed and then it's file name is removed from the spooler directory.

With this procedure, the print jobs do not need to be sent to the printer directly. The benefit of applying this procedure is that sending print jobs to the printer directly may cause two print jobs to interfere with each other if multiple users are trying to use the printer simultaneously. And by storing the print jobs this way, we may prevent this kind of problem. 

Also, if we wouldn't use spooler directory, processes wouldn't be aware of each other at all.

Using a shared storage like this is cool but it brings another issue: **race condition**. 

**Race Condition**: When two or more processes read from the same resource and also write into the same resource at the same time, the final result depends on the running time of these processes. And we call this condition as **race condition** since the processes are kind of racing with each other to do their tasks.

# Intra-Process Communication

We have mentioned about the processes as well as the inter-process communication. One thing to note is that in processes, there might be multiple smaller units of execution and we call these units **threads**. In a process, if there are multiple threads, these threads work together and share the same address space and other resources. Therefore, there should be some kind of communication between them as well. 

And the three key points that need to be emphasized and that we mentioned in inter-process communications are valid in here as well: 

1) The way these threads pass information to each others.
2) Ensuring that two threads don't interfere with each other.
3) Ordering the threads properly if there is a dependency.

Until now we have talked about scenarios in which multiple processes/threads access/modify the shared resources simultaneously. This situation may (and will) end up with many problems if it is not handled properly.

And the **Read-Modify-Write Cycles** is a concept that are useful to introduce before going through different solutions for preventing these problems. 

# Read-Modify-Write Cycles

When multiple processes or threads are accessing/sharing/modifying the shared data, a specific sequence of operations must be performed in order to ensure data consistency and integrity. This sequence of operations is what we call **Read-Modify-Write Cycle**. The overall goal is for the code to reach consistent/same view of the data. 

- **Read**: Reading the current value of a memory location from the memory is called **read**.
- **Modify**: Some operation is performed on the value that was read from a memory location and this is called **modify**. 
- **Write**: The modified value is written back to the same memory location from where the value was read in the first step.

One note is that some parts of this cycle should be atomic. Otherwise, we may end up with race conditions and data inconsistency.

# Preventing Race Conditions

A way to prevent race conditions is to prevent more than one process or thread from reading and modifying the shared data at the same time. In other words, if one process or thread uses a shared variable or file, the other processs or threads should be excluded from doing the same thing and we call this **mutual exclusion**.

And the section of the program/codes in which shared resources are accessed is called **critical region**. 

If we can develop a system in which two or more processes never be within their critical regions at the same time, we can prevent race conditions. But the issue is that if we develop the system with this way (in other words if we only try to prevent multiple processes from being in their critical regions at the same time) we prevent race conditions but we also prevent parallel processes to cooperate correctly and to use shared resources efficiently. 

So to prevent the race conditions and data inconsistency in shared resources in a more efficient and better way, we should introduce these additional 3 conditions: 

1) We shouldn't take the speed or the number of CPUs into account. (Not relying on assumptions about the speed of processors or the number of them helps us to develop a system that can be used in different systems)
2) If there is a process running outside its critical region, it shouldn't block any process. (This will ensure that processes do not block each other unnecessarily when they are not accessing shared resources)
3) There should be no process that is waiting to enter its critical region forever. (This will prevent starvation)

in addition to the first condition that we defined previously 

4) Two processes should not be in their critical regions at the same time.

Now let's try to find a method that can meet all of these four conditions. 

# Mutual Exclusion with Busy Waiting

**Interrupts:** Let's say that there is a process that is currently in it's critical region and call this process as process A. One of the conditions of preventing race conditions was to exclude all other processes to enter their critical regions while process A is in it's critical region. The simplest way to do this is using **interrupts**. So, if process A disables all the interrupts just after it enters it's critical region and then re-enable these interrupts just before leaving the critical region, it can access/modify the shared memory exclusively without the fear of intervention. 

But using only this approach is not a good option because it is not the best practice to give the process in user space the ability to turn off the interrupts since it may forget to turn on the interrupt after leaving the critical region and that would cause many problems. In addition, disabling interrupts will affect only the CPU that executed the process A (because process A was the one that disabled interrupts in our example). In this case, we don't prevent the processes in other CPUs intervening the process A and entering their own critical regions while the process A is in it's critical region. 

So in summary, using interrupts to provide mutual exclusion is not the best way. 

**Lock Variables:** Another way to apply mutual exclusion is using **lock variables**. Instead of interrupts, we can use a variable, which we call lock variable, that takes a value of 0 or 1. 

If the process A enter it's critical region, it can set this lock variable as 1 which basically means that the critical section is occupied at this moment. And if other processes try to enter their critical regions, they will see that lock variable is 1 and they will have to wait until the lock variable is set to 0 (which means the critical region is left and one process can now enter it's own critical region).

But when we use just lock variables, we might encounter with the problem that we observe with print spooler: Sometimes two processes can see the lock variable as 0 at the same time and as a result, they can both enter their critical regions simultaneously. 

Now, let's say that there are two processes: 

```
Process A:

while (TRUE) {
  while (turn!=0) {} // Wait until turn = 0
  critical_region(); // If turn = 0, enter to critical region.
  turn = 1;        
  noncritical_region();
}
```

```
Process B:

while (TRUE) {
  while (turn!=1) {} // Wait until turn = 1
  critical_region(); // If turn = 1, enter to critical region.
  turn = 0;
  noncritical_region();
}
```

When process A leaves the critical region, it sets the turn variable to 1 to allow the process B to enter it's critical region. Suppose that process B finishes its critical region quickly. After then, the turn variable will be set to 0 and both process A and process B will be in their non critical regions. If process A executes it's loop again, enters the critical region, sets the turn variable as 1, and enters it's non critical region, both process A and B will be in their non critical regions and turn variable will be equal to 1. At that moment, if process A finishes it's non-critical region and goes back to the top of it's loop, it won't be permitted to enter it's critical region because turn=1. 

That's why, this kind of procedure is not a good solution because it violates the 2nd condition that we defined previously: 

1) We shouldn't take the speed or the number of CPUs into account. (Not relying on assumptions about the speed of processors or the number of them helps us to develop a system that can be used in different configurations)
2) **If there is a process running outside its critical region, it shouldn't block any process. (This will ensure that processes do not block each other unnecessarily when they are not accessing shared resources)**
3) There should be no process that is waiting to enter its critical region forever. (This will prevent starvation)
4) Two processes should not be in their critical regions at the same time.

So using just lock variables is not the best method to achieve mutual exclusion as well. Let's take a look at other methods.

## Peterson's Solution for Achieving Mutual Exclusion

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

The other methods that are used to do ensure mutual exclusion and prevent race condition are called Test and Set Lock and XCHG.

## TSL (Test and Set Lock)

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
  
## XCHG

```
enter_region:
  MOVE REGISTER, #1   | Load the value of 1 into the register.
  XCHG REGISTER, LOCK | Swap the value of the register with the lock

    // Let's say that the current value of the lock is 0.
    // The processor reads this value in the lock.
    // And then it writes the current value of the register (1) to lock,
    // and writes the value of the lock (0) into the register at the same time.
    // After this, the register is now equal to 0 (which means the lock is acquired)
    // and the lock is now equal to 1 (which represents a locked state)
    // So by storing the initial value of the lock (0) in the register
    // and using the swap operation,
    // we can check the initial value of the lock and set the lock variable
    // to a desired state in an atomic operation.
    // And this atomic operation prevents the situation in which
    // one process (e.g. process A) checks the lock variable and another process (e.g. process B) acquires the lock
    // before the process A sets the lock variable.

  JNE enter_region    | If the value in register is not 0, this means that the lock is already set and some process in it's critical region. So in that case, wait until that process leaves the critical region by jumping into enter_region until the value in register is 0.
  RET                 | Return, indicating that lock is acquired and critical region is entered..

leave_region:
  MOVE_LOCK, #0       | Store the value of 0 in lock variable meaning that the lock is released.
  RET                 | Return, indicating that the lock is released.
```  

So, the solutions we tried until now, **Peterson's solution**, **TSL**, and **XCHG**, to achieve mutual exclusion and prevent race conditions were correct. But they had some issues. 

For instance, they have the defect of busy waiting. In other words, when a process wants to enter it's critical region, it checks to see it is allowed to enter. If not, the process just sits in the loop and wait until the entry is allowed. And this waiting process wastes the CPU time. That's why it is not the best practice.

In addition, suppose  that there are two processes: process A and process B and the priority of process A is higher than the priority of process B. When we use methods like **Peterson's solution**, **TSL**, or **XCHG**, there is a chance that process A can be prevented from entering it's critical region because process B is currently in it's critical region and holding the lock variable. And this is called **priority inversion**. 

So in the next steps, we will try to find a way to eliminate the busy waiting and priority inversion problems as much as possible. 

# Lock Implementation with Semi-Busy Waiting 

```
mutex_lock: 
  TSL REGISTER, MUTEX | Copy the mutex (mutual exclusion) lock to register. Then set mutex lock to 1.
  CMP REGISTER, #0    | If the value of the mutex lock was 0, this means that mutex lock was available. In that case, jump into the JZE command and return. If the value of the mutex lock was 1, this means that mutex lock was not available. In that case, jump into the CALL command.
  JZE ok
  CALL thread_yield   | Mutex lock is not available. Schedule another process/thread

    // Instead of checking the status of the lock repeatedly (busy-waiting),
    // and wasting CPU time, we can allow another process/thread to run.

  JMP mutex_lock      | and run the mutex_lock again with a new process/thread.
  RET                 | Return, indicating that lock is acquired and critical region is entered..

mutex_unlock:
  MOVE_MUTEX, #0       | Store the value of 0 in lock variable meaning that the lock is released.
  RET                 | Return, indicating that the lock is released.
```

We mentioned about process/thread trying to acquire a lock. And if the lock is not available for that process/thread, we call this ```lock contention```. 

# Lock Contention

Lock contention depends on 

1) the frequency of attempts to acquire the lock      (as the number of attempts to acquire the lock increases, the probability of lock contention increases)
2) the amount of time a process/thread holds the lock (if a process hold the lock very short time, the probability of lock contention decreases)
3) number of processes/threads that acquired the lock (as the number of processes that want to acquire the lock increases, the probability of lock contention increases)

If the lock contention is low, this means that the length of time a process/thread waits for the lock variable to be unlocked is low. In other words, processes/threads don't wait too much and in that kind of scenario, TSL might be a good solution.

# Producer-Consumer Problem

In producer-consumer problem, there are two processes. And t hey share a common buffer which it's size is fixed. 

One of these two processes produces information and puts it into this buffer. We call this process **producer**. Another process takes this information from the buffer and we call this process **consumer**. 

Now imagine that the buffer is full and there is no empty space. In that case, if the producer wants to put a new information into this buffer, that would cause a problem. The solution in here is for the producer to go to sleep, and when the consumer removes one or more items and buffer has empty slot(s), the producer can be awakened and put it's information into the buffer. 

Similarly, if the buffer is completely empty, and if the consumer wants to remove an item from that buffer, that's a problem too since there is nothing to remove. The solution for the consumer is to sleep and once the producer puts an information to the buffer and buffer becomes non-empty, the consumer can be awakened and consume the information in the buffer.

Here is a smiple application of this problem:

```
#define N 100                // The length of buffer
int count = 0;               // Number of items in the buffer

void producer(void) {
  int item = produce_item(); // Produce the next item
  if (count == N) {
    sleep();                 // If the buffer is full, don't put the item into the buffer and sleep until being awakened
  }
  insert_item();             // Now put the item into the buffer
  count++;                   // Increase the number of items in the buffer by 1
  if (count == 1) {
    wakeup(consumer);        // If an item is available in the buffer, wake up the consumer and let it know about this
  }
}

void consumer(void) {
  if (count == 0) {      
    sleep();                 // If the buffer is empty, don't attempt to extract item from the buffer and sleep until being awakened
  }
  int item = remove_item();  // Now extract an item from the buffer
  count--;                   // Decrease the number of items in the buffer by 1
  if (count == N-1) {
    wakeup(producer);        // If the buffer was full before extracting an item, this means that an empty slot became available in the buffer. In that case, wake up the producer and let it know about this so that it can put a new item into the buffer if it is waiting. 
  }
  consume_item(item);
}
    
```

But there are some key points that we should consider: 

If we look at from the producer's perspective: 

1) How can the producer know if a slot is free or not ?
2) If the slot is not free, how can the producer know if it/when it will become free ?

And if we look at from the consumer's perspective: 

1) How can the consumer know if an information is available in the buffer ?
2) If there is nothing available to consume in the buffer, how can the consumer know if/when an information will become available ?

To answer these questions, we should first introduce a new concept named **Pipe**. 

## Pipe 

Pipe is basically an inter-process communication mechanism that provides temporary storage between processes. A pipe is basically implemented with a buffer data structure in the kernel. And in the produer-consumer problem, the output of the producer is passed to this buffer and the consumer takes the information from the same buffer. 

When the buffer is full, pipe blocks the producer to put a new information to it. Similarly, when the buffer is empty, it blocks the consumer to prevent it to attempt consuming an information from an empty buffer. 

And when a space becomes available in the buffer, the pipe unblocks the producer. Similarly, when some data becomes available in the buffer, the pipe unblocks the consumer. 

So, in summary pipe is a unidirectional data channel that can be used for inter-process communication. You can create pipes between two processes or threads to ensure smooth data flow between processes/threads. 


In the producer-consumer problem above, the access to the count variable is not constrained. That's why a race condition might occur. 

For instance, let's assume that the buffer is empty and the consumer reads the count variable to see if it is 0 or not. At that moment, consumer starts sleeping since it finds the count value as 0. Then let's say that scheduler starts running the producer. Producer produces an item and inserts it into the buffer since the buffer is not full, increments the value of count from 0 to 1, and lastly wakes up the consumer which is technically **not sleeping**.

In another case, let's say that count equals to 1 and consumer begins running it's codes. It will first remove an item from the buffer since count is not 0. Then it will decrease the value of count from 1 to 0 and consume the item without waking up the producer since the buffer was not full before extracting the item from it. So, after consuming the item, the consumer will start the loop again. At that moment, count value equals to 0. That's why the consumer will sleep. Sooner or later, the producer will produce items and fill the whole buffer. At that moment, consumer has already been sleeping and since the buffer is full, the producer will sleep as well and they will both sleep forever. 

The main issue in these two scenarios is that a wake-up call that is sent to a process that is not sleeping is lost. If this wake-up call wouldn't be lost, everything would work fine. 

In addition, we used variables in the form of integers to provide synchronization between processes/threads until now. When we use just an integer value to provide access to shared resources, the processes/threads can access to the shared resources only one at a time.  

So we can develop a new mechanism that allows multiple processes to access to the shared resources simultaneously. We call this mechanism **semaphores**.

# Semaphores 

A semaphore is an integer value just like mutex. But the only way to access it is through two separate operations that are called **wait()** and **signal()**.

- wait():  Decrements the value of the semaphore by 1 which means the resource is acquired. Before this decrementation, if the value of the semaphore was 0 or negative, this means that resource(s) controlled by the semaphore were already being used. And after wait() operation decreases the value of the semaphore by 1, the value of the semaphore will be lower than 0. In that case, we add the current thread into the wait queue, because of the lack of available resources, block it (since it cannot access to the shared resource at this moment), and schedule another thread to avoid spinning and wasting CPU time.

- signal(): Increments the value of the semaphore by 1 which means that the process/thread that was using a resource left it's critical region and stopped accessing to that resource. If the semaphore value was negative before this increment, this means that there were waiting processes/threads in the wait queue. And after we release the resource and increment the value of semaphore by 1, one of these waiting processes/threads can now start using that resource. So in that condition, we pick one thread from the wait queue and add it to the scheduler.

In below, you can see the implementation of Semaphore.

```
class Semaphore {
  int value;             // The value of semaphore
  queue<Thread*> waitQ;  // Queue that holds threads that are blocked (waiting) because of the lack of resources.
  void Init(int v);      
  void wait();           // Wait operation. This operation is called by a thread/process when it wants to release a resource.   
  void signal();         // Signal operation. This operation is called by a thread/process when it wants to acquire a resource.
}

void Semaphore::Init(int v) {
  value = v;
  waitQ.init();          // Initialize an empty queue to hold threads that are blocked (waiting) because of the lack of resources.                         
}

void Semaphore::wait() {                  
  value--;                            // Decrement the value of semaphore by 1. 
  if (value < 0) {                    // If the new value of the semaphore is negative, this means that resource(s) controlled by the semaphore was already being used.
    waitQ.add(current_thread);        // Add current thread into the wait queue, because of the lack of available resources
    current_thread->status = blocked; // Update the status of the thread as "blocked" because it cannot access to the shared resource at this moment
    schedule();                       // Schedule another thread to avoid spinning and wasting CPU time.
  }
}

void Semaphore::signal() {                   
  value++;                              // Increment the value of the semaphore by 1. The process/thread that was using a resource left it's critical region and stopped accessing to that resource. 
  if (value <= 0) {                     // If the semaphore value was negative before this increment, this means that there were waiting processes/threads in the wait queue. 
    Thread *thd= waitQ.getNextThread(); // In that case, after the shared resource is being released in the previous steps, one of these waiting processes/threads can now start using that resource. In that condition, we pick one thread from the wait queue. 
    scheduler->add(thd);                // And then add it to the scheduler.
  }
}
```

Imagine that there are two processes: process A and process B: 

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

And assume that we want the statement A2 in process A to be completed before statement B4 begins in process B. How to do this ? 

We can put the signal() call after A2, and wait() call before B4. Through that way, after B1, B2, and B3 are executed, we wait the signal coming from the signal() operation. And that signal only comes after A2 is completed. Through this way, we can ensure that statement A2 is completed before statement B4 begins.

Semaphores are elegant solutions for sycnhronization of the processes/threads. But a race condition can occur like in the other methods if multiple processes/threads try to execute the wait() and signal() operatiions simultaneously. For instance, if one thread is in the middle of decrementing the semaphore value by using wait() operation and another thread tries to increment the same value in signal() operation at the same time, that will cause race condition. 

Therefore, we must impement the wait() and signal() operations in atomic way so that they should be executed exclusively.

We can make the wait() and signal() operations atomic by using **interrupts** and **lock variable** 

```
class Semaphore {
  int lockvar;           // The lock variable
  int value;             // The value of semaphore
  queue<Thread*> waitQ;  // Queue that holds threads that are blocked (waiting) because of the lack of resources.
  void Init(int v);      
  void wait();           // Wait operation. This operation is called by a thread/process when it wants to release a resource.   
  void signal();         // Signal operation. This operation is called by a thread/process when it wants to acquire a resource.
}

void Semaphore::Init(int v) {
  value = v;
  waitQ.init();          // Initialize an empty queue to hold threads that are blocked (waiting) because of the lack of resources.                         
}

void Semaphore::wait() {
  lock(&lockvar);                     // Lock the lock variable so that when a process/thread acquires resources, no other process/threads can interfere with this.                 
  value--;                            // Decrement the value of semaphore by 1. 
  if (value < 0) {                    // If the new value of the semaphore is negative, this means that resource(s) controlled by the semaphore was already being used.
    waitQ.add(current_thread);        // Add current thread into the wait queue, because of the lack of available resources
    current_thread->status = blocked; // Update the status of the thread as "blocked" because it cannot access to the shared resource at this moment
    unlock(&lockvar);                 // Unlock the lock variable so that another process/thread can start it's operations.
    schedule();                       // Schedule another thread to avoid spinning and wasting CPU time.
  }
  else {
    unlock(&lockvar);                 // Unlock the lock variable so that another process/thread can start it's operations.
  }
}

void Semaphore::signal() {
  lock(&lockvar);                       // Lock the lock variable so that when a process/thread release resources, no other process/threads can interfere with this.                 
  value++;                              // Increment the value of the semaphore by 1. The process/thread that was using a resource left it's critical region and stopped accessing to that resource. 
  if (value <= 0) {                     // If the semaphore value was negative before this increment, this means that there were waiting processes/threads in the wait queue. 
    Thread *thd= waitQ.getNextThread(); // In that case, after the shared resource is being released in the previous steps, one of these waiting processes/threads can now start using that resource. In that condition, we pick one thread from the wait queue. 
    scheduler->add(thd);                // And then add it to the scheduler.
  }
  unlock(&lockvar);                     // Unlock the lock variable so that another process/thread can start it's operations.
}
```

In the examples above, we used **binary/mutex semaphores**. These semaphores can be see nas lock. They are ideal for mutual exclusion problems. In these problems, when the semaphore value is initialized to 1, this means that the lock is available. 

There is also another type of semaphores that is called **counting semaphores**. This is a type of semaphore that represents the number of processes/threads that are allowed to be in their critical regions at the same time. In cases when we want multiple processes/threads to enter their critical regions, we can use counting semaphores. But in these cases, mutual exclusion is not guaranteed. 

Let's review the use case of both binary/mutex semaphores and counting semaphores in the producer-consumer problem. 

```
#define N 100               // Define the size of the buffer

Semaphore empty = N;        // Define a semaphore to manage the number of emtpy slots in the buffer
Semaphore full = 0;         // Define a semaphore to manage the number of full slots in the buffer
Semaphore mutex = 1;        // Define a semaphore to manage the lock/unlock process and to make operations atomic

T buffer[N];                // Define an empty buffer that has N elements
int widx = 0,               // Define an integer value to write items into the buffer
int ridx = 0;               // Define an integer value to read items from the buffer

#define N 100 // Define the size of the buffer

Semaphore empty = N; // Define a semaphore to manage the number of empty slots in the buffer (initially all slots are empty)
Semaphore full = 0; // Define a semaphore to manage the number of full slots in the buffer (initially all slots are empty)
Semaphore mutex = 1; // Define a semaphore to manage the lock/unlock process and to make operations atomic (initially unlocked)

T buffer[N]; // Define an empty buffer that has N elements
int widx = 0; // Define an integer value to write items into the buffer (initially at index 0)
int ridx = 0; // Define an integer value to read items from the buffer (initially at index 0)

Producer(T item) {
    wait(&empty); // Decrement the value of the empty semaphore by one. If the value of the empty semaphore was 0 before this decrementation, this means that there is no empty slot in the buffer. In this case, the producer process will be blocked and added to the empty semaphore's wait queue.

    wait(&mutex); // Lock the mutex to ensure exclusive access to the shared buffer before putting a new item to it.

    buffer[widx] = item; // Put an item into the next available empty slot in the buffer
    widx = (widx + 1) % N; // Update the index of the next available empty slot (using modulo to wrap around)

    signal(&mutex); // Unlock the mutex after putting an item into the buffer.

    signal(&full); // Increment the value of the full semaphore by one. If the value of the full semaphore was larger than or equal to N before this incrementation, this means that the buffer was full, and a consumer waiting on the full semaphore will be unblocked and added to the ready queue.
}

Consumer(T &item) {
    wait(&full); // Decrement the value of the full semaphore by one. If the value of the full semaphore was 0 before this decrementation, this means that there are no full slots in the buffer. In this case, the consumer process will be blocked and added to the full semaphore's wait queue.

    wait(&mutex); // Lock the mutex to ensure exclusive access to the shared buffer.

    item = buffer[ridx]; // Read an item from the next available full slot in the buffer
    ridx = (ridx + 1) % N; // Update the index of the next available full slot (using modulo to wrap around)

    signal(&mutex); // Unlock the mutex after reading an item from the buffer.

    signal(&empty); // Increment the value of the empty semaphore by one. If the value of the empty semaphore was larger than or equal to N before this incrementation, this means that the buffer was empty, and a producer process waiting on the empty semaphore will be unblocked and added to the ready queue.
}
```

So, semaphores are great but like all the other methods, they have some downsides as well. 

- It is not always easy to write the semaphore code. Sometimes, it can be difficult.
- If a thread dies while holding a semaphore, the permit to access to a shared resource is basically lost. And this can prevent other threads being blocked from accessing shared resource even. That's why we need to be extra careful when constructing the semaphores.

In addition, they may cause a situation called **deadlock** which we will explain in an example later. To avoid this situation, we should

- acquire the multiple locks in the same order.
- release the locks in reverse order if possible.

And we can show how these solutions work to avoid what they call **deadlock** in an example. In below, you see two very similar but different codes: 

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
    down(&resource_1);
    down(&resource_2);

    use_both_resources();

    up(&resource_2);
    up(&resource_1);
  }

```

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
    down(&resource_2);
    down(&resource_1);

    use_both_resources();

    up(&resource_1);
    up(&resource_2);
  }

```

In the second case, process A can acquire resource 1, and process B can acquire resource 2. Then process A will attempt to acquire resource 2 but it won't be able to because resource 2 is hold by the process B. Similarly, process B will attempt to acquire resource 1 but it won't be able to because resource 1 is hold by the process A. This is called **deadlock** and both processes will wait to hold a resource forever if they are not interrupted. 

But by applyting the two advices (acquiring locks in the same order and releasing in the reverse order) like we did in the 1st case scenario, we can avoid deadlock.

! Slides between 50 and 72 are passed 

Sometimes people can get confused about **deadlock** and **starvation**. So, let's define both of them in more detail

# Deadlock vs Starvation

- **Deadlock**: This occurs when the processes wait for resource that will never be available. 
- **Starvation** The resource can become available at some point but if a process cannot get access to that resource, that process will experience starvation. In other words, the process waits for its turn but its turn never comes even if there is an available resource.

Deadlock occurs when **none** of the processes are able to move ahead while starvation occurs when a process waits for indefinite time to get the resource it needs to move forward. 

If we want to give an example, let's say that you submit a large document to printer. But if other people keep submitting small documents continuously, this means that when one small document is printed, another one starts and your document won't get a chance to be printed. Because the resources for printing are continuously being used by some other processes. This is where we see starvation. There is no deadlock in here because we don't see dependeny between processes to move forward. Deadlock occurs among processes that need to acquire resources in order to progress.

Okay but still, the definition of resource seems vague. What are the things that we call **resource** in general ? 

# Resources

We call anything that needs to be 

1) acquired
2) used
3) released

 **resource**. 

So, a printer, lock variable, or semaphore, for instance, can be seen as resources because they all need to be acquired, used, and then released.

The resource can be **preemptable** or **nonpreemptable** as well. In other words, sometimes, you can take away some resources from the process while the process is actively using that resource. These resources are preemptable. But not all the resources are like this. There are also other resources that cannot/should not be taken away from the process if it is actively using it. 

We can also divide the resources into two categories: **Reusable**, and **Consumable**. 

**Reusable Resources**: We call a resource reusable if it is/can be used by **ONLY ONE** process at a time **over and over again**. **CPU, I/O channels, memory, data structures such as files, databases, semaphores can be given as an example of reusable resources**. 

**Consumable Resources**: These are the resources that can be created and then destroyed/consumed and once we consume these resources, they are not going to be available to be used anymore. **Interrupts, signals, messages, information in I/O buffers can be given as an example of consumable resources**. 

If you don't know what the interrupt is: interrupt is basically a signal/notification that is sent by hardware or software to the CPU. It indicates that an event happened that requires attention. The interrupts are generated by external devices such as keyboard, mouse, etc. or internal system components such as disk controller, timer, etc. One way to represent interrupts is using a vector of numerical values associated with a specific interrupt type. 

When an interrupt happens, the information of the currently executed process (e.g. registers, program counter, etc.) is saved and the control is transferred to the interrupt handler, which is a software responsbile from handling interrupts. And the intrrupt handler performs the necessary actions. 

And if you don't know what the signal is: signal is a mechanism that is used for inter-process communication. It is sent from one process to another, or from kernel to process to notify the process about an event. Signals can be represented in various ways (e.g. constants, enumerated values, signal numbers that are basically integer values associated with specific signal types, etc.)














  












