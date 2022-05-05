//
// fork_6.c
//
// Preventing a child process to become ZOMBIE - Using signal() system call
//
// At the termination of the child, a ‘SIGCHLD’ signal is generated
// and is delivered to the parent by the kernel.
// If the parent call signal(SIGCHLD, SIG_IGN), then the SIGCHLD signal is ignored,
// and the child process entry will be deleted from the process table.
//

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    printf("Test");
    return 0;
}
