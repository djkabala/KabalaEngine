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
#include "Field.h"


// Static Class Varible implementations: 
const char *Field::_defaultTypeName[] = 
{   
    "bool",
    "Int8",
    "UInt8",
    "Int16",
    "UInt16",
    "Int32",
    "UInt32",
    "Int64", 
    "UInt64", 
    "Real32", 
    "Real64", 
    "Color3f",
    "Color4f",
    "Pnt2f",
    "Pnt3f",
    "Pnt4f",
    "Vec2f",
    "Vec3f",
    "Vec4f",
    "Quaternion",
    "Matrix",
    "std::string",
    "Time",
    "ImagePtr",
    "FieldContainerPtr",
    "NodePtr"
    "void*"
};

const char *Field::_cardinalityName[] = 
{
    "single", 
    "multi"
};

const char *Field::_visibilityName[] = 
{
    "internal", 
    "external"
};

const char *Field::_mtInfluenceName[] =
{
    "cluster", 
    "aspect"
};

const char *Field::_accessName[] = 
{
    "public", 
    "protected", 
    "private"
};

std::vector<std::string> Field::_typeName;

//----------------------------------------------------------------------
// Method: Field
// Author: jbehr
// Date:   Thu Jan  8 19:55:06 1998
// Description:
//         Class Constructor
//----------------------------------------------------------------------
Field::Field(void) :
    _name        (NULL), 
    _cardinality  (   0),
    _type         (   0),
    _visibility   (   1),
    _mtInfluence  (   0),
    _defaultValue (NULL),
    _defaultHeader(NULL), 
    _description  (NULL), 
    _header       (NULL), 
    _access       (   0),
    _publicRead   (false)
{
    
    return;
}

//----------------------------------------------------------------------
// Method: Field
// Author: jbehr
// Date:   Thu Jan  8 19:55:06 1998
// Description:
//         Class Copy Constructor
//----------------------------------------------------------------------

Field::Field(const Field &obj ) : 
    _name        (NULL), 
    _cardinality  (   0),
    _type         (   0),
    _visibility   (   1),
    _mtInfluence  (   0),
    _defaultValue (NULL),
    _defaultHeader(NULL), 
    _description  (NULL), 
    _header       (NULL), 
    _access       (   0)
{
    *this = obj;

    _type = NULL;

    setType(obj._type);
}

//----------------------------------------------------------------------
// Method: ~Field
// Author: jbehr
// Date:   Thu Jan  8 19:55:06 1998
// Description:
//         Class Descructor
//----------------------------------------------------------------------

Field::~Field(void)
{
    setName         (0);
    setType         (0);
    setDescription  (0);
    setDefaultValue (0);
    setDefaultHeader(0);
    setHeader       (0);
}

//----------------------------------------------------------------------
// Method: loadDefaultFieldTypeList
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------

int Field::loadDefaultFieldTypeList(void)
{
    int n = sizeof(_defaultTypeName)/sizeof(char*);

    _typeName.clear();

    for(int i = 0; i < n; ++i) 
    {
        _typeName.push_back(_defaultTypeName[i]);
    }

    return _typeName.size();
}

//----------------------------------------------------------------------
// Method: loadFileTypeList
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------

int Field::loadFieldTypeList(const char *fileName)
{
    ifstream sin(fileName);
    std::string str;

    if (sin) {
        _typeName.clear();
        while (true) {
            sin >> str;
            if (sin.eof()) 
                break;
            else 
                _typeName.push_back(str);
        }
    }

    return _typeName.size();
}

//----------------------------------------------------------------------
// Method: type
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *Field::typeStr(int i)
{
    int vecSize = _typeName.size();

    return (i >= 0 && i < vecSize) ? _typeName[i].c_str() : 0;
}

//----------------------------------------------------------------------
// Method: cardinality
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *Field::cardinalityStr(int i)
{
    int vecSize = sizeof(_cardinalityName )/ sizeof(char*);

    return (i >= 0 && i < vecSize) ? _cardinalityName[i] : 0;
}

//----------------------------------------------------------------------
// Method: visibility
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *Field::visibilityStr(int i)
{
    int vecSize = sizeof(_visibilityName )/ sizeof(char*);

    return (i >= 0 && i < vecSize) ? _visibilityName[i] : 0;
}

//----------------------------------------------------------------------
// Method: access
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *Field::accessStr(int i)
{
    int vecSize = sizeof(_accessName )/ sizeof(char*);

    return (i >= 0 && i < vecSize) ? _accessName[i] : 0;
}

