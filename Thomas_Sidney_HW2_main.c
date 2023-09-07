/**************************************************************
 * Class:  CSC-415-01# Summer 2021
 * Name: Sidney Thomas
 * Student ID: 918656419
 * GitHub Name: bierman
 * Project: Assignment 2 – Command Line Arguments
 *
 * File: Thomas_Sidney_HW2_main.c
 *
 * Description: This C program demonstrates the use of command-line arguments to collect and process
 * personal information and data. The program performs the following:
 *
 * 1. Allocates memory to store personal information, such as the first name etc...
 * 2. Populates the personalInfo structure with data retrieved from command-line arguments.
 * 3. Calls the writePersonalInfo function to perform some write operation with the personalInfo data.
 * 4. Allocates a buffer for data processing.
 * 5. Retrieves strings of data  using the getNext function and processes them.
 * 6. Manages the buffer to  store and commit data in smaller chunks.
 * 7. Commits data  using the commitBlock function when the buffer is full.
 * 8. Ensures that any remaining data in the buffer is properly committed before the program exits.
 * 9. Frees allocated memory to prevent memory leaks.
 * 10. Returns an exit status code based on the result of the checkIt function.
 *
 **************************************************************/

#include <stdio.h>  // library for input/output
#include <stdlib.h> // library for memory management
#include <string.h>
#include "assignment2.h"

int main(int argc, char *argumentValues[])
{
    // allocating memory for storing personalInfo
    personalInfo *studentInfo = (personalInfo *)malloc(sizeof(personalInfo));

    // studentInfo memory allocattion check
    if (studentInfo == NULL)
    {
        // handle memory allocation failure
        printf("studentInfo is NULL!");
        return 1; // exit with an error code
    }

    // populating personalInfo with data from command-line arguments
    studentInfo->firstName = argumentValues[1];
    studentInfo->lastName = argumentValues[2];
    studentInfo->studentID = 918656419;
    studentInfo->level = SENIOR;
    studentInfo->languages = KNOWLEDGE_OF_C | 
                             KNOWLEDGE_OF_JAVA |
                             KNOWLEDGE_OF_JAVASCRIPT | 
                             KNOWLEDGE_OF_CPLUSPLUS | 
                             KNOWLEDGE_OF_HTML | 
                             KNOWLEDGE_OF_MIPS_ASSEMBLER;
    strcpy(studentInfo->message, argumentValues[3]);


    // allocate a buffer for data processing
    int writeSuccess = writePersonalInfo(studentInfo);


    // create a buffer of size BLOCK_SIZE using malloc.
    char *buffer = malloc(BLOCK_SIZE * sizeof(char));

    // buffer memory allocation check
    if (buffer == NULL)
    {
        perror("Failed to allocate memory for the buffer");
        exit(1); // exit the program with an error code.
    }

    // initialize variables to keep track of the buffer position and data written
    size_t bufferPosition = 0; 
    size_t dataWritten = 0;    

    // get the next string
    const char *nextString = getNext();
    while (nextString != NULL)
    {
        
        // process each received string in this loop.
        size_t stringLength = strlen(nextString);
        size_t spaceLeftInBuffer = BLOCK_SIZE - bufferPosition;


        // check if the string can fit in the remaining space in the buffer.
        if (stringLength <= spaceLeftInBuffer)
        {
            // the entire string fits in the remaining space, so copy it to the buffer.
            memcpy(buffer + bufferPosition, nextString, stringLength); // copy string into buffer starting at current buffer position
            bufferPosition += stringLength; // buffer position point to the next available position in buffer
        }
        else
        {
            // the string is larger than the remaining space in the buffer
            // copy as much as possible into the buffer and commit the buffer
            size_t bytesToCopy = spaceLeftInBuffer; // calculates the number of bytes to copy into the buffer

            // copy the calculated number of bytes from nextString to the buffer, 
            // starting at the current buffer position
            memcpy(buffer + bufferPosition, nextString, bytesToCopy);

            // updates the buffer position
            bufferPosition += bytesToCopy; 
            
            // commit the filled buffer using commitBlock.
            commitBlock(buffer);

            // reset the buffer position and copy the remaining part of the string.
            bufferPosition = 0;
            
            // continue copying the remaining part of the string in smaller chunks.
            size_t remainingBytesToCopy = stringLength - spaceLeftInBuffer;

            while (remainingBytesToCopy > 0)
            {
                // determine the size of the next data chunk to copy
                // either set to the remaining bytes to copy if they are less than the block size BLOCK SIZE
                // or it is set to the block size if there are more bytes remaining than the block size
                size_t chunkSize = (remainingBytesToCopy < BLOCK_SIZE) ? remainingBytesToCopy : BLOCK_SIZE;

                // copy the chunk of data from 'nextString' to 'buffer'
                memcpy(buffer, nextString + stringLength - remainingBytesToCopy, chunkSize);

                // update the remaining bytes to copy
                remainingBytesToCopy -= chunkSize;

                // update the buffer position
                bufferPosition = chunkSize;

                // check if the buffer needs to be commited
                if(bufferPosition == 256){
                commitBlock(buffer);
                } 
            }
        }
        nextString = getNext();
    }

    // commit remaining data into the buffer
    if(bufferPosition){
        commitBlock(buffer);
    }

    // free allocated memory
    free(studentInfo);
    free(buffer);

    return checkIt(); // exit successfully
}
