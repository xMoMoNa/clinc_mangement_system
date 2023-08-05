#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "clincMangementSystem_interface.h"

extern size;
int main() {
    int chooseMain=0, chooseAdmin=0, chooseUser=0;
    int tryPassword=3, password=0, checkPassword=1, clearMenu=1, avilableSlots=0, tryGlobal=3;
    int id;
    int age;
    char gender;
    char name[20];
    int time;

    addPatient(1, "Mohammed Mohsen", 24, 'm');
    addPatient(2, "Belal Mostafa", 20, 'm');
    addPatient(3, "Basel", 23, 'm');
    addPatient(4, "Ebrahem", 13, 'm');
    addPatient(5, "Basma", 21, 'f');
    addPatient(6, "Reem", 18, 'f');
    addPatient(7, "Karim", 20, 'm');
    addPatient(8, "Rewan", 18, 'f');
    addPatient(9, "Mohsen", 57, 'm');
    addPatient(10, "esraa", 16, 'f');

    addSlot(1,5);
    addSlot(2,4);
    addSlot(3,3);
    addSlot(4,2);
    addSlot(5,1);
    /*****************************************************************/
    while(1) {
        system("cls");
        printf("+-----------------------------------------------+\n");
        printf("+   Welcome to clinic management system V1.0    +\n");
        printf("+-----------------------------------------------+\n");
        printf("++ Choose mode (any number else will close the system):\n1- Admin mode.\n2- User mode.\n>> Your choice: ");
        scanf("%d", &chooseMain);
        if(chooseMain!=1 && chooseMain !=2) {
            printf(">>> Exit! <<<\n");
            break; /*Close system*/
        }
        switch(chooseMain) {
        case 1: /*admin mode*/
            tryPassword=3;
            checkPassword=0;
            while(tryPassword--) {

                printf(">> enter password: ");
                fflush(stdin);
                scanf("%d", &password);
                if(password==PASSWORD) {
                    checkPassword=1;
                    clearMenu=1;
                    break;
                }
                if(tryPassword) {
                    printf(">>> Not correct Password, try a gain! (%d %s try left) <<<\n", tryPassword, tryPassword==1?"time":"times");
                }
            }
            if(checkPassword==0) {
                break; /*break admin menu*/
            }
            while(1) {
                if(clearMenu) {
                    system("cls");
                    clearMenu=0;
                    printf("+-----------------------------------------------+\n");
                    printf("+        Welcome you are in admin mode.         +\n");
                    printf("+-----------------------------------------------+\n");
                }
                printf("++ Choose option (any number else will return to main menu):\
                       \n1- Add a new patient.\n2- Edit a patient.\n3- Reserve a slot with the doctor.\
                       \n4- Cancel a Reservation.\n5- Delete a patient.\n>> Your choice: ");
                scanf("%d", &chooseAdmin);
                if(chooseAdmin>5 || chooseAdmin<1) {
                    clearMenu=1;
                    break; /*Return to main menu*/
                }
                switch(chooseAdmin) {
                case 1: /*Add patient*/
                    printf(">> enter id: ");
                    fflush(stdin);
                    scanf(" %d", &id);
                    if(checkID(id)) {
                        printf(">>> Invalid id! <<<\n\n");
                        break; /*Return to admin menu*/
                    }
                    printf(">> enter name: ");
                    fflush(stdin);
                    scanf(" %[^\n]s", &name);
                    tryGlobal=3;
                    while(tryGlobal--) {
                        printf(">> enter age: ");
                        fflush(stdin);
                        fflush(stdin);
                        scanf("%d", &age);
                        if(age>150 || age <1) {
                            printf(">>> Not valid age, try again! <<<\n\n");
                        } else {
                            break;
                        }
                    }
                    if(tryGlobal==-1) {
                        printf(">>> Cancel record! <<<\n\n");
                        break;
                    }
                    tryGlobal=3;
                    while(tryGlobal--) {
                        printf(">> Enter a gender ('f' for female, 'm' for male): ");
                        fflush(stdin);
                        scanf(" %c", &gender);
                        if(gender=='f' || gender == 'm') {
                            addPatient(id, name, age, gender);
                            printf(">>> The patient Added successfully.\n\n");
                            break;
                        } else {
                            printf(">>> Not valid gender, try again! <<<\n");
                        }
                        if(tryGlobal==-1) {
                            printf(">>> Cancel record <<<\n\n");
                        }
                    }
                    break;
                case 2: /*edit patient*/
                    printf(">> Enter patient ID: ");
                    scanf("%d",&id);
                    editPatient(id);
                    printf("\n");
                    break;
                case 3: /*reserve a slot*/
                    avilableSlots=0;
                    printf(">> Enter patient ID: ");
                    scanf("%d",&id);
                    if(checkID(id)) {
                        printf("++ Choose your suitable time:\n");
                        avilableSlots=showAvilableSlots();
                        if(!avilableSlots) {
                            printf(">> It is complete today.\n\n");
                            break;
                        }
                        printf(">> Your choice: ");
                        fflush(stdin);
                        scanf("%d",&time);
                        if(addSlot(id, time)) {
                            printf(">>> Reservation done for patient id (%d) for time ", id);
                            showTime((searchPatient(id))->slot);
                            printf(".\n\n");
                        } else {
                            printf(">>> Not available slot! <<<\n\n");
                        }
                    } else {
                        printf(">>> Not found patient! <<<\n\n");
                    }
                    break;
                case 4: /*cancel reservation*/
                    printf(">> Enter patient ID: ");
                    fflush(stdin);
                    scanf("%d",&id);
                    if(checkID(id)) {
                        cancelSlot(id);
                        printf(">>> Remove slot of patient Id:%d\tName:%s\n\n", id, searchPatient(id)->name);
                    } else {
                        printf(">>> Not found! <<<");
                    }
                    break;
                case 5: /*remove patient*/
                    printf(">> Enter patient ID: ");
                    scanf("%d",&id);
                    if(checkID(id)) {
                        removePatient(id);
                        printf(">>> Patient with id (%d) removed.\n\n", id);
                    } else {
                        printf(">>> Not found! <<<\n\n");
                    }
                    break;
                }
            }
            break; /*Break Admin menu*/
        case 2: /*user mode*/
            while(1) {
                if(clearMenu) {
                    system("cls");
                    clearMenu=0;
                    printf("+-----------------------------------------------+\n");
                    printf("+         Welcome you are in user mode.         +\n");
                    printf("+-----------------------------------------------+\n");
                }
                printf("++ Choose option (any number else will return to main menu):\n1- View patient's information.\
                       \n2- View today's reservations and system status.\n3- View all patient.\n>> Your choice: ");
                fflush(stdin);
                scanf("%d", &chooseUser);
                if(chooseUser>4 || chooseUser<1) {
                    clearMenu=1;
                    break; /*return to main menu*/
                }
                switch(chooseUser) {
                case 1: /*View patient's information*/
                    printf(">> Enter patient ID: ");
                    scanf("%d",&id);
                    if(checkID(id)) {
                        showPatient(id);
                        printf("Reservation: ");
                        showTime(searchPatient(id)->slot);
                        printf("\n\n");
                    } else {
                        printf(">>> Not found! <<<\n\n");
                    }
                    break;
                case 2: /*View today's reservations*/
                    avilableSlots=countOfReservation();
                    printf("- There are %d patient in system.\n- There are %d reservation.", size, avilableSlots);
                    printf(avilableSlots==0?".\n":":\n");
                    showReservations();
                    printf("\n");
                    break;
                case 3: /*Show all patients*/
                    showPatients();
                    printf("\n");
                    break;
                }
            }
            break;/*Break of user menu*/
        default: /*1- admin 2- user 3- defaule*/
            break;
        }
        if(checkPassword==0) {
            printf(">>> Exit! <<<\n");
            break; /*Close system*/
        }
    }
    return 0;
}
