all: part1.ans part2.ans

part1: part1.c
	$(CC) -o $@ $^

part1.ans: part1 input.txt
	cat input.txt | ./part1 > $@

part2: part2.c
	$(CC) -o $@ $^

part2.ans: part2 input.txt
	cat input.txt | ./part2 > $@

clean:
	rm part1 part1.ans part2 part2.ans

.PHONY: clean
