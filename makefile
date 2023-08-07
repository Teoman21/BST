COURSE = cs240
SEMESTER = spring2023
CP_NUMBER = 4
LASTNAME = Kaman
GITUSERID = Teoman21
EXE = main

REPODIR = ../$(COURSE)-$(SEMESTER)-cp$(CP_NUMBER)-$(GITUSERID)
TARFILE = CP$(CP_NUMBER)_$(LASTNAME)_$(USER)_$(GITUSERID).tar

FLAGS = -Wall -Wextra -g
# FLAGS = -Wall -O3
CC = g++
BIN = bin
OBJ = obj

all: $(BIN)/$(EXE)
	./$(BIN)/$(EXE)
$(BIN)/$(EXE): $(OBJ)/main.o
	$(CC) $(FLAGS) $(OBJ)/main.o -o $@

$(OBJ)/main.o: main.cpp 
	$(CC) $(FLAGS) -c main.cpp -o $@

tar:	clean
	tar cvvf $(TARFILE) $(REPODIR)
	gzip $(TARFILE)

clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE) *.tar.gz