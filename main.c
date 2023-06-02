#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#indlude <time.h>
#include <unistd.h>
#include <sys/types.h>
#include "Process_Sync.c"
#include "scheduler.asm"
#include "IRQ_Timer.asm"
#include "Process_Sync.c"
#include "Memory_Manager.c"
#include "File_Handling.c"
#include "IDT.c"
#include <stdbool.h>

int execv (const char *filename, char *const argv[]);
void *realloc(void *ptr, size_t size);

struct PCB
{
   uint16_t PID;
   char* state;
   char* Program_Name;
   uint16_t PC;
   char* registers; //every register is separated by a space in the array
   uint32_t start_Address;
   uint32_t end_Address;
   uint16_t Parent_PID;
   uint16_t* Child_PIDS;
   uint16_t Priority;
   void* fds;
   char* process_Owner;
   char* process_priviliges;
   char* CPU_USAGE;
};



struct PCB Array_Of_Processes[2];

uint16_t PPID_Create(uint16_t PID)
{
    PCB processPID;
    Array_Of_Processes[0] = processPID;
    if (PID == 0)
    {
    Array_Of_Processes[0] = processPID;
    processPID.PID == 0;
    return execv (processPID.Program_Name,NULL);
    }
    else if (PID == 1)
    {
    Array_Of_Processes[1] = processPID;
    processPID.PID == 1;
    return execv (processPID.Program_Name,NULL);
    }
}
void sleep(uint32_t millis)
{
    uint32_t CountDown = millis;
    while (CountDown > 0)
    {
        halt();
    }
}
void init_Scheduler(void)
{
    __asm__{
    call IRQ0_handler
    };
}
void context_Switch(void)
{
    init_Scheduler();
    if (Array_Of_Processes[0].state == "active")
    {
        process.state == "inactive";
        Array_Of_Processes[1].state == "active";
    }
    else
    {
        Arrary_Of_Processes[1] = "inactive";
        Arrary_Of_Processes[0] = "active";
    }
}

void kill_Process(PID)
{
    size_t size = 1;
    if (PID == 0 && Array_Of_Processes[0] == "active")
    {

        Array_Of_Processes[0].PID = Array_Of_Processes[1].PID;
        Array_Of_Processes[0].state = Array_Of_Processes[1].state;
        Array_Of_Processes[0].Program_Name = Array_Of_Processes[1].Program_Name;
        Array_Of_Processes[0].PC = Array_Of_Processes[1].PC;
        Array_Of_Processes[0].registers = Array_Of_Processes[1].registers;
        Array_Of_Processes[0].start_Address = Array_Of_Processes[1].start_Address;
        Array_Of_Processes[0].end_Address = Array_Of_Processes[1].end_Address;
        Array_Of_Processes[0].Parent_PID = Array_Of_Processes[1].Parent_PID;
        Array_Of_Processes[0].Child_PIDS = Array_Of_Processes[1].Child_PIDS;
        Array_Of_Processes[0].Priority = Array_Of_Processes[1].Priority;
        Array_Of_Processes[0].fds = Array_Of_Processes[1].fds;
        Array_Of_Processes[0].process_Owner = Array_Of_Processes[1].process_Owner;
        Array_Of_Processes[0].process_priviliges = Array_Of_Processes[1].process_priviliges;
        Array_Of_Processes[0].CPU_USAGE = Array_Of_Processes[1].CPU_USAGE;
        realloc(Array_Of_Processes,size);
    }
    else if (PID == 1 && Array_Of_Processes[1] == "active")
    {
        Array_Of_Processes[1].PID = Array_Of_Processes[0].PID;
        Array_Of_Processes[1].state = Array_Of_Processes[0].state;
        Array_Of_Processes[1].Program_Name = Array_Of_Processes[0].Program_Name;
        Array_Of_Processes[1].PC = Array_Of_Processes[0].PC;
        Array_Of_Processes[1].registers = Array_Of_Processes[0].registers;
        Array_Of_Processes[1].start_Address = Array_Of_Processes[0].start_Address;
        Array_Of_Processes[1].end_Address = Array_Of_Processes[0].end_Address;
        Array_Of_Processes[1].Parent_PID = Array_Of_Processes[0].Parent_PID;
        Array_Of_Processes[1].Child_PIDS = Array_Of_Processes[0].Child_PIDS;
        Array_Of_Processes[1].Priority = Array_Of_Processes[0].Priority;
        Array_Of_Processes[1].fds = Array_Of_Processes[0].fds;
        Array_Of_Processes[1].process_Owner = Array_Of_Processes[0].process_Owner;
        Array_Of_Processes[1].process_priviliges = Array_Of_Processes[0].process_priviliges;
        Array_Of_Processes[1].CPU_USAGE = Array_Of_Processes[0].CPU_USAGE;
        realloc(Array_Of_Processes,size);
        Array_Of_Processes[0].state == "active";
    }
}

void main()
{
    PCB tic_tac_toe;
    Arrary_Of_Processes[0] = tic_tac_toe;
    Arrary_Of_Processes[0].state = "active";
    Arrary_Of_Processes[1] = NULL;
    Arrary_Of_Processes[1].state = "inactive";
    context_Switch();
    enable_paging();
    PPID_Create(0);
     // Initialize the IDT
    initIDT();

    // Load the IDT
    loadIDT();

    // Enable interrupts
    enableInterrupts();

  if (!initializeSDL())
    {
        return 1;
    }

    resetGame();

    bool quit = false;
    SDL_Event event;

    while (!quit)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }

            handleInput(event);
        }

        render();
    }

    cleanupSDL();

    return 0;

}
