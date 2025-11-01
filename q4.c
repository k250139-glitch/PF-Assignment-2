#include <stdio.h>
int push(int stack[],int *top,int maxSize);
int pop(int stack[],int *top);
int peek(int stack[],int *top);
void display(int stack[],int maxSize);
int main(){
    int maxSize=10,top=10,c;
    int stack[maxSize],choice;
    for(int i=0;i<maxSize;i++) stack[i]=-1;
    while(1){
        printf("\nSelect from the above to perform task: \n");
        printf("1. PUSH \n");
        printf("2. POP \n");
        printf("3. PEEK \n");
        printf("4. DISPLAY\n");
        printf("5. EXIT\n");
        printf("Choice: ");
        if(scanf("%d",&choice)!=1){
            printf("\nInvalid Input\n");
            while ((c=getchar()),c != '\n' && c != EOF);
            continue;
        }
        switch (choice)
        {
        case 1:
            push(stack,&top,maxSize);
            break;
        case 2:
            pop(stack,&top);
            break;
        case 3:
            peek(stack,&top);
            break;
        case 4:
            display(stack,maxSize);
            break;
        case 5:
            return 0;
            break;
        
        default:
            printf("\nInvalid Input\n");
            break;
        }
    }
    return 0;
}
int push(int stack[],int *top,int maxSize){
    int c,value;
    if(*top==0){
        printf("\nThe stack is OverFlow\n");
        return 0;
    }
    enterValueAgain:
    printf("Enter the value to be pushed: ");
    if(scanf("%d",&value)!=1){
        printf("\nInvalid Input\n");
        while ((c=getchar()), c != '\n' && c != EOF);
        goto enterValueAgain;
    }
    if(value<0){
        printf("\nThe value must be positive integer.\n");
        goto enterValueAgain;
    }
    for(int i=maxSize-1;i>=0;i--){
        if(stack[i]==-1){
            *top=i;
            stack[i]=value;
            break;
        }
    }
    printf("\nSuccessfully Pushed the value %d in stack\n",value);
    return 0;
}
int pop(int stack[],int *top){
    if(*top==10){
        printf("\nThe stack is underflow\n");
        return 0;
    }
    printf("\nSuccessfully Poped the value %d in stack\n",stack[*top]);
    stack[*top]=-1;
    *top +=1;
    return 0;
}
int peek(int stack[],int *top){
    if(*top==10){
        printf("\nThe stack is Empty\n");
        return 0;
    }
    printf("\nThe top value is %d\n",stack[*top]);
    return 0;
}
void display(int stack[],int maxSize){
    printf("\nThe Stack is: \n");
    for(int i=0;i<maxSize;i++){
        if(stack[i]==-1){
            printf("Empty\n");
        }else{
            printf("%d\n",stack[i]);
        }
    }
}