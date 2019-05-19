
CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -Wall -Werror -I$(INCLUDE_DIR)
EXECUTABLE_FILE = Netflip.out

OBJ = $(BUILD_DIR)/main.o $(BUILD_DIR)/component.o $(BUILD_DIR)/cp_name.o $(BUILD_DIR)/cp_number.o \
$(BUILD_DIR)/entity.o $(BUILD_DIR)/user.o $(BUILD_DIR)/sources.o $(BUILD_DIR)/filter.o $(BUILD_DIR)/command_handler.o  \
$(BUILD_DIR)/cp_bool.o $(BUILD_DIR)/cp_password.o $(BUILD_DIR)/cp_email.o $(BUILD_DIR)/film.o $(BUILD_DIR)/comment.o \
$(BUILD_DIR)/notification.o $(BUILD_DIR)/notihandler.o $(BUILD_DIR)/cp_vint.o $(BUILD_DIR)/server.o

COMPONENT_SLIST = $(INCLUDE_DIR)/sources.h $(INCLUDE_DIR)/component.h
CP_NAME_SLIST = $(COMPONENT_SLIST) $(INCLUDE_DIR)/cp_name.h
CP_NUMBER_SLIST = $(COMPONENT_SLIST) $(INCLUDE_DIR)/cp_number.h
CP_EMAIL_SLIST = $(COMPONENT_SLIST) $(INCLUDE_DIR)/cp_email.h
CP_BOOL_SLIST = $(COMPONENT_SLIST) $(INCLUDE_DIR)/cp_bool.h
CP_PASSWORD_SLIST = $(COMPONENT_SLIST) $(INCLUDE_DIR)/cp_password.h
CP_VINT_SLIST = $(COMPONENT_SLIST) $(INCLUDE_DIR)/cp_vint.h
ENTITY_SLIST = $(COMPONENT_SLIST) $(INCLUDE_DIR)/entity.h
USER_SLIST = $(ENTITY_SLIST) $(INCLUDE_DIR)/user.h
FILM_SLIST = $(ENTITY_SLIST) $(INCLUDE_DIR)/film.h
NOTIFICATION_SLIST = $(ENTITY_SLIST) $(INCLUDE_DIR)/notification.h
COMMENT_SLIST = $(ENTITY_SLIST) $(INCLUDE_DIR)/comment.h
NOTIHANDLER_SLIST = $(INCLUDE_DIR)/sources.h $(USER_SLIST) $(NOTIFICATION_SLIST)
MAIN_SLIST = $(COMPONENT_SLIST) $(ENTITY_SLIST) $(USER_SLIST) $(CP_NAME_SLIST) $(CP_NUMBER_SLIST) \
$(FILM_SLIST) $(NOTIFICATION_SLIST) $(INCLUDE_DIR)/filter.h $(INCLUDE_DIR)/server.h \
$(INCLUDE_DIR)/command_handler.h $(INCLUDE_DIR)/notihandler.h

$(EXECUTABLE_FILE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE_FILE)
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(MAIN_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o
$(BUILD_DIR)/component.o: $(SRC_DIR)/component.cpp $(COMPONENT_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/component.cpp -o $(BUILD_DIR)/component.o
$(BUILD_DIR)/cp_name.o: $(SRC_DIR)/cp_name.cpp $(CP_NAME_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cp_name.cpp -o $(BUILD_DIR)/cp_name.o
$(BUILD_DIR)/cp_number.o: $(SRC_DIR)/cp_number.cpp $(CP_NUMBER_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cp_number.cpp -o $(BUILD_DIR)/cp_number.o
$(BUILD_DIR)/entity.o: $(SRC_DIR)/entity.cpp $(ENTITY_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/entity.cpp -o $(BUILD_DIR)/entity.o
$(BUILD_DIR)/user.o: $(SRC_DIR)/user.cpp $(USER_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/user.cpp -o $(BUILD_DIR)/user.o
$(BUILD_DIR)/sources.o: $(INCLUDE_DIR)/sources.h $(SRC_DIR)/sources.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/sources.cpp -o $(BUILD_DIR)/sources.o
$(BUILD_DIR)/filter.o: $(SRC_DIR)/filter.cpp $(INCLUDE_DIR)/filter.h $(MAIN_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/filter.cpp -o $(BUILD_DIR)/filter.o
$(BUILD_DIR)/command_handler.o: $(SRC_DIR)/command_handler.cpp $(MAIN_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/command_handler.cpp -o $(BUILD_DIR)/command_handler.o
$(BUILD_DIR)/server.o: $(SRC_DIR)/server.cpp $(MAIN_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/server.cpp -o $(BUILD_DIR)/server.o
$(BUILD_DIR)/cp_bool.o: $(SRC_DIR)/cp_bool.cpp $(CP_BOOL_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cp_bool.cpp -o $(BUILD_DIR)/cp_bool.o
$(BUILD_DIR)/cp_password.o: $(SRC_DIR)/cp_password.cpp $(CP_PASSWORD_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cp_password.cpp -o $(BUILD_DIR)/cp_password.o
$(BUILD_DIR)/cp_email.o: $(SRC_DIR)/cp_email.cpp $(CP_EMAIL_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cp_email.cpp -o $(BUILD_DIR)/cp_email.o
$(BUILD_DIR)/cp_vint.o: $(SRC_DIR)/cp_vint.cpp $(CP_VINT_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cp_vint.cpp -o $(BUILD_DIR)/cp_vint.o
$(BUILD_DIR)/notification.o: $(SRC_DIR)/notification.cpp $(NOTIFICATION_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/notification.cpp -o $(BUILD_DIR)/notification.o
$(BUILD_DIR)/comment.o: $(SRC_DIR)/comment.cpp $(COMMENT_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/comment.cpp -o $(BUILD_DIR)/comment.o
$(BUILD_DIR)/film.o: $(SRC_DIR)/film.cpp $(FILM_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/film.cpp -o $(BUILD_DIR)/film.o
$(BUILD_DIR)/notihandler.o: $(SRC_DIR)/notihandler.cpp $(NOTIHANDLER_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/notihandler.cpp -o $(BUILD_DIR)/notihandler.o

.PHONY: clean
clean:
	rm $(BUILD_DIR)/*.o *.out
