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
#include <errno.h>
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
    int writeSuccess = writePersonalInfo(studentInfo);

    // check if the writePersonalInfo function was successful
    if (writeSuccess == 0)
    {
        printf("Personal information written successfully\n");
    }
    else
    {
        printf("Failed to write personal information.\n");
    }

    // create a buffer of size BLOCK_SIZE using malloc.
    char *buffer = (char *)malloc(BLOCK_SIZE * sizeof(char));

    // check if malloc was successful in allocating memory.
    if (buffer == NULL)
    {
        perror("Failed to allocate memory for the buffer");
        exit(1); // exit the program with an error code.
    }

    // initialize variables to keep track of the buffer position and data written.
    size_t bufferPosition = 0; // current position in the buffer.
    size_t dataWritten = 0;    // amount of data written to the buffer.

    char *nextString;
    while ((nextString = getNext()) != NULL)
    {
        // Process each received string in this loop.
        size_t stringLength = strlen(nextString);
        size_t spaceLeftInBuffer = BLOCK_SIZE - bufferPosition;

        // Check if the string can fit in the remaining space in the buffer.
        if (stringLength <= spaceLeftInBuffer)
        {
            // The entire string fits in the remaining space, so copy it to the buffer.
            memcpy(buffer + bufferPosition, nextString, stringLength);
            bufferPosition += stringLength;
        }
        else
        {
            // The string is larger than the remaining space in the buffer.
            // Copy as much as possible into the buffer and commit the buffer.
            size_t bytesToCopy = spaceLeftInBuffer;
            memcpy(buffer + bufferPosition, nextString, bytesToCopy);
            bufferPosition += bytesToCopy;

            // Commit the filled buffer using commitBlock.
            commitBlock(buffer);

            // Reset the buffer position and copy the remaining part of the string.
            bufferPosition = 0;
            bytesToCopy = stringLength - spaceLeftInBuffer;
            memcpy(buffer + bufferPosition, nextString + spaceLeftInBuffer, bytesToCopy);
            bufferPosition += bytesToCopy;
        }
    }

    // done with the allocated memory, so freeing it
    free(studentInfo);
    free(buffer);

    return 0; // exit successfully
}
