#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct User
{
    char name[50];
    long long int cnic;
};

struct  User user;

int login();
void customerInfo();
int getSize(long long int cnic);
void displaInventory();
int updateInventory(int upDatedPD,int to);
int addItemT0Cart(int productCodeInCart[],int QuantutyOfProductInCart[],int itemsNumber);
void showBill(int pcic[],int qpic[],float disCount,int countItem);

int productCode[4]={001,002,003,004};
int quantityInStock[4]={50,10,20,8};
int pricePerProduct[4]={100,200,300,150};

int main(){
    int itemsNumber;
    int productCodeInCart[itemsNumber];
    int QuantutyOfProductInCart[itemsNumber];
    int chose;

    char promocode,promocodeCOde[10];
    bool promocodeOK=false;
    int c;

    login();
    while(true){
    printf("\n");
    printf("What Would you like to perform?\n");
    printf("1. View Customer Information\n");
    printf("2. Display Invetory\n");
    printf("3. Add item to cart\n");
    printf("4. Display Total Bill\n");
    printf("5. SHow Invoice\n");
    printf("6. Exit\n");
    printf("Chose: ");
    while ((c=getchar()),c != '\n' && c != EOF);
    scanf("%d",&chose);
    switch(chose)
    {
    case 1:
        customerInfo();
        break;
    case 2:
        displaInventory();
        break;
    case 3:
        int itemsNumber;
        againitemsNumber:
        printf("How many item you want to add to your cart: ");
        while((c=getchar()),c != '\n' && c != EOF);
        scanf("%d",&itemsNumber);
        if(itemsNumber<0){
            printf("\nInvalid input\n");
            goto againitemsNumber;
        }
        addItemT0Cart(productCodeInCart,QuantutyOfProductInCart,itemsNumber);
        break;
    case 4:
        promocodeOK=false;
        againPromocode1:
        while((c=getchar()),c != '\n' && c != EOF);
        printf("\nDO you have any promocode? (Y/N): ");
        scanf(" %c",&promocode);
        if(toupper(promocode)=='Y'){
            printf("Enter Code: ");
            scanf("%s",promocodeCOde);
            if(strcmp(promocodeCOde,"Eid2025")==0){
                promocodeOK=true;
            }else{
                printf("Invalid promocode.\n");
                goto againPromocode1;
            }
        }
            printf("\nFinall Bill: \n");
            if(promocodeOK){
                showBill(productCodeInCart,QuantutyOfProductInCart,0.25,itemsNumber);
            }else{
                showBill(productCodeInCart,QuantutyOfProductInCart,0.0,itemsNumber);
            }
        break;
    case 5:
        promocodeOK=false;
        againPromocode:
        while((c=getchar()),c != '\n' && c != EOF);
        printf("\nDO you have any promocode? (Y/N): ");
        scanf(" %c",&promocode);
        if(toupper(promocode)=='Y'){
            printf("Enter Code: ");
            scanf("%s",promocodeCOde);
            if(strcmp(promocodeCOde,"Eid2025")==0){
                promocodeOK=true;
            }else{
                printf("Invalid promocode.\n");
                goto againPromocode;
            }
        }
        printf("Customer Name: %s\t\t Customer CNIC %lld",user.name,user.cnic);
        printf("\nFinall Bill: \n");
        if(promocodeOK){
                showBill(productCodeInCart,QuantutyOfProductInCart,0.25,itemsNumber);
            }else{
                showBill(productCodeInCart,QuantutyOfProductInCart,0.0,itemsNumber);
            }
        break;
    case 6:
    return 0;
        printf("\nBye bye");
        break;
    default:
        printf("Invalid Choice\nTry Again\n\n");
        break;
    }
}
    return 0;
}
void customerInfo(){
        printf("\nUser Name: %s\n",user.name);
        printf("User CNIC: %lld\n\n",user.cnic);
}
int login(){
    printf("Name of customer: ");
    scanf("%[^\n]",&user.name);
    againCNIC:
    printf("CNIC number of the customer (Without dashesh[-]): ");
    int c;
    while((c=getchar()),c != '\n' && c != EOF);
    if(scanf("%lld",&user.cnic)!=1){
        printf("\nInvalid CNIC number.\n");
        goto againCNIC;
    }
    if(getSize(user.cnic)!=13){
        printf("\nInvalid CNIC number.\n");
        goto againCNIC;
    }
    return 0;
}
void displaInventory(){
    printf("Product code\tQuantity of product\tQuantity Per Product\n");
    for(int j=0;j<4;j++){
        printf("%d\t\t%d\t\t\t%d\n",productCode[j],quantityInStock[j],pricePerProduct[j]);
    }
}
int updateInventory(int upDatedPD,int to){
    if(to<0) return 0;
    for(int i=0;i<4;i++){
        if(productCode[i]==upDatedPD){
            if(quantityInStock[i]<=to){
                return 0;
            }else{
                quantityInStock[i] -= to;
                return 1;
            }
        }
    }
}
int addItemT0Cart(int productCodeInCart[],int QuantutyOfProductInCart[],int itemsNumber){
    int tempProductCodeInCart,c;
    bool codeExist=false;
    for(int i=0;i<itemsNumber;i++){
        againPC:
        printf("\nProduct %d, Item code: ",i+1);
        while((c=getchar()),c != '\n' && c != EOF);
        scanf("%d",&tempProductCodeInCart);
        for(int j=0;j<4;j++){
            if(productCode[j]==tempProductCodeInCart){
                codeExist=true;
                productCodeInCart[i]=tempProductCodeInCart;
            }
        }
        if(!codeExist){
            printf("\nInvalid Product Code\nTry Again\n");
            goto againPC;
        }
        againQuantutyOfProductInCart:
        printf("Product %d, Quantity of product: ",i+1);
        int c;
        while((c=getchar()),c != '\n' && c != EOF);
        scanf("%d",&QuantutyOfProductInCart[i]);
        if(!updateInventory(productCodeInCart[i],QuantutyOfProductInCart[i])){
            printf("An error occur while updating inventory.\nCheck weather the buying quantity exceed or is the same as the quantity in stock.\n\n");
            goto againQuantutyOfProductInCart;
        }
    }
    return 0;
}
void showBill(int pcic[],int qpic[],float disCount,int countItem){
    float total=0.0;
    printf("Product code\tQuantity of product\tQuantity Per Product\n");
    for(int j=0;j<countItem;j++){
        printf("%d\t\t%d\t\t\t%d\n",pcic[j],qpic[j],(pricePerProduct[j]*qpic[j]));
        total += (pricePerProduct[j]*qpic[j]);
    }
    if(disCount!=0.0){
        printf("Total\t\t\t\t\t%.2f\n",total);
        printf("Discount\t\t\t\t%.2f\n",(total*disCount));
        printf("Final Bill\t\t\t\t%.2f\n",total-(total*disCount));
    }else{
        printf("Total\t\t\t\t\t%.2f\n",total);
    }
}

int getSize(long long int cnic){
    int size=0;
    while(cnic>0){
        size++;
        cnic /=10;
    }
    return size;
}