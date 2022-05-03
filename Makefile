
all : hx

hx : hx.c
	$(CC) -o $@ $<

clean:
	rm -f hx
