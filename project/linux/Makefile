
# use GNU extensions (-std=gnu11) for clock_gettime and CLOCK_MONOTONIC 
# CXX = gcc
CPPFLAGS = -DOpenRP1210DrvExport
CFLAGS = -Wall -fPIC -g -std=gnu11
LDFLAGS = 
LDLIBS =

SRC_DIR = ../../src
OBJ_DIR = obj
BIN_DIR = bin
INC_DIR = ../../inc
INI_DIR = ../../ini
RP1210_HOME = /home/rp1210

ifeq ($(PREFIX),)
	PREFIX := /usr/lib
endif

LIBNAME := open_rp1210
SOURCES := $(filter-out $(SRC_DIR)/dllmain.c, \
	$(wildcard $(SRC_DIR)/*.c))

OBJECTS := $(subst $(SRC_DIR), $(OBJ_DIR), $(patsubst %.c, %.o, $(SOURCES)))
DEPENDS := $(subst $(SRC_DIR), $(OBJ_DIR), $(patsubst %.c, %.d, $(SOURCES)))

.PHONY: all clean
all: $(LIBNAME)

$(LIBNAME): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) -shared $^ -o $(BIN_DIR)/$@.so $(LDLIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile | $(OBJ_DIR)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) -I${INC_DIR} -MMD -MP -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# requires a user "rp1210" with home directory /home/rp1210
# run install as user rp1210, i.e. sudo -u rp1210 make install
# /home/rp1210/rp121032.ini also needs to be manually modified to include open_rp1210
#  under [RP1210Support], APIImplementations=open_rp1210
install: $(BIN_DIR)/$(LIBNAME).so
	mkdir -p $(RP1210_HOME)/open_rp1210	
	install $(BIN_DIR)/$(LIBNAME).so $(RP1210_HOME)/so
	install $(INI_DIR)/linux/open_rp1210.ini $(RP1210_HOME)/

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(DEPENDS)




