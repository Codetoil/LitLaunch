# tool macros
CC ?= gcc
CFLAGS := -shared
DBGFLAGS := -g
COBJFLAGS := -c -Wall -Werror -fpic

# path macros
BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src/main/c
DBG_PATH := debug

# compile macros
TARGET_NAME := litlaunch-library-api
VERSION := 0.1.0+build.1
TARGET_NAME := $(TARGET_NAME)-$(VERSION)
ifeq ($(OS),Windows_NT)
	TARGET_NAME := $(addsuffix .dll,$(TARGET_NAME))
else
	TARGET_NAME := $(addsuffix .so,$(TARGET_NAME))
endif
TARGET := $(BIN_PATH)/$(TARGET_NAME)
TARGET_DEBUG := $(DBG_PATH)/$(TARGET_NAME)

# src files & obj files
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# clean files list
DISTCLEAN_LIST := $(OBJ) \
                  $(OBJ_DEBUG)
CLEAN_LIST := $(TARGET) \
			  $(TARGET_DEBUG) \
			  $(DISTCLEAN_LIST) \
			  ../bin/$(TARGET_NAME)

# default rule
default: clean makedir all copy

# non-phony targets
$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(COBJFLAGS) -o $@ $<

$(DBG_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CC) $(COBJFLAGS) $(DBGFLAGS) -o $@ $<

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CC) $(CFLAGS) $(DBGFLAGS) $(OBJ_DEBUG) -o $@

# phony rules
.PHONY: makedir
makedir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH)

.PHONY: all
all: $(TARGET)

.PHONY: copy
copy: 
	@echo cp $(BIN_PATH)/$(TARGET_NAME) ../bin
	@cp $(BIN_PATH)/$(TARGET_NAME) ../bin 

.PHONY: debug
debug: $(TARGET_DEBUG)

.PHONY: clean
clean:
	@echo rm -f $(CLEAN_LIST)
	@rm -f $(CLEAN_LIST)

.PHONY: distclean
distclean:
	@echo CLEAN $(DISTCLEAN_LIST)
	@rm -f $(DISTCLEAN_LIST)