#include<stdlib.h>
#include <stdio.h>
#include "user.h"
#include "shell.h"
#include<string.h>
#include<unistd.h>
#include <sys/fcntl.h>
#include "builtin.h"
void trimWhitespace(char *str) {
    // Trim leading whitespace
    while (*str == ' ' || *str == '\t') str++;

    // Trim trailing whitespace
    char *end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t')) {
        end--;
    }
    *(end + 1) = '\0';  
}
char** processUserCommands(char *userInput) {
    char* stringToken;
    int i = 0;
    int capacity = 4;
    char **userCommands = malloc(sizeof(char *) * capacity);
    if (!userCommands) {
        handleError();
    }

    size_t len = strlen(userInput);
    if (len > 0 && userInput[len - 1] == '\n') {
        userInput[len - 1] = '\0';  // Remove newline character
    }

    // Tokenize input based on spaces and tabs
    // if (*userInput == '\0') {
    //     userCommands[0] = NULL;  // Set the first element to NULL for empty input
    //     return NULL;  // Return immediately for empty input
    // }
    
    while ((stringToken = strsep(&userInput, " \t"))) {
        if (strlen(stringToken) == 0) {
            continue;  
        }
        

      
        
        if ( strcmp(stringToken,">")!=0 && strchr(stringToken, '>')) {
            // Handle the case where the redirection operator is present in the token
            
           
            char *  location = strchr(stringToken,'>');
            
            *location='\0';
            if(*stringToken!='\0'){
                userCommands[i++]=strdup(stringToken);

            }
            userCommands[i++]=strdup(">");
            location +=1;
            if( location!=NULL && *location!='\0'){
                userCommands[i++]=strdup(location);
            }



        }
       

        else {
            // Regular command/argument, no operator
            
            userCommands[i++] = strdup(stringToken);
        }

        // Ensure that the array has enough space for more tokens
        if (i >= capacity) {
            capacity *= 2;
            char **tmp = realloc(userCommands, sizeof(char *) * capacity);
            if (!tmp) {
                free(userCommands);
                handleError();
            }
            userCommands = tmp;
        }
    }

    userCommands[i] = NULL;  // Null-terminate the array
    return userCommands;
}



void executeUserCommands(char** userCommands, char** searchPath)
{  
 
    size_t idx = 0;
        char **temp = userCommands;
        while (*temp != NULL) {
        idx++;
        temp++;
        }


        
    
    
    

    

    
    pid_t processes[idx];

    for(int i =0;i<idx;i++){
        char ** currentCommand=processUserCommands(userCommands[i]);
        if(isBuiltIn(currentCommand[i])|| searchPath ==NULL){
            processBuiltInCommands(currentCommand,&searchPath);


        }
    
   
        processes[i] = fork();
        
        
        

    if(processes[i]<0){
        handleError();
    }


    


    else if (processes[i] ==0)
    {
        
        
        

        
       
        
        
        
        
        char * executionPath= NULL;
        while(*searchPath){
        size_t len = strlen(*searchPath) + strlen("/") + strlen(currentCommand[0]);
        
        // include for null character
        char * newPath = malloc(sizeof(char)* (len+1));
        if(!newPath){
            handleError();
        }
        

        snprintf(newPath,len+1,"%s/%s",*searchPath,currentCommand[0]);
        
        if(access(newPath,X_OK)==0)
        {
            executionPath = newPath;
            break;

        }
        searchPath++;

        
        
    }
        
       int isRedirect = 0;
        int idx = 0;
        // arguments to send to the command
        char **arguments = malloc(sizeof(char *) * (sizeof(currentCommand) / sizeof(char *)));

        // Use an index to find redirection operator ">"
        while (currentCommand[idx]) {
            if (strcmp(currentCommand[idx], ">") == 0) {
                isRedirect = idx;  // Mark where redirection operator is
                break;
            }
            idx++;
        }
        
        

        if(isRedirect){
           
            close(STDOUT_FILENO);
            close(STDERR_FILENO);
            // open the file after opening it
            for (int i =0;i<isRedirect;i++){
                arguments[i] = strdup(currentCommand[i]);
                
            }
            arguments[isRedirect]=NULL;
            
            
            
            open(currentCommand[isRedirect+1], O_CREAT|O_WRONLY|O_TRUNC,S_IRWXU);


        } // no redirect
        else{
            arguments = currentCommand;
        }
        
        
        
        
        if (execvp(executionPath, arguments) == -1) {
    handleError();
}



    }
}



    
    // this is for the parent  process, after 
    
       for (int i = 0; i < idx; i++) {
        
            waitpid(processes[i], NULL, 0);
            
        }



    

}

char ** processUserInput(char * userInput){
    char* stringToken;
    int i = 0;
    int capacity = 4;
    char **userCommands = malloc(sizeof(char *) * capacity);
    if (!userCommands) {
        handleError();
    }

    size_t len = strlen(userInput);
    if (len > 0 && userInput[len - 1] == '\n') {
        userInput[len - 1] = '\0';  // Remove newline character
    }
    trimWhitespace(userInput);  // Trim spaces before processing

    // Tokenize input based on spaces and tabs
    if (userInput[0] == '\0') {
        
        return NULL;  // Return immediately for empty input
    }
    
    while ((stringToken = strsep(&userInput, "&"))) {
        if (strlen(stringToken) == 0) {
            continue;  
        }
        

      
        
        
        
            // Regular command/argument, no operator
            
            userCommands[i++] = strdup(stringToken);
        }

        // Ensure that the array has enough space for more tokens
        if (i >= capacity) {
            capacity *= 2;
            char **tmp = realloc(userCommands, sizeof(char *) * capacity);
            if (!tmp) {
                free(userCommands);
                handleError();
            }
            userCommands = tmp;
        }
    userCommands[i] = NULL;  // Null-terminate the array
    return userCommands;

    }

    