//----------------------------------------------------------------------
// Method: cardinality
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *Field::cardinalityStr(void)
{
    return cardinalityStr(_cardinality);
}

//----------------------------------------------------------------------
// Method: visibility
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *Field::visibilityStr(void)
{
    return visibilityStr(_visibility);
}

//----------------------------------------------------------------------
// Method: access
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *Field::accessStr(void)
{
    return accessStr(_access);
}

//----------------------------------------------------------------------
// Method: setName
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute name
//----------------------------------------------------------------------
void Field::setName (const char* name )
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
// Method: setDefaultValue
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute description
//----------------------------------------------------------------------
void Field::setDefaultValue (const char* defaultValue )
{
    delete [] _defaultValue;
    
    if (defaultValue && *defaultValue && strcmp(defaultValue,FieldContainer::_nil)) {
        _defaultValue = new char [strlen(defaultValue)+1];
        strcpy(_defaultValue,defaultValue);
    }
    else 
        _defaultValue = 0;
}

//----------------------------------------------------------------------
// Method: setDefaultHeader
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// DefaultHeader:
//         set method for attribute defaultHeader
//----------------------------------------------------------------------
void Field::setDefaultHeader ( const char* defaultHeader )
{
    delete [] _defaultHeader;
    
    if (defaultHeader && *defaultHeader && strcmp(defaultHeader,FieldContainer::_nil)) 
    {
        _defaultHeader = new char [strlen(defaultHeader)+1];
        strcpy(_defaultHeader,defaultHeader);
        
        char *c;
        while(c = strstr(_defaultHeader, "&quot;"))
        {
            *c = '"';
            memcpy(c+1, c+6, strlen(c+6) + 1);
        }
        while(c = strstr(_defaultHeader, "&lt;"))
        {
            *c = '<';
            memcpy(c+1, c+4, strlen(c+4) + 1);
        }
        while(c = strstr(_defaultHeader, "&gt;"))
        {
            *c = '>';
            memcpy(c+1, c+4, strlen(c+4) + 1);
        }
    }
    else
        _defaultHeader = 0;
}

//----------------------------------------------------------------------
// Method: setDescription
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute description
//----------------------------------------------------------------------
void Field::setDescription ( const char* description )
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

void Field::setPublicRead (const char* str )
{
    if ( ! strcasecmp(str, "true" ) )
        _publicRead = true;
    else if ( ! strcasecmp(str, "false" ) )
        _publicRead = false;
    else
    {
        cerr << "FieldContainer::setPublicRead: string " << str 
             << " not recognized!" << endl;
    }
}

//----------------------------------------------------------------------
// Method: setHeader
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// header:
//         set method for attribute header
//----------------------------------------------------------------------
void Field::setHeader ( const char* header )
{
    delete [] _header;
    
    if (header && *header && strcmp(header,FieldContainer::_nil) &&
        strcmp(header,"auto") ) 
    {
        _header = new char [strlen(header)+1];
        strcpy(_header,header);
        
        char *c;
        while(c = strstr(_header, "&quot;"))
        {
            *c = '"';
            memcpy(c+1, c+6, strlen(c+6) + 1);
        }
    }
    else
        _header = 0;
}

//----------------------------------------------------------------------
// Method: setType
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute type
//----------------------------------------------------------------------
void Field::setType ( const char* type )
{
    delete [] _type;
    
    if (type && *type && strcmp(type,FieldContainer::_nil) ) 
    {
        _type = new char [strlen(type)+1];
        strcpy(_type,type);
    }
    else
        _type = 0;
}

//----------------------------------------------------------------------
// Method: setCardinality
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute cardinality
//----------------------------------------------------------------------
void Field::setCardinality ( const char* cardinalityStr ) 
{
    int i, n = sizeof(_cardinalityName)/sizeof(char*);

    for (i = 0; i < n; ++i) 
        if (!strcasecmp(cardinalityStr, _cardinalityName[i]))
        {
            _cardinality = i;
            break;
        }

    if ( i == n )
    {
        cerr << "Field::setCardinality: string '" << cardinalityStr << "' is unknown!" 
             << endl;
        _cardinality = 0;
    }
}

//----------------------------------------------------------------------
// Method: setVisibility
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute visibility
//----------------------------------------------------------------------

