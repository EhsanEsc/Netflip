
CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -Wall -I$(INCLUDE_DIR)
EXECUTABLE_FILE = Netflip.out
OBJ = $(BUILD_DIR)/main.o $(BUILD_DIR)/component.o $(BUILD_DIR)/cp_name.o $(BUILD_DIR)/cp_number.o $(BUILD_DIR)/recomender.o \
$(BUILD_DIR)/entity.o $(BUILD_DIR)/user.o $(BUILD_DIR)/error.o $(BUILD_DIR)/filter.o $(BUILD_DIR)/command_handler.o  \
$(BUILD_DIR)/cp_bool.o $(BUILD_DIR)/cp_password.o $(BUILD_DIR)/cp_email.o $(BUILD_DIR)/film.o $(BUILD_DIR)/comment.o \
$(BUILD_DIR)/notification.o $(BUILD_DIR)/notihandler.o $(BUILD_DIR)/cp_vint.o $(BUILD_DIR)/meserver.o $(BUILD_DIR)/md5.o \
$(BUILD_DIR)/my_server.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o


#################

COMPONENT_SLIST = $(SRC_DIR)/component.cpp $(INCLUDE_DIR)/cp_headers.h
CP_NAME_SLIST = $(SRC_DIR)/cp_name.cpp $(INCLUDE_DIR)/cp_name.h
CP_NUMBER_SLIST = $(SRC_DIR)/cp_number.cpp $(INCLUDE_DIR)/cp_number.h
CP_EMAIL_SLIST = $(SRC_DIR)/cp_email.cpp $(INCLUDE_DIR)/cp_email.h
CP_BOOL_SLIST = $(SRC_DIR)/cp_bool.cpp $(INCLUDE_DIR)/cp_bool.h
CP_PASSWORD_SLIST = $(SRC_DIR)/cp_password.cpp $(INCLUDE_DIR)/cp_password.h $(INCLUDE_DIR)/md5.h
CP_VINT_SLIST = $(SRC_DIR)/cp_vint.cpp $(INCLUDE_DIR)/cp_vint.h

ENTITY_SLIST = $(SRC_DIR)/entity.cpp $(INCLUDE_DIR)/entity.h
USER_SLIST = $(SRC_DIR)/user.cpp $(INCLUDE_DIR)/entity_headers.h
FILM_SLIST = $(SRC_DIR)/film.cpp $(INCLUDE_DIR)/entity_headers.h $(INCLUDE_DIR)/filter.h
NOTIFICATION_SLIST = $(SRC_DIR)/notification.cpp $(INCLUDE_DIR)/notification.h
COMMENT_SLIST = $(SRC_DIR)/comment.cpp $(INCLUDE_DIR)/comment.h $(INCLUDE_DIR)/user.h

NOTIHANDLER_SLIST = $(SRC_DIR)/notihandler.cpp $(INCLUDE_DIR)/command_handler.h $(INCLUDE_DIR)/component.h $(INCLUDE_DIR)/meserver.h
FILTER_SLIST = $(SRC_DIR)/filter.cpp $(INCLUDE_DIR)/filter.h
ERROR_SLIST = $(SRC_DIR)/error.cpp $(INCLUDE_DIR)/error.h $(INCLUDE_DIR)/cp_headers.h
MD5_SLIST = $(SRC_DIR)/md5.cpp
RECOMENDER_SLIST = $(SRC_DIR)/recomender.cpp $(INCLUDE_DIR)/recomender.h

MAIN_SLIST = $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/command_handler.h
COMMANDHANDLER_SLIST = $(SRC_DIR)/command_handler.cpp $(INCLUDE_DIR)/command_handler.h $(INCLUDE_DIR)/component.h $(INCLUDE_DIR)/meserver.h
SERVER_SLIST = $(SRC_DIR)/meserver.cpp $(INCLUDE_DIR)/meserver.h $(INCLUDE_DIR)/entity_headers.h \
$(INCLUDE_DIR)/cp_headers.h $(INCLUDE_DIR)/filter.h $(INCLUDE_DIR)/notihandler.h $(INCLUDE_DIR)/recomender.h

#################

all: $(EXECUTABLE_FILE)

$(EXECUTABLE_FILE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE_FILE)

