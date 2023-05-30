# Test battery for pipex

## Parallelism tests

- [x] `< /dev/stdin sleep 5 | sleep 5 | sleep 5 > /dev/stdout`
	- execute simultaneously all `sleep` processes for about 5 seconds,
	see time (< /dev/stdin sleep 5 | sleep 5 | sleep 5 > /dev/stdout).
	- no process is blocked as `sleep` does not read `stdin` nor 
	writes `stdout`.
	- `$SHELL` displays the prompt

- [x] `< /dev/zero sleep 5 | sleep 10 > /dev/null`
	- last 10 seconds, use time to check
	- `$SHELL` displays the prompt

## Independent commands tests

- [x] `< /dev/stdin cat | ls /dev/stdout > /dev/stdout`
	- directly list via `ls` the `/dev/stdout` file AS `ls` does not depend on 
	its `stdin` (here the pipe read end) to start processing.
	- wait for the user's input via `/dev/stdout` to start processing `cat`
	- `cat` displays nothing as the result is sent to the write end of the pipe.
	- `$SHELL` displays the prompt (which is not the case with 
	`< /dev/stdin cat` where `cat` just expects more...)

	- (HOT CASE, WATCH OUT!)

## Dependent blocking commands tests

- [x] `< /dev/random cat | head -c 80 > /dev/stdout`
	- displays the first 80 bytes from random.
	- `$SHELL` displays the prompt

- [x] `< /dev/stdin cat | head -c 1 > /dev/stdout`
	- display 1 byte sent by the user, as `head` will close the pipe afterwards.
	- `$SHELL` displays the prompt after 1 more try.

- [x] `< /dev/random yes | head > /dev/stdout`
	- displays 10 `y`
	- `$SHELL` displays the prompt

## Dependent nonblocking commands tests

- [x] `< /dev/stdin cat | tee /dev/null > /dev/stdout`
	- wait for the user's input via `/dev/stdout` to start processing `cat`
	- `cat` reads `/dev/stdin` and displays nothing on `stdout` as the result
	is sent to the write end of the pipe.
	- `tee` reads `stdin` (the read end of the pipe) so the process will be 
	blocked until `cat` sends anything...
	- `$SHELL` does not give back the prompt (send `EOF` via `ctrl+d`)

- [x] `< /dev/urandom strings | nl > /dev/stdout`
	- prints and count INDEFINITELY printable character sequences from 
	/dev/urandom that are at least 4 bytes long
	- `$SHELL` does not give back the prompt

- [x] `< /dev/null yes LOSER | nl > /dev/stdout` 
	- prints `LOSER` indefinitely with the line number
	- `$SHELL` does not give back the prompt

- [x] `< test/infile strings | nl | tee > /dev/stdout`
	- prints the 2 lines that have 4 or more charaters
	- `$SHELL` displays the prompt (`strings` has nothing else to read)

- [x] `< /dev/urandom strings | nl | tee > /dev/stdout`
	- prints and count INDEFINITELY printable character sequences from 
	/dev/random that are at least 4 bytes long
	- `$SHELL` does not give back the prompt (`strings` has always something
	to read)

## Mixed dependence commands tests

- [ ] `< /dev/random yes YAAAAAAAS | yes YESYESYES | head > /dev/stdout`
	- displays 10 `YESYESYES` on stdout
	- `$SHELL` displays the prompt

	- FAILURE : Shell not given back. Cause (hypothesis) the `|` between 
	`yes YAAAAAAAS | yes YESYESYES` is still open, as 
	` yes YESYESYES` does not read from it and do NOT close it...
	`yes YAAAAAAAS` is wrinting indefinitely on the pipe and `pipex` is waiting
	`it`...
