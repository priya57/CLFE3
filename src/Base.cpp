#include "Base.h"

#include <stdio.h>
#include <string.h>

int     Base::counter = 0;
char    Base::logFile[256] = {0};
char    Base::msg[256] = {0};

// constructor function:
// called if we create an instance
// here we initialize
Base::Base()
{
    // initialize the log files name
    if (!logFile[0]) strcpy(logFile,"profiles.log");

    // a new instance is created
    counter++;

    // create the output string
    sprintf(msg,"%d instances created.\n",counter);

    // print it!
    appendLog(msg);
}

// destructor function:
// called when the instance is deleted
// for clearing
Base::~Base()
{
    sprintf(msg,"instance %d deleted.\n",counter);
    appendLog(msg);
    counter--;
}

// print a message into the log or/and to screen
int Base::appendLog(char* str)
{
    // print the string to screen
    printf("%s",str);

    // print into the logfile
    //   "a": append
    //   "w": write (creates a new file)
    //   "r": read from a file
    //   "b": binary
    FILE* pHnd = fopen(logFile,"a");
    // check Null-Pointer
    if (!pHnd)  return 0;

    // print into the file
    fprintf(pHnd,"%s",msg);

    // dont forget close
    fclose(pHnd);

    return 1;
}


