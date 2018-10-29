CC = gcc
OBJS = client.o
TARGET = client.out

.SUFFIXES : .c .o

all : $(TARGET)

$(TARGET) : $(OBJS)
	  $(CC) -o $@ $(OBJS) -g -ggdb

clean:
	rm -f $(OBJS) $(TARGET)
