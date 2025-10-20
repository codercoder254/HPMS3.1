//@a.d.a.n_noa😇
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TEMP_MIN 36.1
#define TEMP_MAX 37.2
#define SYSTOLICBP_MIN 90
#define SYSTOLICBP_MAX 120
#define DIASTOLICBP_MIN 60
#define DIASTOLICBP_MAX 80
#define HEARTRATE_MIN 60
#define HEARTRATE_MAX 100


typedef struct{
    float temperature;
    int systolicBP;
    int diastolicBP;
    int heartRate;
}Vitals;

typedef struct{
    int stateCode;
    char statetext[100];
}Status;

//nested struct
typedef struct Patient{
    char name[50];
    signed long long int ID;
    int age;
    Vitals vitals;
    Status status;
    struct Patient *next;
}Patient;

//function to search patient in other functions which need it
Patient* search_patient(Patient *head)
{
    printf("Enter patient name: ");
    char name[50];
    char sname[50];
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    for(int i = 0; name[i] != '\0'; i++)
    {
        sname[i] = tolower(name[i]);
    }

    Patient *temp = head;
    while( temp != NULL)
    {
        char temp_name[50];
        for(int i = 0; temp -> name[i] != '\0'; i++)
        {
            temp_name[i] = tolower(temp -> name[i]);
        }
        if(strcmp(temp_name, sname) == 0)
        {
            return temp;
        }
        temp = temp -> next;
    }
    return NULL;
}

//add patient to linked list
void add_patient(Patient **head, Patient *newP)
{
    if(*head == NULL)
    {
        *head = newP;
    }
    else
    {
        Patient *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newP;
    }
}

