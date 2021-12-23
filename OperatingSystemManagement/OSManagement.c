/*
    *****************************************
    * Joshua Wood                           *
    * CGS 3763                              *
    * 11/21/2021                            *
    * Assignment 7 - OS Management Project  *
    *****************************************

    ========================
    Section 1: Preprocessors
    ========================

    Subsections:
        - C Libraries
        - Macros
        - Function Prototypes

    Functions Prototypes:
        name: displayMenu
        returns: int
        parameters: None

        name: clearScreen
        returns: void
        parameters: None

        name: memoryManagement
        returns: void
        parameters: None

        name: displayProcess
        returns: void
        parameters: Array, int, Array

        name: firstFit
        returns: void
        parameters: Array, int, Array, int

        name: worstFit
        returns: void
        parameters: Array, int, Array, int

        name: bestFit
        returns: void
        parameters: Array, int, Array, int

        name: nextFit
        returns: void
        parameters: Array, int, Array, int

        name: printAttributes
        returns: void
        parameters: Array (char), struct stat

        name: fileAttributes
        returns: void
        parameters: None

        name: multiThreads
        returns: void
        parameters: None

        name: threadFunction
        returns: void *
        parameters: void *
*/

// C Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>

// Macros (Global Constants)
const int EXIT = 0;
const int INVALID = -1;
const int MEMORY = 1;
const int FILES = 2;
const int THREAD = 3;
const int FIRST = 0;
const int BEST = 1;
const int WORST = 2;
const int NEXT = 3;

// Function Prototypes
int displayMenu();
void clearSreen();
void memoryManagement();
void displayProcess(int[], int, int[]);
void firstFit(int[], int, int[], int);
void worstFit(int[], int, int[], int);
void bestFit(int[], int, int[], int);
void nextFit(int[], int, int[], int);
void printAttributes(char [], struct stat);
void fileAttributes();
void multiThreads();
void * threadFunction(void *);

/*
    ========================
    Section 2: Main Function
    ========================

    Functions:
        Main - Collects the users choice and decides on which route to take

    Variables:
        name: usrChoice
        type: int
        desc: Used to store the user's menu selection
        initial: -1
*/
int main ()
{
    int usrChoice = -1;

    while (usrChoice != 0) // Loop continues while usrChoice does not equal zero
    {
        usrChoice = displayMenu(); // Sets usrChoice to the value returned by function displayMenu

        if (usrChoice == MEMORY) // If usrChoice equals 1, call function memoryManagement
        {
            memoryManagement();
        }
        else if (usrChoice == FILES) // If usrChoice equals 2, call function fileAttributes
        {
            fileAttributes();
        }
        else if (usrChoice == THREAD) // If usrChoice equals 3, call function multiThreads
        {
            multiThreads();
        }
        else if (usrChoice == EXIT) // If usrChoice equals 0, exit the program with argument 0
        {
            exit(EXIT);
        }
    }
    return 0; // Returns 0;
}

/*

    ===========================
    Section 3: Helper Functions
    ===========================

    Functions:
        displayMenu - Displays the Operating System Management Menu for the user and collects the users choice
        clearScreen - Clears the terminal of any text after printing an error message. User must hit enter to continue.

    Variables:
        name: usrChoice
        type: int
        desc: Used to store the user's menu selection
        initial: -1

        name: tmp
        type: char
        desc: Used to store the user's input
        initial: None
*/

int displayMenu()
{
    int usrChoice = -1;

    while (usrChoice == -1) // Loops while usrChoice equals -1
    {
        printf("\n\n\t********** Operating System Management Menu **********\n\n");
        printf("Select the OS Program to run; enter the number of your selection\n");
        printf("1). Memory Management\n");
        printf("2). File Management\n");
        printf("3). Multithreading\n");
        printf("0). Exit\n\n");

        printf("=> ");
        scanf("%d", &usrChoice); // Scans in the users input

        if (usrChoice < 0 || usrChoice > 3) // If usrChoice is an invalid input (Less than 0 or greater than 3), call function clearScreen and reset usrChoice to -1
        {
            clearSreen();
            usrChoice = -1;
        }
    }
    return usrChoice; // Return the value usrChoice
}

void clearSreen()
{
    printf("\nError! Reference source not found.\n\n");

    char tmp;

    scanf("%c[^\n]", &tmp); // Scans in the users input

    // system("clear");
    system("cls"); // Calls in system command with argument "cls" for Windows
}

