#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Patient {
    int id;
    char name[50];
    int age;
    char disease[50];
    char doctor[50];
};

// Function to add patient
void addPatient() {
    struct Patient p;
    FILE *fp = fopen("hospital.dat", "ab");

    printf("\nEnter Patient ID: ");
    scanf("%d", &p.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", p.name);
    printf("Enter Age: ");
    scanf("%d", &p.age);
    printf("Enter Disease: ");
    scanf(" %[^\n]", p.disease);
    printf("Enter Doctor Name: ");
    scanf(" %[^\n]", p.doctor);

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);

    printf("\nPatient record added successfully!\n");
}

// Function to display all patients
void displayPatients() {
    struct Patient p;
    FILE *fp = fopen("hospital.dat", "rb");

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n--- Patient Records ---\n");

    while (fread(&p, sizeof(p), 1, fp)) {
        printf("\nID: %d\nName: %s\nAge: %d\nDisease: %s\nDoctor: %s\n",
               p.id, p.name, p.age, p.disease, p.doctor);
    }

    fclose(fp);
}

// Function to search patient
void searchPatient() {
    struct Patient p;
    int id, found = 0;

    FILE *fp = fopen("hospital.dat", "rb");

    printf("\nEnter Patient ID to search: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id == id) {
            printf("\nRecord Found:\n");
            printf("Name: %s\nAge: %d\nDisease: %s\nDoctor: %s\n",
                   p.name, p.age, p.disease, p.doctor);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nRecord not found!\n");

    fclose(fp);
}

// Function to delete patient
void deletePatient() {
    struct Patient p;
    int id, found = 0;

    FILE *fp = fopen("hospital.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    printf("\nEnter Patient ID to delete: ");
    scanf("%d", &id);

    while (fread(&p, sizeof(p), 1, fp)) {
        if (p.id != id) {
            fwrite(&p, sizeof(p), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("hospital.dat");
    rename("temp.dat", "hospital.dat");

    if (found)
        printf("\nRecord deleted successfully!\n");
    else
        printf("\nRecord not found!\n");
}

// Main function
int main() {
    int choice;

    while (1) {
        printf("\n===== Hospital Record System =====\n");
        printf("1. Add Patient\n");
        printf("2. Display Patients\n");
        printf("3. Search Patient\n");
        printf("4. Delete Patient\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addPatient(); break;
            case 2: displayPatients(); break;
            case 3: searchPatient(); break;
            case 4: deletePatient(); break;
            case 5: exit(0);
            default: printf("\nInvalid choice!\n");
        }
    }

    return 0;
}
