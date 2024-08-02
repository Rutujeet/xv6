#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"

volatile static int started = 0; // global for cores, used for sync.

// start() jumps to supervisor mode on all cpus

void main()
{
    if (cpuid() == 0) // tasked core 0 to init stuff
    {
        consoleinit();
        printfinit();

        printf("\n");
        printf("xv6 kernel (core 0) is booting\n");
        printf("\n");

        kinit();            // physical page alloc.
        kvminit();          // create kernel page table
        kvminihart();       // turn on paging
        procinit();         // process table
        trapinit();         // trap vectors (indicate which system call to invoke)
        trapinithart();     // install kernel trap vectors
        plicinit();         // set up interrupt controllers
        plicinithart();     // ask PLIC for device interrupts
        binit();            // buffer cache
        iinit();            // inode (a data structure) table (contains all inodes when file system is created)
        fileinit();         // file table
        virtio_disk_init(); // emulated disk
        userinit();         // first user process

        __sync_synchronize(); // asks the compiler to "chill out" and finish everything above first

        started = 1;
    }
    else
    {
        while (started == 0)
            ;
        __sync_synchronize();
        printf("hart %d starting\n", cpuid());
        kvminithart();
        trapinithart();
        plicinithart();
    }

    scheduler(); // looks for a process to execute
}