/*

    ====================================
    Section 4: Memory Management Section
    ====================================

    Functions:
        memoryManagement - When called, this function loops through each of the four different memory management algorithms and calls their corresponding function

    Variables:
        name: algo
        type: int
        desc: Used as the loop variable that increments by one after every pass
        initial: 0

        name: blockSize
        type: One-dimensional array
        desc: Used to store the sizes of the memory blocks
        initial: 15, 10, 20, 35, 80

        name: processSize
        type: One-dimensional array
        desc: Used to store the sizes of the processes
        initial: 10, 20, 5, 30, 65

        name: blocks
        type: int
        desc: Used to store the numbers of blocks
        initial: sizeof(blockSize) / sizeof(blockSize[0])

        name: processes
        type: int
        desc: Used to store the numbers of processes
        initial: sizeof(processSize) / sizeof(processSize[0])

*/
void memoryManagement()
{
    clearSreen(); // Calls the function clearScreen

    printf("\t********** Memory Management **********\n\n");

    for (int algo = 0; algo < 4; algo++) // Loops until algo is equal to 4, then stops. Increments by 1.
    {
        // Initialize variables
        int blockSize[] = { 15, 10, 20, 35, 80 };
        int processSize[] = { 10, 20, 5, 30, 65 };
        int blocks = sizeof(blockSize) / sizeof(blockSize[0]);
        int processes = sizeof(processSize) / sizeof(processSize[0]);

        if (algo == FIRST) // If algo is equal to macro FIRST (0), call the function firstFit with parameters blockSize, blocks, processSize, processes
        {
            printf("\n\t********** First Fit **********\n\n");
            firstFit(blockSize, blocks, processSize, processes);
        }
        if (algo == BEST) // If algo is equal to macro BEST (1), call the function bestFit with parameters blockSize, blocks, processSize, processes
        {
            printf("\n\t********** Best Fit **********\n\n");
            bestFit(blockSize, blocks, processSize, processes);
        }
        if (algo == WORST) // If algo is equal to macro WORST (2), call the function worstFit with parameters blockSize, blocks, processSize, processes
        {
            printf("\n\t********** Worst Fit **********\n\n");
            worstFit(blockSize, blocks, processSize, processes);
        }
        if (algo == NEXT) // If algo is equal to macro NEXT (3), call the function nextFit with parameters blockSize, blocks, processSize, processes
        {
            printf("\n\t********** Next Fit **********\n\n");
            nextFit(blockSize, blocks, processSize, processes);
        }
    }
}

/*
    =======================================
    Section 5: Memory Management Algorithms
    =======================================

    Functions:
        nextFit -
            a. Input memory blocks with size and processes with size.
            b. Initialize all memory blocks as free.
            c. Start by picking each process and check if it can be assigned to the current block, if yes,
                allocate it the required memory and check for next process but from the block where we
                left not from starting.
            d. If the current block size is smaller then keep checking the further blocks.

        firstFit -
            a. Input memory blocks with size and processes with size.
            b. Initialize all memory blocks as free.
            c. Start by picking each process and check if it can be assigned to current block.
            d. If size-of-process <= size-of-block if yes then assign and check for next process.
            e. If not then keep checking the further blocks.

        bestFit -
            a. Input memory blocks with size and processes with size.
            b. Initialize all memory blocks as free.
            c. Start by picking each process and find the minimum block size that can be assigned to
                current process i.e., find min(blockSize[1], blockSize[2],.....blockSize[n]) > processSize[current],
                if found then assign it to the current process.
            d. If not, then leave that process and keep checking the further processes.

        worstFit -
            a. Input memory blocks with size and processes with size.
            b. Initialize all memory blocks as free.
            c. Start by picking each process and find the maximum block size that can be assigned to
                current process i.e., find max(blockSize[1], blockSize[2],.....blockSize[n]) > processSize[current],
                if found then assign it to the current process.
            d. If not, then leave that process and keep checking the further processes.

    Variables:
        name: allocation
        type: One-dimensional array
        desc: Used to store the block id that a process is allocated to
        initial: None

        name: id
        type: int
        desc: Used to store the block allocation for a process
        initial: 0

        name: bestIdx
        type: int
        desc: Used to store the current best fit value
        initial: INVALID(-1)

        name: worstIdx
        type: int
        desc: Used to store the current worst fit value
        initial: INVALID(-1)

    Parameters:
        blockSize - Used to store the sizes of the memory blocks
        blocks - Used to store the numbers of blocks
        processSize - Used to store the sizes of the processes
        processes - Used to store the numbers of processes
*/

