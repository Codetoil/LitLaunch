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

TARGET_FILENAME := litlaunch-library-api

VERSION := 0.1.0+build.2
UNAME_S := $(shell uname -s)
UNAME_P := $(shell uname -p)
TARGET_VERSIONED_FILENAME := $(TARGET_FILENAME)-$(VERSION)-$(UNAME_S)-$(UNAME_P)
ifeq ($(OS),Windows_NT)
	TARGET_FILENAME := $(addsuffix .dll,$(TARGET_FILENAME))
	TARGET_VERSIONED_FILENAME := $(addsuffix .dll,$(TARGET_VERSIONED_FILENAME))
else
	TARGET_FILENAME := $(addsuffix .so,$(TARGET_FILENAME))
	TARGET_VERSIONED_FILENAME := $(addsuffix .so,$(TARGET_VERSIONED_FILENAME))
endif
TARGET := $(BIN_PATH)/$(TARGET_VERSIONED_FILENAME)
TARGET_DEBUG := $(DBG_PATH)/$(TARGET_VERSIONED_FILENAME)

# src files & obj files
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

# clean files list
CLEAN_LIST := $(OBJ) \
			$(OBJ_DEBUG) \
			$(TARGET) \
			$(TARGET_DEBUG) \
			$(DISTCLEAN_LIST) \
			$(BIN_PATH) \
			../bin/$(TARGET_VERSIONED_FILENAME) \
			../bin/$(TARGET_FILENAME)

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
	@echo cp $(BIN_PATH)/$(TARGET_VERSIONED_FILENAME) ../bin
	@cp $(BIN_PATH)/$(TARGET_VERSIONED_FILENAME) ../bin
	@echo cp ../bin/$(TARGET_VERSIONED_FILENAME) ../bin/$(TARGET_FILENAME)
	@cp ../bin/$(TARGET_VERSIONED_FILENAME) ../bin/$(TARGET_FILENAME)

.PHONY: debug
debug: $(TARGET_DEBUG)

.PHONY: clean
clean:
	@echo rm -rf $(CLEAN_LIST)
	@rm -rf $(CLEAN_LIST)