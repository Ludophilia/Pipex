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

- [ ] How can be managed standard input redirection FROM a file (< file1 cmd1)?
	- [x] Redirection FROM a file? Only from a file?
		- Yes, using anything else returns : ```bash: <command>: No such file
		or directory```
	- [x] What commands accept input from stdin btw? (the filters programs??)
- [ ] 

### Initial tests (& beyond)

- [ ] Find a way to automate tests for this project
- [ ] Mind memleaks
- [ ] Mind unprotected syscalls
- [o] Think about what kind of errors can happen (invalid nb of args, swapped
args...)

## Bonus part

- [ ] Start very early to think about how to manage multiple pipes
(cmd | cmd | cmd)
- [ ] How to manage an here doc (<< here_doc)
- [ ] How to manage a file append instead of a redirect (>> file)
