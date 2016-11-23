#ifndef BASE_H
#define BASE_H

class Base
{
    public:         // access from outside allowed
        Base();
        virtual ~Base();

        // attributes
        // ----------
        // class attribut exists only once!!!
        static int counter;     // counter for instances

        // output file for the protocol
        static char logFile[256];

        // output buffer, we use for printing
        static char msg[256];

        // methodes
        // --------
        // print data to a file and/or to the screen
        int appendLog(char* str);

        // reset the log file
        static void resetLog();

    protected:      //
    private:
};

#endif // BASE_H
