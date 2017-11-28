#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

//　単語の上限数
#define MAX_ENTRY_SIZE 150000

//　辞書
char *Tmidasi[MAX_ENTRY_SIZE];
char *Tyomi[MAX_ENTRY_SIZE];
char *Tkihon[MAX_ENTRY_SIZE];
char *Tpos[MAX_ENTRY_SIZE];
float Tuni[MAX_ENTRY_SIZE];
char Tstr[10000000];
char *endTstr = Tstr;
int  Tnum = 0;

//ファイルのの読み込み
FILE *fopen_read(char *filename){
    FILE *istream = fopen(filename, "r");
    if(istream == NULL){
        fprintf(stderr, "can't open the file: %s\n", filename);
        exit(2);
    }
}

//　辞書の読み込み＋fgetsにより読み込んだ単語の数を数える
int fgetline(char *buf, size_t size, FILE *stream){
    int len;
    /*fgets→ファイル中の文字を一行ずつ読み込む*/
    if(fgets(buf, size, stream) == NULL) return -1;
    /*ファイルに文字がなければエラーステータスとしてー１を返す*/
    len = strlen(buf);
    /*バッファに入っている文字数を記録*/
    if(len == 0) return len;/*0もじならそのまま*/
    if(buf[len-1] == '\n'){
        buf[len-1] = '\0';
         return len-1;
    } else {
        return len;
    }
}


//　コマンドの説明
void print_usage(){
    fprintf(stderr, "Usage: readdic dicfile < text > lookup_result\n");
    exit(2);
}


// 辞書の読み込み
int read_dic(char *filename){
    char buf[10000], midasi[200], yomi[200], kihon[200], pos[200];
    int  num = 0;
    FILE *dicstream = fopen_read(filename);
    // 辞書ファイルを開く
    while(fgetline(buf, sizeof(buf), dicstream) != -1)
    {
        // 辞書ファイルの文末まで１行ずつ読み取る
        sscanf(buf, "%s%s%s%s%f", midasi, yomi, kihon, pos, &Tuni[num]);
        // 辞書の内容を読み込んだバッファから見出し、読み、基本形を得る
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
         // endTstrに辞書の内容を記録、見出し、読みなどの情報の一覧に追加
         //　すべて追加したら辞書のエントリ数を増やす

    }
    Tnum = num;
    return num;
}

// 辞書の検索
int lookup(char *word){
    int i;

/*  linear search */
    for(i = 0; i < Tnum; i++){
        if(!strcmp(word, Tmidasi[i])) return i;
    }

    return -1;
}


// 単語の検索結果
void print_word(int ent){
    //エントリーにある文字は表示、ない文字はエラーを返す
    char unkword[10];
    if(ent == -1){
      printf("Unknown word!!\n");
    } else {
        printf("%s\t%s\t%s\t%s\n", Tmidasi[ent], Tyomi[ent], Tkihon[ent],Tpos[e\
nt]);
    }
}



// メイン関数
int main(int argc, char **argv){
    char buf[100000];
    int i;
    int ent;
    if(argc != 2) print_usage();
    read_dic(argv[1]);
    while(fgetline(buf, sizeof(buf), stdin) != -1){
        /*キーボード入力からバッファに文字を１行ずつ読み込み*/
        print_word(lookup(buf));
        // キーボードに入力された単語の検索結果の表示
    }
  
    return 0;
}
