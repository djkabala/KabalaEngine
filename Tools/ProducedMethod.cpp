// System declarations
#include <iostream>
#include <stdio.h>
#include <string.h>

#ifdef WIN32
#define strcasecmp _stricmp
#endif

// Application dectlarations

using namespace std;

// Class declarations
#include "FieldContainer.h"
#include "ProducedMethod.h"

//----------------------------------------------------------------------
// Method: ProducedMethod
// Author: dkabala
// Description:
//         Class Constructor
//----------------------------------------------------------------------
ProducedMethod::ProducedMethod(void) :
    _name        (NULL), 
    _producedEventType         (   0),
    _description  (NULL)
{
    
    return;
}

//----------------------------------------------------------------------
// Method: ProducedMethod
// Author: dkabala
// Description:
//         Class Copy Constructor
//----------------------------------------------------------------------

ProducedMethod::ProducedMethod(const ProducedMethod &obj ) : 
    _name        (NULL), 
    _producedEventType         (   0),
    _description  (NULL)
{
    *this = obj;

    _producedEventType = NULL;

    setProducedEventType(obj._producedEventType);
}

//----------------------------------------------------------------------
// Method: ~ProducedMethod
// Author: dkabala
// Description:
//         Class Descructor
//----------------------------------------------------------------------

ProducedMethod::~ProducedMethod(void)
{
    setName         (0);
    setProducedEventType         (0);
    setDescription  (0);
}

//----------------------------------------------------------------------
// Method: setName
// Author: dkabala
// Description:
//         set method for attribute name
//----------------------------------------------------------------------
void ProducedMethod::setName (const char* name )
{
    delete [] _name;
    
    if (name && *name && strcmp(name,FieldContainer::_nil)) {
        _name = new char [strlen(name)+1];
        strcpy(_name,name);
    }
    else
        _name = 0;
}

//----------------------------------------------------------------------
// Method: setDescription
// Author: dkabala
// Description:
//         set method for attribute description
//----------------------------------------------------------------------
void ProducedMethod::setDescription ( const char* description )
{
    delete [] _description;
    
    if (description && *description && strcmp(description,FieldContainer::_nil)) {
        _description = new char [strlen(description)+1];
        strcpy(_description,description);
        // On Win32 some garbage is added to the end
        for ( char *p = strchr( _description, 0 ) - 1; 
              p >= _description && ( *p == 0x09 || *p == 0x20 );
              p-- )
            *p = 0;
    }
    else
        _description = 0;
}

//----------------------------------------------------------------------
// Method: setProducedEventType
// Author: dkabala
// Description:
//         set method for attribute type
//----------------------------------------------------------------------
void ProducedMethod::setProducedEventType ( const char* type )
{
    delete [] _producedEventType;
    
    if (type && *type && strcmp(type,FieldContainer::_nil) ) 
    {
        _producedEventType = new char [strlen(type)+1];
        strcpy(_producedEventType,type);
    }
    else
        _producedEventType = 0;
}

//----------------------------------------------------------------------
// Method: getLine
// Author: dkabala
// Description:
//         
//----------------------------------------------------------------------
bool ProducedMethod::getLine (char *line)
{
    sprintf ( line, "%s %s, %s" , 
                        (_name && *_name) ? _name : "None",
                        (_producedEventType && *_producedEventType) ? _producedEventType : "bool",
                        (_description   && *_description) ? _description : "None");

    return true;
}

//----------------------------------------------------------------------
// Method: operator=
// Author: dkabala
// Description:
//         
//----------------------------------------------------------------------
ProducedMethod &ProducedMethod::operator =(const ProducedMethod &obj)
{
    if(this == &obj)
        return *this;

    setName         (obj._name);
    setProducedEventType         (obj._producedEventType);
    setDescription  (obj._description);

    return *this;
}

//----------------------------------------------------------------------
// Method: operator== 
// Author: dkabala
// Description:
//         
//----------------------------------------------------------------------
bool ProducedMethod::operator== (const ProducedMethod &obj)
{
    return ( strcmp(_name,          obj._name         ) == 0 &&
             strcmp(_producedEventType,          obj._producedEventType         ) == 0 &&
             strcmp(_description,   obj._description  ) == 0);

}

