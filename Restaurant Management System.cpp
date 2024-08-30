#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define MAX_EMPLOYEES 10
#define MAX_MENUS 50
#define MAX_ORDERS 50
#define MAX_NAME 50

// Struktur untuk menyimpan data karyawan
typedef struct {
    char id[10];
    char name[MAX_NAME];
    char status[20];
    int workingPeriod;
    float initialSalary;
    float projectedSalary;
} Employee;

// Struktur untuk menyimpan data menu
typedef struct {
    char id[10];
    char name[MAX_NAME];
    char type[10];
    float price;
    int stock;
} Menu;

// Struktur untuk menyimpan data pesanan
typedef struct {
    char id[10];
    int tableNo;
    char employeeName[MAX_NAME];
    Menu orderedMenus[MAX_MENUS];
    int quantity[MAX_MENUS];
    int itemCount;
    float subtotal;
    float total;
    float service;
    float tax;
    float discount;
    float totalPayment;
} Order;

// Deklarasi variabel global
Employee employees[MAX_EMPLOYEES];
Menu menus[MAX_MENUS];
Order orders[MAX_ORDERS];
int employeeCount = 0;
int menuCount = 0;
int orderCount = 0;

// Deklarasi fungsi
void viewEmployees();
void registerEmployee();
void changeEmployeeStatus();
void viewMenus();
void registerMenu();
void updateMenu();
void viewOrderHistory();
void createNewOrder();
void generateDailyReport();
void clearInputBuffer();
float calculateProjectedSalary(float initialSalary, int workingPeriod);

int main() {
    int option;
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Employee Management\n");
        printf("2. Menu Management\n");
        printf("3. Order Management\n");
        printf("4. Daily Report\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);
        clearInputBuffer();

        switch (option) {
            case 1:
                printf("\n1. View Employees\n2. Register Employee\n3. Change Employee Status\n");
                printf("Choose an option: ");
                scanf("%d", &option);
                clearInputBuffer();
                if (option == 1) {
                    viewEmployees();
                } else if (option == 2) {
                    registerEmployee();
                } else if (option == 3) {
                    changeEmployeeStatus();
                } else {
                    printf("Invalid option.\n");
                }
                break;

            case 2:
                printf("\n1. View Menus\n2. Register Menu\n3. Update Menu\n");
                printf("Choose an option: ");
                scanf("%d", &option);
                clearInputBuffer();
                if (option == 1) {
                    viewMenus();
                } else if (option == 2) {
                    registerMenu();
                } else if (option == 3) {
                    updateMenu();
                } else {
                    printf("Invalid option.\n");
                }
                break;

            case 3:
                printf("\n1. View Order History\n2. Create New Order\n");
                printf("Choose an option: ");
                scanf("%d", &option);
                clearInputBuffer();
                if (option == 1) {
                    viewOrderHistory();
                } else if (option == 2) {
                    createNewOrder();
                } else {
                    printf("Invalid option.\n");
                }
                break;

            case 4:
                generateDailyReport();
                break;

            case 5:
                exit(0);

            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}

// Fungsi untuk menampilkan daftar karyawan
void viewEmployees() {
    printf("\nEmployee List:\n");
    printf("ID   | Name         | Status       | WP | Initial Salary | Projected Salary\n");
    for (int i = 0; i < employeeCount; i++) {
        printf("%-4s | %-12s | %-12s | %-2d | %-14.2f | %-17.2f\n",
               employees[i].id, employees[i].name, employees[i].status, employees[i].workingPeriod,
               employees[i].initialSalary, employees[i].projectedSalary);
    }
}

// Fungsi untuk mendaftarkan karyawan baru
void registerEmployee() {
    if (employeeCount >= MAX_EMPLOYEES) {
        printf("Employee list is full. Cannot register more employees.\n");
        return;
    }

    Employee newEmployee;
    printf("Enter name: ");
    fgets(newEmployee.name, MAX_NAME, stdin);
    newEmployee.name[strcspn(newEmployee.name, "\n")] = 0;  // remove newline

    // Validate name
    for (int i = 0; newEmployee.name[i]; i++) {
        if (!isalpha(newEmployee.name[i]) && newEmployee.name[i] != ' ') {
            printf("Invalid name. Only alphabetic characters are allowed.\n");
            return;
        }
    }

    printf("Enter status (active, annual leave, inactive): ");
    fgets(newEmployee.status, 20, stdin);
    newEmployee.status[strcspn(newEmployee.status, "\n")] = 0;  // remove newline
    if (strcmp(newEmployee.status, "active") != 0 && strcmp(newEmployee.status, "annual leave") != 0 &&
        strcmp(newEmployee.status, "inactive") != 0) {
        printf("Invalid status. Must be 'active', 'annual leave', or 'inactive'.\n");
        return;
    }

    printf("Enter working period (in months): ");
    scanf("%d", &newEmployee.workingPeriod);
    if (newEmployee.workingPeriod < 0) {
        printf("Invalid working period. Must be a positive number.\n");
        return;
    }

    printf("Enter initial salary: ");
    scanf("%f", &newEmployee.initialSalary);
    if (newEmployee.initialSalary < 0) {
        printf("Invalid salary. Must be a positive number.\n");
        return;
    }

    // Generate ID
    char firstInitial = toupper(newEmployee.name[0]);
    char secondInitial = firstInitial;
    char *space = strchr(newEmployee.name, ' ');
    if (space != NULL && *(space + 1) != '\0') {
        secondInitial = toupper(*(space + 1));
    }

    int nameLength = strlen(newEmployee.name);
    snprintf(newEmployee.id, 10, "%c%c%02d", firstInitial, secondInitial, nameLength);
    
    // Ensure ID is unique
    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].id, newEmployee.id) == 0) {
            nameLength++;
            snprintf(newEmployee.id, 10, "%c%c%02d", firstInitial, secondInitial, nameLength);
            i = -1;  // Restart loop
        }
    }

    // Calculate projected salary
    newEmployee.projectedSalary = calculateProjectedSalary(newEmployee.initialSalary, newEmployee.workingPeriod);

    // Add to employee list
    employees[employeeCount++] = newEmployee;
    printf("Employee registered successfully.\n");
}

