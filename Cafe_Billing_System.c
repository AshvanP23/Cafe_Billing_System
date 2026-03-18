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
    {1, "Coffee", 40.0, 100},
    {2, "Tea", 20.0, 120},
    {3, "Burger", 120.0, 60},
    {4, "Pizza", 250.0, 40},
    {5, "Sandwich", 90.0, 80},
    {6, "Fries", 110.0, 70},
    {7, "ColdDrink", 60.0, 100},
    {8, "IceCream", 80.0, 90}
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

int main() {
    int option;

    while(1) {
        showMenu();
        printf("\nEnter option: ");
        scanf("%d", &option);

        switch(option) {
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
                break;
            case 7:
                printf("\nThank you. Visit again!\n");
                return 0;
            default:
                printf("\nInvalid option. Please try again.\n");
        }
    }
}

void showMenu() {
    printf("\n====== CAFE BILLING SYSTEM ======\n");
    printf("1. Show Menu & Stock\n");
    printf("2. Add Item to Cart\n");
    printf("3. Show Cart\n");
    printf("4. Remove Item from Cart\n");
    printf("5. Search Product\n");
    printf("6. Checkout & Print Bill\n");
    printf("7. Exit\n");
    printf("=================================\n");
}

void showInventory() {
    printf("\n------------------ CAFE MENU ------------------\n");
    printf("ID\tNAME\t\tPRICE\t\tSTOCK\n");
    printf("-----------------------------------------------\n");

    for(int i = 0; i < MAX; i++) {
        printf("%d\t%-12s\tRs. %.2f\t%d\n",
        inventory[i].id,
        inventory[i].name,
        inventory[i].price,
        inventory[i].quantity);
    }
    printf("-----------------------------------------------\n");
}

void addToCart() {
    int id, qty;

    if(cartCount >= MAX) {
        printf("\nCart is full!\n");
        return;
    }

    printf("Enter product ID: ");
    scanf("%d", &id);

    for(int i = 0; i < MAX; i++) {
        if(inventory[i].id == id) {
            printf("Enter quantity: ");
            scanf("%d", &qty);

            if(qty > inventory[i].quantity) {
                printf("\nNot enough stock available! Only %d left.\n", inventory[i].quantity);
                return;
            }

            cart[cartCount] = inventory[i];
            cart[cartCount].quantity = qty;
            inventory[i].quantity -= qty;
            cartCount++;

            printf("\nItem added to cart successfully!\n");
            return;
        }
    }
    printf("\nProduct ID not found!\n");
}

void showCart() {
    if(cartCount == 0) {
        printf("\nCart is empty!\n");
        return;
    }

    printf("\n------------------ YOUR CART ------------------\n");
    printf("ID\tNAME\t\tPRICE\t\tQTY\n");
    printf("-----------------------------------------------\n");

    for(int i = 0; i < cartCount; i++) {
        printf("%d\t%-12s\tRs. %.2f\t%d\n",
        cart[i].id,
        cart[i].name,
        cart[i].price,
        cart[i].quantity);
    }
    printf("-----------------------------------------------\n");
}

void removeFromCart() {
    int id;

    if(cartCount == 0) {
        printf("\nCart is already empty!\n");
        return;
    }

    printf("Enter product ID to remove: ");
    scanf("%d", &id);

    for(int i = 0; i < cartCount; i++) {
        if(cart[i].id == id) {
            
            for(int k = 0; k < MAX; k++) {
                if(inventory[k].id == id) {
                    inventory[k].quantity += cart[i].quantity;
                    break;
                }
            }

            for(int j = i; j < cartCount - 1; j++) {
                cart[j] = cart[j + 1];
            }

            cartCount--;
            printf("\nItem removed from cart and stock restored!\n");
            return;
        }
    }
    printf("\nItem not found in cart!\n");
}

void searchProduct() {
    char name[30];

    printf("Enter product name to search: ");
    scanf("%s", name);

    for(int i = 0; i < MAX; i++) {
        if(strcasecmp(inventory[i].name, name) == 0) {
            printf("\n--- Product Found ---\n");
            printf("ID: %d\nName: %s\nPrice: Rs. %.2f\nStock Available: %d\n",
            inventory[i].id,
            inventory[i].name,
            inventory[i].price,
            inventory[i].quantity);
            return;
        }
    }
    printf("\nProduct not found!\n");
}

void checkout() {
    float subtotal = 0;

    if(cartCount == 0) {
        printf("\nCannot checkout. Cart is empty!\n");
        return;
    }

    srand(time(0));
    int billNo = rand() % 10000 + 1000;

    printf("\n==================== CAFE RECEIPT ====================\n");
    printf("Bill No: %d\n", billNo);
    printf("------------------------------------------------------\n");
    printf("ID\tNAME\t\tPRICE\t\tQTY\tTOTAL\n");
    printf("------------------------------------------------------\n");

    for(int i = 0; i < cartCount; i++) {
        float total = cart[i].price * cart[i].quantity;

        printf("%d\t%-12s\tRs. %.2f\t%d\tRs. %.2f\n",
        cart[i].id,
        cart[i].name,
        cart[i].price,
        cart[i].quantity,
        total);

        subtotal += total;
    }

    float gst = subtotal * 0.05;
    float finalAmount = subtotal + gst;

    printf("------------------------------------------------------\n");
    printf("Subtotal:\t\t\t\tRs. %.2f\n", subtotal);
    printf("GST (5%%):\t\t\t\tRs. %.2f\n", gst);
    printf("------------------------------------------------------\n");
    printf("FINAL AMOUNT TO PAY:\t\t\tRs. %.2f\n", finalAmount);
    printf("======================================================\n");
    printf("          Thank you for visiting our cafe!            \n");
    printf("======================================================\n\n");

    cartCount = 0;
}
