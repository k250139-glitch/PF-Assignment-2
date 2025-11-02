#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define INVENTORY_SIZE 4
#define MAX_CART_ITEMS 50
struct User {
    char name[50];
    long long int cnic;
};
struct User user = {"N/A", 0};

int productCode[INVENTORY_SIZE] = {1, 2, 3, 4}; 
int quantityInStock[INVENTORY_SIZE] = {50, 10, 20, 8};
int pricePerProduct[INVENTORY_SIZE] = {100, 200, 300, 150};
int productCodeInCart[MAX_CART_ITEMS];
int quantityOfProductInCart[MAX_CART_ITEMS];
int current_cart_count = 0; 
int login_customer();
void customerInfo();
int get_cnic_size(long long int cnic);
void displayInventory();
int get_product_index(int code);
int updateInventory(int product_code, int quantity_to_remove);
void addItemToCart();
void showBill(float disCount);
int main() {
    int chose;
    char promocode_choice, promocodeCode[10];
    bool promocodeOK = false;
    int itemsNumber_UNUSED; 
    login_customer();
    while(true){
        printf("\n=================================================\n");
        printf("What Would you like to perform?\n");
        printf("1. View Customer Information\n");
        printf("2. Display Inventory\n");
        printf("3. Add item to cart\n");
        printf("4. Display Total Bill\n");
        printf("5. Show Invoice\n");
        printf("6. Exit\n");
        printf("Chose: ");
        int c;
        while ((c=getchar()) != '\n' && c != EOF); 
        
        if (scanf("%d", &chose) != 1) {
            printf("\n\t--- Invalid input. Please enter a number. ---\n");
            continue; 
        }

        switch(chose) {
            case 1:
                customerInfo();
                break;
            case 2:
                displayInventory();
                break;
            case 3:
                do {
                    printf("How many items do you want to add to your cart: ");
                    if (scanf("%d", &itemsNumber_UNUSED) != 1 || itemsNumber_UNUSED < 0) {
                        printf("\nInvalid input. Please enter a positive number.\n");
                        while ((c=getchar()) != '\n' && c != EOF); // Clear buffer
                    } else {
                        break;
                    }
                } while (true);
                for (int i = 0; i < itemsNumber_UNUSED; i++) {
                    addItemToCart(); 
                }
                break;
            case 4:
                if (current_cart_count == 0) {
                    printf("\t--- Cart is empty. Add items first (Option 3). ---\n");
                    break;
                }
                
                promocodeOK = false;
                do {
                    printf("\nDo you have any promocode? (Y/N): ");
                    while ((c=getchar()) != '\n' && c != EOF);
                    scanf(" %c", &promocode_choice);
                    
                    if (toupper(promocode_choice) == 'Y') {
                        printf("Enter Code: ");
                        scanf("%s", promocodeCode);
                        if(strcmp(promocodeCode, "Eid2025") == 0) {
                            promocodeOK = true;
                            printf("\t Promocode **Eid2025** applied (25%% discount).\n");
                        } else {
                            printf("\t--- Invalid promocode. Try again or enter 'N'. ---\n");
                        }
                    } else if (toupper(promocode_choice) == 'N') {
                        break; 
                    } else {
                        printf("\t--- Invalid choice. Please enter Y or N. ---\n");
                    }
                } while (!promocodeOK);
                
                printf("\n--- Final Bill ---\n");
                if(promocodeOK) {
                    showBill(0.25);
                } else {
                    showBill(0.0);
                }
                break;
            case 5:
                if (current_cart_count == 0) {
                    printf("\t--- Cart is empty. Add items first (Option 3). ---\n");
                    break;
                }
                promocodeOK = false; 
                do {
                    printf("\nDo you have any promocode for the invoice? (Y/N): ");
                    while ((c=getchar()) != '\n' && c != EOF);
                    scanf(" %c", &promocode_choice);
                    
                    if (toupper(promocode_choice) == 'Y') {
                        printf("Enter Code: ");
                        scanf("%s", promocodeCode);
                        if(strcmp(promocodeCode, "Eid2025") == 0) {
                            promocodeOK = true;
                            printf("\tPromocode  Eid2025  applied (25%% discount).\n");
                        } else {
                            printf("\t Invalid promocode. Try again or enter 'N'.\n");
                        }
                    } else if (toupper(promocode_choice) == 'N') {
                        break; 
                    } else {
                        printf("\t*** Invalid choice. Please enter Y or N. ***\n");
                    }
                } while (!promocodeOK);

                printf("\n=================================== FINAL INVOICE ===============================\n");
                printf("Customer Name: %s\t\t Customer CNIC %lld\n", user.name, user.cnic);
                printf("---------------------------------------------------------------------------\n");
                
                if(promocodeOK) {
                    showBill(0.25);
                } else {
                    showBill(0.0);
                }
                printf("============================================================================\n");
                current_cart_count = 0; 
                break;
            case 6:
                printf("\n Bye\n");
                return 0;
            default:
                printf("\tInvalid Choice. Try Again. \n");
                break;
        }
    }
}
void customerInfo(){
    printf("\n--- Customer Information ---\n");
    printf("User Name: %s\n",user.name);
    printf("User CNIC: %lld\n",user.cnic);
}
int login_customer(){
    printf("Name of customer: ");
    int c;
    while ((c=getchar()) != '\n' && c != EOF); 
    if (scanf("%49[^\n]", user.name) != 1) { 
        fprintf(stderr, "Error reading name.\n");
        strcpy(user.name, "N/A");
    }

    do { 
        printf("CNIC number of the customer (13 digits, no dashes): ");
        while ((c=getchar()) != '\n' && c != EOF); 
        
        if (scanf("%lld", &user.cnic) != 1) {
            printf("\nInvalid CNIC number. Enter only digits.\n");
            user.cnic = 0;
            continue;
        }
        
        if (get_cnic_size(user.cnic) != 13) {
            printf("\nInvalid CNIC number. Must be exactly 13 digits.\n");
            user.cnic = 0;
        }
    } while (user.cnic == 0);
    
    return 0;
}
int get_cnic_size(long long int cnic){
    int size=0;
    if (cnic == 0) return 1;
    while(cnic>0){
        size++;
        cnic /=10;
    }
    return size;
}
void displayInventory(){
    printf("\n---------------------- CURRENT INVENTORY -------------------------\n");
    printf("| %-12s | %-17s | %-17s |\n", "Product Code", "Quantity in Stock", "Price per Product");
    printf("-------------------------------------------------------------\n");
    for(int j=0; j<INVENTORY_SIZE; j++){
        printf("| %-12d | %-17d | %-17d |\n", productCode[j], quantityInStock[j], pricePerProduct[j]);
    }
    printf("-----------------------------------------------------------------\n");
}
int get_product_index(int code) {
    for (int i = 0; i < INVENTORY_SIZE; i++) {
        if (productCode[i] == code) {
            return i;
        }
    }
    return -1;
}
int updateInventory(int product_code, int quantity_to_remove){
    if(quantity_to_remove <= 0) return 0;
    
    int index = get_product_index(product_code);
    
    if(index != -1){
        if(quantityInStock[index] < quantity_to_remove){ 
            return 0;
        } else {
            quantityInStock[index] -= quantity_to_remove;
            return 1; 
        }
    }
    return 0; 
}
void addItemToCart(){
    int tempProductCode, tempQuantity;
    int c;

    if (current_cart_count >= MAX_CART_ITEMS) {
        printf("\t*** Cart is full! Cannot add more items. ***\n");
        return;
    }
    do {
        printf("\nProduct %d, Item code: ", current_cart_count + 1);
        while ((c=getchar()) != '\n' && c != EOF);
        if (scanf("%d", &tempProductCode) != 1) {
            printf("\t*** Invalid input. Try again. ***\n");
            continue;
        }

        int index = get_product_index(tempProductCode);
        if (index == -1) {
            printf("\t*** Invalid Product Code. Try Again. ***\n");
        } else {
            break;
        }
    } while (true);
    do {
        printf("Product %d, Quantity of product: ", current_cart_count + 1);
        while ((c=getchar()) != '\n' && c != EOF);
        if (scanf("%d", &tempQuantity) != 1 || tempQuantity <= 0) {
            printf("\t*** Invalid quantity. Enter a positive number. ***\n");
            continue;
        }
        if(!updateInventory(tempProductCode, tempQuantity)){
             printf("\t*** An error occurred while checking/updating inventory. ***\n");
             printf("\t*** Check whether the buying quantity exceeds the quantity in stock. ***\n");
        } else {
            productCodeInCart[current_cart_count] = tempProductCode;
            quantityOfProductInCart[current_cart_count] = tempQuantity;
            current_cart_count++;
            printf("\t-> Item successfully added to cart.\n");
            break; 
        }
    } while (true);
}
void showBill(float disCount){
    float total = 0.0;
    
    printf("\n| %-12s | %-8s | %-10s | %-10s |\n", "Product Code", "Quantity", "Unit Price", "Subtotal");
    printf("-----------------------------------------------------------\n");
    
    for(int j=0; j < current_cart_count; j++){
        int code = productCodeInCart[j];
        int quantity = quantityOfProductInCart[j];
        int index = get_product_index(code);
        
        if (index != -1) {
            float unit_price = (float)pricePerProduct[index];
            float subtotal = unit_price * quantity;
            total += subtotal;
            printf("| %-12d | %-8d | %-10.2f | %-10.2f |\n", code, quantity, unit_price, subtotal);
        }
    }
    printf("---------------------------------------------------------------\n");
    
    float discount_amount = total * disCount;
    float final_bill = total - discount_amount;

    printf("Total\t\t\t\t\t\t%.2f\n", total);
    
    if(disCount != 0.0){
        printf("Discount (%.0f%%)\t\t\t\t\t%.2f\n", disCount * 100, discount_amount);
        printf("Final Bill\t\t\t\t\t\t%.2f\n", final_bill);
    }
}
