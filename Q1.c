#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int addNewBook(long long int isbns[], char titles[][50], float pricess[], int quantities[]);
int processASale(long long int isbns[], char titles[][50], float pricess[], int quantities[]);
void Generate_Low_Stock_Report(long long int isbns[], char titles[][50], float pricess[], int quantities[]);

int main(){
    int chose;
    long long int isbns[100]={0};
    char titles[100][50];
    float prices[100];
    int quantities[100];
    printf("** Hey! Welcome to Liberty Book store **\n");
    while(1){
        printf("\nMain Menu\n");
        printf("1. Add new Book\n2. Process A Sale\n3. Generate Low-Stock Report\nChose: ");
        if(scanf("%d",&chose) !=1){
            printf("\nInvalid Input. Please chose from above options.\n");
            int c;
            while((c=getchar()), c != '\n' && c != EOF);
            continue;
        }
        switch (chose)
        {
        case 1:
            addNewBook(isbns,titles,prices,quantities);
            break;
        case 2:
            processASale(isbns,titles,prices,quantities);
            break;
        case 3:
            Generate_Low_Stock_Report(isbns,titles,prices,quantities);
            break;
        default:
            printf("\nInvalid Input. Please chose from above options.\n");
            break;
        }
    }
    return 0;
}
int addNewBook(long long int isbns[], char titles[][50], float pricess[], int quantities[]){
    long long int isbn,lastIsbnIndex=-1;
    int quantity;
    float price;
    char title[50];
    for(int i=0;i<100;i++){
        if(isbns[i] != 0){
            lastIsbnIndex=i;
        }
    }
    if(lastIsbnIndex==99){
        printf("\nThe Book Inventory is full.\n");
        return 0;
    }
    isbnAgain:
    printf("Enter ISBN: ");
    if(scanf("%lld",&isbn)!=1){
        printf("\nInvalid Input.\n");
        int c;
        while((c=getchar()), c != '\n' && c!=EOF);
        goto isbnAgain;
    }
    for(int i=0;i<100;i++){
        if(isbn==isbns[i]){
            printf("\nBook of %lld already exist.\n",isbn);
            return 0;
        }
    }
    getchar();
    printf("Enter Title: ");
    fgets(title,sizeof(title),stdin);
    title[strlen(title)-1]='\0';
    againPrice:
    printf("Enter Prices: ");
    if(scanf("%f",&price)!=1){
        printf("\nInvalid Input.\n");
        int c;
        while((c=getchar()), c != '\n' && c!=EOF);
        goto againPrice;
    }
    if(price<1){
        printf("\nYou entered negative or number below zero. WHich is invalid\nTry again\n");
        goto againPrice;
    }
    againQuantity:
    printf("Enter Quantity: ");
    if(scanf("%d",&quantity)!=1){
        printf("\nInvalid Input.\n");
        int c;
        while((c=getchar()), c != '\n' && c!=EOF);
        goto againQuantity;
    }
    if(quantity<1){
        printf("\nYou entered negative or number below zero. WHich is invalid\nTry again\n");
        goto againQuantity;
    }
    isbns[lastIsbnIndex+1]=isbn;
    strcpy(titles[lastIsbnIndex+1],title);
    pricess[lastIsbnIndex+1]=price;
    quantities[lastIsbnIndex+1]=quantity;

    return 1;
}
int processASale(long long int isbns[], char titles[][50], float pricess[], int quantities[]){
    long long int isbn;
    int quantity,tempQuantity;
    bool isbnsExist=false;
    isbnAgain:
    printf("Enter ISBN: ");
    if(scanf("%lld",&isbn)!=1){
        printf("\nInvalid Input.\n");
        int c;
        while((c=getchar()), c != '\n' && c!=EOF);
        goto isbnAgain;
    }
    for(int i=0;i<100;i++){
        if(isbn==isbns[i]){
            isbnsExist=true;
        }
    }
    if(!isbnsExist){
        printf("\nThe book %lld does not exist\n",isbn);
        return 0;
    }
    againQuantity:
    printf("Enter Quantity Sold: ");
    if(scanf("%d",&quantity)!=1){
        printf("\nInvalid Input.\n");
        int c;
        while((c=getchar()), c != '\n' && c!=EOF);
        goto againQuantity;
    }
    if(quantity<1){
        printf("\nYou entered negative or number below zero. WHich is invalid\nTry again\n");
        goto againQuantity;
    }
    for(int i=0;i<100;i++){
        if(isbns[i]==isbn){
            tempQuantity=quantities[i];
            if(quantity>tempQuantity){
                printf("There are %d but you entered %d sold. Which is a mistake.\nTry Again\n",tempQuantity,quantity);
                goto againQuantity;
            }else{
                quantities[i] -=quantity;
                printf("\nSuccessfully updated inventory.\n");
            }
        }
    }
}
void Generate_Low_Stock_Report(long long int isbns[], char titles[][50], float pricess[], int quantities[]){
    int lastBookIndex=0;
    for(int i=0;i<100;i++){
        if(isbns[i] != 0){
            lastBookIndex=i;
        }
    }
    printf("\nBelow are the list of books whose quantity is below 5.\n");
    for(int i=0;i<=lastBookIndex;i++){
        if(quantities[i]<5){
            printf("%lld || %s || %.2f || %d\n",isbns[i],titles[i],pricess[i],quantities[i]);
        }
    }
}