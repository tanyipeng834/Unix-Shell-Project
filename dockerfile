# Use an official Ubuntu as a base image
FROM ubuntu:20.04

# Install necessary dependencies
RUN apt-get update && apt-get install -y \
    gcc \
    make \
    build-essential \
    libc6-dev \
    && rm -rf /var/lib/apt/lists/*

# Set working directory in the container
WORKDIR /app

# Copy your project files into the container
COPY . /app


RUN rm -f  *.exe 

RUN rm -f src/*.o

RUN make shell

# Set default command to run your shell
CMD ["./shell"]
