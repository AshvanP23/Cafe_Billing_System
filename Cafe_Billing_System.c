#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX 8

struct Product {
    int id;
    char name[30];
    float price;
    int quantity;
};

struct Product inventory[MAX] = {
    {1,"Coffee",40,100},
    {2,"Tea",20,120},
    {3,"Burger",120,60},
    {4,"Pizza",250,40},
    {5,"Sandwich",90,80},
    {6,"Fries",110,75},
    {7,"ColdDrink",60,100},
    {8,"IceCream",80,90}
};

struct Product cart[MAX];

int cartCount = 0;

void showMenu();
void showInventory();
void addToCart();
void showCart();
void removeFromCart();
void searchProduct();
void checkout();

int main()
{
    int option;

    while(1)
    {
        showMenu();
        printf("Enter option: ");
        scanf("%d",&option);

        switch(option)
        {
            case 1:
                showInventory();
                break;

            case 2:
                addToCart();
                break;

            case 3:
                showCart();
                break;

            case 4:
                removeFromCart();
                break;

            case 5:
                searchProduct();
                break;

            case 6:
                checkout();
                return 0;

            case 7:
                printf("Thank you. Visit again!\n");
                return 0;

            default:
                printf("Invalid option\n");
        }
    }
}

void showMenu()
{
    printf("\n====== CAFE BILLING SYSTEM ======\n");
    printf("1. Show Menu\n");
    printf("2. Add Item to Cart\n");
    printf("3. Show Cart\n");
    printf("4. Remove Item from Cart\n");
    printf("5. Search Product\n");
    printf("6. Checkout\n");
    printf("7. Exit\n");
}

void showInventory()
{
    printf("\n----------- MENU -----------\n");
    printf("ID\tNAME\t\tPRICE\tSTOCK\n");

    for(int i=0;i<MAX;i++)
    {
        printf("%d\t%-12s\t%.2f\t%d\n",
        inventory[i].id,
        inventory[i].name,
        inventory[i].price,
        inventory[i].quantity);
    }
}

void addToCart()
{
    int id,qty;

    if(cartCount>=MAX)
    {
        printf("Cart full\n");
        return;
    }

    printf("Enter product ID: ");
    scanf("%d",&id);

    for(int i=0;i<MAX;i++)
    {
        if(inventory[i].id==id)
        {
            printf("Enter quantity: ");
            scanf("%d",&qty);

            if(qty>inventory[i].quantity)
            {
                printf("Not enough stock\n");
                return;
            }

            cart[cartCount]=inventory[i];
            cart[cartCount].quantity=qty;

            inventory[i].quantity-=qty;

            cartCount++;

            printf("Item added to cart\n");
            return;
        }
    }

    printf("Product not found\n");
}

void showCart()
{
    printf("\n------ CART ------\n");

    if(cartCount==0)
    {
        printf("Cart empty\n");
        return;
    }

    printf("ID\tNAME\t\tPRICE\tQTY\n");

    for(int i=0;i<cartCount;i++)
    {
        printf("%d\t%-12s\t%.2f\t%d\n",
        cart[i].id,
        cart[i].name,
        cart[i].price,
        cart[i].quantity);
    }
}

void removeFromCart()
{
    int id;

    printf("Enter product ID to remove: ");
    scanf("%d",&id);

    for(int i=0;i<cartCount;i++)
    {
        if(cart[i].id==id)
        {
            for(int j=i;j<cartCount-1;j++)
                cart[j]=cart[j+1];

            cartCount--;

            printf("Item removed\n");
            return;
        }
    }

    printf("Item not found in cart\n");
}

void searchProduct()
{
    char name[30];

    printf("Enter product name: ");
    scanf("%s",name);

    for(int i=0;i<MAX;i++)
    {
        if(strcmp(inventory[i].name,name)==0)
        {
            printf("Found: %d %s %.2f Stock:%d\n",
            inventory[i].id,
            inventory[i].name,
            inventory[i].price,
            inventory[i].quantity);
            return;
        }
    }

    printf("Product not found\n");
}

void checkout()
{
    float subtotal=0;

    if(cartCount==0)
    {
        printf("Cart empty\n");
        return;
    }

    printf("\n========== BILL ==========\n");

    srand(time(0));
    printf("Bill No: %d\n",rand()%1000);

    printf("ID\tNAME\t\tPRICE\tQTY\tTOTAL\n");

    for(int i=0;i<cartCount;i++)
    {
        float total=cart[i].price*cart[i].quantity;

        printf("%d\t%-12s\t%.2f\t%d\t%.2f\n",
        cart[i].id,
        cart[i].name,
        cart[i].price,
        cart[i].quantity,
        total);

        subtotal+=total;
    }

    float gst=subtotal*0.05;
    float final=subtotal+gst;

    printf("-----------------------------\n");
    printf("Subtotal: %.2f\n",subtotal);
    printf("GST (5%%): %.2f\n",gst);
    printf("Total Amount: %.2f\n",final);
    printf("-----------------------------\n");

    printf("Thank you for visiting our cafe!\n");
}
