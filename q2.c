int main() {
    printf("Product code\n");

    int code = 0;
    int flag = 1;
    int quantity = 0;
    int bill = 0;
    int total = 0;
    int voucher = 0;

    char name[50];
    char cnic[20];

    input(name, cnic);

  int arr[4][3] = {
    {1, 50, 100},
    {2, 10, 200},
    {3, 20, 300},
    {4, 8, 150}
};
printf("\n-----------------------------------------------\n");
printf("Product code\tQuantity in stock\tPrice per product\n");
printf("-----------------------------------------------\n");

for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
        if (j == 0)
            printf("   %d\t\t\t", arr[i][j]);  
        else
            printf("%d\t\t\t", arr[i][j]);
    }
    printf("\n");  
}

printf("-----------------------------------------------\n");

    while (1) {
        printf("Input num of product you want (type 0 to end order): ");
        scanf("%d", &code);

        if (code == 0) {
            flag = 0;
            break;
        }

        printf("Input quantity: ");
        scanf("%d", &quantity);

        if (code == 1) {
            arr[0][1] -= quantity;               
            bill = quantity * arr[0][2];
            total += bill;
        } else if (code == 2) {
            arr[1][1] -= quantity;
            bill = quantity * arr[1][2];
            total += bill;
        } else if (code == 3) {
            arr[2][1] -= quantity;
            bill = quantity * arr[2][2];
            total += bill;
        } else if (code == 4) {
            arr[3][1] -= quantity;
            bill = quantity * arr[3][2];
            total += bill;
        } else {
            printf("Invalid product code!\n");
        }
    }

    if (flag == 0) {
        printf("Have you got any vouchers?\n");
        printf("We are offering EID discount!\n");
        printf("Enter your voucher code: ");
        scanf("%d", &voucher);

        if (voucher == 2334) {
            printf("\nYou have availed your discount of 25%%");
            printf("\n----------------------------------------\n");
            printf("\nTOTAL BILL\n");
            printf("Original bill: %d\n", total);
            printf("After discount: %.2f\n", total * 0.75);
        } else {
            printf("\n----------------------------------------\n");
            printf("\nTOTAL BILL\n");
            printf("Original bill: %d\n", total);
        }

        printf("\n----------------------------------------\n");
        printf("Customer Name: %s\n", name);
        printf("CNIC: %s\n", cnic);
        printf("Final Payable Amount: %d\n", total);
    }

    return 0;
}
