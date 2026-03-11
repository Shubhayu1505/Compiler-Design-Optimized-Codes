#include <stdio.h>
#include <string.h>

char p[20][50];
int n;

void lr() {
    for(int i=0;i<n;i++){
        char nt=p[i][0];
        char r[10][20],a[10][20],b[10][20];
        int c=0,ac=0,bc=0,rec=0;
        char t[50];
        strcpy(t,p[i]+3);
        char *tok=strtok(t,"|");
        while(tok){
            strcpy(r[c++],tok);
            tok=strtok(NULL,"|");
        }
        for(int j=0;j<c;j++){
            if(r[j][0]==nt){
                rec=1;
                strcpy(a[ac++],r[j]+1);
            } else strcpy(b[bc++],r[j]);
        }
        if(rec){
            printf("%c->",nt);
            for(int j=0;j<bc;j++){
                printf("%s%c'",b[j],nt);
                if(j<bc-1) printf("|");
            }
            printf("\n%c'->",nt);
            for(int j=0;j<ac;j++) printf("%s%c'|",a[j],nt);
            printf("ε\n");
        } else printf("%s\n",p[i]);
    }
}

void lf() {
    for(int i=0;i<n;i++){
        char nt=p[i][0];
        char r[10][20];
        int c=0;
        char t[50];
        strcpy(t,p[i]+3);
        char *tok=strtok(t,"|");
        while(tok){
            strcpy(r[c++],tok);
            tok=strtok(NULL,"|");
        }
        if(c>1){
            char pre[20]="";
            int pl=0,min=strlen(r[0]);
            for(int j=1;j<c;j++) if(strlen(r[j])<min) min=strlen(r[j]);
            for(int j=0;j<min;j++){
                char cur=r[0][j];
                int m=1;
                for(int k=1;k<c;k++) if(r[k][j]!=cur){m=0;break;}
                if(m){pre[j]=cur;pl++;} else break;
            }
            pre[pl]='\0';
            if(pl>0){
                printf("%c->%s%c'\n",nt,pre,nt);
                printf("%c'->",nt);
                for(int j=0;j<c;j++){
                    printf("%s",r[j]+pl);
                    if(j<c-1) printf("|");
                }
                printf("\n");
            } else printf("%s\n",p[i]);
        } else printf("%s\n",p[i]);
    }
}

int main(){
    FILE *f;
    char fn[20];
    int ch;
    printf("1.Left Recursion\n2.Left Factoring\nChoice:");
    scanf("%d",&ch);
    printf("File:"); scanf("%s",fn);
    f=fopen(fn,"r");
    n=0;
    while(fgets(p[n],50,f)){
        int l=strlen(p[n]);
        if(l&&p[n][l-1]=='\n') p[n][l-1]=0;
        if(l>1&&p[n][l-2]=='\r') p[n][l-2]=0;
        n++;
    }
    fclose(f);
    printf("\nOriginal:\n");
    for(int i=0;i<n;i++) printf("%s\n",p[i]);
    printf("\nTransformed:\n");
    if(ch==1) lr();
    else if(ch==2) lf();
    else printf("Invalid");
    return 0;
}
