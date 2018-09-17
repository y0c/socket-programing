CC = gcc
OBJS = server.o logger.o 
TARGET = server.out
 
.SUFFIXES : .c .o
 
all : $(TARGET)
 
$(TARGET) : $(OBJS)
	  $(CC) -o $@ $(OBJS)
 
clean:
	rm -f $(OBJS) $(TARGET)