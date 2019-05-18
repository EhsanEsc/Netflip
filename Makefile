
CC = g++
CFLAGS = -std=c++11
OBJ = main.o component.o cp_name.o cp_number.o entity.o user.o sources.o filter.o command_handler.o server.o \
cp_bool.o cp_password.o cp_email.o film.o comment.o notification.o notihandler.o cp_vint.o
COMPONENT_SLIST = sources.h component.h
CP_NAME_SLIST = $(COMPONENT_SLIST) cp_name.h
CP_NUMBER_SLIST = $(COMPONENT_SLIST) cp_number.h
CP_EMAIL_SLIST = $(COMPONENT_SLIST) cp_email.h
CP_BOOL_SLIST = $(COMPONENT_SLIST) cp_bool.h
CP_PASSWORD_SLIST = $(COMPONENT_SLIST) cp_password.h
CP_VINT_SLIST = $(COMPONENT_SLIST) cp_vint.h
ENTITY_SLIST = $(COMPONENT_SLIST) entity.h
USER_SLIST = $(ENTITY_SLIST) user.h
FILM_SLIST = $(ENTITY_SLIST) film.h
NOTIFICATION_SLIST = $(ENTITY_SLIST) notification.h
COMMENT_SLIST = $(ENTITY_SLIST) comment.h
NOTIHANDLER_SLIST = sources.h $(USER_SLIST) $(NOTIFICATION_SLIST)
MAIN_SLIST = $(COMPONENT_SLIST) $(ENTITY_SLIST) $(USER_SLIST) $(CP_NAME_SLIST) $(CP_NUMBER_SLIST) \
$(FILM_SLIST) $(NOTIFICATION_SLIST) filter.h server.h command_handler.h notihandler.h

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
command_handler.o: command_handler.cpp $(MAIN_SLIST)
	$(CC) $(CFLAGS) -c command_handler.cpp -o command_handler.o
server.o: server.cpp $(MAIN_SLIST)
	$(CC) $(CFLAGS) -c server.cpp -o server.o
cp_bool.o: cp_bool.cpp $(CP_BOOL_SLIST)
	$(CC) $(CFLAGS) -c cp_bool.cpp -o cp_bool.o
cp_password.o: cp_password.cpp $(CP_PASSWORD_SLIST)
	$(CC) $(CFLAGS) -c cp_password.cpp -o cp_password.o
cp_email.o: cp_email.cpp $(CP_EMAIL_SLIST)
	$(CC) $(CFLAGS) -c cp_email.cpp -o cp_email.o
cp_vint.o: cp_vint.cpp $(CP_VINT_SLIST)
	$(CC) $(CFLAGS) -c cp_vint.cpp -o cp_vint.o
notification.o: notification.cpp $(NOTIFICATION_SLIST)
	$(CC) $(CFLAGS) -c notification.cpp -o notification.o
comment.o: comment.cpp $(COMMENT_SLIST)
	$(CC) $(CFLAGS) -c comment.cpp -o comment.o
film.o: film.cpp $(FILM_SLIST)
	$(CC) $(CFLAGS) -c film.cpp -o film.o
notihandler.o: notihandler.cpp $(NOTIHANDLER_SLIST)
	$(CC) $(CFLAGS) -c notihandler.cpp -o notihandler.o
clean:
	rm *.o *.out
