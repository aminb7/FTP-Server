CC = g++
BUILD_DIR = build
SRC_DIR = src
INCLUDE_DIR = include
CFLAGS = -std=c++11 -Wall -Werror -I$(INCLUDE_DIR)

OBJECTS = \
	$(BUILD_DIR)/CommandHandler.o \
	$(BUILD_DIR)/UserIdentityInfo.o \
	$(BUILD_DIR)/User.o \
	$(BUILD_DIR)/Configuration.o \
	$(BUILD_DIR)/Logger.o \
	$(BUILD_DIR)/Utilities.o \
	$(BUILD_DIR)/UserManager.o \

CommandHandlerSensitivityList = \
	$(SRC_DIR)/CommandHandler.cpp \
	$(INCLUDE_DIR)/CommandHandler.h \

ConfigurationSensitivityList = \
	$(SRC_DIR)/Configuration.cpp \
	$(INCLUDE_DIR)/Configuration.h \

UserIdentityInfoSensitivityList = \
	$(SRC_DIR)/UserIdentityInfo.cpp \
	$(INCLUDE_DIR)/UserIdentityInfo.h \

UserSensitivityList = \
	$(SRC_DIR)/User.cpp \
	$(INCLUDE_DIR)/User.h \

LoggerSensitivityList = \
	$(SRC_DIR)/Logger.cpp \
	$(INCLUDE_DIR)/Logger.h \

UtilitiesSensitivityList = \
	$(SRC_DIR)/Utilities.cpp \
	$(INCLUDE_DIR)/Utilities.h \

UserManagerSensitivityList = \
	$(SRC_DIR)/UserManager.cpp \
	$(INCLUDE_DIR)/UserManager.h \

ServerSensitivityList = \
	$(SRC_DIR)/Server.cpp \
	$(INCLUDE_DIR)/Server.h \

ClientSensitivityList = \
	$(SRC_DIR)/Client.cpp \
	$(INCLUDE_DIR)/Client.h \

all: $(BUILD_DIR) Server.out Client.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

Server.out: $(BUILD_DIR)/Server.o $(OBJECTS)
	$(CC) $(CFLAGS) -o Server.out $(BUILD_DIR)/Server.o $(OBJECTS)

Client.out: $(BUILD_DIR)/Client.o $(OBJECTS)
	$(CC) $(CFLAGS) -o Client.out $(BUILD_DIR)/Client.o $(OBJECTS)

$(BUILD_DIR)/CommandHandler.o: $(CommandHandlerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/CommandHandler.cpp -o $(BUILD_DIR)/CommandHandler.o

$(BUILD_DIR)/Configuration.o: $(ConfigurationSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Configuration.cpp -o $(BUILD_DIR)/Configuration.o

$(BUILD_DIR)/User.o: $(UserSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/UserIdentityInfo.o: $(UserIdentityInfoSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/UserIdentityInfo.cpp -o $(BUILD_DIR)/UserIdentityInfo.o

$(BUILD_DIR)/Logger.o: $(LoggerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Logger.cpp -o $(BUILD_DIR)/Logger.o

$(BUILD_DIR)/Utilities.o: $(UtilitiesSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Utilities.cpp -o $(BUILD_DIR)/Utilities.o

$(BUILD_DIR)/UserManager.o: $(UserManagerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/UserManager.cpp -o $(BUILD_DIR)/UserManager.o

$(BUILD_DIR)/Server.o: $(ServerSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Server.cpp -o $(BUILD_DIR)/Server.o

$(BUILD_DIR)/Client.o: $(ClientSensitivityList)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/Client.cpp -o $(BUILD_DIR)/Client.o

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out