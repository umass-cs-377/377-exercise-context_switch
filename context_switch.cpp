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