//function to create new patient
Patient *create_Patient(void)
{
    char temp_Name[30];
    signed long long int temp_ID;
    int temp_Age;
    float temp_temperature;
    int temp_SystolicBP;
    int temp_DiastolicBP;
    int temp_Heartrate;
    int temp_Statecode;
    char temp_Statetext[100];

    printf("New patient.\n");
    printf("Name of patient: ");
    fgets(temp_Name, sizeof(temp_Name),stdin);
    temp_Name[strcspn(temp_Name, "\n")] = '\0';
    printf("Enter: \n");
    printf("ID: ");
    scanf(" %llu",&temp_ID);
    printf("Age: ");
    scanf(" %d",&temp_Age);
    printf("Body temperature: ");
    scanf(" %f", &temp_temperature);
    printf("SystolicBP: ");
    scanf(" %d",&temp_SystolicBP);
    printf("DiastolicBP: ");
    scanf(" %d",&temp_DiastolicBP);
    printf("HeartRate: ");
    scanf(" %d",&temp_Heartrate);
    printf("Statecode: ");
    scanf(" %d",&temp_Statecode);
    printf("Statetext: ");
    while (getchar() != '\n');  // clear stdin
    fgets(temp_Statetext, sizeof(temp_Statetext), stdin);
    temp_Statetext[strcspn(temp_Statetext, "\n")] = '\0';

    Patient *newPatient = (Patient*)malloc(sizeof(Patient));
    if (!newPatient)
    {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newPatient->ID = temp_ID;
    newPatient->age = temp_Age;
    strncpy(newPatient->name,temp_Name,sizeof(newPatient->name)-1);
    newPatient->name[sizeof(newPatient->name)-1] = '\0';
    newPatient->vitals.temperature = temp_temperature;
    newPatient->vitals.systolicBP = temp_SystolicBP;
    newPatient->vitals.diastolicBP = temp_DiastolicBP;
    newPatient->vitals.heartRate = temp_Heartrate;
    newPatient->status.stateCode = temp_Statecode;
    strncpy(newPatient->status.statetext, temp_Statetext, sizeof(newPatient->status.statetext)-1);
    newPatient->status.statetext[sizeof(newPatient->status.statetext)-1] = '\0';
    newPatient->next = NULL;

    return newPatient;
}


int check_vitals(Patient *head)
{
    Patient *temp_patient = search_patient(head);
    if (temp_patient == NULL)
    {
        perror("Patient not found!\n");
        return -1;
    }
    printf("Checking  vitals for %s\n", temp_patient->name);
    int check_array[5];
    //Temperature
    if(temp_patient->vitals.temperature >= TEMP_MIN && temp_patient->vitals.temperature <= TEMP_MAX)
    {
        check_array[0] = 0;
    }
    else
    {
        check_array[0] = 1;
    }
    //Systolic BP
    if(temp_patient->vitals.systolicBP >= SYSTOLICBP_MIN && temp_patient->vitals.systolicBP <= SYSTOLICBP_MAX)
    {
        check_array[1] = 0;
    }
    else
    {
        check_array[1] = 1;
    }
    //DiastolicBP
    if(temp_patient->vitals.diastolicBP >= DIASTOLICBP_MIN && temp_patient->vitals.diastolicBP <= DIASTOLICBP_MAX)
    {
        check_array[2] = 0;
    }
    else
    {
        check_array[2] = 1;
    }
    //Heartrate
    if(temp_patient->vitals.heartRate >= HEARTRATE_MIN && temp_patient->vitals.heartRate <= HEARTRATE_MAX)
    {
        check_array[3] = 0;
    }
    else
    {
        check_array[3] = 1;
    }

    int check_counter = 0;
    for(int i = 0; i<4; i++)
    {
        if(check_array[i] != 0)
        {
            check_counter++;
        }
    }

    if(check_counter == 0)
        check_array[4] = 0; // normal
    else if(check_counter == 1)
        check_array[4] = 1; // warning
    else
        check_array[4] = 2; // emergency

    return check_array[4];
}


Patient* update_vitals(Patient *head)
{
    Patient *temp_patient = search_patient(head);
    if (temp_patient == NULL)
    {
        perror("Patient not found!\n");
        return NULL;
    }
    printf("Updating vitals...\n");
    while(1)
    {
        char Element_name[20];
        printf("Element to be updated?(Temperature/SystolicBP/DiastolicBP/HeartRate): ");
        scanf("%19s",Element_name);

        char element_name[20];
        int i;
        for(i=0; Element_name[i] != '\0'; i++)
        {
            element_name[i] = tolower((unsigned char)Element_name[i]);
        }
        element_name[i] = '\0';

        if(strcmp(element_name,"temperature") == 0)
        {
            float temp_temperature;
            printf("Temperature update.\nInsert: ");
            scanf(" %f",&temp_temperature);
            temp_patient->vitals.temperature = temp_temperature;
            printf("Temperature updated: %f\n.",temp_patient->vitals.temperature);
            break;
        }
        else if(strcmp(element_name,"systolicbp") == 0)
        {
            int temp_systolicbp;
            printf("SystolicBP update.\nInsert: ");
            scanf(" %d",&temp_systolicbp);
            temp_patient->vitals.systolicBP = temp_systolicbp;
            printf("SystolicBP updated: %d\n.",temp_patient->vitals.systolicBP);
            break;
        }
        else if(strcmp(element_name,"diastolicbp") == 0 )
        {
            int temp_diastolicbp;
            printf("DiastolicBP update.\nInsert: ");
            scanf(" %d",&temp_diastolicbp);
            temp_patient->vitals.diastolicBP = temp_diastolicbp;
            printf("DiastolicBP updated: %d.\n",temp_diastolicbp);
            break;
        }
        else if(strcmp(element_name,"heartrate") == 0 )
        {
            int temp_heartrate;
            printf("Heartrate update.\nInsert: ");
            scanf(" %d",&temp_heartrate);
            temp_patient->vitals.heartRate = temp_heartrate;
            printf("Heartrate updated: %d.\n",temp_heartrate);
            break;
        }
        else
        {
            printf("Seems you entered a wrong element.Try again.\n");
        }
    }

    return temp_patient;
}

void print_patient(Patient *temp_p)
{
    Patient *temp_patient = search_patient(temp_p);
    if (temp_patient == NULL)
    {
        perror("Patient not found!\n");
        return;
    }
    printf("Patient: %s\n",temp_patient->name);
    printf("ID: %llu\n",temp_patient->ID);
    printf("Age: %d\n",temp_patient->age);
    printf("Body temperature: %.2f\nSystolicBP: %d\nDiastolicBP: %d\nHeartRate: %d\n",
        temp_patient->vitals.temperature,
        temp_patient->vitals.systolicBP,
        temp_patient->vitals.diastolicBP,
        temp_patient->vitals.heartRate);
    printf("Status code: %d\n",temp_patient->status.stateCode);
    printf("Status text: %s\n",temp_patient->status.statetext);
}

// view all patients
void viewAllpatients(Patient *head)
{
    if (head == NULL)
    {
        printf("No patients to view.\n");
        return;
    }

    Patient *temp_patient = head;
    while (temp_patient != NULL)
    {
        printf("Patient: %s\n",temp_patient->name);
    printf("ID: %llu\n",temp_patient->ID);
    printf("Age: %d\n",temp_patient->age);
    printf("Body temperature: %.2f\nSystolicBP: %d\nDiastolicBP: %d\nHeartRate: %d\n",
        temp_patient->vitals.temperature,
        temp_patient->vitals.systolicBP,
        temp_patient->vitals.diastolicBP,
        temp_patient->vitals.heartRate);
    printf("Status code: %d\n",temp_patient->status.stateCode);
    printf("Status text: %s\n",temp_patient->status.statetext);
        printf("------------------------------------\n");
        temp_patient = temp_patient->next;
    }
}

int main(void)
{
    Patient *head = NULL;
    int choice;

    while(1)
    {
        printf("\n=== Hospital Management Menu ===\n");
        printf("1. Add Patient\n");
        printf("2. View All Patients\n");
        printf("3. View a Patient's Details\n");
        printf("4. Check Vitals\n");
        printf("5. Update Vitals\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);
        while (getchar() != '\n');  // clear newline from input buffer

        switch(choice)
        {
            case 1:
            {
                Patient *newP = create_Patient();
                add_patient(&head, newP);
                break;
            }

            case 2:
                viewAllpatients(head);
                break;

            case 3:
                if(head != NULL)
                    print_patient(head);
                else
                    printf("No patient to view!\n");
                break;

            case 4:
                if(head != NULL)
                {
                    int check = check_vitals(head);
                    if(check == 0)
                    {
                        printf("All vitals normal.\n");
                    }
                    else if(check == 1)
                    {
                        printf("Warning: one vital sign is outside normal range.\n");
                    }
                    else
                    {
                        printf("Emergency: multiple vital signs are outside normal range.\n");
                    }
                }
                else
                    printf("No patient to check!\n");
                break;

            case 5:
                if(head != NULL)
                    update_vitals(head);
                else
                    printf("No patient to update!\n");
                break;

            case 6:
                printf("Exiting program...\n");
                printf("Made by Adan\n");
                return 0;

            default:
                printf("Invalid option, please try again.\n");
        }
    }
}
