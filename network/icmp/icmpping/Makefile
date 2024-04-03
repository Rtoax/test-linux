# 编译makefile
# 荣涛 2020年10月12日

ICMP_INC := -I ./
ICMP_SRC := icmpping.c

ICMP_DEP := icmpping.o

ICMP_TARGET=icmpping

all:$(ICMP_TARGET)


$(ICMP_DEP): $(ICMP_SRC)
	gcc -c $(ICMP_SRC) $(ICMP_INC) -o $(ICMP_DEP)

$(ICMP_TARGET): $(ICMP_DEP)
	gcc $(ICMP_DEP) main.c $(ICMP_INC) -o $(ICMP_TARGET)

clean:
	rm -f $(ICMP_DEP) $(ICMP_TARGET)

