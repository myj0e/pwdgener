VERSION  =1.00
CC   =gcc
DEBUG   =-DUSE_DEBUG
CFLAGS  =-Wall
SOURCES   =$(wildcard ./*.c)
INCLUDES   =-I./
LIB_NAMES  =
LIB_PATH  =
OBJ   =$(patsubst %.c, %.o, $(SOURCES))
TARGET  =pwdgener

#links
$(TARGET):$(OBJ)
	@mkdir -p output
	$(CC) $(OBJ) $(LIB_PATH) $(LIB_NAMES) -o output/$(TARGET)$(VERSION)
	@rm -rf $(OBJ)
 
#compile
%.o: %.c
	$(CC) $(INCLUDES) $(DEBUG) -c $(CFLAGS) $< -o $@

.PHONY:clean
clean:
	@echo "Remove linked and compiled files......"
	rm -rf $(OBJ) $(TARGET) output 