
all: a.out hello.out

hello.o: hello.asm
	nasm hello.asm -felf64

a.out: hello.o
	ld $(<) -o $(@)

hello.out:
	ld -T linker.ld -o $(@)
	@objdump -D hello.out | grep -e "\.text" -e "\.data" -A 2 | sed 's/^/[objdump] /g'

clean:
	rm -f *.o *.out