// Fungsi untuk menghitung gaji proyek
float calculateProjectedSalary(float initialSalary, int workingPeriod) {
    float salary = initialSalary;
    for (int i = 0; i < workingPeriod; i++) {
        salary += round(salary * 0.015);
    }
    return salary;
}

// Fungsi untuk mengubah status karyawan
void changeEmployeeStatus() {
    char id[10];
    printf("Enter Employee ID: ");
    scanf("%s", id);
    clearInputBuffer();

    int found = -1;
    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].id, id) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Employee not found.\n");
        return;
    }

    printf("Employee found: %s\n", employees[found].name);
    printf("Enter new status (active, annual leave, inactive): ");
    fgets(employees[found].status, 20, stdin);
    employees[found].status[strcspn(employees[found].status, "\n")] = 0;  // remove newline

    if (strcmp(employees[found].status, "active") != 0 && strcmp(employees[found].status, "annual leave") != 0 &&
        strcmp(employees[found].status, "inactive") != 0) {
        printf("Invalid status. Must be 'active', 'annual leave', or 'inactive'.\n");
        return;
    }

    printf("Employee status updated successfully.\n");
}

// Fungsi untuk menampilkan daftar menu
void viewMenus() {
    printf("\nMenu List:\n");
    printf("ID    | Name                  | Type       | Price\n");
    for (int i = 0; i < menuCount; i++) {
        printf("%-5s | %-20s | %-10s | %-6.2f\n",
               menus[i].id, menus[i].name, menus[i].type, menus[i].price);
    }
}

