PRIVATE_PATH = ~/cmpt433/private/
PUBLIC_PATH = ~/cmpt433/public/

SOURCE_PATH = $(PRIVATE_PATH)myApps/fproj/wat/
DEST_PATH = $(PRIVATE_PATH)fs-qt4.7.3/usr/myApps/

CC_C = arm-linux-gcc
C_FLAGS = -Wall -g -march=armv4t -msoft-float -mtune=arm920t -mcpu=arm920t -lm -lpthread -lnsl

N_C = gcc
NC_FLAGS = -Wall -g -lm -lpthread

app: 
	$(CC_C) $(C_FLAGS) -o wat main.c watworkers.c
	cp $(SOURCE_PATH)wat $(DEST_PATH)
	cp $(SOURCE_PATH)wat $(PUBLIC_PATH)
