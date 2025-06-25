

CC = gcc
TARG = shell
OPTS = -Wall -O -g -Werror
SRC_DIR = src
INC_DIR = include


SRC_FILES = $(wildcard $(SRC_DIR)/*.c)

# Object files corresponding to the source files
OBJS = $(SRC_FILES:.c=.o)


CFLAGS = -I$(INC_DIR) $(OPTS)

# Rule to compile the object files
$(TARG).o: $(SRC_DIR)/$(TARG).c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARG): $(OBJS)
	$(CC) -o $(TARG) $(CFLAGS) $(OBJS)

# Rule to create object files from the source files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Default target
all: $(TARG)

docker: docker-build docker-run

# Build the Docker image
docker-build:
	docker build  -t shell-image .

# Run the Docker container
docker-run:
	docker run -it --rm $(TARG)-image

clean:
	rm -f $(SRC_DIR)/*.o *.txt $(TARG)