// Fungsi untuk mendaftarkan menu baru
void registerMenu() {
    if (menuCount >= MAX_MENUS) {
        printf("Menu list is full. Cannot register more menus.\n");
        return;
    }

    Menu newMenu;
    printf("Enter name: ");
    fgets(newMenu.name, MAX_NAME, stdin);
    newMenu.name[strcspn(newMenu.name, "\n")] = 0;  // remove newline

    // Validate name
    for (int i = 0; newMenu.name[i]; i++) {
        if (!isalnum(newMenu.name[i]) && newMenu.name[i] != ' ') {
            printf("Invalid name. Only alphanumeric characters are allowed.\n");
            return;
        }
    }

    printf("Enter type (food, beverage): ");
    fgets(newMenu.type, 10, stdin);
    newMenu.type[strcspn(newMenu.type, "\n")] = 0;  // remove newline
    if (strcmp(newMenu.type, "food") != 0 && strcmp(newMenu.type, "beverage") != 0) {
        printf("Invalid type. Must be 'food' or 'beverage'.\n");
        return;
    }

    printf("Enter price: ");
    scanf("%f", &newMenu.price);
    if (newMenu.price < 0) {
        printf("Invalid price. Must be a positive number.\n");
        return;
    }

    // Generate ID
    char firstInitial = toupper(newMenu.name[0]);
    char secondInitial = toupper(newMenu.name[1]);
    int randomDigits = rand() % 900 + 100;  // random number between 100 and 999
    snprintf(newMenu.id, 10, "%c%c%d", firstInitial, secondInitial, randomDigits);

    // Ensure ID is unique
    for (int i = 0; i < menuCount; i++) {
        if (strcmp(menus[i].id, newMenu.id) == 0) {
            randomDigits++;
            snprintf(newMenu.id, 10, "%c%c%d", firstInitial, secondInitial, randomDigits);
            i = -1;  // Restart loop
        }
    }

    // Initialize stock
    newMenu.stock = 50;

    // Add to menu list
    menus[menuCount++] = newMenu;
    printf("Menu registered successfully.\n");
}

