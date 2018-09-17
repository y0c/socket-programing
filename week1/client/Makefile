CC = gcc
OBJS = client.o 
TARGET = client.out
 
.SUFFIXES : .c .o
 
all : $(TARGET)
 
$(TARGET) : $(OBJS)
	  $(CC) -o $@ $(OBJS)
 
clean:
	rm -f $(OBJS) $(TARGET)