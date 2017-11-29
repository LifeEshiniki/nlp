#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define MAX_ENTRY_SIZE 150000

struct trie{
        int key;// キーisentry0なら０
        int is_entry; //あるなら１、ないなら０ 
        char *midasi; //is_entryが０なら空文字
        char *yomi;
        char *kihon;
        float Tuni;//is_entryが０ならMAX
        struct *trie next[16];
    
    };
int  Tnum = 0;

FILE *fopen_read(char *filename){
    FILE *istream = fopen(filename, "r");
    if(istream == NULL){
        fprintf(stderr, "can't open the file: %s\n", filename);
        exit(2);
    }
    return istream;
}

int fgetline(char *buf, size_t size, FILE *stream){
    int len;
    if(fgets(buf, size, stream) == NULL) return -1;
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

int read_dic_trie(char *filename){
    //バイトスライス
    char buf[10000], midasi[200], yomi[200], kihon[200], pos[200];
    int num = 0;
    struct trie *new,*root;

    while(fgetline(buf, sizeof(buf), dicstream) != -1){
        sscanf(buf, "%s%s%s%s%f", midasi, yomi, kihon, pos, &Tuni[num]);
        if ((new = malloc(sizeof(struct trie)) == NULL){
            return -1;
        }

        new 
    }


}

trie *trie_new(void) {
    //　ノードの定義
    trie *p = (trie*) malloc(sizeof(trie));
    p->key = 0;
    p->is_entry = 0;
    p->midasi = NULL;
    p->yomi = NULL;
    p->kihon = NULL;
    p->Tuni= 1000;  
    p->next = NULL;
    return p;
}
int search_trie(trie){

}


int lookup(char *word){
 int i;

/*  線形探索 */
    for(i = 0; i < Tnum; i++){
        if(!strcmp(word, Tmidasi[i])) return i;
    }

    return -1;
}
int bilookup(char *word){
 int mid = (Tnum-1)/2;
    int right = (Tnum-1);
    int left = 0; 

/* 二分探索 */
do{
    mid = (right -left)/2;

    if(!strcmp(word, Tmidasi[mid])) {
        return mid;
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
        printf("%s\t%s\t%s\t%s\n", Tmidasi[ent], Tyomi[ent], Tkihon[ent],Tpos[ent]);
    }
}

void longest_match(char *get){
    char *w;
    int i;
    int result;
    int l = strlen(get);
    int p=0;    
    printf("%d length.\n",l);
    printf("%s is input.\n",get);
    printf("initial %d\n",p);
    i=l;
    while(p <= l){
	printf("check p=%d,l=%d \n",p,l);
	    for(i = l;p >= i; i--){
            printf("%dnya\n",i);

            strncpy(w,get+p,i);

	    printf("%s is here?",w);
            result = lookup(w);

            if(result != -1)break;
}
	printf("%dhoge",result);
	printf("%dhog",p);
        print_word(result);

        if(result != 1){
            p = i+1;
        }
        else{
            p = p+1;
        }

    }    
}

/*コスト最小法*/
void cost_min(char *get){
    
    int i,j;
    int count,ent;
    int len = strlen(get);
    char *p[len];
    int w[len];
    float n[len];
    char *tango;
    char *s[len][10000];
    int wcost[len][10000];

    //初期化
    for (i=0;i<len;i++){
        if(i == 0) {
            n[i]=0;
            w[i]=0;
            }
        else {
            n[i]=1000;
            w[i]=0; 
        }
    }

    /*位置iで終わる単語を記録する*/
    for(i=1;i<=len;i++){
        for(j=i;j<1;j--){
            // Iで終わる単語をｓに入れる
            strncpy(tango,get+j,i);
            ent = lookup(tango);
            if(ent != -1){
                //　単語が存在
                s[i][j] = tango;
                wcost[i][j] = Tuni[ent];
                
            }

             // 
        }

        
        for (j=0;j > i;j++){
            //i番目で終わる全単語のうちコストが最小の物を選ぶ
            if (n[i] > wcost[i][j] + n[i-(strlen(s[i][j]))] ){
                w[i] = j;
            }
        }
        n[i] = n[i-(strlen(s[i][w[i]]))] + wcost[i][w[i]];
    }
    // バックトラック
    count = 0;
    i = strlen(get);
    while(i==0){
        p[count]=s[i][w[i]];
        i -= strlen(p[count]);
        count++;
    }
    for(j=count;j==0;j--){
        printf("%s\n",p[j]);
    }

}
int main(int ac, char **av){
    char buf[100000];
    int i;
    int ent;
    if(ac != 2) print_usage();

    read_dic(av[1]);
    printf("%s",av[1]);
    while(fgetline(buf, sizeof(buf),stdin) != -1){
	printf("%s is dumped.\n",buf);
        cost_min(buf);
    }
    return 0;
    
}