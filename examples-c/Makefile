cc = gcc

src = $(wildcard *.c)
target = $(patsubst %.c, %, $(src) )

%:%.c
	$(cc)  $< -o $@     -lgpioc

all:$(target)

clean:
	-rm $(target)