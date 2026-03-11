#include <stdio.h>
#include <string.h>
#include <ctype.h>

char p[20][10],f[20][20],fl[20][20],n[20],t[20];
int np=0,nt=0;

void a(char *s,char c){if(!strchr(s,c)){int l=strlen(s);s[l]=c;s[l+1]=0;}}

void fst(){
    int ch;
    do{ch=0;
        for(int i=0;i<np;i++){
            char nt1=p[i][0],*rhs=p[i]+2;
            int id=0;for(int j=0;j<nt;j++)if(n[j]==nt1)id=j;
            if(islower(rhs[0])||strchr("()+-*/",rhs[0])){
                if(!strchr(f[id],rhs[0])){a(f[id],rhs[0]);ch=1;}
            }else if(rhs[0]=='#'){
                if(!strchr(f[id],'#')){a(f[id],'#');ch=1;}
            }else{
                for(int k=0;rhs[k];k++){
                    if(isupper(rhs[k])){
                        for(int l=0;l<nt;l++)if(n[l]==rhs[k]){
                            for(int m=0;f[l][m];m++)if(f[l][m]!='#'&&!strchr(f[id],f[l][m])){a(f[id],f[l][m]);ch=1;}
                            if(!strchr(f[l],'#'))break;
                        }
                    }else{if(!strchr(f[id],rhs[k])){a(f[id],rhs[k]);ch=1;}break;}
                }
            }
        }
    }while(ch);
}

void foll(){
    for(int i=0;i<nt;i++)a(fl[i],'$');
    int ch;
    do{ch=0;
        for(int i=0;i<np;i++){
            char nt1=p[i][0],*rhs=p[i]+2;
            int idNt;for(int j=0;j<nt;j++)if(n[j]==nt1)idNt=j;
            for(int j=0;rhs[j];j++)if(isupper(rhs[j])){
                int idB;for(int k=0;k<nt;k++)if(n[k]==rhs[j])idB=k;
                if(!rhs[j+1]){for(int m=0;fl[idNt][m];m++)if(!strchr(fl[idB],fl[idNt][m])){a(fl[idB],fl[idNt][m]);ch=1;}}
                else{int all=1;
                    for(int k=j+1;rhs[k];k++){
                        if(isupper(rhs[k])){
                            int idC;for(int l=0;l<nt;l++)if(n[l]==rhs[k])idC=l;
                            for(int m=0;f[idC][m];m++)if(f[idC][m]!='#'&&!strchr(fl[idB],f[idC][m])){a(fl[idB],f[idC][m]);ch=1;}
                            if(!strchr(f[idC],'#')){all=0;break;}
                        }else{if(!strchr(fl[idB],rhs[k])){a(fl[idB],rhs[k]);ch=1;}all=0;break;}
                    }
                    if(all)for(int m=0;fl[idNt][m];m++)if(!strchr(fl[idB],fl[idNt][m])){a(fl[idB],fl[idNt][m]);ch=1;}
                }
            }
        }
    }while(ch);
}

int main(){
    FILE *fp;char fn[30];
    printf("Enter filename: ");scanf("%s",fn);
    fp=fopen(fn,"r");
    fscanf(fp,"%d",&np);
    for(int i=0;i<np;i++){
        fscanf(fp,"%s",p[i]);
        if(!strchr(n,p[i][0]))n[nt++]=p[i][0];
    }
    fclose(fp);
    fst();foll();
    printf("\nFIRST:\n");
    for(int i=0;i<nt;i++){
        printf("FIRST(%c)={",n[i]);
        for(int j=0;f[i][j];j++){if(f[i][j]=='#')printf("#");else printf("%c",f[i][j]);if(f[i][j+1])printf(" ");}
        printf("}\n");
    }
    printf("\nFOLLOW:\n");
    for(int i=0;i<nt;i++){
        printf("FOLLOW(%c)={",n[i]);
        for(int j=0;fl[i][j];j++){printf("%c",fl[i][j]);if(fl[i][j+1])printf(" ");}
        printf("}\n");
    }
    return 0;
}
