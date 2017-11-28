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
    FILE *fp = fopen(filename, "r");
    if(fp == NULL){
        fprintf(stderr, "can't open the file: %s\n", filename);
        exit(2);
    }
}

/*バッファに読み込む*/
int fgetline(char *buf, size_t size, FILE *stream){
    int len;
    if(fgets(buf, size, stream) == NULL) return -1;   /*読み込む文字がないなら終了*/
    // fgetsの
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

/*最長一致法*/
int longest_match(char *get){
    char *p;
    char *w;
    int i,j,result;
    int l = strlen(get);
    p = get;

    while(p != NULL){
        for (i=l;p>=i;i--){
            /*最長の単語を見つける、先頭位置Pからiまでの単語が辞書に存在するか調べる*/ 
            //ｗに先頭位置ｐから現在の位置iまでの単語を代入する
            // 最長の単語が見つかったらループを抜ける
        if(lookup(w) != -1) 
        print_word(result);
        return i;
        } 

    

        if(result != 1){
            p = get + (i + 1);
        }
        else{
            p = p + 1;
        }

    }    
}
/*コスト最小法*/
void cost_min(int len){
    
    int i,j;
    char p[len];
    int n[len],w[len];

    char *s[len][MAX];
    /*位置iで終わる単語を記録する*/
    for(i=0;i<len;i++){
        for(j=i,j<0;j--){
            p[j] = buf
             //読み取った文字をpにいれる  
        }
    }

}

int main(int argc, char **argv){
    char buf[100000];
    /*バッファには何が入る？？*/
    int i;
    int ent;
    if(argc != 2) error_message();
    read_dic(argv[1]);
    /*辞書の読み出し
    辞書のファイルを読み込む→辞書のサイズを更新→辞書に単語を登録
    */
    while(fgetline(buf, sizeof(buf), stdin) != -1){
        /*バッファに入っている文字列を読み出し、辞書にその単語があれば表示する*/
        print_word(lookup(buf));
        /**/
    }
    while(argv != NULL){//文末まで最長一致法による形態素解析
        ent = 0;
        ent = longest_match(*argv);
        

    }
    return 0;
}

int main (void){
    int c;
    char buf[10000000];
    size_t size;
    size = sizeof(buf);

    while((fgets(buf,size,stdin != NULL)){

    }
    return 0;
}