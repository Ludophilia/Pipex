
# Examples of tests

`sleep 1 | sleep 1 | sleep 1`
	(is supposed to last 1 seconds, time (sleep 1 | sleep 1 | sleep 1) for
	proof)

`< /dev/stdin cat | ls /dev/stdout`
	(should list /dev/stdout but wait for the user to input)

`sleep 5 | sleep 10`
	(is supposed to last 10 seconds, time (sleep 5 | sleep 10) for proof)

`yes | head`
	(displays 10 y)