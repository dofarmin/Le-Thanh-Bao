#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 10000
void removeSpecialCharacters(char *test){
    int i,j;
    if(test[strlen(test)-3] == '\'' && test[strlen(test)-2] == 'l' && test[strlen(test)-1] == 'l') test[strlen(test)-3] = '\0';
    for(i = 0;test[i] != '\0';++i){
        while(!(test[i] >= 'a' && test[i] <= 'z') && !(test[i] >= 'A' && test[i] <= 'Z') && !(test[i] == '\0') && !(test[i] >= '0' && test[i] <= '9')){
            for(j = i;test[j] != '\0';++j){
                test[j] = test[j+1];
            }
            test[j] = '\0';
        }
    }
    return;
}
int alreadyHave(char test[MAX][200],char *temp){
    int i;
    for (i = 0;test[i][0] != '\0';i++) if(strcmp(test[i],temp)==0) return 1;
    return 0;
}
int checkSpecialCharacter(char test){
    if((test >= 'a' && test <= 'z')||(test >= 'A' && test <= 'Z')) return 0;
    return 1;
}
void lowercase(char *test){
    int i;
    for(i = 0;test[i] != '\0';++i){
        if(test[i] >= 'A' && test[i] <= 'Z') test[i] += 32;
    }
    return;
}

int meanninglessWordorNumber(char *test){
    char temp[200], temp2[200];
    strcpy(temp,test);
    lowercase(temp);
    FILE *f = fopen("stopw.txt", "r");
    if(!f) exit(1);
    while(fscanf(f, "%s", temp2) == 1){
        removeSpecialCharacters(temp);
        if(strcmp(temp, temp2)==0){
        fclose(f);
        return 1;
    }
        if(temp[0] >= '0' && temp[0] <= '9'){
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

int checkCapital(char *test){
    char temp[200];
    strcpy(temp, test);
    removeSpecialCharacters(temp);
    if(temp[0] >= 'A' && temp[0] <= 'Z') return 1;
    else return 0;
}

void indexTable(){
    char words[MAX][200], words2[MAX][200], temp[200], line[500];
    int i = 0,next = 0,a,b,c,d,n,linenumber = 1,count = 0;
    FILE *f = fopen("vanban.txt", "r");
    if(!f) exit(1);
    while(fscanf(f, "%s", temp) == 1){
        if(meanninglessWordorNumber(temp) == 0){
            if(next == 1 && checkCapital(temp) == 1){
                if(temp[strlen(temp) - 1] != '.' || strcmp(temp, "U.S.") == 0) continue;
                else{
                    next = 0;
                    continue;
                }
            }
            if(temp[strlen(temp)-1] != '.' && temp[0] != '\0' && alreadyHave(words,temp) == 0){
            next = 1;
            strcpy(words[i], temp);
            removeSpecialCharacters(words[i]);
            lowercase(words[i]);
            i++;
            }else if(strcmp(temp, "U.S.") != 0 && temp[0] != '\0' && alreadyHave(words,temp) == 0){
                next = 0;
                strcpy(words[i], temp);
                removeSpecialCharacters(words[i]);
                lowercase(words[i]);
                i++;
            }
        
        }
    }
    for(a = 0;a < i;++a){
        for(b = a+1;b < i;++b){
            if(strcmp(words[a], words[b]) > 0){
                strcpy(temp, words[a]);
                strcpy(words[a], words[b]);
                strcpy(words[b], temp);
            }
        }
    }
    b = 0;
    for(a = 0;a < i;++a) if(strcmp(words[a], words[a+1]) != 0) strcpy(words2[b++], words[a]);
    strcpy(words2[b], words[i]);
    fseek(f, 0, SEEK_SET);
    for(c = 0;c < b;++c){
        fseek(f, 0, SEEK_SET);
        printf("%s ",words2[c]);
            while(fscanf(f,"%s",temp) == 1){
                removeSpecialCharacters(temp);
                lowercase(temp);
                if(strcmp(words2[c], temp) == 0) count++;
            }
        fseek(f, 0, SEEK_SET);
        printf(" %d",count);
        count = 0;
            while(fgets(line, 256, f) != NULL){
                a = 0;
                n = strlen(line);
                    while(a < n){
                    d = 0;
                    while( a < n && d < strlen( words2[c] ) && ( line[a] == words2[c][d] || line[a] + 32 == words2[c][d] ) ){
                            ++a;
                            ++d;
                        }
                    if( (a == n||checkSpecialCharacter(line[a])==1) && d == strlen( words2[c] ) ) 
                    {
                        
                        printf(",%d", linenumber);
                    }
                    while(a < n && line[a] != ' ') a++;
                    a++;
                    }
        linenumber++;
    }
    printf("\n");
    linenumber = 1;
    }
    fclose(f);
    return;
}
    
void main(){
    indexTable();
    return;
}