$(BUILD_DIR)/component.o: $(COMPONENT_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/component.cpp -o $(BUILD_DIR)/component.o
$(BUILD_DIR)/cp_name.o: $(CP_NAME_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cp_name.cpp -o $(BUILD_DIR)/cp_name.o
$(BUILD_DIR)/cp_number.o: $(CP_NUMBER_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cp_number.cpp -o $(BUILD_DIR)/cp_number.o
$(BUILD_DIR)/cp_bool.o: $(CP_BOOL_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cp_bool.cpp -o $(BUILD_DIR)/cp_bool.o
$(BUILD_DIR)/cp_password.o: $(CP_PASSWORD_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cp_password.cpp -o $(BUILD_DIR)/cp_password.o
$(BUILD_DIR)/cp_email.o: $(CP_EMAIL_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cp_email.cpp -o $(BUILD_DIR)/cp_email.o
$(BUILD_DIR)/cp_vint.o:  $(CP_VINT_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/cp_vint.cpp -o $(BUILD_DIR)/cp_vint.o

$(BUILD_DIR)/entity.o: $(ENTITY_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/entity.cpp -o $(BUILD_DIR)/entity.o
$(BUILD_DIR)/user.o: $(USER_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/user.cpp -o $(BUILD_DIR)/user.o
$(BUILD_DIR)/film.o: $(FILM_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/film.cpp -o $(BUILD_DIR)/film.o
$(BUILD_DIR)/notification.o: $(NOTIFICATION_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/notification.cpp -o $(BUILD_DIR)/notification.o
$(BUILD_DIR)/comment.o: $(COMMENT_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/comment.cpp -o $(BUILD_DIR)/comment.o

$(BUILD_DIR)/filter.o: $(FILTER_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/filter.cpp -o $(BUILD_DIR)/filter.o
$(BUILD_DIR)/notihandler.o: $(NOTIHANDLER_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/notihandler.cpp -o $(BUILD_DIR)/notihandler.o
$(BUILD_DIR)/error.o: $(ERROR_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/error.cpp -o $(BUILD_DIR)/error.o
$(BUILD_DIR)/md5.o: $(MD5_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/md5.cpp -o $(BUILD_DIR)/md5.o
$(BUILD_DIR)/recomender.o: $(RECOMENDER_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/recomender.cpp -o $(BUILD_DIR)/recomender.o

# $(BUILD_DIR)/main.o: $(MAIN_SLIST)
# 	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o
$(BUILD_DIR)/command_handler.o: $(COMMANDHANDLER_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/command_handler.cpp -o $(BUILD_DIR)/command_handler.o
$(BUILD_DIR)/meserver.o: $(SERVER_SLIST)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/meserver.cpp -o $(BUILD_DIR)/meserver.o

# APHTTPE ENGINE MAKEFILE ...

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CFLAGS) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CFLAGS) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CFLAGS) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CFLAGS) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CFLAGS) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CFLAGS) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: $(SRC_DIR)/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp $(INCLUDE_DIR)/command_handler.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: $(SRC_DIR)/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BUILD_DIR)/main.o

# myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o
# 	$(CC) $(CFLAGS) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o  -o myserver.out

#

.PHONY: clean
clean:
	rm $(BUILD_DIR)/*.o *.out

#################

$(INCLUDE_DIR)/component.h : $(INCLUDE_DIR)/error.h
$(INCLUDE_DIR)/cp_bool.h : $(INCLUDE_DIR)/component.h
$(INCLUDE_DIR)/cp_email.h : $(INCLUDE_DIR)/component.h
$(INCLUDE_DIR)/cp_name.h : $(INCLUDE_DIR)/component.h
$(INCLUDE_DIR)/cp_number.h : $(INCLUDE_DIR)/component.h
$(INCLUDE_DIR)/cp_password.h : $(INCLUDE_DIR)/component.h
$(INCLUDE_DIR)/cp_vint.h : $(INCLUDE_DIR)/component.h
$(INCLUDE_DIR)/cp_headers.h : $(INCLUDE_DIR)/component.h $(INCLUDE_DIR)/cp_bool.h $(INCLUDE_DIR)/cp_email.h \
$(INCLUDE_DIR)/cp_name.h $(INCLUDE_DIR)/cp_number.h $(INCLUDE_DIR)/cp_password.h $(INCLUDE_DIR)/cp_vint.h

$(INCLUDE_DIR)/entity.h : $(INCLUDE_DIR)/cp_headers.h
$(INCLUDE_DIR)/user.h : $(INCLUDE_DIR)/entity.h
$(INCLUDE_DIR)/film.h : $(INCLUDE_DIR)/entity.h
$(INCLUDE_DIR)/comment.h : $(INCLUDE_DIR)/entity.h
$(INCLUDE_DIR)/notification.h : $(INCLUDE_DIR)/entity.h
$(INCLUDE_DIR)/entity_headers.h : $(INCLUDE_DIR)/entity.h $(INCLUDE_DIR)/user.h \
$(INCLUDE_DIR)/film.h $(INCLUDE_DIR)/comment.h $(INCLUDE_DIR)/notification.h

$(INCLUDE_DIR)/notihandler.h : $(INCLUDE_DIR)/error.h
$(INCLUDE_DIR)/filter.h : $(INCLUDE_DIR)/cp_headers.h $(INCLUDE_DIR)/entity_headers.h $(INCLUDE_DIR)/error.h
$(INCLUDE_DIR)/error.h :
$(INCLUDE_DIR)/md5.h :
$(INCLUDE_DIR)/recomender.h :

$(INCLUDE_DIR)/command_handler.h : $(INCLUDE_DIR)/error.h $(INCLUDE_DIR)/server.h
$(INCLUDE_DIR)/server.h : $(INCLUDE_DIR)/error.h $(INCLUDE_DIR)/component.h $(INCLUDE_DIR)/notihandler.h
