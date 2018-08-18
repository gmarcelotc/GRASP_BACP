CC = g++
CFLAGS = -Wall -m32
RM= rm
RMFLAGS = -rf *.o *~

all: main.cpp 
	$(CC) $(CFLAGS) main.cpp -o bacp
clean:
	$(RM) $(RMFLAGS) bacp