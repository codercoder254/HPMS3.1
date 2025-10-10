//@a.d.a.n_noa&June😇
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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


int check_vitals(Patient *temp_p)
{
    Patient *temp_patient = temp_p;
    printf("Checking  vitals...\n");
    int check_array[5];
    //Temperature
    if(temp_patient->vitals.temperature >= 36.1 && temp_patient->vitals.temperature <= 37.2)
    {
        check_array[0] = 0;
    }
    else
    {
        check_array[0] = 1;
    }
    //Systolic BP
    if(temp_patient->vitals.systolicBP >= 90 && temp_patient->vitals.systolicBP <= 120)
    {
        check_array[1] = 0;
    }
    else
    {
        check_array[1] = 1;
    }
    //DiastolicBP
    if(temp_patient->vitals.diastolicBP >= 60 && temp_patient->vitals.diastolicBP <= 80)
    {
        check_array[2] = 0;
    }
    else
    {
        check_array[2] = 1;
    }
    //Heartrate
    if(temp_patient->vitals.heartRate >= 60 && temp_patient->vitals.heartRate <= 100)
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


Patient* update_vitals(Patient *temp_p)
{
    Patient *temp_patient = temp_p;
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
    Patient *temp_patient = temp_p;
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
        printf("No patients available.\n");
        return;
    }

    Patient *temp = head;
    while (temp != NULL)
    {
        print_patient(temp);
        printf("------------------------------------\n");
        temp = temp->next;
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
        printf("3. Check Vitals\n");
        printf("4. Update Vitals\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);
        getchar();

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
                    check_vitals(head);
                else
                    printf("No patient to check!\n");
                break;

            case 4:
                if(head != NULL)
                    update_vitals(head);
                else
                    printf("No patient to update!\n");
                break;

            case 5:
                printf("Exiting program...\n");
                printf("Made by Adan\n");
                return 0;

            default:
                printf("Invalid option, please try again.\n");
        }
    }
}
