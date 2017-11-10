#include <stdio.h>

int main (void){
    int c;
    unsigned char euc_ch[3];
    while ((c = getchar())!= EOF){
        if(c >= 128){/*1byeに収まらない場合*/
            euc_ch[0] = c;
            if((c = getchar())!= EOF){
                euc_ch[1] = c; /*EUC2byte文字*/
                euc_ch[2] = '\0'; 
            }else{
                printf("input text is not encoded EUC code.\n");
                
            }
        } else if(c == '\n'){/*改行*/
            continue;
        } else{
            euc_ch[0] = c;
            euc_ch[1] = '\0';/*ASCII*/
        }
        } 
        printf("%s\n", euc_ch);
    }
    return;
(}
