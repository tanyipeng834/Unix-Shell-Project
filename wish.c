#include<stdio.h>
#include<stdlib.h>

#include "builtin.h"
#include "user.h"
#include <unistd.h>
#include<string.h>

char** processUserCommands(char* userInput);
void handleError();

void executeUserCommands(char** userCommands, char** searchPath);

int main(int argc , char*argv[]){

    
    char ** searchPath = malloc(sizeof(char*) *1);

    searchPath[0] ="/bin";
    
    


    if(argc ==1){

    


char* userInput =NULL;

size_t bufferSize =10;

printf("wish> ");
while(getline(&userInput,&bufferSize,stdin)!=-1){
printf("wish> ");

//


char ** processedUserInput = processUserInput(userInput);

if(processedUserInput!=NULL){

executeUserCommands(processedUserInput,searchPath);
}






    
      
   




}




free(searchPath);
exit(0);



}



    
    //Case where the shell is in batch mode, the commands are in the .txt file
    else if(argc==2){
        FILE * file = fopen(argv[1],"r");
        char * line;
        size_t bufferSize =10;
        while(getline(&line,&bufferSize,file)!=-1)
        {
            printf("%s",line);

        }





    }
    else{
        handleError();

    }




   

    

    




}
void handleError(){
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message)); 
    exit(1);

}


