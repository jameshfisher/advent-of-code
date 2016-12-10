all: part1.ans

part1: part1.c
	$(CC) -o $@ $^

part1.ans: part1 input.txt
	cat input.txt | ./part1 > $@

clean:
	rm part1 part1.ans

.PHONY: clean
