#ifndef CLINCMANGEMENTSYSTEM_INTERFACE_H_INCLUDED
#define CLINCMANGEMENTSYSTEM_INTERFACE_H_INCLUDED
#define null ((void*) (0))

typedef struct Node node;

struct Node {
    unsigned int id;
    int age;
    char *name;
    char gender;
    char slot;
    node* next;
};

node *slot[5];
node *header, *top;
/********************************/
int checkID(int id);
void addPatient(int id, char* name, int age, char gender);
void removePatient(int id);
void editPatient(int id);
void showPatients();
void showPatient(int id);
node* searchPatient(int id);
int addSlot(int id, int time);
void cancelSlot(int id);
void showReservations();
void showTime(int i);
int countOfReservation();
int showAvilableSlots();



#endif // CLINCMANGEMENTSYSTEM_INTERFACE_H_INCLUDED
