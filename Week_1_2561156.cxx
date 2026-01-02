#include <stdio.h>
#include<conio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for Product details
typedef struct {
    int id;
    char name[30];
    int quantity;
    float price;
    float total;
} Product;

// Function Prototypes
void addProducts();
void displayInventory();
void searchProduct();

void main ()
{
    int choice;

    while (1) {
        printf("\n--- Shop Management System ---");
        printf("\n1. Add 5 Products & Save to File");
        printf("\n2. Display All Products & Total Bill");
        printf("\n3. Search Product by ID");
        printf("\n4. Exit");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addProducts(); break;
            case 2: displayInventory(); break;
            case 3: searchProduct(); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    getch();
}

// 1. Add 5 Product details and save to file
void addProducts() {
    FILE *fp = fopen("shop.dat", "ab"); // Open in append-binary mode
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Product p;
    printf("\nEnter details for 5 products:\n");
    for (int i = 0; i < 5; i++) {
        printf("\nProduct %d:", i + 1);
        printf("\nID: "); scanf("%d", &p.id);
        printf("Name: "); scanf("%s", p.name);
        printf("Quantity: "); scanf("%d", &p.quantity);
        printf("Price per unit: "); scanf("%f", &p.price);
        
        // Calculate total for the item
        p.total = p.quantity * p.price;

        fwrite(&p, sizeof(Product), 1, fp);
    }

    fclose(fp);
    printf("\nProducts saved successfully!");
}

// 2. Read from file and display in tabular format
void displayInventory() {
    FILE *fp = fopen("shop.dat", "rb");
    if (fp == NULL) {
        printf("\nNo records found. Please add products first.\n");
        return;
    }

    Product p;
    float grandTotal = 0;

    printf("\n%-10s %-20s %-10s %-10s %-10s", "ID", "Name", "Qty", "Price", "Total");
    printf("\n------------------------------------------------------------\n");

    while (fread(&p, sizeof(Product), 1, fp)) {
        printf("%-10d %-20s %-10d %-10.2f %-10.2f\n", p.id, p.name, p.quantity, p.price, p.total);
        grandTotal += p.total;
    }

    printf("------------------------------------------------------------\n");
    printf("Grand Total Bill: %.2f\n", grandTotal);

    fclose(fp);
}

// 3. Search product by ID
void searchProduct() {
    FILE *fp = fopen("shop.dat", "rb");
    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    int searchId, found = 0;
    Product p;

    printf("\nEnter Product ID to search: ");
    scanf("%d", &searchId);

    while (fread(&p, sizeof(Product), 1, fp)) {
        if (p.id == searchId) {
            printf("\nProduct Found!");
            printf("\nID: %d\nName: %s\nQuantity: %d\nPrice: %.2f\nTotal: %.2f\n", 
                    p.id, p.name, p.quantity, p.price, p.total);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nProduct with ID %d not found.\n", searchId);
    }

    fclose(fp);
}
