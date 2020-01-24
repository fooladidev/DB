#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char integer[]="INT";
char text[]="TEXT";
char flo[]="FLOAT";
char del_record[]="DELETER";
char del_table[]="DELETEC";





int locfield(char arr[][20],char iwords[][20],int x,int n){
    int i=0;
    int k=2;
    while(i<n){
        if(strcmp(arr[x],iwords[k])==0){

            return k;
        }
        else{
            k+=2;
            i++;
        }

    }
    return 0;


}

int separate(char str[],char arr[][20]){
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
FILE* fileopen(char name[]){
    FILE* file;
    file=fopen(name,"r+b");
    if(!file) {
        file = fopen(name, "w+b");
        return file ;
    }
    printf("file exist");
    return NULL;
}
void par(char arr[][20],int n){
    int i=0;
    while(i<n){
        puts(arr[i]);
        i++;
    }
}
int main_find(FILE*fp,char iwords[][20],int intv ,char charvalue[],int l,int rsize){


    int i=3;
    int tsize=0;
    while(i<l){
        if(strcmp(iwords[i],integer)==0){
            tsize+=4;
            i+=2;
        }
        else if(strcmp(iwords[i],text)==0){
            tsize+=20;
            i+=2;

        }
        else if(strcmp(iwords[i],flo)==0){
            tsize+=4;
            i+=2;

        }
    }
    i=0;
    int x;
    char xc[20];

    fseek(fp,0,SEEK_SET);
    int filoc;

    int ch = getc(fp);
    while (ch != EOF)
    {
        ch = getc(fp);
    }
    int loc= ftell(fp);
    int locr=0;
    fseek(fp,tsize,SEEK_SET);

    if(intv!=0) {
        while (loc > locr) {

            fread(&x, sizeof(int), 1, fp);
            if (x == intv) {
                filoc = -1 * (4 + tsize);
                fseek(fp, filoc, SEEK_CUR);
                break;

            } else {
                filoc = -1 * 4;
                fseek(fp, filoc, SEEK_CUR);
                fseek(fp, rsize, SEEK_CUR);
                locr = ftell(fp);

            }

        }
    }
    if(intv==0){
        while (loc > locr) {

            fread(&xc, 20, 1, fp);
            if ( strcmp(xc,charvalue)==0) {
                filoc = -1 * (20 + tsize);
                fseek(fp, filoc, SEEK_CUR);
                break;

            } else {
                filoc = -1 * 20;
                fseek(fp, filoc, SEEK_CUR);
                fseek(fp, rsize, SEEK_CUR);
                locr = ftell(fp);

            }

        }

    }
    loc=ftell(fp);
    return loc;

}

int updatee(FILE *fp,char iwords[][20],char arr[][20],int n,int loc){
    fseek(fp,loc,SEEK_SET);



    int l1=locfield(arr,iwords,4,n);
    int i=3;
    int tsize=0;
    while(i<l1){
        if(strcmp(iwords[i],integer)==0){
            tsize+=4;
            i+=2;
        }
        else if(strcmp(iwords[i],text)==0){
            tsize+=20;
            i+=2;

        }
        else if(strcmp(iwords[i],flo)==0){
            tsize+=4;
            i+=2;

        }

    }
    fseek(fp,tsize,SEEK_CUR);
    char*ptr1;
    char*pend;
    int intval;
    char charval[20];
    float floatval;

    if(strcmp(iwords[l1+1],integer)==0){
        intval =strtol(arr[5], &ptr1, 10);
        fwrite(&intval, sizeof(int),1,fp);

    }
    else if(strcmp(iwords[l1+1],text)==0){

        strcpy(charval,arr[5]);
        char c[]="\0";
        i=0;
        while(i<20){
            fwrite(c,1,1,fp);
            i++;

        }
        fseek(fp,-20,SEEK_CUR);

        fwrite(charval,20,1,fp);

    }
    if(strcmp(iwords[l1+1],flo)==0){
        strcpy(charval,arr[5]);
        floatval = strtof(charval, &pend);
        fwrite(&floatval, sizeof(float),1,fp);


    }




}



void print_rec(FILE *fp,char iwords[][20],int loc,int nfield){
    fseek(fp,loc,SEEK_SET);
    int i=0;
    int h=2;
    int intvalue;
    char charvalue[20];
    float floatvalue;

    while(i<nfield){
        printf("%-10s",iwords[h]);
        h+=2;
        i++;

    }
    putchar('\n');
    h=2;
    i=0;

    while (i < nfield) {
        if (strcmp(iwords[h + 1], integer) == 0) {
            fread(&intvalue, sizeof(int), 1, fp);
            printf("%-10d", intvalue);
            h += 2;
            i++;


        }
        else if (strcmp(iwords[h + 1], text) == 0) {
            fread(&charvalue, 20, 1, fp);
            printf("%-10s", charvalue);
            h += 2;
            i++;


        }
        else if (strcmp(iwords[h + 1], flo) == 0) {
            fread(&floatvalue, sizeof(float), 1, fp);
            printf("%-10f", floatvalue);
            h += 2;
            i++;


        }

    }
}


void delete_record(FILE *fp,int loc,int size_record,FILE* target){
    int locat;
    int locn=0;
    char cr[10000];
    char vr[50];
    fseek(fp,0,SEEK_SET);
    int ch = getc(fp);
    while (ch != EOF)
    {
        ch = getc(fp);
    }
    locat= ftell(fp);
    fseek(fp,0,SEEK_SET);

    fread(&cr,loc,1,fp);
    fwrite(&cr,loc,1,target);
    fseek(fp,size_record,SEEK_CUR);
    while(locn!=locat){
        fread(&vr,size_record,1,fp);
        fwrite(&vr,size_record,1,target);
        locn=ftell(fp);

    }

    /*fseek(fp,0,SEEK_SET);
    int ch = getc(fp);
    while (ch != EOF)
    {
        ch = getc(fp);
    }
    locat= ftell(fp);
    fseek(fp,0,SEEK_SET);
    while(loc!=locr){
        fread(&c,1,1,fp);
        fputc(c,target);
        locr=ftell(fp);
    }
    fseek(fp,size_record,SEEK_CUR);
    while(locr!=locat){
        fread(&c,1,1,fp);
        fputc(c,target);
        locr=ftell(fp);
    }*/



}

int exec(char str[]) {
    int j;
    char arr[30][20];
    char str1[200];
    strcpy(str1,str);

    separate(str1,arr);

    //int nfield=n/2 -1;


    char ct[]="CT";
    char insert[]="INSERT";
    char print[]="PRINT";
    char update[]="UPDATE" ;
    char findd[]="FIND" ;



    if(strcmp(arr[0],ct) == 0){

        FILE* file;
        char tname[30];
        strcpy(tname,arr[1]);
        char txt[]=".txt";
        strcat(tname,txt);
        file= fileopen(tname);
        if(!file){
            puts("Error!\n");
            return 1;
        }

        FILE* file1;
        char iname[30];
        strcpy(iname,arr[1]);
        char itxt[]="_info.txt";
        strcat(iname,itxt);
        file1=fopen(iname,"w+");
        fprintf(file1,"%s",str);
        fclose(file);
        fclose(file1);



    }
    else if(strcmp(arr[0],insert) == 0){
        FILE *fp ;
        char tname[30];
        strcpy(tname,arr[1]);
        char txt[]=".txt";
        strcat(tname,txt);
        fp=fopen(tname,"ab");

        if(!fp){
            puts("Error!\n");
            return 1;
        }

        char info[200];
        char info1[200];
        char info_words[30][20];


        FILE* file1;
        char iname[30];
        strcpy(iname,arr[1]);
        char itxt[]="_info.txt";
        strcat(iname,itxt);
        file1=fopen(iname,"r+");
        fgets(info,200,file1);
        strcpy(info1,info);
        int n =separate(info1,info_words);
        int nfield =n/2-1;

        int i=0;
        int h=2;//fields after arr[2]
        int intvalue;
        char *pend;
        char charvalue[20];
        float floatvalue;
        char *ptr1;
        while(i<nfield){
            int l=locfield(arr,info_words,h,nfield);
            if(l!=0){
                if(strcmp(info_words[l+1],integer)==0){
                    intvalue= strtol(arr[h+1], &ptr1, 10);

                    fwrite(&intvalue, sizeof(int),1,fp);
                    h+=2;

                    i++;


                }
                if(strcmp(info_words[l+1],text)==0){
                    strcpy(charvalue,arr[h+1]);
                    fwrite(&charvalue,20,1,fp);
                    h+=2;
                    i++;



                }
                if(strcmp(info_words[l+1],flo)==0){
                    strcpy(charvalue,arr[h+1]);
                    floatvalue = strtof(charvalue, &pend);
                    fwrite(&floatvalue, sizeof(float),1,fp);
                    h+=2;

                    i++;


                }


            }





        }








        fclose(fp);
        fclose(file1);

    }
    else if(strcmp(arr[0],print)==0){
        int size_record=0;
        FILE *fp ;
        char tname[30];
        strcpy(tname,arr[1]);
        char txt[]=".txt";
        strcat(tname,txt);
        fp=fopen(tname,"rb");

        if(!fp){
            puts("Error!\n");
            return 1;
        }

        char info[200];
        char info1[200];
        char info_words[20][20];

        FILE* file1;
        char iname[30];
        strcpy(iname,arr[1]);
        char itxt[]="_info.txt";
        strcat(iname,itxt);
        file1=fopen(iname,"r+");
        fgets(info,200,file1);
        strcpy(info1,info);
        int n =separate(info1,info_words);
        int nfield=n/2-1;

        int i=0;
        int h=2;
        int intvalue;
        float floatvalue;
        char charvalue[20];
        while(i<n){
            if(strcmp(info_words[i],integer)==0){
                size_record+=4;
                i++;

            }
            else if(strcmp(info_words[i],text)==0){
                size_record+=20;
                i++;

            }
            else if(strcmp(info_words[i],flo)==0){
                size_record+=4;
                i++;

            }
            i++;
        }
        i=0;


        while(i<nfield){
            printf("%-15s",info_words[h]);
            h+=2;
            i++;

        }
        putchar('\n');
        h=2;
        i=0;
        fseek(fp,0,SEEK_SET);

        int rrecord=0;

        int ch = getc(fp);
        while (ch != EOF)
        {
            ch = getc(fp);
        }
        int loc= ftell(fp);
        int locr=0;
        char xx[2];
        int flag1=0;
        fseek(fp,0,SEEK_SET);


        while(locr!=loc) {

            while (i < nfield) {
                if (strcmp(info_words[h + 1], integer) == 0) {
                    fread(&intvalue, sizeof(int), 1, fp);
                    printf("%-15d", intvalue);
                    h += 2;
                    i++;


                }
                else if (strcmp(info_words[h + 1], text) == 0) {
                    fread(&charvalue, 20, 1, fp);
                    printf("%-15s", charvalue);
                    h += 2;
                    i++;


                }
                else if (strcmp(info_words[h + 1], flo) == 0) {
                    fread(&floatvalue, sizeof(float), 1, fp);
                    printf("%-15f", floatvalue);
                    h += 2;
                    i++;


                }

            }

            rrecord+=1;
            h=2;
            i=0;

            fseek(fp,rrecord * size_record,SEEK_SET);

            locr=ftell(fp);
            putchar('\n');
        }
        fclose(fp);
        fclose(file1);

    }

    else if(strcmp(arr[0],update)==0){
        int size_record=0;
        FILE *fp ;
        char tname[30];
        strcpy(tname,arr[1]);
        char txt[]=".txt";
        strcat(tname,txt);
        fp=fopen(tname,"r+b");

        if(!fp){
            puts("Error!\n");
            return 1;
        }

        char info[200];
        char info1[200];
        char info_words[20][20];

        FILE* file1;
        char iname[30];
        strcpy(iname,arr[1]);
        char itxt[]="_info.txt";
        strcat(iname,itxt);
        file1=fopen(iname,"r+");
        fgets(info,200,file1);
        strcpy(info1,info);
        int n =separate(info1,info_words);
        int nfield=n/2-1;
        int i=0;
        while(i<n){
            if(strcmp(info_words[i],integer)==0){
                size_record+=4;
                i++;

            }
            else if(strcmp(info_words[i],text)==0){
                size_record+=20;
                i++;

            }
            else if(strcmp(info_words[i],flo)==0){
                size_record+=4;
                i++;

            }
            i++;
        }


        i=0;
        int h=2;
        int intvalue=0;
        char charvalue[20];
        char *ptr1;
        int loc;

        int l=locfield(arr,info_words,h,nfield);//

        if(l!=0){
            if(strcmp(info_words[l+1],integer)==0){
                intvalue= strtol(arr[h+1], &ptr1, 10);
                loc=main_find(fp,info_words,intvalue,charvalue,l,size_record);

                updatee(fp,info_words,arr,nfield,loc);

            }
            if(strcmp(info_words[l+1],text)==0){
                strcpy(charvalue,arr[h+1]);
                loc=main_find(fp,info_words,intvalue,charvalue,l,size_record);

                updatee(fp,info_words,arr,nfield,loc);


            }

        }


        fclose(fp);
        fclose(file1);

    }

    else if(strcmp(arr[0],findd)==0){
        int size_record=0;
        FILE *fp ;
        char tname[30];
        strcpy(tname,arr[1]);
        char txt[]=".txt";
        strcat(tname,txt);
        fp=fopen(tname,"r+b");

        if(!fp){
            puts("Error!\n");
            return 1;
        }

        char info[200];
        char info1[200];
        char info_words[20][20];

        FILE* file1;
        char iname[30];
        strcpy(iname,arr[1]);
        char itxt[]="_info.txt";
        strcat(iname,itxt);
        file1=fopen(iname,"r+");
        fgets(info,200,file1);
        strcpy(info1,info);
        int n =separate(info1,info_words);
        int nfield=n/2-1;
        int i=0;
        int h=2;

        while(i<n){
            if(strcmp(info_words[i],integer)==0){
                size_record+=4;
                i++;

            }
            else if(strcmp(info_words[i],text)==0){
                size_record+=20;
                i++;

            }
            else if(strcmp(info_words[i],flo)==0){
                size_record+=4;
                i++;

            }
            i++;
        }

        int l=locfield(arr,info_words,h,nfield);
        int intvalue=0;
        int loc;
        char charvalue[20];
        char *ptr1;

        if(l!=0){
            if(strcmp(info_words[l+1],integer)==0){
                intvalue= strtol(arr[h+1], &ptr1, 10);
                loc=main_find(fp,info_words,intvalue,charvalue,l,size_record);
                print_rec(fp,info_words,loc,nfield);


            }
            if(strcmp(info_words[l+1],text)==0){
                strcpy(charvalue,arr[h+1]);
                loc=main_find(fp,info_words,intvalue,charvalue,l,size_record);
                print_rec(fp,info_words,loc,nfield);


            }

        }
        fclose(fp);
        fclose(file1);
    }
    else if(strcmp(arr[0],del_record)==0){


        int size_record=0;
        FILE *fp ;
        char tname[30];
        strcpy(tname,arr[1]);
        char txt[]=".txt";
        strcat(tname,txt);
        fp=fopen(tname,"r+b");

        if(!fp){
            puts("Error!\n");
            return 1;
        }

        char info[200];
        char info1[200];
        char info_words[20][20];

        FILE* file1;
        char iname[30];
        strcpy(iname,arr[1]);
        char itxt[]="_info.txt";
        strcat(iname,itxt);
        file1=fopen(iname,"r+");
        fgets(info,200,file1);
        strcpy(info1,info);
        int n =separate(info1,info_words);
        int nfield=n/2-1;
        int i=0;
        int h=2;

        while(i<n){
            if(strcmp(info_words[i],integer)==0){
                size_record+=4;
                i++;

            }
            else if(strcmp(info_words[i],text)==0){
                size_record+=20;
                i++;

            }
            else if(strcmp(info_words[i],flo)==0){
                size_record+=4;
                i++;

            }
            i++;
        }

        int l=locfield(arr,info_words,h,nfield);
        int intvalue=0;
        int loc;
        char s[]="tar.txt";
        char charvalue[20];
        char *ptr1;
        FILE *sp;
        sp=fopen(s,"wb");

        if(l!=0){
            if(strcmp(info_words[l+1],integer)==0){
                intvalue= strtol(arr[h+1], &ptr1, 10);
                loc=main_find(fp,info_words,intvalue,charvalue,l,size_record);
                printf("%d",loc);
                delete_record(fp,loc,size_record,sp);
                fclose(fp);
                fclose(sp);
                remove(tname);
                rename(s,tname);



            }
            if(strcmp(info_words[l+1],text)==0){
                strcpy(charvalue,arr[h+1]);
                loc=main_find(fp,info_words,intvalue,charvalue,l,size_record);
                delete_record(fp,loc,size_record,sp);
                fclose(fp);
                fclose(sp);
                remove(tname);
                rename(s,tname);


            }

        }







    }
    else if(strcmp(arr[0],del_table)==0){
        FILE *fp ;
        char tname[30];
        strcpy(tname,arr[1]);
        char txt[]=".txt";
        strcat(tname,txt);
        remove(tname);


        FILE* file1;
        char iname[30];
        strcpy(iname,arr[1]);
        char itxt[]="_info.txt";
        strcat(iname,itxt);
        remove(iname);

    }




}
