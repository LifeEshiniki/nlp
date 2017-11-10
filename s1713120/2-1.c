/*
課題２－１
アルゴリズム
文字種を分ける（範囲指定、場合分け）
• ASCII 文字（数字、アルファベット、記号を含む 1byte 文字）
• 平仮名 
• 片仮名 
• 横棒（‘ー’） 
• 数字 
• 2byte コードとしてのアルファベット 
• 漢字 
• 句読点（‘。’, ‘、’, ‘！’, ‘？’ の４種）
• その他
↓
１文字ごとに文字種を調べる
↓
もし前の文字と異なれば改行を入れる
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ASCIITYPE_S 0x00
#define ASCIITYPE_E 0x7f
#define HIRAGANA_S 0xa4a1
#define HIRAGANA_E 0xa4f3
#define KATAKANA_S 0xa5a1
#define KATAKANA_E 0xa5f6
#define NUMBER_S 0x30
#define NUMBER_E 0x39
#define TWOBYTECODE_S 0xa3b0
#define TWOBYTECODE_E 0xa3fa
#define KANJI_S 0xb0a1
#define KANJI_E 0xf4fe 
#define KUTOUTEN_S 0xa1a1
#define KUTOUTEN_E 0xa1aa
#define ASCIITYPE 1
#define HIRAGANA 2
#define KATAKANA 3
#define NUMBER 4
#define TWOBYTECODE 5
#define KANJI 6
#define KUTOUTEN 7
#define DASH 0xa1bc
#define OTHER 0
char euc_ch[3];
int check[2];

int check_character(int k){
  int i=0;
  int j,c,ans;
  
  /*printf("\ninput %d\n",k);*/
  
    if(k >=128){
      euc_ch[0] = k;
      i = k;
     
        if((k = getchar())!= EOF){
	  euc_ch[1] = k;
	  euc_ch[2] =  '\0';
	  j = k; /*EUC2byte文字*/
	    
        }else{
            printf("input text is not encoded EUC code.\n");
            }
        }
    else{
        j = k;
	euc_ch[0] = k;
	euc_ch[1] =  '\0';
        }
    
    c = (256 * i) + j;

    if (c >= HIRAGANA_S && c <= HIRAGANA_E){
        ans =  HIRAGANA;
    }
    else if(c >= KATAKANA_S && c <= KATAKANA_E){
        ans =  KATAKANA;
    } 
    else if(c >= ASCIITYPE_S && c <= ASCIITYPE_E){
        if(c >= NUMBER_S && c <= NUMBER_E){
            ans =  NUMBER;
        }
        else{
        ans =  ASCIITYPE;
        }

    } 
    else if(c >= TWOBYTECODE_S && c <= TWOBYTECODE_E){
        ans =  TWOBYTECODE;
    } 
    else if(c >= KANJI_S && c <= KANJI_E){
        ans =  KANJI;
    } 
    else if(c >= KUTOUTEN_S && c <= KUTOUTEN_E){
        ans =  KUTOUTEN;
    }
    else if(c == DASH){
      ans = DASH;
    }
    else{
        ans =  OTHER;
    }
    printf("%d",ans);
    return ans;
}


int main (void){
    int c;
    check[0] = 0; /*初期化*/
    while((c = getchar())!= EOF){
        
        check[1] = check_character(c);
        
        /*隣り合う文字種が同じかどうか*/
        if(check[0] == check[1] || check[1] == DASH){
            printf("%s",euc_ch);
        }
        else{
            printf("\n%s",euc_ch);
            check[0] = check[1];
        }
    }
    return 0;
}
