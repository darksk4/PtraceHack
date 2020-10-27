#include<stdio.h>
#include<sys/ptrace.h>
#include<sys/wait.h>
#include<sys/user.h>
#include<sys/syscall.h>
#include<sys/reg.h>

int status;

void changeData(pid_t child)
{
    struct user_regs_struct regs;
    while(true)
    {
        ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
        waitpid(child, &status, 0);
        ptrace(PTRACE_GETREGS, child, NULL, &regs);
        long data = ptrace(PTRACE_PEEKDATA, child, regs.rbp-0x24, NULL);
        if(data & 0xffffffff == 0xffffffff)
            ptrace(PTRACE_POKEDATA, child, regs.rbp-0x24, 1337);
        if(regs.rax == 2)
        {
            ptrace(PTRACE_POKEDATA, child, regs.rbp-0x34, 2);
            return;
        }
    }
}

void breakpointSyscall(pid_t child)
{
    bool isFirstSyscallTrace = false;
    while(true)
    {
        ptrace(PTRACE_SYSCALL, child, 0, 0);
        waitpid(child, &status, 0);
        if(WIFEXITED(status))
            break;
        long orig_rax = ptrace(PTRACE_PEEKUSER, child, sizeof(long)*ORIG_RAX, 0);
        if(orig_rax == SYS_ptrace)
        {
            if(isFirstSyscallTrace)
            {
                changeData(child);
                ptrace(PTRACE_DETACH, child, NULL , NULL);
            }
            else
                isFirstSyscallTrace = true;
        }
    }
}

void parent(pid_t child)
{
    waitpid(child, &status, 0);
    ptrace(PTRACE_SETOPTIONS, child, 0 , PTRACE_O_TRACESYSGOOD);
    ptrace(PTRACE_ATTACH, child, NULL, NULL);
    breakpointSyscall(child);
    return;
}

void child(pid_t child)
{
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    kill(getpid(), SIGSTOP);
    char *args[] = {"program", "__gmon_start__\0", 0};
    execv("./program", args);
}

int main()
{
    pid_t pid = fork();
    if(pid == 0)
        child(pid);
    else
        parent(pid);
    return 0;
}
