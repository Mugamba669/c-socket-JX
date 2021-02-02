#include <stdio.h>
#include <stdlib.h>
void main(){
    FILE *ptr;
    ptr = fopen("enrollment-file.txt","w+");
    if(ptr == NULL){
        perror("Error opening file:");
        exit(1);
    }else{
        puts("=========Enrollment-file.txt is sucessfull============");
        fclose(ptr);
    }
}