void nextFit(int blockSize[], int blocks, int processSize[], int processes)
{
    // Initialize variables
    int allocation[processes];
    int id = 0;

    memset(allocation, INVALID, sizeof(allocation));

    for (int i = 0; i < processes; i++) // Loops through the number of process, incrementing by 1
    {
        while (id < blocks) // Loops while id is less than the number of blocks
        {
            if (blockSize[id] >= processSize[i]) // If blockSize with index id is greater than or equal to the current process size ...
            {
                allocation[i] = id; // Update the allocation array and set the element of index in the outer loop to variable id
                blockSize[id] -= processSize[i]; // Reduce available memory of the current blockSize by the processSize
                break; // Breaks out of the inner loop
            }
            id = (id + 1) % blocks; // Update value of id to next index in array blockSize by adding 1 to id then modulus the total number of blocks
        }
    }
    displayProcess(allocation, processes, processSize); // Calls the function displayProcess with arguments allocation, processes, and processSize
}

void firstFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[processes];

    memset(allocation, INVALID, sizeof(allocation));

    for (int i = 0; i < processes; i++) // Loops through the number of processes, incrementing by 1
    {
        for (int j = 0; j < blocks; j++) // Loop through the number of blocks, incrementing by 1
        {
            if (blockSize[j] >= processSize[i]) // If blockSize with index of inner loop is greater than or equal to the current processSize ...
            {
                allocation[i] = j; // Update the allocation array and set the element at index of outer loop equal to the inner looping variable
                blockSize[j] -= processSize[i]; // Reduce available memory of the current blockSize by the processSize
                break; // Breaks out of the inner loop
            }
        }
    }
    displayProcess(allocation, processes, processSize); // Calls the function displayProcess with arguments allocation, processes, and processSize
}

void bestFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[processes];

    memset(allocation, INVALID, sizeof(allocation));

    for (int i = 0; i < processes; i++) // Loops through the number of processes, incrementing by 1
    {
        int bestIdx = INVALID; // Declare bestIdx variable

        for (int j = 0; j < blocks; j++) // Loops through the number of blocks, incrementing by 1
        {
            if (blockSize[j] >= processSize[i]) // If blockSize with index of inner loops is greater than or equal to the current processSize ...
            {
                if (bestIdx == INVALID) // If bestIdx is equal to INVALID (-1) ...
                {
                    bestIdx = j; // Set bstIdx equal to the current block
                }
                else if (blockSize[bestIdx] > blockSize[j]) // Else if blockSize at index bestIdx is greater than the value of blockSize of inner looping variable ...
                {
                    bestIdx = j; // Set bstIdx equal to the current block
                }
            }
        }

        if (bestIdx != INVALID) // If bestIdx does not equal INVALID(-1) ...
        {
            allocation[i] = bestIdx; // Update allocation array at index of outer loop to bestIdx
            blockSize[bestIdx] -= processSize[i]; // Reduce available memory of the current blockSize by the processSize
        }
    }
    displayProcess(allocation, processes, processSize); // Calls the function displayProcess with arguments allocation, processes, and processSize
}

void worstFit(int blockSize[], int blocks, int processSize[], int processes)
{
    int allocation[processes];

    memset(allocation, INVALID, sizeof(allocation));

    for (int i = 0; i < processes; i++) // Loops through the number of processes, increment by 1
    {
        int wstIdx = INVALID; // Declare wstInd variable

        for (int j = 0; j < blocks; j++) // Loops through the number of blocks, increment by 1
        {
            if (blockSize[j] >= processSize[i]) // If blockSize with index of inner loops is greater than or equal to the current processSize ...
            {
                if (wstIdx == INVALID) // If wstIdx is equal to INVALID (-1) ...
                {
                    wstIdx = j; // Set wstIdx equal to the current block
                }
                else if (blockSize[wstIdx] < blockSize[j]) // Else if blockSize at index wstIdx is less than the value of blockSize of inner looping variable ...
                {
                    wstIdx = j; // Set wstIdx equal to the current block
                }
            }
        }
        if (wstIdx != INVALID) // If wstIdx does not equal INVALID(-1) ...
        {
            allocation[i] = wstIdx; // Update allocation array at index of outer loop to wstIdx
            blockSize[wstIdx] -= processSize[i]; // Reduce available memory of the current blockSize by the processSize
        }
    }
    displayProcess(allocation, processes, processSize); // Calls the function displayProcess with arguments allocation, processes, and processSize
}

