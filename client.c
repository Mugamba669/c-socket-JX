#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#define MAX_PATIENTS 100
int patients_number = 0;
//file
FILE *patient_file;

//structure
typedef struct Patients
{
    char patient_name[50];
    char patient_gender[50];
    char DOI[100];
    char status[100];
} patient;
//officer name
char officer_name[50];
char district_name[30];

//socket globals
int sockfd, portno, n;
struct sockaddr_in serv_addr;
struct hostent *server;
char buffer[256];
portno = 4000;

//display commands
void display_commands()
{
    char commands[5][30] =
        {"1:ADD_PATIENT", "2:ADD_PATIENT_LIST_",
         "3:CHECK_STATUS", "4:ADD_PATIENT_FILE.TXT", "5:SEARCH_CRITERIA"};
    int next_command;
    puts("\n============Commands=========\n\t");
    for (next_command = 0; next_command < 5; next_command++)
    {
        puts(commands[next_command]);
    }
    // int selected_command;
    // printf("\nSelectCommand:");
    // scanf("%d", &selected_command);
    // return selected_command;
}

int main(){
    // create socket and get file descriptor
     //buffer[256] = "1";
     display_commands();
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        server = gethostbyname("127.0.0.1");
        if (server == NULL)
        {
            fprintf(stderr, "ERROR, no such host\n");
            exit(0);
           // get_command(display_commands());
        }

        bzero((char *)&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(portno);
        //connect to server with server address which is set above (serv_addr)

        if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        {
            perror("ERROR while connecting");
            //exit(1);
            //get_command(display_commands());
        }
        while (1)
        {
            bzero(buffer, 256);
            //gets(buffer);
            printf("%s", buffer);
            printf("\nEnter Buffer:");
            scanf("%s", buffer);

            n = write(sockfd, buffer, strlen(buffer));
            //printf("n:%d", n);
            if (n < 0)
            {
                perror("\n\t======ERROR while writing to socket Try Again======\n\t");
                printf("\n\t=======Try Again or Enter another command========\t\n");
                //get_command(display_commands());
            }

            bzero(buffer, 256);
             //buffer = "1";
            n = read(sockfd,buffer, 255);

            if (n < 0)
            {
                perror("ERROR while reading from socket");
                exit(1);
                printf("\n\t=======File couldnot be read=======\t\n");
                //get_command(display_commands());
            }
            printf("\n=====server replied: %s =======\n", buffer);
            

            if (!bcmp(buffer, "quit", 4))
                break;
        }
   // }
    // else
    // {
    //     printf("\n\t\t=======Patient File is empty=======\t\t\n");
    //     get_command(display_commands());
    // }
//}

}