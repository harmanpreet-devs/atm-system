#include <stdio.h>
#define MAX 100

int balance = 10000;

int history[MAX];
int topHistory = -1;

int stack[MAX];
int topStack = -1;

// Push into stack
void push(int amount) {
    if (topStack == MAX - 1) {
        printf("Stack Overflow\n");
        return;
    }
    stack[++topStack] = amount;
}

// Pop from stack
int pop() {
    if (topStack == -1) {
        printf("No transaction to undo\n");
        return 0;
    }
    return stack[topStack--];
}

// Add to history
void addHistory(int amount) {
    history[++topHistory] = amount;
}

// Display history
void showHistory() {
    if (topHistory == -1) {
        printf("No transactions yet.\n");
        return;
    }

    printf("\nTransaction History:\n");
    int i;
    for (i = topHistory; i >= 0; i--) {
        if (history[i] > 0)
            printf("Deposited: %d\n", history[i]);
        else
            printf("Withdrawn: %d\n", -history[i]);
    }
}

// Deposit function
void deposit(int amount) {
    balance += amount;
    push(amount);          // store for undo
    addHistory(amount);    // store in history
    printf("Deposited: %d\n", amount);
}

// Withdraw function
void withdraw(int amount) {
    if (amount > balance) {
        printf("Insufficient Balance!\n");
        return;
    }
    balance -= amount;
    push(-amount);         // negative for withdraw
    addHistory(-amount);
    printf("Withdrawn: %d\n", amount);
}

// Undo last transaction
void undo() {
    int last = pop();

    if (last == 0) return;

    balance -= last;  // reverse operation

    printf("Undo successful!\n");
}

// Show balance
void checkBalance() {
    printf("Current Balance: %d\n", balance);
}

int main() {
    int choice, amount;

    while (1) {
        printf("\n--- ATM Menu ---\n");
        printf("1. Check Balance\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Transaction History\n");
        printf("5. Undo Last Transaction\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                checkBalance();
                break;

            case 2:
                printf("Enter amount to deposit: ");
                scanf("%d", &amount);
                deposit(amount);
                break;

            case 3:
                printf("Enter amount to withdraw: ");
                scanf("%d", &amount);
                withdraw(amount);
                break;

            case 4:
                showHistory();
                break;

            case 5:
                undo();
                break;

            case 6:
                printf("Thank you!\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}