void Field::setVisibility(const char *visibilityStr)
{
    int i = 0;
    int n = sizeof(_visibilityName) / sizeof(char *);

    for(i = 0; i < n; ++i) 
    {
        if(strcasecmp(visibilityStr, _visibilityName[i]) == 0)
        {
            _visibility = i;
            break;
        }
    }

    if(i == n)
    {
        cerr << "Field::setVisibility: string '" 
             << visibilityStr 
             << "' is unknown!" 
             << endl;

        _visibility = 1;
    }
}

int Field::getMTInfluence(void)
{
    return _mtInfluence;
}

void Field::setMTInfluence(const char *influenceStr)
{
    int i = 0;
    int n = sizeof(_mtInfluenceName) / sizeof(char *);

    for(i = 0; i < n; ++i)
    {
        if(strcasecmp(influenceStr, _mtInfluenceName[i]) == 0)
        {
            _mtInfluence = i;
            break;
        }
    }

    fprintf(stderr, "serInf %s : %d\n", influenceStr, _mtInfluence);

    if(i == n)
    {
        cerr << "Field::setMTInfluence: string '" 
             << influenceStr 
             << "' is unknown!" 
             << endl;

        _visibility = 1;
    }
}

//----------------------------------------------------------------------
// Method: setAccess
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute cardinality
//----------------------------------------------------------------------
void Field::setAccess ( const char* accessStr ) 
{
    int i, n = sizeof(_accessName)/sizeof(char*);

    for (i = 0; i < n; ++i) 
        if (!strcasecmp(accessStr, _accessName[i]))
        {
            _access = i;
            break;
        }

    if ( i == n )
    {
        cerr << "Field::setAccess: string '" << accessStr << "' is unknown!" << endl;
        _access = 0;
    }
}

//----------------------------------------------------------------------
// Method: getLine
// Author: jbehr
// Date:   Thu Jan  8 19:55:06 1998
// Description:
//         
//----------------------------------------------------------------------
bool Field::getLine (char *line)
{
    char * def;
    def = new char [ (_defaultValue ? strlen( _defaultValue) : 0 ) + 
                      (_defaultHeader ? strlen( _defaultHeader) : 0 ) +
                      16 
                    ];
    if ( _defaultHeader && *_defaultHeader )
    {
        if ( _defaultValue && *_defaultValue )
            sprintf( def, "%s (%s)", _defaultValue, _defaultHeader );
        else
            sprintf( def, "None" );
    }
    else                
    {
        if ( _defaultValue && *_defaultValue )
            sprintf( def, "%s", _defaultValue );
        else
            sprintf( def, "None" );
    }   
                
    sprintf ( line, "%s %s %s %s %s %s %s, %s" , 
                        (_name && *_name) ? _name : "None",
                        cardinalityStr(), 
                        (_type && *_type) ? _type : "bool",
                        visibilityStr(), accessStr(), 
                        (_header && *_header) ? _header : "auto", 
                        def, 
                        (_description   && *_description) ? _description : "None");

    delete [] def;
    return true;
}

//----------------------------------------------------------------------
// Method: operator=
// Author: jbehr
// Date:   Thu Jan  8 19:55:06 1998
// Description:
//         
//----------------------------------------------------------------------
Field &Field::operator =(const Field &obj)
{
    if(this == &obj)
        return *this;

    setName         (obj._name);
    setType         (obj._type);
    setDefaultValue (obj._defaultValue);
    setDefaultHeader(obj._defaultHeader);
    setDescription  (obj._description);
    setHeader       (obj._header);

    _cardinality = obj._cardinality;
    _visibility  = obj._visibility;
    _mtInfluence = obj._mtInfluence;
    _access      = obj._access;

    return *this;
}

//----------------------------------------------------------------------
// Method: operator== 
// Author: jbehr
// Date:   Thu Jan  8 19:55:06 1998
// Description:
//         
//----------------------------------------------------------------------
bool Field::operator== (const Field &obj)
{
    return ( strcmp(_name,          obj._name         ) == 0 &&
             strcmp(_type,          obj._type         ) == 0 &&
             strcmp(_defaultValue,  obj._defaultValue ) == 0 &&
             strcmp(_defaultHeader, obj._defaultHeader) == 0 &&
             strcmp(_description,   obj._description  ) == 0 &&
             strcmp(_header,        obj._header       ) == 0 &&

            _cardinality == obj._cardinality                 &&
            _visibility  == obj._visibility                  &&
            _mtInfluence == obj._mtInfluence                 &&
            _access      == obj._access                        );
}
