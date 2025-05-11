#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

struct Process {
    int id;
    uint32_t esp, ebp;
    uint32_t eip;
    bool active;
};

#define MAX_PROCESSES 10
extern Process process_list[MAX_PROCESSES];

int create_process(void (*entry)());
void switch_process(int next_id);
void scheduler();

#endif