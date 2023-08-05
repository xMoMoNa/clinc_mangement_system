#include "stdio.h"
#include "stdlib.h"
#include "clincMangementSystem_interface.h"


int size=0;

/*****************************************************************/
int checkID(int id) {
    header=top;
    while(header!=null) {
        if(header->id==id) {
            return 1;
        }
        header=header->next;
    }
    return 0;
}

/*****************************************************************/
void addPatient(int id, char* name, int age, char gender) {
    node* newPatient = (node*) malloc(sizeof(node));
    if(top==null) {
        newPatient->next=null;
    } else {
        newPatient->next=top;
    }
    top=newPatient;
    newPatient->id=id;
    newPatient->name=&name[0];
    newPatient->age=age;
    newPatient->gender=gender;
    newPatient->slot=-1;
    size++;
}
/*****************************************************************/

void removePatient(int id) {
    node* temp;
    header=searchPatient(id);
    temp=header->next->next;
    free(header->next);
    header->next=temp;
    size--;
}
/*****************************************************************/

void editPatient(int id) {
    int i=0, tryGlobal;
    char gender;
    header=searchPatient(id);
    printf("--------------------\n");
    showPatient(id);
    printf("--------------------\n");
    printf("Choose edit:\n1- Name.\n2- Age.\n3- Gender.\nYour choice:");
    scanf("%d", &i);
    switch(i) {
    case 1:
        printf(">> Enter a new name (old: %s): ", header->name);
        scanf("%s", &header->name);
        break;
    case 2:
        printf(">> Enter a new age (old: %d): ", header->age);
        scanf("%d", &header->age);
        break;
    case 3:
        tryGlobal=3;
        while(tryGlobal--) {
            printf(">> Enter new gender ('f' for female, 'm' for male) (old: %s): ", header->gender=='f'?"femal":"male");
            fflush(stdin);
            scanf(" %c", &gender);
            if(gender=='f' || gender == 'm') {
                header->gender=gender;
                printf(">>> Edit gender successfully.\n\n");
                break;
            } else {
                printf(">>> Not valid gender, try again! <<<\n");
            }
            if(tryGlobal==-1) {
                printf(">>> Cancel Editing. <<<\n\n");
            }
        }
    }
}
    /*****************************************************************/

    void showPatients() {
        header=top;
        while(header !=0) {
            printf("--------------------\n");
            showPatient(header->id);
            header=header->next;
        }
        printf("--------------------\n");
    }
    /*****************************************************************/

    void showPatient(int id) {
        node *patient=searchPatient(id);
        printf("ID: %d\nName: %s\nAge: %d\nGender: %s\n",
               patient->id, patient->name, patient->age, patient->gender=='f'?"female":"male");

    }
    /*****************************************************************/
    node* searchPatient(int id) {
        header=top;
        while(header!=null) {
            if(header->id==id) {
                return header;
            }
            header=header->next;
        }
        return null;
    }
    /*****************************************************************/

    int addSlot(int id, int time) {
        int i=0;
        while(time>0) {
            if(slot[i]==null) {
                time--;
            }
            i++;
        }
        i--;
        header=searchPatient(id);
        if(header) {
            if(i<5 && i>=0 && slot[i]==null) {
                slot[i]=header;
                header->slot=i;
                return 1;
            }
        }
        return 0;
    }
    /*****************************************************************/

    void cancelSlot(int id) {
        header=searchPatient(id);
        if(header != null) {
            slot[header->slot]=null;
            header->slot=-1;
        } else {
            printf("not found!\n");
        }
    }
    /*****************************************************************/

    void showReservations() {
        int check=0;
        for(int i=0; i<5; i++) {
            if(slot[i]!=null) {
                printf("- ");
                showTime(i);
                printf(" ==> Id: %d\tName: %s\n",slot[i]->id, slot[i]->name);

                check=1;
            }
        }
        if(!check) {
            printf(">> There is no reservation today.\n\n");
        }
    }
    /*****************************************************************/

    void showTime(int i) {
        switch(i) {
        case -1:
            printf("No reservation");
            break;
        case 0:
            printf("02:00 pm to 02:30 pm");
            break;
        case 1:
            printf("02:30 pm to 03:00 pm");
            break;
        case 2:
            printf("03:00 pm to 03:30 pm");
            break;
        case 3:
            printf("04:00 pm to 04:30 pm");
            break;
        case 4:
            printf("04:30 pm to 05:00 pm");
            break;
        }
    }
    /*****************************************************************/

    int countOfReservation() {
        int avilableSlots=0;
        int i=0;
        while(i<5) {
            if(slot[i]!=null) {
                avilableSlots++;
            }
            i++;
        }
        return avilableSlots;
    }
    /*****************************************************************/

    int showAvilableSlots() {
        int avilableSlots=0;
        int i=0, c=1;
        while(i<5) {
            if(slot[i]==null) {
                printf("%d- ", c);
                c++;
                showTime(i);
                printf("\n");
                avilableSlots++;
            }
            i++;
        }
        return avilableSlots;
    }