// Fungsi untuk memperbarui menu
void updateMenu() {
    char id[10];
    printf("Enter Menu ID: ");
    scanf("%s", id);
    clearInputBuffer();

    int found = -1;
    for (int i = 0; i < menuCount; i++) {
        if (strcmp(menus[i].id, id) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Menu not found.\n");
        return;
    }

    printf("Menu found: %s\n", menus[found].name);
    printf("Enter new name: ");
    fgets(menus[found].name, MAX_NAME, stdin);
    menus[found].name[strcspn(menus[found].name, "\n")] = 0;  // remove newline

    printf("Enter new type (food, beverage): ");
    fgets(menus[found].type, 10, stdin);
    menus[found].type[strcspn(menus[found].type, "\n")] = 0;  // remove newline

    printf("Enter new price: ");
    scanf("%f", &menus[found].price);

    // Generate new ID
    char firstInitial = toupper(menus[found].name[0]);
    char secondInitial = toupper(menus[found].name[1]);
    int randomDigits = rand() % 900 + 100;  // random number between 100 and 999
    snprintf(menus[found].id, 10, "%c%c%d", firstInitial, secondInitial, randomDigits);

    // Ensure ID is unique
    for (int i = 0; i < menuCount; i++) {
        if (strcmp(menus[i].id, menus[found].id) == 0) {
            randomDigits++;
            snprintf(menus[found].id, 10, "%c%c%d", firstInitial, secondInitial, randomDigits);
            i = -1;  // Restart loop
        }
    }

    printf("Menu updated successfully.\n");
}

// Fungsi untuk melihat riwayat pesanan
void viewOrderHistory() {
    printf("\nOrder History (Last 5 Orders):\n");
    for (int i = (orderCount > 5 ? orderCount - 5 : 0); i < orderCount; i++) {
        printf("Order ID: %s, Table No: %d, Employee: %s\n", orders[i].id, orders[i].tableNo, orders[i].employeeName);
        printf("Items:\n");
        for (int j = 0; j < orders[i].itemCount; j++) {
            printf("  - %s (%d): %.2f\n", orders[i].orderedMenus[j].name, orders[i].quantity[j], orders[i].orderedMenus[j].price);
        }
        printf("Subtotal: %.2f, Service: %.2f, Tax: %.2f, Discount: %.2f, Total Payment: %.2f\n",
               orders[i].subtotal, orders[i].service, orders[i].tax, orders[i].discount, orders[i].totalPayment);
    }
}

// Fungsi untuk membuat pesanan baru
void createNewOrder() {
    if (orderCount >= MAX_ORDERS) {
        printf("Order limit reached. Cannot accept more orders today.\n");
        return;
    }

    Order newOrder;
    printf("Enter Employee ID: ");
    char employeeId[10];
    scanf("%s", employeeId);
    clearInputBuffer();

    int foundEmployee = -1;
    for (int i = 0; i < employeeCount; i++) {
        if (strcmp(employees[i].id, employeeId) == 0) {
            foundEmployee = i;
            strcpy(newOrder.employeeName, employees[i].name);
            break;
        }
    }

    if (foundEmployee == -1) {
        printf("Employee not found.\n");
        return;
    }

    printf("Enter number of items: ");
    scanf("%d", &newOrder.itemCount);
    clearInputBuffer();

    newOrder.subtotal = 0;
    for (int i = 0; i < newOrder.itemCount; i++) {
        printf("Enter Menu ID: ");
        char menuId[10];
        scanf("%s", menuId);
        clearInputBuffer();

        int foundMenu = -1;
        for (int j = 0; j < menuCount; j++) {
            if (strcmp(menus[j].id, menuId) == 0) {
                foundMenu = j;
                break;
            }
        }

        if (foundMenu == -1) {
            printf("Menu not found.\n");
            return;
        }

        printf("Enter quantity: ");
        int quantity;
        scanf("%d", &quantity);
        clearInputBuffer();

        if (quantity > menus[foundMenu].stock) {
            printf("Insufficient stock for %s. Maximum available: %d\n", menus[foundMenu].name, menus[foundMenu].stock);
            return;
        }

        newOrder.orderedMenus[i] = menus[foundMenu];
        newOrder.quantity[i] = quantity;
        newOrder.subtotal += quantity * menus[foundMenu].price;

        // Deduct stock
        menus[foundMenu].stock -= quantity;
    }

    // Generate Order ID
    snprintf(newOrder.id, 10, "ORD%02d", orderCount + 1);
    newOrder.tableNo = orderCount + 1;

    // Calculate service, tax, discount, and total payment
    newOrder.service = newOrder.subtotal * 0.05;
    newOrder.tax = (newOrder.subtotal + newOrder.service) * 0.1;
    int discountMultiplier = (int)(newOrder.subtotal / 500000);
    newOrder.discount = newOrder.subtotal * discountMultiplier * 0.025;
    newOrder.totalPayment = newOrder.subtotal + newOrder.service + newOrder.tax - newOrder.discount;

    // Add to order list
    orders[orderCount++] = newOrder;
    printf("Order created successfully.\n");
}

// Fungsi untuk menghasilkan laporan harian
void generateDailyReport() {
    int totalOrders = orderCount;
    int totalFoods = 0;
    int totalBeverages = 0;
    float totalTransaction = 0;
    int employeeOrderCount[MAX_EMPLOYEES] = {0};

    for (int i = 0; i < orderCount; i++) {
        totalTransaction += orders[i].totalPayment;
        for (int j = 0; j < orders[i].itemCount; j++) {
            if (strcmp(orders[i].orderedMenus[j].type, "food") == 0) {
                totalFoods += orders[i].quantity[j];
            } else if (strcmp(orders[i].orderedMenus[j].type, "beverage") == 0) {
                totalBeverages += orders[i].quantity[j];
            }
        }
        for (int k = 0; k < employeeCount; k++) {
            if (strcmp(orders[i].employeeName, employees[k].name) == 0) {
                employeeOrderCount[k]++;
            }
        }
    }

    // Find MVE
    int maxOrders = 0;
    for (int i = 0; i < employeeCount; i++) {
        if (employeeOrderCount[i] > maxOrders) {
            maxOrders = employeeOrderCount[i];
        }
    }

    printf("\nDaily Report:\n");
    printf("Total Orders: %d\n", totalOrders);
    printf("Total Ordered Foods: %d\n", totalFoods);
    printf("Total Ordered Beverages: %d\n", totalBeverages);
    printf("Total Transaction: %.2f\n", totalTransaction);
    printf("MVE of the Day: ");
    for (int i = 0; i < employeeCount; i++) {
        if (employeeOrderCount[i] == maxOrders) {
            printf("%s ", employees[i].name);
        }
    }
    printf("\n");
}

// Fungsi untuk membersihkan buffer input
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != EOF && c != '\n');
}

