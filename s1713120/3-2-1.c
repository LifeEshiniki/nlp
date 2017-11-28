#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 150000

char *midashi[MAX];
char *[MAX];
char *kihon[MAX];
char *pos[MAX];
float Tuni[MAX];
char Tstr[10000000];
char *endTstr = Tstr;
int  dicsize = 0;


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



void error_message(){
    fprintf(stderr, "Error\n");
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
        midashi[num] = endTstr;
        endTstr += strlen(midasi)+1;
        strcpy(endTstr, yomi);
        yomi[num] = endTstr;
        endTstr += strlen(yomi)+1;
        strcpy(endTstr, kihon);
        kihon[num] = endTstr;
        endTstr += strlen(kihon)+1;
	    strcpy(endTstr, pos);
        pos[num] = endTstr;
        endTstr += strlen(pos)+1;
         num++;
    }
    dicsize = num;
    return num;
}

int li_lookup(char *word){
    int i;

/*  線形探索 */
    for(i = 0; i < Tnum; i++){
        if(!strcmp(word, Tmidasi[i])) return i;
    }

    return -1;
}

int lookup(char *word){
    
    int mid = dicsize/2;
    int right = dicsize-1;
    int left = 0; 

/* 二分探索 */

do{
    mid = (left + right)/2;

    if(!strcmp(word, midashi[mid])) {
        return mid;
    }
    else if(strcmp(word,midashi[mid])>0){
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
        printf("%s\t%s\t%s\t%s\n", midashi[ent], yomi[ent], kihon[ent],pos[e\
nt]);
    }
}

void longest_match(char *get){
    char *w;
    int i,result;
    int l = strlen(get);
    int p=0;

    while(p <= l){
        for (i=l;p>=i;i--){
            /*最長の単語を見つける、先頭位置Pからiまでの単語が辞書に存在するか調べる*/
            strncpy(w,get+p,l);
            //wにpからiまでの部分文字列を代入
            result = lookup(w);
            if(result != -1) break;
        } 

        print_word(result);

        if(result != 1){
            p = i+1;
        }
        else{
            p = p+1;
        }

    }    
}

int main(int argc, char **argv){
    // 入力形式はプログラム、辞書ファイル、テキストファイル
    char buf[1000000];
    int i;
    int ent;
    if(argc != 3) error_message();
    read_dic(argv[1]);
    while(fgetline(buf, sizeof(buf), argv[2]) != -1){
        // テキストから一行ずつ読み取る
        longest_match(buf);
    }
    return 0;
 }
