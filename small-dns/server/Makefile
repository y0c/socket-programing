CC = gcc
OBJS = main.o hashtable.o
TARGET = main.out

.SUFFIXES : .c .o

all : $(TARGET)

$(TARGET) : $(OBJS)
	  $(CC) -o $@ $(OBJS)

clean:
	rm -f $(OBJS) $(TARGET)
