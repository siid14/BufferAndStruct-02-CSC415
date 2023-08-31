/**************************************************************
 * Class:  CSC-415-01# Summer 2021
 * Name: Sidney Thomas
 * Student ID: 918656419
 * GitHub Name: bierman
 * Project: Assignment 2 – Command Line Arguments
 *
 * File: Thomas_Sidney_HW2_main.c
 *
 * Description: To show how to use ...
 *
 **************************************************************/

#include <stdio.h>  // library for input/output
#include <stdlib.h> // library for memory management
#include <string.h>
#include "assignment2.h"

int main(int argc, char *argumentValues[])
{

    // printing the size of personalInfo structure
    printf("Size of personalInfo: %lu bytes\n", (unsigned long)sizeof(personalInfo));

    // allocating memory for personalInfo
    personalInfo *studentInfo = (personalInfo *)malloc(sizeof(personalInfo));

    if (studentInfo == NULL)
    {
        // handle memory allocation failure
        printf("studentInfo is NULL!");
        return 1; // exit with an error code
    }

    // populating data to personalInfo
    studentInfo->firstName = argumentValues[1];
    studentInfo->lastName = argumentValues[2];
    studentInfo->studentID = 918656419;
    studentInfo->level = SENIOR;
    studentInfo->languages = KNOWLEDGE_OF_C | KNOWLEDGE_OF_JAVA | KNOWLEDGE_OF_JAVASCRIPT | KNOWLEDGE_OF_CPLUSPLUS | KNOWLEDGE_OF_HTML | KNOWLEDGE_OF_MIPS_ASSEMBLER;
    strcpy(studentInfo->message, argumentValues[3]);

    printf("firstName is %s\n", studentInfo->firstName);
    printf("lastName is %s\n", studentInfo->lastName);
    printf("studentID is %d\n", studentInfo->studentID);
    printf("gradelevel is %u\n", studentInfo->level);
    printf("message is %s\n", studentInfo->message);

    // ? check that
    // printf("languages is 0x%x\n", studentInfo->languages); // Print as hexadecimal

    // using the allocated memory

    // calling the writePersonalInfo function to write the studentInfo
    int writeSucess = writePersonalInfo(studentInfo);

    // check if the writePersonalInfo function was successful
    if (writeSucess == 0)
    {
        printf("Personal information written successfullu\n");
    }
    else
    {
        printf("Failed to write personal information.\n");
    }

    // done with the allocated memory, so freeing it
    free(studentInfo);

    return 0; // exit successfully
}
