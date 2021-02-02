#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
int tt_patients,j,flag;
// function prototypes 
    void storeData(void);
    void addList(void);
    void checkStatus(void);
    void searchCreteria(void);

  struct patientData{
        char fname[100];
        char sname[100];
        char date[100];
        char condition[100];
        char gender[40];
    };

FILE *ptr;
// health ooficial
 struct covidOfficial{
    char referral[100];
    char username[100];
};

void bzero(void *a, size_t n)
{
    memset(a, 0, n);
}

void bcopy(const void *src, void *dest, size_t n)
{
    memmove(dest, src, n);
}

// struct sockaddr_in *init_sockaddr_in(uint16_t port_number)
// {
//     struct sockaddr_in *socket_address = malloc(sizeof(struct sockaddr_in));
//     memset(socket_address, 0, sizeof(*socket_address));
//     socket_address->sin_family = AF_INET;
//     socket_address->sin_addr.s_addr = htonl(INADDR_ANY);
//     socket_address->sin_port = htons(port_number);
//     return socket_address;
// }

char *process_operation(char *input){

    char *output = malloc(256);
    
    switch (input[0]) {
    case  '1':
        storeData();
        memcpy(output,"Addpatient (one) executed", 30);
        return output;
        
        break;

    case '2':
        addList();
         memcpy(output,"Addpatient(multiple) executed", 30);
         return output;
        

         break;
    

    case '3':
       checkStatus();
         memcpy(output,"Check-status executed", 30);
        return output;
    break;


    case '4':
         searchCreteria();
         memcpy(output,"Search is executed",30);
    return output;
    break;

    case '5':
         memcpy(output,"Display window wiped", 30);
    return system("clear"),output;
     
    break;

    default:
        memcpy(output,"Type a valid command", 24);
    return output;
    break;
    }

}
int main(int argc, char *argv[]){
// data
    struct patientData list[tt_patients];
    struct covidOfficial official;

    const uint16_t port_number = 4000;
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_sockaddr; //= init_sockaddr_in(port_number);
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(4000);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // struct sockaddr_in *client_sockaddr = malloc(sizeof(struct sockaddr_in));
    socklen_t server_socklen = sizeof(server_sockaddr);
    // socklen_t client_socklen = sizeof(*client_sockaddr);

    if (bind(server_fd, (const struct sockaddr *)&server_sockaddr, server_socklen) < 0)
    {
        perror("Error! Bind has failed:");
        exit(1);
    }
    if (listen(server_fd, 3) < 0){
        perror("Error! Can't listen:");
        exit(1);
    }else{
        puts("listening on port 4000........");
    }

    //variable buffer to store strings receiver over the network
    const size_t buffer_len = 256;
    //memory allocation.
    char *buffer = malloc(buffer_len * sizeof(char));
    
    char *response = NULL;
    time_t last_operation;
    __pid_t pid = -1;
    char name[256];

    //Run forever
    while (1){
         strcpy(name, buffer);
        int client_fd = accept(server_fd, (struct sockaddr *)&server_sockaddr, &server_socklen);

        pid = fork();

        if (pid == 0){
            close(server_fd);
            if (client_fd == -1){
                exit(0);
            }

            printf("\nConnection id: `%d`  established.\nProcessing at %d.\nWaiting for commands...\n", client_fd, getpid());

            last_operation = clock();

            while (1) {
                read(client_fd, buffer, buffer_len);
                
                if (!strcmp(buffer, "close")) {
                    printf("Process %d: ", getpid());
                    close(client_fd);
                    printf("Closing session with `%d`. Bye!\n", client_fd);
                    break;
                }

                if (strlen(buffer) == 0){
                    clock_t d = clock() - last_operation;
                    double dif = 5.0 * d / CLOCKS_PER_SEC;
   

                    if (dif > 1.0) {
                        printf("Process %d: ", getpid());
                        close(client_fd);
                        printf("Connection timed out after %.3lf seconds. ", dif);
                        printf("Closing session with `%d`. Bye!\n", client_fd);
                        break;
                    }

                //    continue;
                }

                response = process_operation(buffer);
                  send(client_fd,response, 256, 0);

                bzero(buffer, buffer_len * sizeof(char));

                last_operation = clock();
            }
            exit(0);
        } else {
            close(client_fd);
        }

    }
}

