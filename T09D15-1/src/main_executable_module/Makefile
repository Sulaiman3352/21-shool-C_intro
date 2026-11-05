#Compiler and flags
CC = gcc
CFLAGS = -Wall -g -lm  # Add math library linking flag

#Directories
SRC_DIR = ../data_libs ../data_module ../yet_another_decision_module ../main_executable_module
BUILD_DIR = ../../build

#Explicitly define the source files to be included
DATA_LIBS_SRCS = $(wildcard ../data_libs/*.c)
DATA_MODULE_SRCS = $(wildcard ../data_module/*.c)  # Include all files in data_module
DECISION_MODULE_SRCS = $(wildcard ../yet_another_decision_module/*.c)  # Include all files in yet_another_decision_module

# Main executable source file (explicitly specifying the main file)
MAIN_EXEC_SRCS = main_executable_module.c  # Specify the main source file explicitly

# Exclude unwanted files (add any files you want to exclude from the build here)
EXCLUDE_FILES = \
    ../yet_another_decision_module/yet_another_decision_module_entry.c \
    ../data_module/data_module_entry.c

# Combine all source files into SRCS, excluding the unwanted files
SRCS = $(filter-out $(EXCLUDE_FILES), $(DATA_LIBS_SRCS) $(DATA_MODULE_SRCS) $(DECISION_MODULE_SRCS) $(MAIN_EXEC_SRCS))

# Debugging: Print the source files found
$(info SRCS: $(SRCS))

# Convert source files to object files
OBJS = $(SRCS:.c=.o)

# Output executable
TARGET = $(BUILD_DIR)/Quest_3

# Standard targets

# Default target: Build everything
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $(TARGET) $(CFLAGS)  # Link with -lm flag for math library

# for 4th Quest
TARGET_1 = $(BUILD_DIR)/Quest_4
build_with_macro: $(TARGET_1)
$(TARGET_1): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $(TARGET_1) $(CFLAGS)

# -------- Static Library: data_stat.a for 5th Quest --------
TARGET_STATIC = $(BUILD_DIR)/Quest_5
LIB_DIR = ../data_libs/
DATA_STAT_SRCS = ../data_libs/data_stat.c
DATA_STAT_OBJS = $(DATA_STAT_SRCS:.c=.o)
STATIC_LIB = $(LIB_DIR)/data_stat.a


# Build data_stat.a from data_stat.c
#$(STATIC_LIB): $(DATA_STAT_OBJ)
#	@mkdir -p $(LIB_DIR)
#	ar rcs $(STATIC_LIB) $(DATA_STAT_OBJ)

# Explicit alias target for data_stat.a so you can run "make data_stat.a"
data_stat.a: $(STATIC_LIB)
$(STATIC_LIB): $(DATA_STAT_OBJ)
	@mkdir -p $(LIB_DIR)
	ar rcs $(STATIC_LIB) $(DATA_STAT_OBJ)

# Build the main executable with static linking
build_with_static: $(STATIC_LIB) $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $(TARGET_STATIC) $(STATIC_LIB) $(CFLAGS)

# -------------- 6th Quest -------------
LIB_NAME = data_process 
FFLAGS = -shared -fPIC
path = ../data_module/data_process.c
prod = ../data_module/data_process.so
TARGET_dynamic = $(BUILD_DIR)/Quest_6
process = ../data_module/data_process.o

data_process.so: $(prod)
$(prod): $(process)
	$(CC) $(process) $(FFLAGS) -o $(prod)

export LD_LIBRARY_PATH=../data_module:$$LD_LIBRARY_PATH
build_with_dynamic: data_process.so $(TARGET_dynamic)
$(TARGET_dynamic): $(OBJS) data_process.so
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) -o $(TARGET_dynamic) ../data_module/data_process.so -lm
#-L.$(prod) $(LIB_NAME) $(FFLAGS)


# Rule for compiling .c files to .o files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean target: Delete object files and executable
clean:
	rm -f $(OBJS) $(DATA_STAT_OBJ) $(TARGET) $(TARGET_STATIC) $(TARGET_1) $(STATIC_LIB) $(prod) $(TARGET_dynamic)

# Rebuild target: Clean and then build everything
rebuild: clean all

# Phony targets (to avoid conflicts with files named clean, all, or rebuild)
.PHONY: clean all rebuild