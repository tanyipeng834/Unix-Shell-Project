#include<stdio.h>
#include<stdlib.h>
#include "builtin.h"
#include<string.h>
#include "shell.h"
#include<unistd.h>

int isBuiltIn(char * command)
{
    char*builtInCommands[3] ={"path","cd","exit"};

    
   
    for(int i=0;i<3;i++){
         
        if(strcmp(command,builtInCommands[i])==0)
        {
           
            return 1;

        }
        
    }
    // return 0 as they dont match;
    return 0;


}

void processBuiltInCommands(char** userCommands,char*** searchPath)
{   
    
    char * command = userCommands[0];
    
    
    if(strcmp(command,"exit")==0){
       
        exit(0);
    }
    else if (strcmp(command,"cd")==0){
        
        if(userCommands[1]== NULL || userCommands[2] !=NULL){
            handleError();
        }
        if(chdir(userCommands[1])!=0){
            handleError();
        }

    }
    // for commands like
    else if(strcmp(command,"path")==0){
        // obtain the count;
        int argumentCount =0;
        while(userCommands[argumentCount]){
            
            argumentCount++; 

        }
       

        *searchPath = malloc(sizeof(char*) * (argumentCount+2));
        if(*searchPath==NULL){
            
            handleError();
        }
        
        if (argumentCount==1){
            *searchPath = NULL;
            return;
        }
        int i =0;
        // this would always be there
        
        while(userCommands[i])
        {
            (*searchPath)[i] = strdup(userCommands[i]);
            i++;

        }
        // Null terminate the string array
        (*searchPath)[i]=NULL;




    }
    
}