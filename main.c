#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "db.h"
char name[]="student";

int separatee(char str[],char arr[][20]){
    int i = 0;
    char s[2]=" ";
    char *token;
    token = strtok(str, s);
    while (token != NULL) {
        strcpy(arr[i],token);
        i++;

        token = strtok(NULL, s);
    }
    return i;

}

int menu(){

    while(1){
        system("cls");
        puts("0-show students");
        puts("1-add new student");
        puts("2-find a student");
        puts("3-remove a student");
        puts("4-update information of a student");
        puts("5-delete");
        puts("6-Exit");
        int d;
        int res=scanf("%d",&d);
        char s[1000];
        gets(s);
        if(res!=1)continue;
        if(d<0 || d>6)continue;
        return d;
    }
}

void show(char str[]){
    char s[]="PRINT student";
    strcpy(str,s);

}

int insert(char str[]){
    int i=0;
    while(str[i]!='\0'){
        str[i]='\0';
        i++;
    }
    FILE * file1;
    char info[100];
    char info_words[20][20];
    file1=fopen("student_info.txt","r+");
    fgets(info,200,file1);
    int n =separatee(info,info_words);
    int nfield = n/2 -1 ;
    char integ[]="INT";
    char textt[]="TEXT";
    char floatt[]="FLOAT";
    int x;
    char s[1000];
    char r[20];
    float fx;
    i=3;
    char insertt[]="INSERT";
    strcpy(info_words[0],insertt);
    while(i<n){
        if(strcmp(info_words[i],integ)==0){
            printf("student's %s : ",info_words[i-1]);
            scanf("%d",&x);

            gets(s);
            itoa(x, r, 10);
            strcpy(info_words[i],r);
            i+=2;

        }
        else if(strcmp(info_words[i],textt)==0){
            printf("student's %s : ",info_words[i-1]);
            scanf("%s",r);
            gets(s);
            strcpy(info_words[i],r);
            i+=2;

        }
        else if(strcmp(info_words[i],floatt)==0){
            printf("student's %s : ",info_words[i-1]);
            scanf("%f",&fx);
            gets(s);
            gcvt(fx, 10, r);
            strcpy(info_words[i],r);
            i+=2;

        }

    }
    i=0;
    char space[]=" ";
    while(i<n){
        strcat(str,info_words[i]);
        strcat(str,space);
        i++;
    }


}

void deleter(char str[]){
    char find[]="DELETER";
    char space[]=" ";
    char value[20];
    char str1[100];
    char r[20];

    strcpy(str1,find);

    strcat(str1,space);
    strcat(str1,name);
    strcat(str1,space);
    printf("delete according to : ");
    scanf("%s",r);
    strcat(str1,r);
    strcat(str1,space);
    printf("which of them? : ");
    scanf("%s",value);
    strcat(str1,value);

    strcpy(str,str1);




}

void find_std(char str[]){
    char find[]="FIND";
    char space[]=" ";
    char value[20];
    char str1[100];
    char r[20];

    strcpy(str1,find);

    strcat(str1,space);
    strcat(str1,name);
    strcat(str1,space);
    printf("find according to : ");
    scanf("%s",r);
    strcat(str1,r);
    strcat(str1,space);
    printf("which of them? : ");
    scanf("%s",value);
    strcat(str1,value);

    strcpy(str,str1);

}

void update(char str[]){
    char str1[100];
    char space[]=" ";
    char fi[20];
    char s[20];
    char fval[20];
    char updatee[]="UPDATE";
    strcpy(str1,updatee);
    strcat(str1,space);
    strcat(str1,name);
    strcat(str1,space);
    printf("according to which property: ");
    scanf("%s",fi);
    gets(s);
    strcat(str1,fi);
    strcat(str1,space);
    printf("value of property: ");
    scanf("%s",fi);
    gets(s);
    strcat(str1,fi);
    strcat(str1,space);
    printf("what property change: ");
    scanf("%s",fi);
    gets(s);
    strcat(str1,fi);
    strcat(str1,space);
    printf("%s change to: ",fi);
    scanf("%s",fi);
    gets(s);
    strcat(str1,fi);

    strcpy(str,str1);
    //exec(str);



}
void delete(char str[]){
    char del[]="DELETEC";
    char space[]=" ";
    strcpy(str,del);
    strcat(str,space);
    strcat(str,name);
}
int main() {
    FILE *th;
    th=fopen("f.txt","rb");
    if(!th){
        char str1[]="CT student id INT name TEXT family TEXT garde FLOAT fathern TEXT len INT";
        exec(str1);
        th=fopen("f.txt","wb");

    }
    fclose(th);
    char s[]="f.txt";



    char str[100];
    while(1){
        int x =menu();
        switch(x){

            case 0:
                show(str);
                exec(str);
                system("pause");
                break;

            case 1:
                insert(str);
                exec(str);
                system("pause");
                break;
            case 2:
                find_std(str);
                exec(str);
                putchar('\n');
                system("pause");
                break;
            case 3:
                deleter(str);
                exec(str);
                system("pause");

                break;
            case 4:
                update(str);
                exec(str);
                break;
            case 5:
                remove(s);
                delete(str);
                exec(str);
                system("pause");


            case 6:
                return 0;



        }

    }
}