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


int fgetline(char *buf, size_t size, FILE *stream){
    int len;
    /*fgets→ファイル中の文字を一行ずつ読み込む*/
    if(fgets(buf, size, stream) == NULL) return -1;
    /*ファイルに文字がなければエラーステータスとしてー１を返す*/
    len = strlen(buf);
    /*あいうえお\nほげほげ\n\0ならこの関数の返り値は？*/
    /*バッファに入っている文字数を記録*/
    if(len == 0) return len;/*0もじならそのまま*/
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


int read_dic(char *filename){
    char buf[10000], midasi[200], yomi[200], kihon[200], pos[200];
    int  num = 0;
    FILE *dicstream = fopen_read(filename);
    while(fgetline(buf, sizeof(buf), dicstream) != -1){
        sscanf(buf, "%s%s%s%s%f", midasi, yomi, kihon, pos, &Tuni[num]);
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


int lookup(char *word){
    int i;

/*  linear search */
    for(i = 0; i < Tnum; i++){
        if(!strcmp(word, Tmidasi[i])) return i;
    }

    return -1;
}

void print_word(int ent){//エントリーにある文字は表示、ない文字はエラーを返す
    char unkword[10];
    if(ent == -1){
      printf("Unknown word!!\n");
    } else {
        printf("%s\t%s\t%s\t%s\n", Tmidasi[ent], Tyomi[ent], Tkihon[ent],Tpos[e\
nt]);
    }
}

int main(int argc, char **argv){
    char buf[100000];
    int i;
    int ent;
    if(ac != 2) print_usage();
    read_dic(av[1]);
    while(fgetline(buf, sizeof(buf), stdin) != -1){
        /*バッファの文字を読み込み*/
        print_word(lookup(buf));
    }
    return 0;
}
