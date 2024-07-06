#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 100
#define MAX_CATEGORY_LENGTH 20

typedef struct {
    char date[11];  // Format: YYYY-MM-DD
    char category[MAX_CATEGORY_LENGTH];
    float amount;
} Expense;
void addExpense(Expense expenses[], int *count) {
    if (*count >= MAX_EXPENSES) {
        printf("Expense list is full!\n");
        return;
    }

    Expense newExpense;
    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", newExpense.date);
    printf("Enter category: ");
    scanf("%s", newExpense.category);
    printf("Enter amount: ");
    scanf("%f", &newExpense.amount);

    expenses[*count] = newExpense;
    (*count)++;
    printf("Expense added successfully!\n");
}
void viewExpenses(Expense expenses[], int count) {
    printf("Date       | Category         | Amount\n");
    printf("----------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%s | %-15s | %.2f\n", expenses[i].date, expenses[i].category, expenses[i].amount);
    }
}
void saveExpenses(Expense expenses[], int count) {
    FILE *file = fopen("expenses.txt", "w");
    if (file == NULL) {
        printf("Could not open file for writing.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s %s %.2f\n", expenses[i].date, expenses[i].category, expenses[i].amount);
    }
    fclose(file);
    printf("Expenses saved to file successfully.\n");
}
void loadExpenses(Expense expenses[], int *count) {
    FILE *file = fopen("expenses.txt", "r");
    if (file == NULL) {
        printf("No saved expenses found.\n");
        return;
    }
    *count = 0;
    while (fscanf(file, "%s %s %f", expenses[*count].date, expenses[*count].category, &expenses[*count].amount) != EOF) {
        (*count)++;
        if (*count >= MAX_EXPENSES) break;
    }
    fclose(file);
    printf("Expenses loaded from file successfully.\n");
}
void generateReport(Expense expenses[], int count) {
    float totalAmount = 0;
    for (int i = 0; i < count; i++) {
        totalAmount += expenses[i].amount;
    }
    printf("Total Expenses: %.2f\n", totalAmount);
}
int main() {
    Expense expenses[MAX_EXPENSES];
    int count = 0;
    int choice;

    loadExpenses(expenses, &count);

    do {
        printf("\nExpense Tracker\n");
        printf("1. Add Expense\n");
        printf("2. View Expenses\n");
        printf("3. Save Expenses\n");
        printf("4. Generate Report\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addExpense(expenses, &count);
                break;
            case 2:
                viewExpenses(expenses, count);
                break;
            case 3:
                saveExpenses(expenses, count);
                break;
            case 4:
                generateReport(expenses, count);
                break;
            case 5:
                saveExpenses(expenses, count);
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

