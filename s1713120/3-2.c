#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAX_ENTRY_SIZE 150000

char *Tmidasi[MAX_ENTRY_SIZE];
char *Tyomi[MAX_ENTRY_SIZE];
char *Tkihon[MAX_ENTRY_SIZE];
char *Tpos[MAX_ENTRY_SIZE];
float Tuni[MAX_ENTRY_SIZE];
char Tstr[10000000];
char *endTstr = Tstr;
int  Tnum = 0;


FILE *fopen_read(char *filename){
    FILE *istream = fopen(filename, "r");
    if(istream == NULL){
        fprintf(stderr, "can't open the file: %s\n", filename);
        exit(2);
    }
}

/*バッファに読み込む*/
int fgetline(char *buf, size_t size, FILE *stream){
    int len;
    if(fgets(buf, size, stream) == NULL) return -1;   /*読み込む文字がないなら終了*/
    len = strlen(buf); 
    if(len == 0) return len;
    if(buf[len-1] == '\n'){
        buf[len-1] = '\0';
         return len-1;
    } else {
        return len;
    }
}



void print_usage(){
    fprintf(stderr, "Usage: readdic dicfile < text > lookup_result\n");
    exit(2);
}

/*辞書の読み込み*/


int read_dic(char *filename){

    /*単語、単語の見出し、単語の読み、基本形*/
    char buf[10000], midasi[200], yomi[200], kihon[200], pos[200];
    int  num = 0;
    
    /*辞書ファイルを読み込む*/
    FILE *dicstream = fopen_read(filename);


    while(fgetline(buf, sizeof(buf), dicstream) != -1){
        
        /*単語のステータスの表示*/
        sscanf(buf, "%s%s%s%s%f", midasi, yomi, kihon, pos, &Tuni[num]);
        
        /*見出しの単語をヒープにダンプ*/
        strcpy(endTstr, midasi);
        Tmidasi[num] = endTstr;
        endTstr += strlen(midasi)+1;
        strcpy(endTstr, yomi);
        Tyomi[num] = endTstr;
        endTstr += strlen(yomi)+1;
        strcpy(endTstr, kihon);
        Tkihon[num] = endTstr;
        endTstr += strlen(kihon)+1;
	strcpy(endTstr, pos);
        Tpos[num] = endTstr;
        endTstr += strlen(pos)+1;
         num++;
    }
    Tnum = num;
    return num;
}


int lookup(char *word,int length){
    
    int mid = length/2;
    int right = length-1;
    int left = 0; 

/* 二分探索 */

do{
    mid = (left + right)/2;

    if(!strcmp(word, Tmidasi[mid])) {
        return i;
    }
    else if(strcmp(word,Tmidasi[mid])>0){
        left = mid+1;
    }
    else {
        right = mid-1;
    }
} while (left >= right);
    return -1;
}

void print_word(int ent){
    char unkword[10];
    if(ent == -1){
      printf("Unknown word!!\n");
    } else {
        printf("%s\t%s\t%s\t%s\n", Tmidasi[ent], Tyomi[ent], Tkihon[ent],Tpos[e\
nt]);
    }
}

 main(int ac, char **av){
    char buf[100000];
    int i;
    int ent;
    int dicsize;
    if(ac != 2) print_usage();
    dicsize = read_dic(av[1]);
    while(fgetline(buf, sizeof(buf), stdin) != -1){
        print_word(lookup(buf,dicsize));
    }
}