/*

    ==========================
    Section 6: File Attributes
    ==========================

    Functions:
        fileAttributes - Function designed to replicate the behavior of the file control block (FCB) on an operating system.

        printAttributes - Prints out all the file attributes within the directory the program is running

    Variables:
        name: statBuff
        type: struct stat
        desc: Stores the attribute structure
        initial: None

        name: err
        type: int
        desc: Stores an error code
        initial: None

        name: de
        type: struct dirent *
        desc: Pointer
        initial: None

        name: dr
        type: DIR *
        desc: Indicates the current directory
        initial: opendir(".")

        name: t
        type: time_t
        desc: Used for obtaining data involving time
        initial: None

        name: timeStr
        type: char[100]
        desc: Stores the time in a string
        initial: None

*/
void fileAttributes()
{
    /*
        Variable Declaration
    */
    struct stat statBuff;
    int err;
    struct dirent * de;
    DIR *dr = opendir(".");

    if (dr == NULL) { // If the DIR variable dr is equal to NULL ...
        printf("Could not open current directory"); // Output to the console "Could not open current directory"
    }

    while (de = readdir(dr)) { // While reading the directing contents and NOT NULL ...
        err = stat(de->d_name, &statBuff); // Set the variable err equal to function call stat() passing arguments: d_name of the directory entry and the struct stat statBuff

        if (err == INVALID) { // If err is equal to INVALID (-1), indicating the file could not be accessed, then output the following ....
            printf("Error in stat\n");
            printf("Press \'Enter\' to continue");
            getchar(); // Call function getchar
        }
        printAttributes(de->d_name, statBuff); // Call function printAttributes passing arguments: d_name of the directory entry and the struct stat statBuff
    }
}

void printAttributes(char name[], struct stat statBuff)
{
    /*
        Variable Declaration
    */
    time_t t;
    char timeStr[100];
    struct tm dt;
    time(&t);

    printf("\n------------------------------ File = %s ------------------------------", name); // Output the file name

    printf("\n\nDevice ID: %d", &statBuff.st_rdev); // Output the device id

    printf("\nFile Serial Number: %ju", &statBuff.st_ino); // Output the file serial number

    printf("\nFile User ID: %-8d", &statBuff.st_uid); // Output the user id

    printf("\nFile Group ID: %-8d", &statBuff.st_gid); // Output the group id

    printf("\nFile Mode: %d", &statBuff.st_mode); // Output the file mode

    /*
        Evaluate the file mode for owner permissions
    */

    printf("\nOwner permissions: ");

    if (&statBuff.st_mode && S_IRUSR)
        printf("read ");
    if (&statBuff.st_mode && S_IWUSR)
        printf("write ");
    if (&statBuff.st_mode && S_IXUSR)
        printf("execute");

    /*
        Evaluate the file mode for group permissions
    */

    printf("\nGroup permissions: ");

    if (&statBuff.st_mode && S_IRGRP)
        printf("read ");
    if (&statBuff.st_mode && S_IWGRP)
        printf("write ");
    if (&statBuff.st_mode && S_IXGRP)
        printf("execute");

    /*
        Evaluate the file mode for other permissions
    */

    printf("\nOthers permissions: ");

    if (&statBuff.st_mode && S_IROTH)
        printf("read ");
    if (&statBuff.st_mode && S_IWOTH)
        printf("write ");
    if (&statBuff.st_mode && S_IXOTH)
        printf("execute");

    t = statBuff.st_ctime;

    printf("\nDate Created : %s", ctime(&t)); // Output the file created date

    //data modified
    t = statBuff.st_mtime;
    printf("Date Modified : %s", ctime(&t)); // Output the file last modification date

    //last accessed
    t = statBuff.st_atime;
    printf("Time file was last accessed : %s", ctime(&t)); // Output the file last accessed date

    //file size
    printf("File size: %ld\n", statBuff.st_size); // Output the file size
}

