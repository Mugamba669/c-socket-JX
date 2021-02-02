#include <stdio.h>
#include <string.h>
    typedef struct Patient {
        char fname[50];
        char sname[50];
        char gender[50];
    }list;
void main(){
    int size,g;
    struct Patient list[size];

     printf("\nEnter the number patients to store:");
    scanf("%d",&size);
    for (int i = 0; i < size; i++) {
       /* code here */
       printf("\nRecord %d",i+1);
       puts("Name");
       printf("> ");
       scanf("%s %s",list[i].fname,list[i].sname);

        puts("Gender");
       printf("> ");
       scanf("%s",list[i].gender);
    }
    
     for (int i = 0; i < size; i++) {
       /* code here */ 
       puts(list[i].fname);
       puts(list[i].sname);
       puts(list[i].gender);
    }
}
   
    