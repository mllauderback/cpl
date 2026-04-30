CC := gcc
BIN_DIR := bin
TARGET_NAME := cpl
TEST_RESOURCES_DIR := test_resources
RUN_ARGS := $(TEST_RESOURCES_DIR)/test.cpl
TARGET := $(BIN_DIR)/$(TARGET_NAME)
SRC_DIR := src
BUILD_DIR := build
TESTS_DIR := tests

# Find all .c files in source directory
#SRCS := $(wildcard $(SRC_DIR)/*.c)
SRCS := $(shell find $(SRC_DIR) -name '*.c')
# Find all .h files in source directory
# DEPS := $(wildcard $(SRC_DIR)/*.h)
DEPS := $(shell find $(SRC_DIR) -name '*.h')
# Specify target object files in build directory from SRCS
OBJS := $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Log file for valgrind
LOGS_DIR := logs
DATE := $(shell date +'%Y%m%d-%H%M%S')
LOG := memcheck_${DATE}.log

CFLAGS := -Wall -Wextra
DEBUGFLAGS := -g

# Compile C files with DEPS
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(DEPS)
	@echo "Compiling to objectfiles..."
	@mkdir -p $(@D)
	$(CC) -c -o $@ $< $(CFLAGS)

# Compile object files to target
$(TARGET): $(OBJS)
	@echo "Building executable..."
	@mkdir -p $(@D)
	$(CC) -o $@ $^ $(CFLAGS)
	@echo "Done."

# Run
.PHONY: run
run:
	$(TARGET) $(RUN_ARGS)

# Run with memory leak checks
.PHONY: memcheck
memcheck:
	@echo "Running with memcheck..."
	@mkdir -p $(LOGS_DIR)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --track-origins=yes --log-file="${LOGS_DIR}/${LOG}" ./$(TARGET) $(RUN_ARGS)
	@cat $(LOGS_DIR)/$(LOG)

tests:
	@echo "Compiling tests..."
	@make -C $(TESTS_DIR)

# Compile with debugging flags
# TODO

# Clean build files and executables
.PHONY: clean
clean:
	@echo "Removing object files..."
	@rm -rf $(BUILD_DIR)
	@echo "Removing binary..."
	@rm -f $(TARGET)
	@echo "Done."
