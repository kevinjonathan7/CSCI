#include <stdio.h>      // basic input/output functions
#include <stdlib.h>     // for rand() & srand()
#include <time.h>       // for time() used in srand()
#include <math.h>       // for rounding if needed

#define PWD 123789      // admin password constant

// Product prices
float PA_PRICE = 3.5;   // price of product A
float PB_PRICE = 4.5;   // price of product B
float PC_PRICE = 5.5;   // price of product C

// Stock quantities inside vending machine
int pa_qty = 10, pb_qty = 10, pc_qty = 10; // initial stock
double total_amt = 0.0; // total sales amount using double for precision

// Minimum stock levels
#define MIN_A 2         // alert if product A falls below this
#define MIN_B 2         // alert if product B falls below this
#define MIN_C 2         // alert if product C falls below this

// Function prototype for stock check
void check_min_stock();  // check stock and alert if low

// Purchase product function
void purchase_product() {
    int s, c;             // s = selection, c = confirmation
    float coin;           // coin input
    double price, paid;   // price of selected product, money paid so far
    
    while (1) {           // loop until user exits
        printf("\nAvailable Products:\n");
        if (pa_qty > 0)
            printf("1: Product A - AED %.2f\n", PA_PRICE);  // show price if in stock
        else
            printf("1: Product A - SOLD OUT\n");           // sold out message if not in stock

        if (pb_qty > 0)
            printf("2: Product B - AED %.2f\n", PB_PRICE);
        else
            printf("2: Product B - SOLD OUT\n");

        if (pc_qty > 0)
            printf("3: Product C - AED %.2f\n\n", PC_PRICE);
        else
            printf("3: Product C - SOLD OUT\n");

        printf("Select product (0 to exit): ");  // prompt user to select product 
        scanf("%d", &s);                         // take and read selection input

        if (s == 0) break;                       // exit option
        if (s == 1 && pa_qty > 0) 
            price = PA_PRICE;                    // set price as the product's price to use in payment
        else if (s == 2 && pb_qty > 0) 
            price = PB_PRICE;
        else if (s == 3 && pc_qty > 0) 
            price = PC_PRICE;
        else {
            printf("Invalid selection or sold out!\n"); // handle invalid input or when product is sold out 
            continue;
        }

        printf("Confirm Product %d? (1=Yes, -1=No): ", s); // ask for confirmation of selection
        scanf("%d", &c); 
        if (c == -1) continue;                     // go to available products if not confirmed

        paid = 0.0;                                // reset payment amount
        while (paid < price) {                      // loop until fully paid
            printf("\nOutstanding Balance : AED %.2f\n", price - paid);
            printf("Insert coins (1, 0.5, 0.25 or 0 to cancel): "); // accept coins
            scanf("%f", &coin);

            if (coin == 0) {                        // cancel payment mid-way
                printf("Purchase cancelled. Collect your AED %.2f\n", paid);
                paid = 0.0;
                price = 0.0;
                break;
            }

            if (coin == 1 || coin == 0.5 || coin == 0.25)
                paid += coin;                        // add coin to paid amt
            else
                printf("Invalid coin!\n");          // reject invalid coins
        }

        if (price == 0.0) continue;                 // skip if purchase cancelled

        // update stock after successful purchase
        if (s == 1) pa_qty--;
        else if (s == 2) pb_qty--;
        else if (s == 3) pc_qty--;

        total_amt += price;                          // add to total sales
        printf("Product dispensed! Change: AED %.2f\n", paid - price); // display image and show change

        check_min_stock();                           // check stock alerts
    }
}

// Function to alert low stock
void check_min_stock() {
    if (pa_qty <= MIN_A)
        printf("ALERT: Product A stock low (%d left)\n", pa_qty); // displays alert message for product a
    if (pb_qty <= MIN_B)
        printf("ALERT: Product B stock low (%d left)\n", pb_qty); // displays alert message for product b
    if (pc_qty <= MIN_C)
        printf("ALERT: Product C stock low (%d left)\n", pc_qty); // displays alert message for product c
}

// Replenish products randomly 5–10 items
void random_replenish() {
    int choice, add_qty;

    printf("Select product to replenish (1=A, 2=B, 3=C): ");
    scanf("%d", &choice);

    add_qty = rand() % 6 + 5;                      // random 5-10

    if (choice == 1) {
        pa_qty += add_qty;
        printf("Product A replenished with %d items.\n", add_qty);
    }
    else if (choice == 2) {
        pb_qty += add_qty;
        printf("Product B replenished with %d items.\n", add_qty);
    }
    else if (choice == 3) {
        pc_qty += add_qty;
        printf("Product C replenished with %d items.\n", add_qty);
    }
    else {
        printf("Invalid selection!\n");            // handle wrong input
    }
}

// Admin mode for managing vending machine
void admin_mode() {
    int password, ch;
    int no;
    float new_price;

    printf("Enter admin password: ");
    scanf("%d", &password);

    if (password != PWD) {                          // check password
        printf("Incorrect password!\n");            // display wrong password message if input is wrong
        return;
    }

    while (1) {
        printf("\n--- ADMIN MENU ---\n");
        printf("1. Replenish Products (Random 5-10)\n");
        printf("2. Change Product Prices\n");
        printf("3. Display Total Sales\n");
        printf("4. Display Product Quantities\n");
        printf("0. Exit Admin Mode\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        if (ch == 0) break;                          // exit admin

        else if (ch == 1) {
            random_replenish();                       // call replenish function 
        }
        else if (ch == 2) {
            printf("Enter product number to update price (1=A, 2=B, 3=C): ");
            scanf("%d", &no);
            printf("Enter new price: ");
            scanf("%f", &new_price);
            if (no == 1) PA_PRICE = new_price;          // sets new price for product a
            else if (no == 2) PB_PRICE = new_price;     // sets new price for product b
            else if (no == 3) PC_PRICE = new_price;     // sets new price for product c
            printf("Price updated!\n");
        }
        else if (ch == 3) {
            printf("Total sales amount: AED %.2f\n", total_amt);

            int reset;
            printf("Reset total sales to zero? (1=Yes, 0=No): ");
            scanf("%d", &reset);
            if (reset == 1) {
                total_amt = 0.0;
                printf("Total sales reset. Remember to collect the money.\n");
            }
        }
        else if (ch == 4) {
            printf("Product A: %d\n", pa_qty);
            printf("Product B: %d\n", pb_qty);
            printf("Product C: %d\n", pc_qty);
        }
        else {
            printf("Invalid choice!\n");             // handle invalid admin input
        }
    }
}

// Main function
int main() {
    int choice;
    srand(time(NULL));                                // regenerates a new set of random outputs for random replenish

    while (1) {
        printf("\n  VENDING MACHINE  \n");
        printf("1. Purchase Product\n");
        printf("2. Admin Mode\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 0) break;                      // exit program
        else if (choice == 1) purchase_product();   // call purchase
        else if (choice == 2) admin_mode();         // call admin
        else printf("Invalid option!\n");           // invalid menu option
    }

    printf("Exited successfully.\n");                // final message
    return 0;                                        // end program
}
