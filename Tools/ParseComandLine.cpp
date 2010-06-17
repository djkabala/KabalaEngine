
#include "ParseComandLine.h"

#include <string.h>
#include <iostream>

using namespace std;

/*

   Method:       ParseComandLine(int argc, char **argv)
   Class:        ParseComandLine
   ReturnValue:  None  (Constructor)


   Aufruf ist simpel und eigentlich auch selbsterkl"arend.
   Was main() uebergebenbekommen hat, uebergibt man einfach
   weiter. 

   Achtung: Folgen mehr als ein Argument auf eine Option gehen alle ausser
            dem Ersten verloren.

   Call is simple, probably selfexplainig. Simply pass on, what main() got
   passed.

   Caution: If for one option more than one arguments are passed, all
            but the first are lost.

*/


ParseComandLine::ParseComandLine(int argc, char **argv)
{
   int count = argc-1;
   ParseOption* OptBuffer;
   char *opt, *arg;
   
   _options = NULL;
   _numopt = 0;
   
   _progname = new char[strlen(argv[0]) +1];
   *_progname = '\0';
   if((_progname = strcpy(_progname,argv[0])) == NULL) {
      cerr << "ParseComandLine: Error copying string!!! Exiting...." << endl;
      exit(1);
   }
   
   while(count) {
      arg = NULL;
      if((*argv[argc - count] != '-') && (*argv[argc - count] != '+')) {
	 cerr << "ParseComandLine: Error: Only ONE Arg per option allowed!" << endl;
	 exit(1);
      }
      opt = argv[argc-count]+1;
      count--;
      if(count > 0)
	if((*argv[argc - count] != '-') && (*argv[argc - count] != '+')) {
	   arg = argv[argc-count];
	   count--;
	}
      OptBuffer = new ParseOption(opt,arg,(*(opt-1) == '-' ? false : true));
      _numopt++;
      if((_options = (ParseOption **) 
	  realloc((void *) _options, (_numopt * sizeof(ParseOpt_Ptr)))) == NULL) {
	 cerr << "ParseComandLine: Memory allocation fault !! Exiting ..." <<endl;
      }
      _options[_numopt-1] = OptBuffer;
      OptBuffer = NULL;
   }
}


/*

   Method:       isSet(char *option)
   Class:        ParseComandLine
   ReturnValue:  bool

   Mit dieser Methode ueberprueft man, ob eine bestimmte Option
   benutzte wurde oder nicht. Das ist sinnvoll fuer Optionen 
   ohne Argumente.

   Achtung: der parameter 'option' sollte ein String sein der die
            Option die Ueberprueft werden soll enthaelt, ABER ohne dass
            fuehrende '+' oder '-'.

   Also option = "verbose" testet +verbose und -verbose.

   This Method checks if a specific option was supplied.
   Its useful for options without any arguments.

   Caution: Supplied parameter 'option' must not contain the leading '-' 
            or '+'. It should contain the name of the option.

   Example:  option = 'verbose' checks for +verbose and -verbose


*/



bool ParseComandLine::isSet(char *option)
{
   int i,result;
   bool retval = false;

   if(option)
     for(i=0; i< _numopt;i++) {
       if((result = strcmp(option,_options[i]->getOptName())) == 0) {
	 retval = true;
	 i = _numopt;
       }
     }
   return(retval);
}





/*

   Method:       getArgument(char *option, int type)
   Class:        ParseComandLine
   ReturnValue:  void*

   Mit dieser Methode erhaelt man das Argument einer Option.
   Parameter
      - option wie oben definiert.
      - type = BOOL, INT, ....  siehe define-statements im Header-File.

   liefert einen void - Pointer, der dann mit cast (<typ> *) Zugriff
   auf den jeweiligen Wert erlaubt. (Siehe Doku)

   Im Falle das die Option nicht gesetzt oder kein/ein fehlerhaftes
   Argument uebergeben wurde wird NULL zurueckgeliefert.

   This method returns the argument of an option.
   Parameters:
      - option : same as above.
      - type   : BOOL, INT, ...   as specified with the #define-statements
                 in the header - file.

   The returned value is of type void* which, after casted like (<type>*)
   gives you access to the specific argument.

   If the specefied option was not supplied, or no argument was given
   with it, NULL is returned.
*/



void *ParseComandLine::getArgument(char *option, int type) 
{
   int i,result;

   if(!option) return(NULL);
   
   for(i=0; i< _numopt;i++)
     if((result = strcmp(option,_options[i]->getOptName())) == 0)
       return(_options[i]->convertArg(type));
   return(NULL);
}





ParseOption::ParseOption(char *name, char *arg, bool set)
{
   _arg = NULL;
   _arg1 = set;
   _name = new char[strlen(name)+1];
   *_name = '\0';

   if((_name = strcpy(_name, name)) == NULL) {
      cerr << "ParseOption:Error copying string!!! Exiting...." << endl;
      exit(1);
   }
   if(arg) {
      _arg = new char[strlen(arg)+1];
      if((_arg = strcpy(_arg, arg)) == NULL) {
	 cerr << "ParseOption:Error copying string!!! Exiting...." << endl;
	 exit(1);
      }
   }
}

void *ParseOption::convertArg(int type) 
{
   int result;
   
   if(!_arg && type != BOOL) return(NULL);
   
   switch(type) {
    case NONE:
      return(NULL);
      break;
    case BOOL:
      return((void *) &_arg1);
      break;
    case CHAR:
      if(strlen(_arg) > 2) return(NULL);
      _arg2 = *_arg;
      return((void *) &_arg2);
    case INT:
      result = sscanf(_arg,"%d", &_arg3);
      if(result) return((void *) &_arg3);
      return(NULL);
      break;
    case LONG:
      result = sscanf(_arg,"%ld", &_arg4);
      if(result) return((void *) &_arg4);
      return(NULL);
      break;
    case FLOAT:
      result = sscanf(_arg,"%f", &_arg5);
      if(result) return((void *) &_arg5);
      return(NULL);
      break;
    case DOUBLE:
      result = sscanf(_arg,"%lf", &_arg6);
      if(result) return((void *) &_arg6);
      return(NULL);
      break;
    case STRING:
       return((void *) _arg);
      break;
    default:
      return(NULL);
      break;
   }
}


