# Test battery for pipex

## Parallelism tests

- [x] `time (< /dev/stdin sleep 5 | sleep 5 | sleep 5 > /dev/stdout)`
	`time ./pipex /dev/stdin "sleep 5" "sleep 5" "sleep 5" /dev/stdout`
	- execute simultaneously all `sleep` processes for about 5 seconds,
	see time (< /dev/stdin sleep 5 | sleep 5 | sleep 5 > /dev/stdout).
	- no process is blocked as `sleep` does not read `stdin` nor 
	writes `stdout`.
	- `$SHELL` displays the prompt

- [x] `time (< /dev/zero sleep 5 | sleep 10 > /dev/null)`
	`time ./pipex /dev/zero "sleep 5" "sleep 10" /dev/null`
	- last 10 seconds, use time to check
	- `$SHELL` displays the prompt

- [x] `time (< /dev/zero sleepina 5 | sleep 10 > /dev/null)`
	`time ./pipex /dev/zero "sleepina 5" "sleep 10" /dev/null`

## Independent commands tests

- [x] `< /dev/stdin cat | ls /dev/stdout > /dev/stdout`
	`./pipex /dev/stdin cat "ls /dev/stdout" /dev/stdout`
	- directly list via `ls` the `/dev/stdout` file AS `ls` does not depend on 
	its `stdin` (here the pipe read end) to start processing.
	- wait for the user's input via `/dev/stdout` to start processing `cat`
	- `cat` displays nothing as the result is sent to the write end of the pipe.
	- `$SHELL` displays the prompt (which is not the case with 
	`< /dev/stdin cat` where `cat` just expects more...)

- [x] `< /dev/random yes YAAAAAAAS | yes YESYESYES > /dev/stdout`
	`./pipex /dev/random "yes YAAAAAAAS" "yes YESYESYES" /dev/stdout`
	- writes indefinitely `YESYESYES` on `/dev/stdout`
	- `$SHELL` does not give back the prompt
	- [x] The leaks are not correctly managed when SIGINT is sent to stop the
	loop. Could be a good idea to move cmdenvs to the stack...

- [ ] `< /dev/random yes YAAAAAAAS | yess YESYESYES > /dev/stdout`
	`./pipex /dev/random "yes YAAAAAAAS" "yess YESYESYES" /dev/stdout`
	- returns `bash: yess: command not found` nothing more.
	- [x] The leaks are not correctly managed on the one of the childs
	- [ ] the error propagates (multiple error messages), which is not good
	either... 

- [ ] `< /dev/random yass YAAAAAAAS | yess YESYESYES > /dev/stdout`
	`./pipex /dev/random "yass YAAAAAAAS" "yess YESYESYES" /dev/stdout`
	- returns `bash: yess: command not found` nothing more.
	- [x] The leaks are not correctly managed on the one of the childs
	- [ ] the error propagates (multiple error messages), which is not good
	either... 
	- [ ] the error messages are intertwinded....

- [x] `< /dev/random yes YAAAAAAAS | yes YESYESYES | yes 42 > /dev/stdout`
	`./pipex /dev/random "yes YAAAAAAAS" "yes YESYESYES" "yes 42" /dev/stdout`
	- writes indefinitely `42` on `/dev/stdout`
	- `$SHELL` does not display the prompt
	- [x] The leaks are not correctly managed when SIGINT is sent to stop the
	loop. Could be a good idea to move cmdenvs to the stack...

## Dependent blocking commands tests

- [x] `< /dev/random cat | head -c 80 > /dev/stdout`
	`./pipex /dev/random cat "head -c 80" /dev/stdout`
	- displays the first 80 bytes from random.
	- `$SHELL` displays the prompt

- [x] `< /dev/stdin cat | head -c 1 > /dev/stdout`
	`./pipex /dev/stdin cat "head -c 1" /dev/stdout`
	- display 1 byte sent by the user, as `head` will close the pipe afterwards.
	- `$SHELL` displays the prompt after 1 more try.

- [x] `< /dev/random yes | head > /dev/stdout`
	`./pipex /dev/random yes head /dev/stdout`
	- displays 10 `y`
	- `$SHELL` displays the prompt

## Dependent nonblocking commands tests

- [x] `< /dev/stdin cat | tee /dev/null > /dev/stdout`
	`./pipex /dev/stdin cat "tee /dev/null" /dev/stdout`
	- wait for the user's input via `/dev/stdout` to start processing `cat`
	- `cat` reads `/dev/stdin` and displays nothing on `stdout` as the result
	is sent to the write end of the pipe.
	- `tee` reads `stdin` (the read end of the pipe) so the process will be 
	blocked until `cat` sends anything...
	- `$SHELL` does not give back the prompt (send `EOF` via `ctrl+d`)
	- [x] The leaks are not correctly managed when SIGINT is sent to stop the
	loop. Could be a good idea to move cmdenvs to the stack...

- [x] `< /dev/urandom strings | nl > /dev/stdout`
	`./pipex /dev/urandom strings nl /dev/stdout`
	- prints and count INDEFINITELY printable character sequences from 
	/dev/urandom that are at least 4 bytes long
	- `$SHELL` does not give back the prompt
	- [x] The leaks are not correctly managed when SIGINT is sent to stop the
	loop. Could be a good idea to move cmdenvs to the stack...

- [x] `< /dev/null yes LOSER | nl > /dev/stdout`
	`./pipex /dev/null "yes LOSER" nl /dev/stdout`
	- prints `LOSER` indefinitely with the line number
	- `$SHELL` does not give back the prompt
	- [x] The leaks are not correctly managed when SIGINT is sent to stop the
	loop. Could be a good idea to move cmdenvs to the stack...

- [x] `< test/infile strings | nl | tee > /dev/stdout`
	`./pipex test/infile strings nl tee /dev/stdout`
	- prints the 2 lines that have 4 or more charaters
	- `$SHELL` displays the prompt (`strings` has NOTHING ELSE to READ)

- [x] `< /dev/urandom strings | nl | tee > /dev/stdout`
	`./pipex /dev/urandom strings nl tee /dev/stdout`
	- prints and count INDEFINITELY printable character sequences from 
	/dev/random that are at least 4 bytes long
	- `$SHELL` does not give back the prompt (`strings` has always something
	to read)
	- [x] The leaks are not correctly managed when SIGINT is sent to stop the
	loop. Could be a good idea to move cmdenvs to the stack...

## Mixed dependence commands tests

- [x] `< /dev/random yes YAAAAAAAS | yes YESYESYES | head > /dev/stdout`
	`./pipex /dev/random "yes YAAAAAAAS" "yes YESYESYES" head /dev/stdout`
	- displays 10 `YESYESYES` on stdout
	- `$SHELL` displays the prompt

- [x] `< /dev/random yes YAAAAAAAS | yes YESYESYES | strings | tee | head > /dev/stdout`
	`./pipex /dev/random "yes YAAAAAAAS" "yes YESYESYES" strings tee head /dev/stdout`
	- displays 10 `YESYESYES` on stdout
	- `$SHELL` displays the prompt
