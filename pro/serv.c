#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

int tt_patients,flag = 0,j,choose;

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

void bzero(void *a, size_t n){
    memset(a, 0, n);
}
// ---------------------------------------
void bcopy(const void *src, void *dest, size_t n){
    memmove(dest, src, n);
}
///////////////////////////////////////////
struct sockaddr_in *init_sockaddr_in(uint16_t port_number){
    struct sockaddr_in *socket_address = malloc(sizeof(struct sockaddr_in));
    memset(socket_address, 0, sizeof(*socket_address));
    socket_address->sin_family = AF_INET;
    socket_address->sin_addr.s_addr = htonl(INADDR_ANY);
    socket_address->sin_port = htons(port_number);
    return socket_address;
}

char *storeInFile(char input[25]){
    char *output = malloc(1024);
        puts(input);
        switch (input[0]){
            case  '1':
               // storeData();
                memcpy(output,"Addpatient is executed",56);
                return output;
            break;

            case '2':
               addList();
                memcpy(output,"Patient list added stored into the enrollment file", 56);
                return output;
            break;

            case '3':
                memcpy(output,"Check_status is executed", 56);
                return output;
            break;

            case '4':
                memcpy(output,"Search is executed",56);
                return output;
            break;

            case '5':
                memcpy(output,"Display window clear",56);
                return output;
            break;

            // default:
            //     memcpy(output,"Please enter a valid command from the list above...",56);
            //     return output;
            // break;
    } 
}

int main(int argc, char *argv[]){

    // Establishing server sockets
    const uint16_t port = 4000;
    int soc = socket(AF_INET, SOCK_STREAM, 0);
    
    // struct patientData list[tt_patients];
    // struct covidOfficial official;

    struct sockaddr_in *socket_serv = init_sockaddr_in(port);
    struct sockaddr_in *client_sockaddr = malloc(sizeof(struct sockaddr_in));
    // socket sizes
    socklen_t server_socklen = sizeof(*socket_serv);
    socklen_t client_socklen = sizeof(*client_sockaddr);

    if (bind(soc, (const struct sockaddr *)socket_serv, server_socklen) < 0){
        perror("Error! Bind has failed:");
        exit(1);
    }
    if (listen(soc,3) < 0){
        perror("Error listen() failed:");
        exit(1);
    } else{
        puts("listening on port 4000........");
    }

    //variable server_msg to store strings received over the network
    const size_t server_msg_len = 256;
    //memory allocation.
    char *server_msg = malloc(server_msg_len * sizeof(char));
    char *response = NULL;

    time_t last_operation;
    __pid_t pid = -1;
    char name[256];

    //Run forever
    while (1){
         strcpy(name, server_msg);

        int acpt = accept(soc, (struct sockaddr *)&client_sockaddr, &client_socklen);

        pid = fork();

        if (pid == 0){
             // close(soc);

            if (acpt < 0){
                perror("Error accept():");
                exit(1);
            }

            printf("\nConnection with `%d` has been established and delegated to the process %d.\nWaiting for a query...\n", acpt, getpid());
            
            last_operation = clock();
                read(acpt, server_msg, server_msg_len);

            while (1) {
                //printf("Name:%d", re);
                if (!strcmp(server_msg, "close")){
                    printf("Process %d: ", getpid());
                    close(acpt);
                    printf("Closing session with `%d`. Bye!\n", acpt);
                    break;
                }

                if (strlen(server_msg) == 0)
                {
                    clock_t d = clock() - last_operation;
                    double dif = 5 * d / CLOCKS_PER_SEC;

                    if (dif > 1.0) {
                        printf("Process %d: ", getpid());
                        close(acpt);
                        printf("Connection timed out after %.3lf seconds. ", dif);
                        printf("Closing session with `%d`. Bye!\n", acpt);
                        break;
                    }

                    // continue;
                }
                free(response);
               
                response = storeInFile(server_msg);
               
                 int snd = write(acpt,response,256);
                if (snd < 0) {
                   /* code here */ 
                   perror("Error send():");
                   exit(1);
                }
                bzero(server_msg, server_msg_len * sizeof(char));

                last_operation = clock();
            }
            
            sleep(1); //  Sleeping the server 2 seconds to prevent it from over using the CPU processing....

            exit(1);
        }else{
            close(acpt);
        }
    }
}




//file pointer
            void  storeData(void){
                 struct patientData list[tt_patients];
                 struct covidOfficial official;
                          puts("=====================Add Patient details============");
                            puts("1. Add one patient.");
                            puts("2. Add multiple patients.");
                            printf("\nMake a choice: ");
                            scanf("%d",&choose);
                            puts("===================================================");

                // Adding details to the patient list
                switch (choose){
                
                         case 1:
                            puts("-----------------Your adding one patient to the list-------------");
                            puts("==============Health official details==============");
                            puts("Enter your username");
                            printf("> ");
                            scanf("%s",official.username);
                            puts("Enter your referral");
                            printf("> ");
                            scanf("%s",official.referral);
                            puts("===================================================");

                            for(j = 0; j < 1; j++){
                            
                                // Store one patient data to the patient list.
                                puts("Enter your patient's name eg::(Mugamba Bruno)");
                                printf("> ");

                                scanf("%s %s",list[j].fname,list[j].sname);

                                puts("Enter patient's gender eg(M or F)");
                                printf("> ");
                                scanf("%s",list[j].gender);

                                puts("Enter the date of confirmation eg(dd-mm-yy)");
                                printf("> ");
                                scanf("%s",list[j].date);

                                puts("Enter the patient's condition eg(symptomatic or asymptomatic)");
                                printf("> ");
                                scanf("%s",list[j].condition);

                                printf("\n*******You have successfuly added one patient to the patient list*********\n");
                            }
                         break;

                        case 2:
                            puts("==================Your adding multiple patients=============");
                            printf("Enter the number of patients to store: ");
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
                            while(flag < tt_patients){

                                printf("\n***********Patient record[%d]***********\n",flag+1);

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
                                flag++;
                            }
                             printf("\n***********You have successfull stored %d patients in patients.txt.**************\n",tt_patients); 
                          break;

                            default:
                                 puts("Please select from the list above");
                             break;
                }   
        }

            void addList(void){

                         struct patientData list[tt_patients];
                         struct covidOfficial official;

                    ptr = fopen("enrollment-file.txt","a+");
                    if(ptr == NULL){
                            perror("Error in creating the file!");
                        exit(1);
                    }else{
                        while(flag < tt_patients && !feof(stdin)){
                            fprintf(ptr,"%s %-2s %-4s %-2s %-4s %-4s %-4s\n",list[flag].fname,list[flag].sname,list[flag].gender,list[flag].date,list[flag].condition,official.username,official.referral);
                            flag++;
                        }
                        fclose(ptr);
                    }
                    puts("=======================================================================================");
                    puts("       List added stored in file"); 
                    puts("======================================================================================");
            
            }

        void checkStatus(void){
            int cases = 0;
            char check;
            // opening the file for checking
                ptr = fopen("enrollment-file","r");
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

        void searchCreteria(void){
            char str1[30];
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
                            puts("===============================================");
                            puts(str2);
                            puts("===============================================");

                            cs++;
                        }
                        line++;
                     }
      
                 //    no result found
                    if(cs == 0){
                        puts("===========No results founds============");
                    }

                    fclose(ptr);
                 }
        }