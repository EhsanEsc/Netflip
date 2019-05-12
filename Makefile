
CC = g++
CFLAGS = -std=c++11
OBJ = main.o component.o cp_name.o cp_number.o entity.o user.o sources.o filter.o
COMPONENT_SLIST = sources.h component.h
CP_NAME_SLIST = $(COMPONENT_SLIST) cp_name.h
CP_NUMBER_SLIST = $(COMPONENT_SLIST) cp_number.h
ENTITY_SLIST = $(COMPONENT_SLIST) entity.h
USER_SLIST = $(ENTITY_SLIST) user.h
MAIN_SLIST = $(COMPONENT_SLIST) $(ENTITY_SLIST) $(USER_SLIST) $(CP_NAME_SLIST) $(CP_NUMBER_SLIST) filter.h

a.out: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o a.out
main.o: main.cpp $(MAIN_SLIST)
	$(CC) $(CFLAGS) -c main.cpp -o main.o
component.o: component.cpp $(COMPONENT_SLIST)
	$(CC) $(CFLAGS) -c component.cpp -o component.o
cp_name.o: cp_name.cpp $(CP_NAME_SLIST)
	$(CC) $(CFLAGS) -c cp_name.cpp -o cp_name.o
cp_number.o: cp_number.cpp $(CP_NUMBER_SLIST)
	$(CC) $(CFLAGS) -c cp_number.cpp -o cp_number.o
entity.o: entity.cpp $(ENTITY_SLIST)
	$(CC) $(CFLAGS) -c entity.cpp -o entity.o
user.o: user.cpp $(USER_SLIST)
	$(CC) $(CFLAGS) -c user.cpp -o user.o
sources.o: sources.h sources.cpp
	$(CC) $(CFLAGS) -c sources.cpp -o sources.o
filter.o: filter.cpp filter.h $(MAIN_SLIST)
	$(CC) $(CFLAGS) -c filter.cpp -o filter.o
clean:
	rm *.o *.out
