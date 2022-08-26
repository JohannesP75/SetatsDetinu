/*
    File created on July 18th, 2015, at 18:32
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "country.h"
#include "io.h"

int main(int argc, char** argv){
    t_country country;
    char* buffer=(char*)malloc(30*sizeof(char));

    print_presentation();
    //scanf(buffer,"%s");
    //fgets(buffer,30,stdin);
    read_line(buffer, 30, stdin);
    int i=0;
    while(buffer[i]!='\0'){
        buffer[i]=(char)toupper((char)buffer[i]);
        i++;
    }

    do{
        if(strcmp(buffer,"AGAIN")==0)
            init_country_restart(&country);
        else if(strcmp(buffer,"NO")==0)
            init_country(&country);
        else if(strcmp(buffer,"YES")==0){
            print_instructions();
            init_country(&country);
        }
    }while(strcmp(buffer,"AGAIN")!=0&&strcmp(buffer,"NO")!=0&&strcmp(buffer,"YES")!=0);

    free(buffer);

    while(country.ending==END_NONE){
        turn_playing_country(&country);
        end_turn_computing(&country);
        ending_management(country);
    }

    return 0;
}