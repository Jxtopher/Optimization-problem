#
# @Author: *
# @License: *
# @Date: *
# @Version: 1
# @Description: Makefile
#

CC = gcc
CFLAGS = 
OFLAGS = -Os # Optimization flags
GFLAGS = -pedantic -Wall -Wextra
DFLAGS = -DDEBUG
FLAGS = $(CFLAGS) $(OFLAGS) $(GFLAGS) $(DFLAGS)
EXEC_NAME = subsetsum

#INCLUDES =
LIBS = -lm
#OBJ_FILES = fichier_1.o fichier_2.o
#INSTALL_DIR = /usr/bin

#all : $(EXEC_NAME)

#$(EXEC_NAME): main.cpp
all : main.c 
	$(CC) $(FLAGS) $< subset_sum_problem.c -o $(EXEC_NAME) $(LIBS)

run:
	./$(EXEC_NAME)

packages-debain:
	apt-get install g++ build-essential

.PHONY: clean

clean:
	rm $(EXEC_NAME)

mrproper:
	rm $(EXEC_NAME) *.o