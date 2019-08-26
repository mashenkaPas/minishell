# minishell
#before running your program,change zsh to bash
#zsh dont support get_next_line. 
#if you want to keep zsh, change get_next_line to readLine();readLine ->also support automatical upload of files.

As beautiful as a shell

![Quick Demo][quick-demo]

## About

Minishell is the second project of the Unix branch at 42.
It's a minimum viable version of a real shell.
The main goal is to have a good understanding of process creation and
synchronisation using the C programmming language.

## Installation & Usage

### Requirements
The only requirements are:
- GNU make (v3.81)
- GCC (v4.2.1)

Those versions are the ones used during development.

### Building the program

1. Download/Clone this repo

        git clone https://github.com/mashenkaPas/minishell
2. `cd` into the root directory and run `make`

        cd minishell
        make

### Running the program

After building the source, run `./minishell` from the project root.

## Main Project Instructions

### Mandatory

- Can only use C
- Must respect the school imposed coding style ([The Norme][norme-pdf])
- No memory leaks
- Implement a series of builtins: `echo`, `cd`, `setenv`, `unsetenv`, `env`, `exit`
- Manage the errors without using `errno`, by displaying a message adapted
to the error output
- Can only use these standard library functions:
    - malloc, free
    - access
    - open, close, read, write
    - opendir, readdir, closedir
    - getcwd, chdir
    - stat, lstat, fstat
    - fork, execve
    - wait, waitpid, wait3, wait4
    - signal, kill
    - exit
- Must have a Makefile to build the program
- The binary file must be named `minishell`
- Can use [Libft][libft-url]
- Handle program interruption (Ctrl + D)
- [Click here][1] for the rest

### Bonuses

- Signal management (specifically Ctrl + C)
- PATH's right management (error handling)
- Multiple commands (semi colons)


## Notes

- You can find the project instructions by https://github.com/mashenkaPas/minishell/blob/master/minishell.en.pdf
- I commented the whole codebase so it's easy to navigate and understand it.
- No need to mention the odd spacing in files, I'm using a tab size of 4.
- There are probably better ways to implement it, we are limited by a set of functions at my school (just to make it harder and give us a deeper understanding of what's happening in the back), please, review the project instructions before you explain how `X` or `Y` would have been a better way to do it ;)


Enjoy!



The objective of this project is for you to create the simplest start of a shell script. Shell is beautiful! Isn’t there a famous saying? “As beautiful as Shell?” Thanks to all the shell projects, you will connect with the infinite power of Mankind Intelligence


amazing resourse https://brennan.io/2015/01/16/write-a-shell-in-c/


# MAIN SYSTEM FUNCTIOINS :

## Chdir


int chdir(const char *path);
The chdir command is a system function (system call) which is used to change the current working directory. On some systems, this command is used as an alias for the shell command cd. chdir changes the current working directory of the calling process to the directory specified in path.


On success, zero is returned.  On error, -1 is returned,

## Fork



Fork system call use for creates a new process, which is called child process, which runs concurrently with process  parent process. function fork return the integer ,if the value is Negative -creation of a child process was unsuccessful,if value 0 returned to the newly created child process. and if value is >0 returned to parent or caller.
### IMPORTANT
Parent process and child process are running the same program, but it does not mean they are identical. OS allocate different data and state for these two processes and also control the flow of these processes can be different.


## Execve



The exec() family of functions replaces the current process image with a new process image. It loads the program into the current process space and runs it from the entry point.

https://linux.die.net/man/3/exec

int execl(const char *path, const char *arg, ...);

int execlp(const char *file, const char *arg, ...);

int execle(const char *path, const char *arg, ..., 
                               char * const envp[]);
                               
int execv(const char *path, char *const argv[]);

int execvp(const char *file, char *const argv[]);

int execvpe(const char *file, char *const argv[], 
                              char *const envp[]);



###           IMPORTANT Fork() vs Exec()



The fork system call creates a new process. The new process created by fork() is copy of the current process except the returned value. The exec system call replaces the current process image with another (different) one.

## Wait



A call to wait() blocks the calling process until one of its child processes exits or a signal is received. After child process terminates, parent continues its execution after wait system call instruction. If program has no child process then wait() returns immediately “-1”.

pid_t wait(int *status);

pid_t waitpid(pid_t pid, int *status, int options);


# IMPORATANT 



if more than one child processes are terminated, then wait() reaps any arbitrarily child process but if we want to reap any specific child process, we use waitpid() function.
WAITPID return pid of child, if child has exited , or 0, if using WNOHANG and child hasn’t exited.


HOW TO find out the status of child process ?

Status information about the child reported by wait is more than just the exit status of the child, it also includes
1. WIFEXITED(status): child exited normally
• WEXITSTATUS(status): return code when child exits


2. WIFSIGNALED(status): child exited because a signal was not caught
• WTERMSIG(status): gives the number of the terminating signal


3. WIFSTOPPED(status): child is stopped
• WSTOPSIG(status): gives the number of the stop signal

## Access


access() checks whether the calling process can access the file pathname. If pathname is a symbolic link, it is dereferenced.


## pid_t 
data type stands for process identification and it is used to represent process ids. 
