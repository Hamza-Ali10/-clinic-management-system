#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100
#define MAX_SLOTS 5

// Patient structure
struct Patient {
    char name[50];
    int age;
    char gender;
    int id;
    int reservedSlot; // 0 if not reserved, otherwise the reserved slot index
};

// Function prototypes
void adminMode();
void userMode();
int isIdExists(int id);
void addPatient();
void editPatient();
void reserveSlot();
void cancelReservation();
void viewPatientRecord();
void viewTodayReservations();
void printAvailableSlots();
void initializeSlots();

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

void adminMode() {
    int password = 1234;
    int enteredPassword;
    int attempts = 0;

    do {
        printf("Enter password (Attempts left: %d): ", 3 - attempts);
        scanf("%d", &enteredPassword);

        if (enteredPassword == password) {
            printf("Login successful! Welcome to Admin Mode\n");
            int adminChoice;

            do {
                printf("Admin Mode Menu:\n");
                printf("1. Add new patient record\n");
                printf("2. Edit patient record\n");
                printf("3. Reserve a slot with the doctor\n");
                printf("4. Cancel reservation\n");
                printf("5. Logout\n");
                printf("Enter your choice: ");
                scanf("%d", &adminChoice);

                switch (adminChoice) {
                    case 1:
                        addPatient();
                        break;
                    case 2:
                        editPatient();
                        break;
                    case 3:
                        reserveSlot();
                        break;
                    case 4:
                        cancelReservation();
                        break;
                    case 5:
                        printf("Logging out from Admin Mode\n");
                        break;
                    default:
                        printf("Invalid choice. Try again.\n");
                }
            } while (adminChoice != 5);

            break;
        } else {
            attempts++;

            if (attempts == 3) {
                printf("Incorrect password for 3 consecutive times. Exiting...\n");
                break;
            }

            printf("Incorrect password. Try again.\n");
        }
    } while (1);
}

void userMode() {
    int userChoice;

    do {
        printf("User Mode Menu:\n");
        printf("1. View patient record\n");
        printf("2. View today's reservations\n");
        printf("3. Logout\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                viewPatientRecord();
                break;
            case 2:
                viewTodayReservations();
                break;
            case 3:
                printf("Logging out from User Mode\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (userChoice != 3);
}

int isIdExists(int id) {
    for (int i = 0; i < MAX_PATIENTS; i++) {
        if (patients[i].id == id) {
            return 1; // ID exists
        }
    }
    return 0; // ID does not exist
}

void addPatient() {
    struct Patient newPatient;
    printf("Enter patient name: ");
    scanf("%s", newPatient.name);
    printf("Enter patient age: ");
    scanf("%d", &newPatient.age);
    printf("Enter patient gender (M/F): ");
    scanf(" %c", &newPatient.gender);
    printf("Enter patient ID: ");
    scanf("%d", &newPatient.id);

    if (isIdExists(newPatient.id)) {
        printf("Patient with the same ID already exists. Rejecting the entry.\n");
    } else {
        for (int i = 0; i < MAX_PATIENTS; i++) {
            if (patients[i].id == 0) {
                patients[i] = newPatient;
                printf("Patient record added successfully!\n");
                return;
            }
        }
        printf("Maximum number of patients reached. Cannot add more patients.\n");
    }
}

void editPatient() {
    int id;
    printf("Enter patient ID to edit: ");
    scanf("%d", &id);

    for (int i = 0; i < MAX_PATIENTS; i++) {
        if (patients[i].id == id) {
            printf("Enter updated patient name: ");
            scanf("%s", patients[i].name);
            printf("Enter updated patient age: ");
            scanf("%d", &patients[i].age);
            printf("Enter updated patient gender (M/F): ");
            scanf(" %c", &patients[i].gender);
            printf("Patient record updated successfully!\n");
            return;
        }
    }

    printf("Patient ID not found. Incorrect ID.\n");
}

void reserveSlot() {
    int id, slotIndex;
    printf("Available slots for reservation:\n");
    printAvailableSlots();

    printf("Enter patient ID: ");
    scanf("%d", &id);
    printf("Enter slot index to reserve (1-5): ");
    scanf("%d", &slotIndex);

    if (slotIndex < 1 || slotIndex > MAX_SLOTS) {
        printf("Invalid slot index. Try again.\n");
        return;
    }

    if (reservedSlots[slotIndex - 1] != 0) {
        printf("Slot already reserved. Choose another slot.\n");
    } else {
        for (int i = 0; i < MAX_PATIENTS; i++) {
            if (patients[i].id == id) {
                patients[i].reservedSlot = slotIndex;
                reservedSlots[slotIndex - 1] = id;
                printf("Reservation successful!\n");
                return;
            }
        }

        printf("Patient ID not found. Incorrect ID.\n");
    }
}

void cancelReservation() {
    int id;
    printf("Enter patient ID to cancel reservation: ");
    scanf("%d", &id);

    for (int i = 0; i < MAX_PATIENTS; i++) {
        if (patients[i].id == id) {
            if (patients[i].reservedSlot != 0) {
                reservedSlots[patients[i].reservedSlot - 1] = 0;
                patients[i].reservedSlot = 0;
                printf("Reservation canceled successfully!\n");
            } else {
                printf("Patient does not have any reservation.\n");
            }
            return;
        }
    }

    printf("Patient ID not found. Incorrect ID.\n");
}

void viewPatientRecord() {
    int id;
    printf("Enter patient ID to view record: ");
    scanf("%d", &id);

    for (int i = 0; i < MAX_PATIENTS; i++) {
        if (patients[i].id == id) {
            printf("Patient ID: %d\n", patients[i].id);
            printf("Name: %s\n", patients[i].name);
            printf("Age: %d\n", patients[i].age);
            printf("Gender: %c\n", patients[i].gender);
            if (patients[i].reservedSlot != 0) {
                printf("Reserved Slot: %d\n", patients[i].reservedSlot);
            } else {
                printf("No reservations.\n");
            }
            return;
        }
    }

    printf("Patient ID not found. Incorrect ID.\n");
}

void viewTodayReservations() {
    printf("Today's reservations:\n");
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (reservedSlots[i] != 0) {
            printf("Slot %d: Patient ID %d\n", i + 1, reservedSlots[i]);
        }
    }
}

void printAvailableSlots() {
    for (int i = 0; i < MAX_SLOTS; i++) {
        if (reservedSlots[i] == 0) {
            printf("Slot %d: Available\n", i + 1);
        } else {
            printf("Slot %d: Reserved (Patient ID %d)\n", i + 1, reservedSlots[i]);
        }
    }
}

void initializeSlots() {
    for (int i = 0; i < MAX_SLOTS; i++) {
        reservedSlots[i] = 0;
    }
}