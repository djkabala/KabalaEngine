/*

    Interessant ist nur die Klasse ParseComandLine.

    Von aussen erreichbare Methoden sind:

       - ParseComandLine()    - Der Constructor
       - isSet()
       - getArgument()

*/


#ifndef _PARSE_CMD_LINE_H_
#define _PARSE_CMD_LINE_H_

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#ifndef WIN32
#include <unistd.h>
#endif

#define     NONE   0
#define     BOOL   1
#define     CHAR   2
#define     INT    3
#define     LONG   4
#define     FLOAT  5
#define     DOUBLE 6
#define     STRING 7

class ParseOption {
   
 private:
   
   char * _name;
   char * _arg;
   
   bool     _arg1;
   char    _arg2;
   int     _arg3;
   long    _arg4;
   float   _arg5;
   double  _arg6;
   char*   _arg7;
   
 public:

   ParseOption(char *name, char *arg, bool set);

   void *convertArg(int type);
   
   char *getOptName(void) { return _name;};
};

typedef ParseOption* ParseOpt_Ptr;



class ParseComandLine {
   
 private:
   
   int              _numopt;
   char*            _progname;
   ParseOpt_Ptr*    _options;
   
 public:
   
   ParseComandLine(int argc, char **argv);
   
	 bool isSet(char* option);

   void *getArgument(char *option, int type);
   
   char *getProgName(void) {return _progname;};
   
};

#endif
