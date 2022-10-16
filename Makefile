CC = gcc
CFLAGS = -Wall -O2
LIBS = -lm
OBJS = main.o deque.o commands.o
TARGET = main
ARGS = input.txt
DOCS = ./LaTeX/latex
AUX = {aux,fdb_latexmk,fls,log,synctex.gz}

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

run: $(TARGET)
	./main $(ARGS)

clean:
	rm -f $(TARGET) $(OBJS)
	rm -f $(DOCS).$(AUX)