#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_STOCKS 100
#define SYMBOL_LENGTH 10
#define HASH_TABLE_SIZE 101

typedef struct Stock {
    char symbol[SYMBOL_LENGTH];
    float price;
    int quantity;
} Stock;

Stock stocks[MAX_STOCKS];
int stock_count = 0;

int hash_table[HASH_TABLE_SIZE];

int hash(const char *symbol) {
    unsigned long hash = 5381;
    int c;
    while ((c = *symbol++))
        hash = ((hash << 5) + hash) + c;
    return hash % HASH_TABLE_SIZE;
}

void load_stocks() {
    FILE *file = fopen("stocks.dat", "rb");
    if (file) {
        fread(&stock_count, sizeof(int), 1, file);
        fread(stocks, sizeof(Stock), stock_count, file);
        fclose(file);
        for (int i = 0; i < stock_count; i++) {
            int index = hash(stocks[i].symbol);
            hash_table[index] = i + 1;
        }
    } else {
        for (int i = 0; i < HASH_TABLE_SIZE; i++) {
            hash_table[i] = -1;
        }
    }
}

void save_stocks() {
    FILE *file = fopen("stocks.dat", "wb");
    if (file) {
        fwrite(&stock_count, sizeof(int), 1, file);
        fwrite(stocks, sizeof(Stock), stock_count, file);
        fclose(file);
    }
}

Stock *find_stock(const char *symbol) {
    int index = hash(symbol);
    int stock_index = hash_table[index] - 1;
    if (stock_index >= 0 && stock_index < stock_count && strcmp(stocks[stock_index].symbol, symbol) == 0) {
        return &stocks[stock_index];
    }
    return NULL;
}

void log_transaction(const char *action, const char *symbol, int quantity, float price) {
    FILE *log_file = fopen("transactions.log", "a");
    if (log_file) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        fprintf(log_file, "[%04d-%02d-%02d %02d:%02d:%02d] %s %d shares of %s at $%.2f\n",
                t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
                t->tm_hour, t->tm_min, t->tm_sec,
                action, quantity, symbol, price);
        fclose(log_file);
    }
}

void add_stock(const char *symbol, float price, int quantity) {
    if (stock_count < MAX_STOCKS) {
        strcpy(stocks[stock_count].symbol, symbol);
        stocks[stock_count].price = price;
        stocks[stock_count].quantity = quantity;
        int index = hash(symbol);
        hash_table[index] = stock_count + 1;
        stock_count++;
        save_stocks();
        printf("Added stock: %s\n", symbol);
    } else {
        printf("Maximum stock limit reached.\n");
    }
}

void delete_stock(const char *symbol) {
    Stock *stock = find_stock(symbol);
    if (stock) {
        int index = stock - stocks;
        for (int i = index; i < stock_count - 1; i++) {
            stocks[i] = stocks[i + 1];
        }
        stock_count--;
        save_stocks();
        int hash_index = hash(symbol);
        hash_table[hash_index] = -1;
        printf("Deleted stock: %s\n", symbol);
    } else {
        printf("Stock %s not found.\n", symbol);
    }
}

void display_stocks() {
    if (stock_count == 0) {
        printf("No stocks available.\n");
        return;
    }
    printf("Current Stocks:\n");
    for (int i = 0; i < stock_count; i++) {
        printf("Symbol: %s, Price: %.2f, Quantity: %d\n", stocks[i].symbol, stocks[i].price, stocks[i].quantity);
    }
}

void buy_stock(const char *symbol, int quantity) {
    Stock *stock = find_stock(symbol);
    if (stock) {
        stock->quantity -= quantity; // Update the stock quantity
        save_stocks(); // Save the updated stocks
        log_transaction("Bought", symbol, quantity, stock->price); // Log the transaction
        printf("Bought %d shares of %s. New quantity available: %d\n", quantity, symbol, stock->quantity);
    } else {
        printf("Stock %s not found.\n", symbol); // Error if stock not found
    }
}

