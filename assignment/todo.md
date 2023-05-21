# Pipex, todo


## Preparatory work

### Understand and experiment with unknown or misunderstood syscalls 
### and libcalls

#### level0

- [x] open/close
- [x] access
- [x] unlink
- [x] perror/strerror

#### level1

- [x] wait/waitpid
- [x] exit

#### level2

- [x] execve (and related syscalls)

## Mandatory part

### Initial setup

- [x] Read the assignment again, don't forget any details
- [x] Add libft and ft_printf to the project
- [x] Build the first version of the project makefile

### Project foundations

- [ ] Manage standard input redirection of a cmd to a file (< file1 cmd1)?
	- [x] Redirection FROM a file? Only from a file?
	- [x] What commands accept input from stdin btw? (the filters programs??)
	- [x] Write a draft version of pipex which can manage `< file1 cmd1`
	- [x] Improve that version : source file and functions architecture
	- [x] There a memory leak in your code...
	- [x] Improve that version : use execve instead of execvp... Create the
	function responsible to search PATH to find the right cmd...

- [ ] Manage piping from one command to another (cmd1 | cmd2)
	- [ ]

- [ ] Does < and > create files if they do not exist ?

### Initial tests (& beyond)

- [ ] Find a way to automate tests for this project
- [o] Mind memleaks
- [o] Mind unprotected syscalls
- [x] Mind missing ENV variables (like PATH. What happens if there is no PATH)
- [o] Think about what kind of errors can happen (invalid nb of args, swapped
args...)

## Bonus part

- [ ] Start very early to think about how to manage multiple pipes
(cmd | cmd | cmd)
- [ ] How to manage an here doc (<< here_doc)
- [ ] How to manage a file append instead of a redirect (>> file)
