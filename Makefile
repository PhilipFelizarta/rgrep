# Your program must compile with 'make'
# You must not change this file.

CC = gcc
FLAGS = -std=c99 -O0 -Wall -Werror -g -pedantic 

rgrep:
	$(CC) $(FLAGS) rgrep.c -o rgrep

clean:
	rm -rf rgrep *.dSYM

check: clean rgrep
	test "`echo "a\nb\nc" | ./rgrep 'a'`" = "a"
	test "`echo "a\n" | ./rgrep 'a'`" = "a"
	test "`echo "a" | ./rgrep '...'`" = ""
	test "`echo "abc" | ./rgrep '.b.'`" = "abc"
	test "`echo "h\naaaaah" | ./rgrep 'a+h'`" = "aaaaah"
	test "`echo "h\naaaaahhhhh" | ./rgrep 'aa+hh+'`" = "aaaaahhhhh"
	test "`echo "h\naaaaahhhhh\n" | ./rgrep 'aa+hh+'`" = "aaaaahhhhh"
	test "`echo "a" | ./rgrep 'a?a'`" = "a"
	test "`echo "woot\nwot\nwat\n" | ./rgrep 'wo?t'`" = "wot"
	test "`echo "CCCCCCC\nC+\nC++" | ./rgrep '.\+\+'`" = "C++"
	test "`echo "GG" | ./rgrep '.+'`" = "GG"
	test "`echo "woooooo_CSE31.jpg" | ./rgrep 'w.+_...31\.jpg'`" = "woooooo_CSE31.jpg"
	test "`echo "a" | ./rgrep 'a'`" = "a"
	test "`echo "a" | ./rgrep 'b'`" = ""
	test "`echo "b" | ./rgrep '.'`" = "b"
	test "`echo "b" | ./rgrep '..'`" = ""
	test "`echo "abc" | ./rgrep '.b.'`" = "abc"
	test "`echo ".\nperiod" | ./rgrep '\.'`" = "."
	test "`echo "plus\n+" | ./rgrep '\+'`" = "+"
	test "`echo "?\nquestion" | ./rgrep '\?'`" = "?"
	test "`echo "0\n1\n2" | ./rgrep '1+'`" = "1"
	test "`echo "22" | ./rgrep '2+'`" = "22"
	test "`echo "333" | ./rgrep '33?3'`" = "333"
	test "`echo "4444" | ./rgrep '444?44'`" = "4444"
	test "`echo "fine.txt\nreallylong.txt\nabc.txt\ns.txt\nope.pdf" | ./rgrep '...+\.txt'`" = "fine.txt\nreallylong.txt\nabc.txt"
	test "`echo "aaaaa" | ./rgrep 'a+'`" = "aaaaa"
	test "`echo "hidden\nhidin\nhbdwen\nhadbn" | ./rgrep 'h.d..?n'`" = "hidden\nhidin\nhdbwen\nhadbn"
	test "`echo "theyre\nthere\theere\ntherre" | ./rgrep 'they?re'`" = "theyre\nthere"
	test "`echo "cut\cuut\ncu.t" | ./rgrep 'cu\.?t'`" = "cut\ncu.t"
	test "`echo "ab\naab\aaab" | ./rgrep 'a?ab+'`" = "aab\naaab"
	@echo "Passed sanity check."