void sell_stock(const char *symbol, int quantity) {
    Stock *stock = find_stock(symbol);
    if (stock) {
        if (stock->quantity >= quantity) {
            stock->quantity -= quantity; // Decrease the stock quantity
            save_stocks(); // Save the updated stocks
            log_transaction("Sold", symbol, quantity, stock->price); // Log the transaction
            printf("Sold %d shares of %s. New quantity: %d\n", quantity, symbol, stock->quantity);
        } else {
            printf("Not enough shares to sell. Available: %d\n", stock->quantity);
        }
    } else {
        printf("Stock %s not found.\n", symbol); // Error if stock not found
    }
}

void search_stock(const char *symbol) {
    Stock *stock = find_stock(symbol);
    if (stock) {
        printf("Stock found: Symbol: %s, Price: %.2f, Quantity: %d\n", stock->symbol, stock->price, stock->quantity);
    } else {
        printf("Stock %s not found.\n", symbol);
    }
}

int main() {
    load_stocks();
    int choice, role;
    char symbol[SYMBOL_LENGTH];
    float price;
    int quantity;

    while (1) {
        printf("Enter your role (1 for Admin, 2 for Customer, 3 to Exit): ");
        scanf("%d", &role);

        if (role == 3) {
            save_stocks();
            printf("Exiting the program.\n");
            return 0;
        }

        while (1) {
            printf("\nStock Market Simulator\n");

            if (role == 1) { // Admin Menu
                printf("1. Add Stock\n");
                printf("2. Delete Stock\n");
                printf("3. Display Stocks\n");
                printf("4. Switch Role\n");
                printf("5. Exit\n");
            } else if (role == 2) { // Customer Menu
                printf("1. Display Stocks\n");
                printf("2. Search Stock\n");
                printf("3. Buy Stock\n");
                printf("4. Sell Stock\n");
                printf("5. Switch Role\n");
                printf("6. Exit\n");
            }

            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    if (role == 1) { // Admin add stock
                        printf("Enter stock symbol: ");
                        scanf("%s", symbol);
                        printf("Enter stock price: ");
                        scanf("%f", &price);
                        printf("Enter stock quantity: ");
                        scanf("%d", &quantity);
                        add_stock(symbol, price, quantity);
                    } else if (role == 2) { // Customer Display
                        display_stocks();
                    }
                    break;
                case 2:
                    if (role == 1) { // Admin delete stock
                        printf("Enter stock symbol to delete: ");
                        scanf("%s", symbol);
                        delete_stock(symbol);
                    } else if (role == 2) { // Customer search stock
                        printf("Enter stock symbol to search: ");
                        scanf("%s", symbol);
                        search_stock(symbol);
                    }
                    break;
                case 3:
                    if (role == 1) { // Admin display stock
                        display_stocks();
                    } else if (role == 2) { // Customer buy stock
                        printf("Enter stock symbol to buy: ");
                        scanf("%s", symbol);
                        printf("Enter quantity to buy: ");
                        scanf("%d", &quantity);
                        buy_stock(symbol, quantity);
                    }
                    break;
                case 4:
                    if (role == 1) { // Admin switch role
                        break; // Break to outer loop to switch role
                    } else if (role == 2) { // Customer sell stock
                        printf("Enter stock symbol to sell: ");
                        scanf("%s", symbol);
                        printf("Enter quantity to sell: ");
                        scanf("%d", &quantity);
                        sell_stock(symbol, quantity);
                    }
                    break;
                case 5:
                    if (role == 1) { // Admin switch role
                        break; // Break to outer loop to switch role
                    } else if (role == 2) { // Customer switch role
                        break; // Break to outer loop to switch role
                    }
                    break;
                case 6:
                    if (role == 2) { // Customer exit
                        save_stocks();
                        printf("Exiting the program.\n");
                        return 0;
                    }
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
                    break;
            }

            // If we reach here, it means we need to switch roles
            if (choice == 4 || choice == 5) {
                break; // Break to outer loop to switch role
            }
        }
    }
    return 0;
}