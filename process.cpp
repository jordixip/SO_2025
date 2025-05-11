#include "process.h"

Process process_list[MAX_PROCESSES];

int create_process(void (*entry)()) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (!process_list[i].active) {
            process_list[i].id = i;
            process_list[i].eip = (uint32_t)entry;
            process_list[i].active = true;
            return i;
        }
    }
    return -1;
}

void switch_process(int next_id) {
    asm volatile (
        "mov %0, %%esp\n"
        "mov %1, %%ebp\n"
        "jmp *%2\n"
        :
    : "r"(process_list[next_id].esp), "r"(process_list[next_id].ebp), "r"(process_list[next_id].eip)
        );
}

void scheduler() {
    static int current = 0;

    int next = (current + 1) % MAX_PROCESSES;
    while (!process_list[next].active) {
        next = (next + 1) % MAX_PROCESSES;
    }

    switch_process(next);
    current = next;
}