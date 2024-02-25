# COMPSCI 377 LAB: Context Switch

## Purpose

The purpose of this laboratory experiment is to explore and analyze the concept of context switching within computer systems. Context switching plays a crucial role in the efficient multitasking capabilities of modern operating systems, allowing them to manage multiple tasks concurrently. This lab aims to provide a comprehensive understanding of the mechanisms involved in context switching, its impact on system performance, and the techniques employed by operating systems to facilitate seamless transitions between different execution contexts.

The TA present in your lab will do a brief explanation of the various parts of this lab, but you are expected to answer all questions by yourself. Please raise your hand if you have any questions during the lab section. Questions and Parts have a number of points marked next to them to signify their weight in this lab’s final grade.

Please read through this lab and follow the instructions. After you do that, visit Gradescope and complete the questions associated with this lab by the assigned due date.

**You may work in groups up to 3 to complete this lab. Make sure you submit as a group in Gradescope.**

## Setup

Once you have logged in to Edlab, you can clone this repo using

```bash
git clone  https://github.com/umass-cs-377/377-exercise-context_switch.git
```

Then you can use `cd` to open the directory you just cloned:

```bash
cd 377-exercise-context_switch
```

This repo includes a Makefile that allows you to locally compile and run all the sample code listed in this tutorial. You can compile them by running `make`. Feel free to modify the source files yourself, after making changes you can run `make` again to build new binaries from your modified files. You can also use `make clean` to remove all the built files, this command is usually used when something went wrong during the compilation so that you can start fresh.


## Part 1

In this lab, your task is to implement a basic context switch in a simulated environment. We provide you with two structures: `cpu`, representing CPU registers, and `task_struct`, representing a *process control block* with details such as process ID, state, CPU registers, and maximum run time.

Tasks in the *ready state* are stored in `run_list` for those currently running and `complete_list` for those that have finished execution. The main loop iterates over all processes in the ready state, and a context switch is performed as needed.

Your responsibility is to implement the context_switch() function.

```c++
#include <iostream>
#include <list>
#include <iomanip>  // For std::setw

#define rd() \
    rand()%90 + 10 

#define RUNNING 0
#define READY 1
#define SLEEPING 2
#define EXIT 3

using namespace std;

struct cpu
{
    int eip;
    int esp;
    int exb;
    int exc;
    int exd;
    int pc;
};

struct task_struct
{
    int pid;
    int state;
    struct cpu reg;

    int max_run;
};

list<task_struct *> run_list;
list<task_struct *> complete_list;

void pcb_print(list<task_struct *> l) {

    cout << "PID  STATE  eip  esp  exb  exc  exd  pc  max_run" << endl;

    for(auto pcb : l) {
    cout << pcb->pid << setw(5) << pcb->state << setw(8) << pcb->reg.eip << setw(5) << pcb->reg.esp \
         << setw(5) << pcb->reg.exb << setw(5) << pcb->reg.exc << setw(5) << pcb->reg.exd << setw(4) \
         << pcb->reg.pc << setw(4) << pcb->max_run << endl;
    }

}

void context_switch(struct task_struct *curr, struct task_struct *prev, struct cpu *cpu) {

    // your code goes here 
}

void run() {

    struct cpu cpu;
    struct task_struct *curr = nullptr;
    struct task_struct *prev = nullptr;

    pcb_print(run_list);

    while (run_list.size() > 0) {

        curr = run_list.front();
        run_list.pop_front();

        context_switch(curr, prev, &cpu);

        // do some work
        cpu.pc ++;

        if (cpu.pc < curr->max_run)
            run_list.push_back(curr);
        else
            complete_list.push_back(curr);

        prev = curr;
    }

    context_switch(NULL, prev, &cpu);

    pcb_print(complete_list);
}

int main(int argc, char const *argv[])
{
    // init the list
    for (int i = 1; i<10; i++) {
        struct task_struct *pcb  = new task_struct{i, READY, {rd(), rd(), rd(), rd(), rd(), 0}, i};
        run_list.push_back(pcb);
    }

    run(); 

    //cleanup
    for (auto it = run_list.begin(); it != run_list.end(); ++it) {
        delete *it;
    }
    for (auto it = complete_list.begin(); it != complete_list.end(); ++it) {
        delete *it;
    }

    return 0;
}
```
In the above code, you may notice two new elements, so let's review them. The macro rd() generates a random integer between [10, 100). A macro is a fragment of code that has been given a name. It's a way to define a shorthand for a more extended or complex sequence of instructions. Macros are typically used to simplify code, improve code readability, and make it easier to maintain. The other element is setw(n), which essentially outputs n whitespaces. 