/////////////////////
 void  storeData(void){
                
                 struct patientData mono;
                 struct covidOfficial official;
               
                            puts("-----------------Your adding one patient to the file-------------");
                            puts(" ");
                            puts("============= Health official's details ============");
                            puts("Enter your username");
                            printf("> ");
                            scanf("%s",official.username);
                            puts("Enter your referral");
                            printf("> ");
                            scanf("%s",official.referral);
                            puts("===================================================");
                             ptr = fopen("enrollment-file.txt","a+");
                            if(ptr == NULL){
                                    perror("Error in creating the file!");
                                    exit(1);
                             }else{
                                for(j = 0; j < 1 && !feof(stdin); j++){
                                
                                    // Store one patient data to the enrollment file.
                                    puts("Enter your patient's name eg::(Mugamba Bruno)");
                                    printf("> ");

                                    scanf("%s %s",mono.fname,mono.sname);

                                    puts("Enter patient's gender eg(M or F)");
                                    printf("> ");
                                    scanf("%s",mono.gender);

                                    puts("Enter the date of confirmation eg(dd-mm-yy)");
                                    printf("> ");
                                    scanf("%s",mono.date);

                                    puts("Enter the patient's condition eg(symptomatic or asymptomatic)");
                                    printf("> ");
                                    scanf("%s",mono.condition);
                                    fprintf(ptr,"%s %-2s %-4s %-2s %-4s %-4s %-4s\n",mono.fname,mono.sname,mono.gender,mono.date,mono.condition,official.username,official.referral);
                                    
                                    printf("\n*******You have successfuly added one patient to the patient list*********\n");
                                }
                        fclose(ptr);
                    }
                }

            void addList(void){
                // Patients data
                 struct patientData list[tt_patients];
                //  Health official's data
                 struct covidOfficial official;
                    
                            puts("==================Your adding multiple patients=============");
                            printf("\nEnter the number of patients to store: ");
                            scanf("%d",&tt_patients);
                            // health official's information
                             puts("***********Health Official's Data***********");
                            puts("Enter your username");
                            printf("> ");
                                scanf("%s",official.username);

                                puts("Enter your referral");
                                printf("> ");
                                scanf("%s",official.referral);

                                puts("*****************************************************");

                                 ptr = fopen("enrollment-file.txt","a+");
                         if(ptr == NULL){
                              perror("Error in creating the file!");
                              exit(1);
                          }else{
                       
                            for( flag = 0 ; flag < tt_patients && !feof(stdin); flag++){

                                        printf("\n******Patient record[%d]*******\n",flag+1);

                                        puts("\nEnter your patient's name eg::(mugamba bruno)");
                                        printf("> ");
                                        scanf("%s %s",list[flag].fname,list[flag].sname);

                                        puts("Enter patient's gender:");
                                        printf("> ");
                                        scanf("%s",list[flag].gender);

                                        puts("Enter the date of confirmation eg(dd-mm-yy)");
                                        printf("> ");
                                        scanf("%s",list[flag].date);

                                        puts("Enter the patient's condition eg(symptomatic or asymptomatic):");
                                        printf("> ");
                                        scanf("%s",list[flag].condition); 

                                        fprintf(ptr,"%s %-2s %-4s %-2s %-4s %-4s %-4s\n",list[flag].fname,list[flag].sname,list[flag].gender,list[flag].date,list[flag].condition,official.username,official.referral);
                                        
                                        }
                                 fclose(ptr);
                            }
                    puts("=========================================================");

                             printf("\n*****You have successfull stored %d patients in patients.txt.*****\n",tt_patients); 
                    
                    puts("=========================================================");
            
            }
// ////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void checkStatus(void){
            int cases = 0;
            char check;
            // opening the file for checking
               ptr = fopen("enrollment-file.txt","r");
                if(ptr == NULL){
                    perror("Failed to open file, check the directory or file extension");
                    exit(1);
                }else{
                    // scanning through the file.
                    for(check = getc(ptr); check != EOF; check = getc(ptr)){
                        if(check == '\n'){
                                cases++; // Incrementing every after a new line.
                            }
                        }
                    puts("===============================================================");
                    printf("\n******You have %d cases registered in enrollment-file.txt********\n",cases);
                    puts("===============================================================");

                   fclose(ptr);
                  
                }
        }
/////////////////////////////////////////////////////////////////////////////////////////////////////
        void searchCreteria(void){
            char str1[100];
            char str2[100];
            int cs,line;
             ptr = fopen("enrollment-file.txt","r");
            if(ptr == NULL){
                perror("Error opening file, try checking the file extension or file directory.");
                 exit(1);
                 }else{
                        puts("==========Search either by name or date==============");
                        printf("\nSearch here:");
                        scanf("%s",str1);

                    while (fgets(str2,sizeof(str2),ptr) != NULL){
                    /* code here */ 
                        if((strstr(str2,str1)) != NULL){
                            puts("==========================================");
                            puts(str2);
                            puts("==========================================");

                            cs++;
                        }
                        line++;
                     }
      
                 //    no result found
                    if(cs == 0){
                        puts("=========== No results founds ============");
                    }

                    fclose(ptr);
                 }
        }