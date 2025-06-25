
# Unix Shell Project


This shell project is based on on the OSTEP textbook and it's projects with the specifications listed [here]("https://github.com/remzi-arpacidusseau/ostep-projects/tree/master/processes-shell")

## Dependencies

The project has the following dependencies:
- `make`
- `gcc` 
- `docker` 

## Building


To build and run the docker image, you can do the following:
```
# build and run the container image
make docker
```
A docker image will be built with all dependecies installed which would allow user to run the shell in the docker container.
## Key Features

### Setting of Path Envionment Variable

This shell uses the `path` command to set the $PATH envionment variable to set the execution path.

This shell utilizes the path command to search for executable and there is a default path `/bin` that has already been set for the user.

### Built In Commands

- `cd` Use this command to change directories .

- `exit` Use this command to exit the current shell session.

- `path` use this command to overrise the current `/bin` path. Usage: `path <new path>`

### Redirection

`>` command is used to redirect `stdout` and `stderr` to a file such as `output.txt`. Usage: `ls >output.txt`

### Parallel Commands

`&` command is used for parallel commands. This allow commands to be run in parallel.

- E.g. `sleep 3 & echo hello`

The expected result would be that hello would be outputed while the terminal would be slept for 3 seconds due to parallel commands where each processes is forked from the main shell process.


### Future Works

- [x] Add pipe command `|` to pipe the output to another command
- [ ] Add signals processing to handle signals like `SIGINT`