/*
    =========================
    Section 7: Multithreading
    =========================

    Functions:
        multiThreads -

        threadFunction - Output when the thread starts, prints, and ends

    Variables:
        name: SIZE
        type: const int
        desc: Stores the numbers of threads created
        initial: 7

        name: i
        type: int
        desc: Looping variable
        initial: None

        name: error
        type: int
        desc: Store the return value from function pthread_create
        initial: None

        name: tid
        type: pthread_t array[7]
        desc: Array used for the function
        initial: None

        name: LOOP
        type: const int
        desc: Used for number of iterations
        initial: 10

        name: myid
        type: int *
        desc: Stores the thread id
        initial: (int *) vargp

    Parameters:

*/
void multiThreads()
{
    const int SIZE = 7;
    int i;
    int error;
    pthread_t tid[7];

    for (i = 0; i < SIZE; i++) {
        error = pthread_create(&tid[i], NULL, &threadFunction, (void *) &tid[i]);

        if (error != 0) // Thread could not be created
            printf("\nThread can't be created: [%s] Press Enter to continue ...", strerror(error));
    }

    for (i = 0; i < SIZE; i++) {
        pthread_join(tid[i], NULL);
    }
}

void * threadFunction(void * vargp)
{
    const int LOOP = 10;
    int i;
    int * myid = (int *) vargp;

    printf("\n------------------------\n");
    printf("Thread ID %d has started", *myid);
    printf("\n------------------------\n");

    for (i = 0; i < LOOP; i++) {
        printf("Thread ID %d is printing\n", *myid);
    }

    printf("-------------------------\n");
    printf("Thread ID %d has finished", *myid);
    printf("\n-------------------------\n");

    return NULL;
}
/*

    ========================
    Section 8: Final Display
    ========================

    Parameters:
        allocation - Used to store the block number allocations
        processes - Contains the number of processes
        processSize - Stores the processes
*/

void displayProcess(int allocation[], int processes, int processSize[])
{
    printf("Process No.\tProcess Size\tBlock No.\n");

    for (int i = 0; i < processes; i++) // Loop through the processes
    {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]); // Display the process number and the process size

        if (allocation[i] == INVALID) // If value is INVALID (-1), output "Not allocated"
        {
            printf("Not allocated\n");
        }
        else // Else ...
        {
            printf("%d\n", allocation[i] + 1); // Output the current allocation
        }
    }
}

/*
    **END OF PROGRAM**

-- Memory Management --

Testing:
* Source compiles with no errors
* Source compiles with no warnings
* Source runs with no errors
* Source includes comments

Perform the following test cases:
<Test Cases>                <Action>                                                            <Expected outcome>
Test Case 1                 Run executable The executable runs                                  The output in the command prompt should be similar to Error! Reference source not found.
Test Case 2                 User enters an invalid menu option value, value 2, or value 3       The output in the command prompt should be similar to Error! Reference source not found.
Test Case 3                 User enters menu option value 1; memoryManagement function          The output in the command prompt should be similar to Figure 2 memoryManagement function output
Test Case 4                 User enters menu option value 1; nextFit function                   The output in the command prompt should be similar to Figure 3 nextFit function output
Test Case 5                 User enters menu option value 1; firstFit function                  The output in the command prompt should be similar to Figure 4 firstFit function output
Test Case 6                 User enters menu option value 1; bestFit function                   The output in the command prompt should be similar to Figure 5 bestFit function output
Test Case 7                 User enters menu option value 1; worstFit function                  The output in the command prompt should be similar to Figure 6 worstFit function output
Test Case 8                 User enters menu option value 0                                     End of functionality; �Process returned 0 (0x0)� displayed in output similar to Figure 7 Successful end of program

-- File Attributes --

Testing:
* Source compiles with no errors
* Source compiles with no warnings
* Source runs with no errors
* Source includes comments

Perform the following test cases:
<Test Cases>               <Action>                                                             <Expected outcome>
Test Case 1                Run executable                                                        The executable runs. The output in the command prompt should be similar to Error! Reference source not found.
Test Case 2                User enters 2 to select File Management                               Console output should be similar to Figure 2 FCB Attributes per File in Directory relative to where the program is running

-- Multi threading --

Testing:
* Source compiles with no errors
* Source compiles with no warnings
* Source runs with no errors
* Source includes comments

Perform the following test cases:
<Test Cases>               <Action>                                                             <Expected outcome>
Test Case 1                Run executable                                                        The executable runs. The output in the command prompt should be similar to Error! Reference source not found.
Test Case 2                User enters 3 to select Multithreading                                Console output should be similar to Figure 2 Multithreads
*/
