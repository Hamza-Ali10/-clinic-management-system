#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_SLOTS 5

#include "clinic.h"

// Patient structure
struct Patient {
    char name[50];
    int age;
    char gender;
    int id;
    int reservedSlot; // 0 if not reserved, otherwise the reserved slot index
};



// Global variables
struct Patient patients[MAX_PATIENTS];
int reservedSlots[MAX_SLOTS];

int main() {
    initializeSlots();

    int choice;
    printf("Welcome to Clinic Management System!\n");
    printf("Choose mode: \n");
    printf("1. Admin Mode\n");
    printf("2. User Mode\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        adminMode();
    } else if (choice == 2) {
        userMode();
    } else {
        printf("Invalid choice. Exiting...\n");
    }

    return 0;
}

