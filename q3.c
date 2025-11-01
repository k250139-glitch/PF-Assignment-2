#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* toBinary(int n);
int query(int sectors[][3]);
int diagnostics(int sectors[][3]);
int updateSectorStatus(int sectors[][3]);
int main(){
    int sectors[][3]={
        {3,1,4},
        {4,1,2}
    },c;
    while (true)
    {
        printf("\n\n");
        int chose;
        printf("Chose from the above: \n");
        printf("1. Update sector status  \n");
        printf("2. Query sector status\n");
        printf("3. Run System Diagnostic\n");
        printf("Chose: ");
        if(scanf("%d",&chose) != 1){
            printf("Invalid input.");
            while ((c=getchar()), c != '\n' && c != EOF);
            
            continue;
        }
        switch (chose)
        {
        case 1:
            updateSectorStatus(sectors);
            break;
        case 2:
            query(sectors);
            break;
        case 3:
            diagnostics(sectors);
            break;
        
        default:
            printf("Invalid choice\nTry Again");
            break;
        }
    }
    return 0;
}
int updateSectorStatus(int sectors[][3]){
    int sectorRow,sectorCol,binaryTOInteger,c,bit;
    char status;
    againSector:
    printf("\nEnter the sector in which you want to update: \nrow: ");
    if(scanf("%d",&sectorRow) != 1){
        printf("Invalid input.");
        while ((c=getchar()), c != '\n' && c != EOF);
        goto againSector;
    }
    printf("Column: ");
    if(scanf("%d",&sectorCol) != 1){
        printf("Invalid input.");
        while ((c=getchar()), c != '\n' && c != EOF);
        goto againSector;
    }
    if(sectorRow>2 || sectorCol>3 || sectorRow<0 || sectorCol<0){
        printf("\nInvalid Sector\n");
        goto againSector;
    }
    printf("\n");
        switch (sectorCol)
            {
            case 0:
                printf("In sector %d%d the Power Status: ",sectorRow,sectorCol);
                bit=((sectors[sectorRow][sectorCol])>>0) & 1;
                switch(bit)
                {
                case 0:
                    printf("Off");
                    break;
                case 1:
                    printf("On");
                    break;
                }
                printf("\nDo you want to change the status? (Y/N): ");
                scanf(" %c",&status);
                if(toupper(status)=='Y'){
                    sectors[sectorRow][sectorCol] ^=1<<0;
                    printf("\nSuccessfully changes the Status\n");
                }else if (toupper(status)=='N'){
                    printf("\nContinuing without changing the Status\n");
                }else{
                    printf("Invalid Input.");
                }
                break;
            case 1:
                printf("In sector %d%d the Overload: ",sectorRow,sectorCol);
                bit=((sectors[sectorRow][sectorCol])>>1) & 1;
                switch (bit)
                {
                case 0:
                    printf("Normal");
                    break;
                case 1:
                    printf("Overloaded");
                    break;
                }
                printf("\nDo you want to change the status? (Y/N): ");
                scanf(" %c",&status);
                if(toupper(status)=='Y'){
                    sectors[sectorRow][sectorCol] ^=1<<1;
                    printf("\nSuccessfully changes the Status\n");
                }else if (toupper(status)=='N'){
                    printf("\nContinuing without changing the Status\n");
                }else{
                    printf("Invalid Input.");
                }
                break;
            case 2:
                printf("In sector %d%d the Maintainance: ",sectorRow,sectorCol);
                bit=((sectors[sectorRow][sectorCol])>>2) & 1;
                switch (bit)
                {
                case 0:
                    printf("No");
                    break;
                case 1:
                    printf("Required");
                    break;
                }
                printf("\nDo you want to change the status? (Y/N): ");
                scanf(" %c",&status);
                if(toupper(status)=='Y'){
                    sectors[sectorRow][sectorCol] ^=1<<2;
                    printf("\nSuccessfully changes the Status\n");
                }else if (toupper(status)=='N'){
                    printf("\nContinuing without changing the Status\n");
                }else{
                    printf("Invalid Input.");
                }
            break;
        }
    return 0;
}
int query(int sectors[][3]){
    for(int i=0;i<2;i++){
        for(int j=0;j<3;j++){
            printf("The sector %d%d is ",i,j);
            switch(sectors[i][j]){
            case 0:
                printf("Power: Off | Overload: Normal | Maintanance: No ");
                break;
            case 1:
                printf("Power: On | Overload: Normal | Maintanance: No ");
                break;
            case 2:
                printf("Power: Off | Overload: Overloaded | Maintanance: No ");
                break;
            case 3:
                printf("Power: On | Overload: Overloaded | Maintanance: No ");
                break;
            case 4:
                printf("Power: Off | Overload: Normal | Maintanance: Required ");
                break;
            case 5:
                printf("Power: Off | Overload: Overloaded | Maintanance: Required ");
                break;
            case 6:
                printf("Power: On | Overload: Overloaded | Maintanance: Required ");
                break;
            default:
                printf("Invalid Status Flag");
                break;
            }
            printf("\n");
        }
    }
}
int diagnostics(int sectors[][3]){
for(int i=0;i<2;i++){
    for(int j=0;j<3;j++){
            switch (sectors[i][j])
            {
            case 2:
                printf("In sector %d%d, ",i,j);
                printf("Overload: Overloaded");
                break;
            case 3:
                printf("In sector %d%d, ",i,j);
                printf("Overload: Overloaded");
                break;
            case 4:
                printf("In sector %d%d, ",i,j);
                printf("Maintanance: Required ");
                break;
            case 5:
                printf("In sector %d%d, ",i,j);
                printf("Overload: Overloaded & Maintanance: Required ");
                break;
            case 6:
                printf("In sector %d%d, ",i,j);
                printf("Overload: Overloaded & Maintanance: Required ");
                break;
            }
        printf("\n");
    }
}
}

char* toBinary(int n) {
    char* binary = (char*)malloc(4);
    if (!binary) return NULL;
    binary[3] = '\0'; 
    for (int i = 2; i >= 0; i--) {
        binary[i] = (n & 1) ? '1' : '0';
        n >>= 1;
    }
    return binary;
}