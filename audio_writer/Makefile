arm = arm-linux-g++
FLAGS = -g -lm  -lpthread -march=armv4t -msoft-float -mtune=arm920t -mcpu=arm920t
SOURCE = main.cpp 
OBJECT = $(SOURCE:=.o)
EXECUTABLE = wifi 
FS = $(HOME)/SFU/cmpt433/private/fs-qt4.7.3/usr/myApps/
NFS = $(HOME)/SFU/cmpt433/public/


all: clean $(OBJECT)
	$(arm) $(FLAGS) -o $(EXECUTABLE) $(OBJECT)
	cp $(EXECUTABLE) $(NFS)

$(OBJECT): 	
	$(arm) $(FLAGS) -c -o $@ $(@:.o=) 

clean:
	rm -f *.o $(EXECUTABLE)
