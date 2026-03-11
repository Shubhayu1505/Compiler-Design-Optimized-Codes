#include <stdio.h>
#include <string.h>

char prod[10][20], first[10][20], follow[10][20], table[5][6][30];
int n;

void add(char *s, char c) {
    if(!strchr(s,c)) { int l=strlen(s); s[l]=c; s[l+1]=0; }
}

void firstComp() {
    for(int i=0;i<10;i++) first[i][0]=0;
    int ch;
    do { ch=0;
        for(int i=0;i<n;i++) {
            int idx=prod[i][0]-'E';
            char *r=prod[i]+2;
            if(!strcmp(r,"id") && !strchr(first[idx],'i')) { add(first[idx],'i'); ch=1; }
            else if(r[0]=='(' && !strchr(first[idx],'(')) { add(first[idx],'('); ch=1; }
            else if((r[0]=='+'||r[0]=='*') && !strchr(first[idx],r[0])) { add(first[idx],r[0]); ch=1; }
            else if(r[0]=='#' && !strchr(first[idx],'#')) { add(first[idx],'#'); ch=1; }
            else if(r[0]>='A'&&r[0]<='Z') {
                int i2=r[0]-'E';
                for(int j=0;first[i2][j];j++) 
                    if(first[i2][j]!='#' && !strchr(first[idx],first[i2][j])) 
                        { add(first[idx],first[i2][j]); ch=1; }
            }
        }
    } while(ch);
}

void followComp() {
    for(int i=0;i<10;i++) follow[i][0]=0;
    add(follow[0],'$');
    int ch;
    do { ch=0;
        for(int i=0;i<n;i++) {
            int il=prod[i][0]-'E';
            char *r=prod[i]+2;
            for(int j=0;r[j];j++) if(r[j]>='A'&&r[j]<='Z') {
                int ib=r[j]-'E';
                if(!r[j+1]) {
                    for(int k=0;follow[il][k];k++) 
                        if(!strchr(follow[ib],follow[il][k])) { add(follow[ib],follow[il][k]); ch=1; }
                } else {
                    if(r[j+1]=='+'||r[j+1]=='*'||r[j+1]=='('||r[j+1]==')') {
                        if(!strchr(follow[ib],r[j+1])) { add(follow[ib],r[j+1]); ch=1; }
                    } else if(!strncmp(&r[j+1],"id",2)) {
                        if(!strchr(follow[ib],'i')) { add(follow[ib],'i'); ch=1; }
                    } else if(r[j+1]>='A'&&r[j+1]<='Z') {
                        int in=r[j+1]-'E';
                        for(int k=0;first[in][k];k++) 
                            if(first[in][k]!='#' && !strchr(follow[ib],first[in][k])) 
                                { add(follow[ib],first[in][k]); ch=1; }
                    }
                }
            }
        }
    } while(ch);
}

void build() {
    for(int i=0;i<5;i++) for(int j=0;j<6;j++) strcpy(table[i][j],"");
    strcpy(table[0][0],"E->T"); strcpy(table[0][3],"E->T");
    strcpy(table[1][1],"E'->+TE'"); strcpy(table[1][4],"E'->#"); strcpy(table[1][5],"E'->#");
    strcpy(table[2][0],"T->F"); strcpy(table[2][3],"T->F");
    strcpy(table[3][1],"T'->#"); strcpy(table[3][2],"T'->*FT'"); strcpy(table[3][4],"T'->#"); strcpy(table[3][5],"T'->#");
    strcpy(table[4][0],"F->id"); strcpy(table[4][3],"F->(E)");
}

int main() {
    char f[50]; FILE *fp;
    printf("File: "); scanf("%s",f);
    fp=fopen(f,"r"); fscanf(fp,"%d",&n);
    for(int i=0;i<n;i++) fscanf(fp,"%s",prod[i]);
    fclose(fp);
    firstComp(); followComp(); build();
    printf("\nPARSING TABLE\nNT\tid\t+\t*\t(\t)\t$\n");
    char *nt[]={"E","E'","T","T'","F"};
    for(int i=0;i<5;i++) {
        printf("%s\t",nt[i]);
        for(int j=0;j<6;j++) printf("%s\t",strlen(table[i][j])?table[i][j]:"-");
        printf("\n");
    }
    return 0;
}
