#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void encodeMessage(char message[]);
void decodeMessage(char message[]);

int main(){
    char message[1024];
    int chose,c;
    while(1){
        printf("\nChose from the above: \n");
        printf("1. Encode message \n");
        printf("2. Decode message \n");
        printf("3. Exit \n");
        if(scanf("%d",&chose)!=1){
            printf("\nInvalid input.\nChose from above options.");
            while((c=getchar()),c != '\n' && c != EOF);
            continue;
        }
        switch (chose)
        {
        case 1:
            getchar();
            printf("\nMessage: ");
            scanf("%[^\n]",message);
            encodeMessage(message);
            break;
        case 2:
            getchar();
            printf("\nMessage: ");
            scanf("%[^\n]",message);
            decodeMessage(message);
            break;
        case 3:
            return 0;
            break;
        default:
            printf("\nInvalid input.\nChose from above options.");
            break;
        }
    }
    return 0;
}
void encodeMessage(char message[]){
    int length=strlen(message),j=0,tempASCI;
    char encodedMessage[length+1],finalEnocdedMessage[length+1];
    for(int i=length-1;i>=0;i--){
        encodedMessage[j++]=message[i];
    }
    encodedMessage[j] = '\0';
    for(int i=0;i<j;i++){
        tempASCI=encodedMessage[i];
        tempASCI ^= 1<<1;
        tempASCI ^= 1<<4;
        finalEnocdedMessage[i]=tempASCI;
    }
    finalEnocdedMessage[j] = '\0';
    printf("\nEncoded Message:\n%s\n",finalEnocdedMessage);
}
void decodeMessage(char message[]){
    int length=strlen(message),j=0,tempASCI;
    char decodedMessage[length+1],finalDeocdedMessage[length+1];
    for(int i=0;i<length;i++){
        tempASCI=message[i];
        tempASCI ^= 1<<1;
        tempASCI ^= 1<<4;
        decodedMessage[i]=tempASCI;
    }
    decodedMessage[length] = '\0';
    for(int i=length-1;i>=0;i--){
        finalDeocdedMessage[j++]=decodedMessage[i];
    }
    finalDeocdedMessage[j] = '\0';
    printf("\nDecoded Message:\n%s\n",finalDeocdedMessage);
}