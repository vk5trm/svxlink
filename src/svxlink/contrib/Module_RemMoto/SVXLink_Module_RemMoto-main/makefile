LDFLAGS=-ludev

cm119: cm119.o $(LDFLAGS)


.PHONY: install
install: cm119
	cp cm119 /usr/local/bin

.PHONY: clean
clean:
	rm -f cm119 *.o
