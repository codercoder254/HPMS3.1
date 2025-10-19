BEGIN PROGRAM HospitalManagementSystem

    INCLUDE standard libraries (stdio.h, stdlib.h, string.h, etc.)

    DEFINE structure PATIENT
        name
        age
        gender
        disease
        admission_date
        discharge_date
        room_number
    END STRUCTURE

    DECLARE array patients[MAX_PATIENTS]
    DECLARE integer patient_count = 0

    FUNCTION addPatient()
        PROMPT user for patient details
        STORE details in patients[patient_count]
        INCREMENT patient_count
        DISPLAY confirmation message
    END FUNCTION

    FUNCTION viewPatients()
        IF patient_count == 0
            DISPLAY "No patients currently recorded"
        ELSE
            FOR each patient in patients
                DISPLAY patient details in formatted output
            END FOR
        END IF
    END FUNCTION

    FUNCTION searchPatient()
        PROMPT user for name or ID to search
        SCAN through patient records
        IF match found
            DISPLAY matching patient details
        ELSE
            DISPLAY "Patient not found"
        END IF
    END FUNCTION

    FUNCTION dischargePatient()
        PROMPT for patient name
        FIND and REMOVE from list or mark as discharged
        DISPLAY success message
    END FUNCTION

    FUNCTION mainMenu()
        REPEAT
            DISPLAY menu options:
                1. Add new patient
                2. View patients
                3. Search patient
                4. Discharge patient
                5. Exit
            READ user choice
            SWITCH choice
                CASE 1: call addPatient()
                CASE 2: call viewPatients()
                CASE 3: call searchPatient()
                CASE 4: call dischargePatient()
                CASE 5: EXIT loop
                DEFAULT: DISPLAY "Invalid option"
            END SWITCH
        UNTIL user chooses Exit
    END FUNCTION

    CALL mainMenu()

END PROGRAM