#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>

//socket globals
int sockfd, n;
struct sockaddr_in serv_addr;
struct hostent *server;
char client_msg[256];
// char other[256];
char choice[100];
socklen_t portno = 4000;

//Enter string commands
   char *executeStringCommand(char cmd[20]){
     if(strcmp("Addpatient",cmd) == 0){
        return "1";
    }else if (strcmp("Addpatient-list",cmd) == 0){
        return "2";
    } else if (strcmp("Check-status",cmd) == 0) {
        return "3";
    } else if (strcmp("Search",cmd) == 0){
        return "4";
    } else if(strcmp("clear",cmd) == 0){
        
         return "5";
    }else {
       return "6";
    }
}

//display commands
void showCommands(){
    char commands[6][100] = {"## Addpatient","## Addpatient-list","## Check-status", "## Search","## Type \'clear\' to wipe the screen","> Type your command below"};
    int cd;
    puts("============Commands=========");
    for (cd = 0; cd < 6; cd++) {
        puts(commands[cd]);
    }
    puts("======================================");
}

int main(){
    // create socket and get file descriptor
         showCommands();
            sockfd = socket(AF_INET, SOCK_STREAM, 0);
            server = gethostbyname("127.0.0.1");

        if (server == NULL){
            fprintf(stderr, "Error, no such host\n");
            exit(0);
        }

        bzero((char *)&serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
        serv_addr.sin_port = htons(portno);
        //connect to server with server address which is set above (serv_addr)

        if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
            perror("Error while connecting");
            exit(1);
        }
        while (1){
            bzero(client_msg, 256);
            printf("\n# ");
            scanf("%s",choice);
            // store data into the client_msg container
              snprintf(client_msg,sizeof(client_msg),"%s",executeStringCommand(choice));
            // printf("%s", client_msg);

          // sending message to the server
            n = write(sockfd,client_msg, 256);
            if (n < 0) {
                perror("Error write() failed:");
                exit(1);
            }else {
               /* code here */ //puts("Message sent");
            }
            // 
            bzero(client_msg, 256);
            int re = read(sockfd,client_msg, 256);

            if (re < 0){
                perror("Error read() failed:");
                exit(1);
            }
            printf("\nServer: %s\n",client_msg);
           /////////////////////////////////////////////////
            // if (!bcmp(client_msg, "quit", 4))
            //     break;
        }
}