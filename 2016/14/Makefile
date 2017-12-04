all: part1

part1: part1.c
	$(CC) -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lcrypto -o $@ $^

clean:
	rm -f part1

.PHONY: clean
