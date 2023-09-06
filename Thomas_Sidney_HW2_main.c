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
    printf("argumentValues[3]: %s\n", argumentValues[3]);

    printf("firstName is %s\n", studentInfo->firstName);
    printf("lastName is %s\n", studentInfo->lastName);
    printf("studentID is %d\n", studentInfo->studentID);
    printf("gradelevel is %u\n", studentInfo->level);
    printf("message is %s\n", studentInfo->message);

    // ? check that
    // printf("languages is 0x%x\n", studentInfo->languages); // Print as hexadecimal

    // using the allocated memory
    int writeSuccess = writePersonalInfo(studentInfo);

    if (writeSuccess == 0)
    {
        printf("Personal information written successfully\n");
    }
    else
    {
        printf("Failed to write personal information.\n");
    }

    // ...

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

    const char *nextString;
    while ((nextString = getNext()) != NULL)
    {
        // process each received string in this loop.
        size_t stringLength = strlen(nextString);
        size_t spaceLeftInBuffer = BLOCK_SIZE - bufferPosition;

        printf("String Length: %zu\n", stringLength);
        printf("Space Left in Buffer: %zu\n", spaceLeftInBuffer);
        printf("\n");

        // check if the string can fit in the remaining space in the buffer.
        if (stringLength <= spaceLeftInBuffer)
        {
            // the entire string fits in the remaining space, so copy it to the buffer.
            memcpy(buffer + bufferPosition, nextString, stringLength);
            bufferPosition += stringLength;
        }
        else
        {
            // the string is larger than the remaining space in the buffer.
            // copy as much as possible into the buffer and commit the buffer.
            size_t bytesToCopy = spaceLeftInBuffer;
            memcpy(buffer + bufferPosition, nextString, bytesToCopy);
            bufferPosition += bytesToCopy;

            printf("Buffer is filled so committing block\n");
            // commit the filled buffer using commitBlock.
            commitBlock(buffer);

            // reset the buffer position and copy the remaining part of the string.
            bufferPosition = 0;

            // Continue copying the remaining part of the string in smaller chunks.
            size_t remainingBytesToCopy = stringLength - spaceLeftInBuffer;
            printf("Remaining part of string: %zu\n", remainingBytesToCopy);

            while (remainingBytesToCopy > 0)
            {
                size_t chunkSize = (remainingBytesToCopy < BLOCK_SIZE) ? remainingBytesToCopy : BLOCK_SIZE;
                printf("chunk size: %zu\n", chunkSize);

                memcpy(buffer, nextString + stringLength - remainingBytesToCopy, chunkSize);
                remainingBytesToCopy -= chunkSize;
                bufferPosition = chunkSize;

                printf("Buffer is filled so committing block\n");
                // commit the filled buffer using commitBlock.
                commitBlock(buffer);
            }
        }
    }

    checkIt();

    // done with the allocated memory, so freeing it
    free(studentInfo);
    free(buffer);

    return checkIt(); // exit successfully
}
