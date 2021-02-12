#include <mysql.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct patient{
    char fname[50];
    char sname[50];
    char date[50];
    char gender[30];
    char condition[50];
    char username[30];
};



int main(){
	MYSQL *conn = mysql_init(NULL);
	
	char sql[1024];
	FILE *file;
	float tc = clock();
	int flag = 0;

 struct patient details[100];

	if (conn == NULL){
		/* code */
		fprintf(stderr,"%s\n",mysql_error(conn));
		exit(1);
	}
	
	if (mysql_real_connect(conn,"127.0.0.1","root","","covid_recess",0,NULL,0) == NULL){
		fprintf(stderr,"%s\n",mysql_error(conn));
		exit(1);
	}

	 file = fopen("patients.txt","r");
    if(file == NULL){
        perror("Error in file:");
        exit(1);
    }else{
         while(!feof(file)){
               fscanf(file,"%s %s %s %s %s %s \n",details[flag].fname,details[flag].sname,details[flag].gender,details[flag].date,details[flag].condition,details[flag].username);

				sprintf(sql,"INSERT INTO `patients`( id,fname,sname,dte,gender,status,username)VALUES('0','%s','%s','%s','%s','%s','%s');",details[flag].fname,details[flag].sname,details[flag].date,details[flag].gender,details[flag].condition,details[flag].username);
			 
                flag++;
        } 
		
       // puts(details[2].sname);
        fclose(file);
    }
	if (mysql_query(conn,sql)){
				fprintf(stderr,"%s\n",mysql_error(conn));
				exit(1);
			 }
		printf("The client id for mysql :%s  has inserted data successfully  in %f seconds\n",mysql_get_client_info(),tc/CLOCKS_PER_SEC);
		mysql_close(conn);
		exit(1);
	
}	
