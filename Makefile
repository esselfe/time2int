
default:
	gcc -std=c11 -Wall -O2 time2int.c -o time2int

clean:
	@rm -v time2int 2>/dev/null || true
