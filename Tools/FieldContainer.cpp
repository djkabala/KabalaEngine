// System declarations
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "OpenSG/OSGXmlpp.h"

using namespace std;
using namespace xmlpp;

// Application declarations

#ifdef WIN32
#define strcasecmp _stricmp
#define strdup     _strdup
#endif

// Class declarations
#include "FieldContainer.h"

// Include the template strings
#include "FCFieldsTemplate_h.h"
#include "FCBaseTemplate_h.h"
#include "FCBaseTemplate_inl.h"
#include "FCBaseTemplate_cpp.h"
#include "FCTemplate_h.h"
#include "FCTemplate_inl.h"
#include "FCTemplate_cpp.h"


// Static Class Varible implementations: 
const char FieldContainer::_filePrefix    [] = "KE";
const char FieldContainer::_descFileSuffix[] = "fcd";
const char FieldContainer::_decFileSuffix [] = "h";
const char FieldContainer::_inlFileSuffix [] = "inl";
const char FieldContainer::_impFileSuffix [] = "cpp";
const char FieldContainer::_nil           [] = "nil";

FieldContainer::KeyDic FieldContainer::_keyDic[] = 
{
    { FieldContainer::NAME_FIELD,                  "name"                  },
    { FieldContainer::PARENT_FIELD,                "parent"                },
    { FieldContainer::LIBRARY_FIELD,               "library"               }, 
    { FieldContainer::STRUCTURE_FIELD,             "structure"             },
    { FieldContainer::POINTERFIELDTYPES_FIELD,     "pointerfieldtypes"     },
    { FieldContainer::TYPE_FIELD,                  "type"                  },
    { FieldContainer::CARDINALITY_FIELD,           "cardinality"           },
    { FieldContainer::VISIBILITY_FIELD,            "visibility"            },
    { FieldContainer::MT_INFLUENCE_FIELD,          "mtInfluence"           },
    { FieldContainer::DEFAULTVALUE_FIELD,          "defaultValue"          },
    { FieldContainer::DEFAULTHEADER_FIELD,         "defaultHeader"         },
    { FieldContainer::HEADER_FIELD,                "header"                },
    { FieldContainer::ACCESS_FIELD,                "access"                },
    { FieldContainer::SYSTEMCOMPONENT_FIELD,       "systemcomponent"       },
    { FieldContainer::PARENTSYSTEMCOMPONENT_FIELD, "parentsystemcomponent" },
    { FieldContainer::DECORATABLE_FIELD,           "decoratable"           },
    { FieldContainer::USELOCALINCLUDES_FIELD,      "useLocalIncludes"      },
    { FieldContainer::UNKNOWN_FIELD,                NULL                   }
};

const char *FieldContainer::_pointerFieldTypesName[] = 
{
    "none", "single", "multi", "both"
};

const char *FieldContainer::_abstractName[] = 
{
    "concrete", "abstract"
};

//----------------------------------------------------------------------
// Method: FieldContainer
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         Class Constructor
//----------------------------------------------------------------------
FieldContainer::FieldContainer(void) : 
    _name                 (    0), 
    _parentFieldContainer (    0), 
    _description          (    0),
    _library              (    0), 
    _pointerFieldTypes    (    0), 
    _abstract             (    0),
    _mtInfluenceMask      (    0),
    _systemComponent      (false), 
    _parentSystemComponent(true ),
    _fcdFileName          (    0), 
    _decoratable          (false),
    _useLocalIncludes     (false)
{
    return;
}

//----------------------------------------------------------------------
// Method: FieldContainer
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         Class Copy Constructor
//----------------------------------------------------------------------
FieldContainer::FieldContainer(FieldContainer &obj) : 
    _name                 (    0),
    _parentFieldContainer (    0), 
    _description          (    0),
    _library              (    0), 
    _pointerFieldTypes    (    0), 
    _abstract             (    0),
    _mtInfluenceMask      (    0),
    _systemComponent      (false), 
    _parentSystemComponent(true ),
    _fcdFileName          (    0), 
    _decoratable          (false),
    _useLocalIncludes     (false)
{
    return;
}

//----------------------------------------------------------------------
// Method: ~FieldContainer
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         Class Descructor
//----------------------------------------------------------------------
FieldContainer::~FieldContainer (void )
{
    return;
}

//----------------------------------------------------------------------
// Method: clear
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//       
//----------------------------------------------------------------------
void FieldContainer::clear (void)
{
    setName(0);
    setParentFieldContainer(0);
    setLibrary(0);
    setDescription(0);
    _pointerFieldTypes = 0;
    _abstract = 0;
    _systemComponent = false;
    _parentSystemComponent = true;
    _decoratable = false;
    _useLocalIncludes = false;
    
    _fieldList.clear();

    if(_fcdFileName)   free(_fcdFileName);
    _fcdFileName = 0;
    
    return;
}

//----------------------------------------------------------------------
// Method: getField
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
FieldContainer::FieldKey FieldContainer::findFieldKey  ( const char *key)
{
    FieldContainer::FieldKey keyValue = UNKNOWN_FIELD;
    int i;

    for(i = 0; _keyDic[i].name; i++) 
    {
        if(!strcmp(_keyDic[i].name, key)) 
        {
            keyValue = _keyDic[i].key;
            break;
        }
    }

    return keyValue;
}

//----------------------------------------------------------------------
// Method: putField
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
void FieldContainer::putField ( ofstream &out, const char *prefix,
                                            FieldContainer::FieldKey key, const char *value)
{
    int i;
    char *name = 0;

    for (i = 0; _keyDic[i].name; i++)
        if (_keyDic[i].key == key) {
            name = _keyDic[i].name;
            break;
        }

    if (name && value && *value) 
        out << prefix << name << "=" << "\"" << value << "\"" << '\n';
}

//----------------------------------------------------------------------
// Method: pointerFieldTypes
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *FieldContainer::pointerFieldTypesStr(int i)
{
    int vecSize = sizeof(_pointerFieldTypesName )/ sizeof(char*);

    return (i >= 0 && i < vecSize) ? _pointerFieldTypesName[i] : 0;
}

//----------------------------------------------------------------------
// Method: abstractStr
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
const char *FieldContainer::abstractStr(int i)
{
    int vecSize = sizeof(_abstractName )/ sizeof(char*);

    return (i >= 0 && i < vecSize) ? _abstractName[i] : 0;
}

//----------------------------------------------------------------------
// Method: setName
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute name
//----------------------------------------------------------------------
void FieldContainer::setName (const char* name )
{
    if(_name != NULL)
        delete [] _name;

    if (name && *name && strcmp(name,_nil)) {
        _name = new char [strlen(name)+1];
        strcpy(_name,name);
    }
    else 
        _name = 0;
}

//----------------------------------------------------------------------
// Method: setParentFieldContainer
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute parentFieldContainer
//----------------------------------------------------------------------
void FieldContainer::setParentFieldContainer (const char* parentFieldContainer )
{
    if(_parentFieldContainer != NULL)
        delete [] _parentFieldContainer;

    if (parentFieldContainer && *parentFieldContainer) {
        _parentFieldContainer = new char [strlen(parentFieldContainer)+1];
        strcpy(_parentFieldContainer,parentFieldContainer);
    }
    else 
        _parentFieldContainer = 0;
}

//----------------------------------------------------------------------
// Method: setDescription
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute description
//----------------------------------------------------------------------
void FieldContainer::setDescription (const char* description )
{
    if(_description != NULL)
        delete [] _description;

    if (description && *description) {
        _description = new char [strlen(description)+1];
        strcpy(_description,description);
    }
    else 
        _description = 0;
}

//----------------------------------------------------------------------
// Method: setLibrary
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Library:
//         set method for attribute library
//----------------------------------------------------------------------
void FieldContainer::setLibrary (const char* library )
{
    if(_library != NULL)
        delete [] _library;

    if (library && *library) {
        _library = new char [strlen(library)+1];
        strcpy(_library,library);
    }
    else 
        _library = 0;
}

//----------------------------------------------------------------------
// Method: setPointerFieldTypes
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute pointerFieldTypes
//----------------------------------------------------------------------
void FieldContainer::setPointerFieldTypes (const char* str )
{
    int i, n = sizeof(_pointerFieldTypesName)/sizeof(const char *);

    for (i = 0; i < n; ++i) 
        if (!strcasecmp(str, _pointerFieldTypesName[i]))
        {
            _pointerFieldTypes = i;
            break;
        }

    if ( i == n )
    {
        cerr << "FieldContainer::setPointerFieldTypes: string " << str 
             << " not recognized!" << endl;
    }
}

//----------------------------------------------------------------------
// Method: setAbstract
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute abstract
//----------------------------------------------------------------------
void FieldContainer::setAbstract (const char* str )
{
    int i, n = sizeof(_abstractName)/sizeof(const char *);

    for (i = 0; i < n; ++i) 
        if (!strcasecmp(str, _abstractName[i])) 
            {
                _abstract = i;
                break;
            }

    if ( i == n )
    {
        cerr << "FieldContainer::setAbstract: string " << str << " not recognized!"
             << endl;
    }
}

//----------------------------------------------------------------------
// Method: setSystemComponent
// Author: dr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute systemComponent
//----------------------------------------------------------------------
void FieldContainer::setSystemComponent (const char* str )
{
    if ( ! strcasecmp(str, "true" ) )
        _systemComponent = true;
    else if ( ! strcasecmp(str, "false" ) )
        _systemComponent = false;
    else
    {
        cerr << "FieldContainer::setSystemComponent: string " << str 
             << " not recognized!" << endl;
    }
}

//----------------------------------------------------------------------
// Method: setDecoratable
// Author: dr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute decoratable
//----------------------------------------------------------------------
void FieldContainer::setDecoratable (const char* str )
{
    if ( ! strcasecmp(str, "true" ) )
        _decoratable = true;
    else if ( ! strcasecmp(str, "false" ) )
        _decoratable = false;
    else
    {
        cerr << "FieldContainer::setDecoratable: string " << str 
             << " not recognized!" << endl;
    }
}

//----------------------------------------------------------------------
// Method: setUseLocalIncludes
// Author: dr
//----------------------------------------------------------------------
void FieldContainer::setUseLocalIncludes (const char* str )
{
    if ( ! strcasecmp(str, "true" ) )
        _useLocalIncludes = true;
    else if ( ! strcasecmp(str, "false" ) )
        _useLocalIncludes = false;
    else
    {
        cerr << "FieldContainer::setUseLocalIncludes: string " << str 
             << " not recognized!" << endl;
    }
}

//----------------------------------------------------------------------
// Method: setParentSystemComponent
// Author: dr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         set method for attribute systemComponent
//----------------------------------------------------------------------
void FieldContainer::setParentSystemComponent (const char* str )
{
    if ( ! strcasecmp(str, "true" ) )
        _parentSystemComponent = true;
    else if ( ! strcasecmp(str, "false" ) )
        _parentSystemComponent = false;
    else
    {
        cerr << "FieldContainer::setParentSystemComponent: string " << str 
             << " not recognized!" << endl;
    }
}

//----------------------------------------------------------------------
// Method: readDesc
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::readDesc (const char *fn)
{
    bool retCode = false;

    ifstream istr( fn );

    int nodeCount;
    xmlcontextptr               context( new xmlcontext );
    xmldocument                 node( context );
    xmlnodeptr                  nP;
    xmlnodelist::const_iterator nI;
    xmlattributes               attr;
    xmlattributes::iterator     aI;

    clear();

    list<Field>::iterator npI = _fieldList.end();

    if(istr) 
    {
        try
        {
            node.load( istr, context ); 
            attr = node.get_attrmap();

            for(aI = attr.begin(); aI != attr.end(); aI++)
            {
                switch(findFieldKey(aI->first.c_str())) 
                {
                    case NAME_FIELD:
                        setName(aI->second.c_str());
                        break;
                    case PARENT_FIELD:
                        setParentFieldContainer(aI->second.c_str());
                        break;
                    case LIBRARY_FIELD:
                        setLibrary(aI->second.c_str());
                        break;
                    case POINTERFIELDTYPES_FIELD:
                        setPointerFieldTypes(aI->second.c_str());
                        break;
                    case STRUCTURE_FIELD:
                        setAbstract(aI->second.c_str());
                        break;
                    case SYSTEMCOMPONENT_FIELD:
                        setSystemComponent(aI->second.c_str());
                        break;
                    case PARENTSYSTEMCOMPONENT_FIELD:
                        setParentSystemComponent(aI->second.c_str());
                        break;
                    case DECORATABLE_FIELD:
                        setDecoratable(aI->second.c_str());
                        break;
                    case USELOCALINCLUDES_FIELD:
                        setUseLocalIncludes(aI->second.c_str());
                        break;
                    default:
                        break;
                }
            }
            
            for(   nI  = node.get_nodelist().begin();
                   nI != node.get_nodelist().end  (); 
                 ++nI) 
            {
                nP   = *nI;       
                attr = nP->get_attrmap();                                     

                if(attr.empty()) 
                {
                    if (nP->get_nodelist().size()) 
                    {
                        nP = nP->get_nodelist().front();
                        setDescription (nP->get_cdata().c_str());
                    }
                }
                else 
                {
                    npI = _fieldList.insert(_fieldList.end(),Field());

                    for(aI = attr.begin(); aI != attr.end(); aI++) 
                    {
                        switch (findFieldKey(aI->first.c_str())) 
                        {
                            case NAME_FIELD:
                                npI->setName(aI->second.c_str());
                                break;
                            case TYPE_FIELD:
                                npI->setType(aI->second.c_str());
                                break;
                            case CARDINALITY_FIELD:
                                npI->setCardinality(aI->second.c_str());
                                break;
                            case VISIBILITY_FIELD:
                                npI->setVisibility(aI->second.c_str());
                                break;
                            case MT_INFLUENCE_FIELD:
                                npI->setMTInfluence(aI->second.c_str());
                                break;
                            case DEFAULTVALUE_FIELD:
                                npI->setDefaultValue(aI->second.c_str());
                                break;
                            case ACCESS_FIELD:
                                npI->setAccess(aI->second.c_str());
                                break;
                            case DEFAULTHEADER_FIELD:
                                npI->setDefaultHeader(aI->second.c_str());
                                break;
                            case HEADER_FIELD:
                                npI->setHeader(aI->second.c_str());
                                break;
                            default:
                            case UNKNOWN_FIELD:
                                break;  
                        }
                    }
                    
                    while ((nodeCount = nP->get_nodelist().size())) 
                    {
                        if (nodeCount == 1) 
                        {
                            nP = nP->get_nodelist().front();
                            if(nP->get_type() == xml_nt_cdata) 
                            {
                                npI->setDescription(
                                    nP->get_cdata().c_str());
                                break;
                            }
                        }
                        else 
                        {
                            cerr << "ERROR: Fields can't have children "
                                 << "nodes" << endl;
                        }
                    }
                }
            }
        }
        
        catch (xmlerror e)
        {
            xmllocation where( context->get_location() );
            xmlstring errmsg( e.get_strerror() );
            
            // print out where the error occured
            cout << fn << ":" << where.get_line() << " ";
            cout << "at position " << where.get_pos();
            cout << ": error: " << errmsg.c_str();
            cout << endl;
            
            // print out line where the error occured
            ifstream errfile( fn );
            int linenr = where.get_line();
            char linebuffer[1024];
            for(int i=0;i<linenr&&!errfile.eof();i++)
                errfile.getline(linebuffer,1024);
            
            int pos = where.get_pos();
            
            if(pos >= 80) 
                pos %= 80;
            
            std::string line( linebuffer + (where.get_pos()-pos) );
            if (line.length()>=79) line.erase(79);
            cout << line.c_str() << endl;
            for(int j=2;j<pos;j++)
                cout << ' ';
            cout << '^' << endl;
        }
        istr.close();
        
        if(_fcdFileName)
            free(_fcdFileName);

        _fcdFileName=strdup(fn);
    }

    list<Field>::iterator fieldIt  = _fieldList.begin();
    list<Field>::iterator fieldEnd = _fieldList.end  ();
    
    unsigned long currentInfluenceMask = 1;

    while(fieldIt != fieldEnd)
    {
        if(fieldIt->getMTInfluence() != 0)
        {
            _mtInfluenceMask |= currentInfluenceMask;
        }

        currentInfluenceMask = currentInfluenceMask << 1;

        ++fieldIt;
    }

    return retCode;
}

char *escapeQuot(char *c)
{
    char *n;

    if (!c)
    {
        // return a empty string.
        n = new char [1];
        n[0] = 0;
        return n;
    }

    n = new char [strlen(c) + 1];
    memcpy(n, c, strlen(c) + 1);
    
    char *r;
    while(r = strchr(n, '"'))
    {
        char * n2 = new char [strlen(n) + 6];
        memcpy(n2, n, r - n);
        n2[r-n] = 0;
        strcat(n2, "&quot;");
        strcat(n2, r+1);
        delete [] n;
        n = n2;
    }

    while(r = strchr(n, '<'))
    {
        char * n2 = new char [strlen(n) + 4];
        memcpy(n2, n, r - n);
        n2[r-n] = 0;
        strcat(n2, "&lt;");
        strcat(n2, r+1);
        delete [] n;
        n = n2;
    }

    while(r = strchr(n, '>'))
    {
        char * n2 = new char [strlen(n) + 4];
        memcpy(n2, n, r - n);
        n2[r-n] = 0;
        strcat(n2, "&gt;");
        strcat(n2, r+1);
        delete [] n;
        n = n2;
    }
    
    return n;
}

//----------------------------------------------------------------------
// Method: writeDesc
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeDesc (const char *fN)
{
    bool retCode = false;

  list<Field>::iterator npI;
  char fileName[512];
  ofstream out;
  const char *nprefix = "\t", *pprefix = "\t\t";
 
  if (fN)
  {
    if(_fcdFileName)
    {
        free(_fcdFileName);
        _fcdFileName=0;
    }
    _fcdFileName = strdup(fN);
    out.open(fN);
  }
  else if(_fcdFileName)
  {
    out.open(_fcdFileName);
  }
  else
  {
    sprintf (fileName,"%s%s.%s", filePrefix(), name(), _descFileSuffix);
    out.open(fileName);
  }
 
  if (out) {
    out << "<?xml version=\"1.0\"?>" << endl << endl;
    out << "<FieldContainer" << endl;
 
    putField(out, nprefix, NAME_FIELD, _name);
    putField(out, nprefix, PARENT_FIELD, _parentFieldContainer);
    putField(out, nprefix, LIBRARY_FIELD, _library);
    putField(out, nprefix, POINTERFIELDTYPES_FIELD, 
             _pointerFieldTypesName[_pointerFieldTypes]);
    putField(out, nprefix, STRUCTURE_FIELD, _abstractName[_abstract]);
    putField(out, nprefix, SYSTEMCOMPONENT_FIELD, 
             _systemComponent?"true":"false");
    putField(out, nprefix, PARENTSYSTEMCOMPONENT_FIELD, 
             _parentSystemComponent?"true":"false");
    putField(out, nprefix, DECORATABLE_FIELD, 
             _decoratable?"true":"false");
    putField(out, nprefix, USELOCALINCLUDES_FIELD, 
             _useLocalIncludes?"true":"false");
    out << ">" << endl;
        if (_description && *_description)
        out << _description << endl;
 
    for (npI = _fieldList.begin(); npI != _fieldList.end(); npI++) {
      if(!npI->type())
      {
        cerr << "Type of field " << npI->name() << " is NULL!?!" << endl;
      }
      out << nprefix << "<Field" << endl;
      putField(out, pprefix, NAME_FIELD, npI->name());
      putField(out, pprefix, TYPE_FIELD, npI->type()?npI->type():"***NULL***");
      putField(out, pprefix, CARDINALITY_FIELD, npI->cardinalityStr());
      putField(out, pprefix, VISIBILITY_FIELD, npI->visibilityStr());
      putField(out, pprefix, DEFAULTVALUE_FIELD, npI->defaultValue());
      
      char *c = escapeQuot(npI->defaultHeader());
      putField(out, pprefix, DEFAULTHEADER_FIELD, c);
      delete [] c;
      
      c = escapeQuot(npI->header());
      putField(out, pprefix, HEADER_FIELD, c);
      delete [] c;
      
      putField(out, pprefix, ACCESS_FIELD, npI->accessStr());
      out << nprefix << ">" << endl;
            if (npI->description() && *npI->description())
          out << nprefix << npI->description() << endl;
      out << nprefix << "</Field>" << endl;
    }
 
    out << "</FieldContainer>" << endl;
 
    retCode = true;
  }
 
    return retCode;
}


//----------------------------------------------------------------------
// Method: writeDec
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeCode (bool base, bool fc, const char *path)
{   
    bool retCode = false;
    char fldFile[1024];
    char decFile[1024];
    char inlFile[1024];
    char impFile[1024];

    if (name()) {

        if (base) {
            retCode = true;

            if(path == NULL || strlen(path) == 0)
            {
                sprintf(fldFile,"%s%sFields.%s", filePrefix(), name(), 
                                            decFileSuffix());
                sprintf(decFile,"%s%sBase.%s", filePrefix(), name(), 
                                            decFileSuffix());
                sprintf(inlFile,"%s%sBase.%s", filePrefix(), name(), 
                                            inlFileSuffix());
                sprintf(impFile,"%s%sBase.%s", filePrefix(), name(), 
                                            impFileSuffix());
            }
            else
            {
                // add path
                sprintf(fldFile,"%s%s%sFields.%s", path, filePrefix(), name(), 
                                            decFileSuffix());
                sprintf(decFile,"%s%s%sBase.%s", path, filePrefix(), name(), 
                                            decFileSuffix());
                sprintf(inlFile,"%s%s%sBase.%s", path, filePrefix(), name(), 
                                            inlFileSuffix());
                sprintf(impFile,"%s%s%sBase.%s", path, filePrefix(), name(), 
                                            impFileSuffix());
            }
            
            retCode &= writeCodeFields(fldFile);
            retCode &= writeBaseCodeDec(decFile);
            retCode &= writeBaseCodeInl(inlFile);
            retCode &= writeBaseCodeImp(impFile);

            if (decoratable())
            {
                sprintf(fldFile,"%s%sDecoratorFields.%s", filePrefix(), name(), 
                                                decFileSuffix());
                sprintf(decFile,"%s%sDecoratorBase.%s", filePrefix(), name(), 
                                                decFileSuffix());
                sprintf(inlFile,"%s%sDecoratorBase.%s", filePrefix(), name(), 
                                                inlFileSuffix());
                sprintf(impFile,"%s%sDecoratorBase.%s", filePrefix(), name(), 
                                                impFileSuffix());

                retCode &= writeDecoratorBase(decFile,inlFile,impFile,fldFile);
            }
            
            if (retCode)
                cerr << "Write OK, Wrote base fields,dec,inl and imp file" << endl;
            else
                cerr << "Write error: Couldn't write the dec,inl and imp file" << endl;
        }
        
        if (fc) {
            retCode = true;
            sprintf(decFile,"%s%s.%s", filePrefix(), name(), decFileSuffix());
            sprintf(inlFile,"%s%s.%s", filePrefix(), name(), inlFileSuffix());
            sprintf(impFile,"%s%s.%s", filePrefix(), name(), impFileSuffix());
            
            FILE *f;
            if ( f = fopen( decFile, "r" ) )
            {
                fclose(f);
                cerr << decFile << " exists, please remove it and try again!" << endl;
                retCode = false;
            }
            if ( f = fopen( inlFile, "r" ) )
            {
                fclose(f);
                cerr << inlFile << " exists, please remove it and try again!" << endl;
                retCode = false;
            }
            if ( f = fopen( impFile, "r" ) )
            {
                fclose(f);
                cerr << impFile << " exists, please remove it and try again!" << endl;
                retCode = false;
            }
            if ( ! retCode )
                return retCode;
                
            retCode &= writeCodeDec(decFile);
            retCode &= writeCodeInl(inlFile);
            retCode &= writeCodeImp(impFile);


            if (decoratable())
            {
                sprintf(decFile,"%s%sDecorator.%s", filePrefix(), name(), 
                                                decFileSuffix());
                sprintf(inlFile,"%s%sDecorator.%s", filePrefix(), name(), 
                                                inlFileSuffix());
                sprintf(impFile,"%s%sDecorator.%s", filePrefix(), name(), 
                                                impFileSuffix());

                retCode &= writeDecoratorCode(decFile,inlFile,impFile);
            }
 
            if (retCode)
                cerr << "Write OK, Wrote dec,inl and imp file" << endl;
            else
                cerr << "Write error: Couldn't write the dec,inl and imp file" << endl;
        }
        
    }
    else
        cerr <<  "ERROR: No node name" << endl;

    
    return retCode;
}


//----------------------------------------------------------------------
// Method: writeTempl
// Author: reiners
// Date:   Thu Mar 29 01:00:00 2001
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeTempl( 
    ofstream & out, 
    char *fcname, 
    char *parentname,
    bool decorator,
    char ** templ )
{
    // file loop
    // some useful strings
    char *libname = _library;
    char *libnameUpper = strdup( _library ? _library : "" );
    char *fcnameUpper = strdup( fcname ? fcname : "UNSET" );
    char *parentnameUpper = strdup( parentname ? parentname : "UNSET" );
    const char *description = _description ? _description : "";
    const char *headerPrefix = _systemComponent ? "" : "OpenSG/";
    const char *parentHeaderPrefix = 
            ( _parentSystemComponent == _systemComponent ) ? "" : "OpenSG/";

    char *s;
    for (  s = libnameUpper; s && *s; *s = toupper(*s), s++ ) {}
    for (  s = fcnameUpper; s && *s; *s = toupper(*s), s++ ) {}
    for (  s = parentnameUpper; s && *s; *s = toupper(*s), s++ ) {}

    // field loop
    // useful strings
    char        *fieldname        = NULL;
    const char  *fieldtype        = NULL;
    char        *fieldcardinality = NULL, 
                *fielddescription = NULL;
    char        *fieldnameCaps = NULL, 
                *fieldnameUpper = NULL;
    char        *fieldnameDesc    = NULL;   

    // state
    char ** flStart;
    list<Field>::iterator fieldIt;
    bool inFieldLoop = false;
    bool skipFieldLoop = false;
    int skipIf = 0; // count of open if or else clauses
    
    bool retCode = true;

    for ( ; *templ; templ++ )
    {
        char *s = *templ;

        // just skipping to else of endif?
        if ( skipIf > 0 )
        {
            if ( strncmp( s, "@@", 2 ) )
                continue;
                
            if ( ! strncmp( s, "@@if", 4 ) )
                skipIf ++;
            else if ( ! strcmp( s, "@@endif" ) )
                skipIf --;
            else if ( ! strcmp( s, "@@else" ) )
            {
                if ( skipIf == 1) 
                    skipIf = 0;
            }
            continue;
        }
        
        // if in field loop, prepare the strings
        if ( inFieldLoop && ! skipFieldLoop)
        {
            static char *cardnames[] = { "SF", "MF" };
            
            if(fieldname != NULL)
            {
                delete [] fieldname;
            }

            fieldname = fieldIt->name();

            fieldtype = fieldIt->type();
            fieldcardinality = cardnames[ fieldIt->cardinality() ];
            fielddescription = (char*)( fieldIt->description() ? 
                                  fieldIt->description() : "" );
            
            if ( fieldnameCaps ) free( fieldnameCaps );
            fieldnameCaps = strdup( fieldname );
            fieldnameCaps[0] = toupper( fieldnameCaps[0] );
        
            if ( fieldnameUpper ) free( fieldnameUpper );
            fieldnameUpper = strdup( fieldname );
            for ( char *s = fieldnameUpper; s && *s; *s = toupper(*s), s++ ) {}

            if ( fieldnameDesc ) free( fieldnameDesc );
            fieldnameDesc = strdup( fieldname );

            fieldname = new char[strlen(fieldIt->name()) + 3];
            strcpy(&(fieldname[2]), fieldIt->name());           

            fieldname[0] = tolower(cardnames[fieldIt->cardinality()][0]);
            fieldname[1] = tolower(cardnames[fieldIt->cardinality()][1]);
            fieldname[2] = toupper(fieldname[2]);
        }

        // is it a special line?
        if ( ! strncmp( s, "@@", 2 ) )
        {
            // specials
            // field ids/masks
            if ( ! strcmp( s, "@@FieldIdsAndMasksDecl@@" ) )
            {
                fieldIt = _fieldList.begin();
                if ( fieldIt == _fieldList.end() )
                {
                    continue;
                }
                
                int maxlen = 4; // NextFieldId is min length
                for(; fieldIt != _fieldList.end(); fieldIt++)
                {
                    if ( strlen( fieldIt->name()) > maxlen )
                        maxlen = strlen( fieldIt->name());
                }
                char *spc = new char [maxlen + 1];
                memset( spc, ' ', maxlen );
                spc[maxlen]=0;
                
                fieldIt = _fieldList.begin();
                const char *name, *prevname;
                name = fieldIt->name();
                // first field: refer to parent's last field
                out << "    enum" << endl;
                out << "    {" << endl;

                out << "        " 
                    << (char)toupper( name[0] ) << name + 1 
                    << "FieldId"
                    << spc + strlen( name )
                    << " = Inherited::NextFieldId"
                    << "," << endl;
                    
                for(fieldIt++; fieldIt != _fieldList.end(); fieldIt++)
                {
                    prevname = name;
                    name = fieldIt->name();
                    out << "        " 
                        << (char)toupper(name[0]) << name + 1 << "FieldId"
                        << spc + strlen( name )
                        << " = " << (char)toupper(prevname[0]) 
                        << prevname + 1 << "FieldId"
                        << spc + strlen(prevname)
                        << " + 1"
                        << "," << endl;
                }

                out << "        " 
                    << "NextFieldId " 
                    << spc + 4              
                    << "= "
                    << (char)toupper(name[0]) 
                    << name + 1 << "FieldId "
                    << spc + strlen(name)
                    << "+ 1"
                    << endl;
                
                out  << "    };" << endl << endl;
                
                delete [] spc;
                
                for ( fieldIt = _fieldList.begin(); fieldIt != _fieldList.end(); fieldIt++ )
                {
                    name = fieldIt->name();
                    out << "    static const OSG::BitVector " 
                        << (char)toupper( name[0] ) << name + 1 << "FieldMask;" << endl;
                }

                out << endl;
            }       
            // loop specials 
            else if ( ! strcmp( s, "@@BeginFieldLoop@@" ) )
            {
                inFieldLoop = true;
                flStart = templ;
                fieldIt = _fieldList.begin();
                if ( fieldIt == _fieldList.end() ) 
                    skipFieldLoop = true;
            }
            else if ( ! strcmp( s, "@@EndFieldLoop@@" ) )
            {
                if ( skipFieldLoop )
                {
                    inFieldLoop = false;
                    skipFieldLoop = false;
                    continue;                   
                }
                
                fieldIt++;
                if ( fieldIt != _fieldList.end() ) 
                {
                    templ = flStart;
                }
                else
                {
                    inFieldLoop = false;
                    skipFieldLoop = false;
                }
            }
            else if ( ! strcmp( s, "@@BeginSFFieldLoop@@" ) )
            {
                inFieldLoop = true;
                flStart = templ;
                
                for (   fieldIt = _fieldList.begin();
                        fieldIt != _fieldList.end() && 
                        fieldIt->cardinality() != 0;
                        fieldIt++ ) {}
                        
                if ( fieldIt == _fieldList.end() ) // No singlefields
                    skipFieldLoop = true;
            }
            else if ( ! strcmp( s, "@@EndSFFieldLoop@@" ) )
            {
                if ( skipFieldLoop )
                {
                    skipFieldLoop = false;
                    inFieldLoop = false;
                    continue;
                }
                
                for (   fieldIt++;
                        fieldIt != _fieldList.end() && 
                        fieldIt->cardinality() != 0;
                        fieldIt++ ) {}
                        
                if ( fieldIt != _fieldList.end() ) 
                {
                    templ = flStart;
                }
                else
                {
                    inFieldLoop = false;
                }
            }
            else if ( ! strcmp( s, "@@BeginMFFieldLoop@@" ) )
            {
                inFieldLoop = true;
                flStart = templ;
                
                for (   fieldIt = _fieldList.begin();
                        fieldIt != _fieldList.end() && 
                        fieldIt->cardinality() != 1;
                        fieldIt++ ) {}
                        
                if ( fieldIt == _fieldList.end() ) // No singlefields
                    skipFieldLoop = true;
            }
            else if ( ! strcmp( s, "@@EndMFFieldLoop@@" ) )
            {
                if ( skipFieldLoop )
                {
                    skipFieldLoop = false;
                    inFieldLoop = false;
                    continue;
                }
                
                for (   fieldIt++;
                        fieldIt != _fieldList.end() && 
                        fieldIt->cardinality() != 1;
                        fieldIt++ ) {}
                        
                if ( fieldIt != _fieldList.end() ) 
                {
                    templ = flStart;
                }
                else
                {
                    inFieldLoop = false;
                }
            }
            else if ( skipFieldLoop )   // skip if processing
                continue;
            // if else endif handling
            else if ( ! strncmp( s, "@@if", 4 ) )
            {
                static char * keys[] = {
                    "Pointerfield", "SFPointerfield", "MFPointerfield",
                    "Abstract", "hasFields", 
                    "hasPrivateFields", "hasProtectedFields", "hasPublicFields", 
                    "isPrivate", "isProtected", "isPublic",
                    "hasDefaultHeader", "SystemComponent",
                    "isDecoratable", "Decorator", "Library",
                    "useLocalIncludes",
                    "parentsystemcomponent",
                    NULL };
                
                char *key = s + strcspn( s, " \t");
                key += strspn( key, " \t");
                
                bool notElem = false;               
                if ( *key == '!' )
                {
                    key++;
                    key += strspn( key, " \t");
                    notElem = true;
                }
                
                int i;
                for ( i = 0; keys[i]; i++ )
                    if ( ! strcasecmp( key, keys[i] ) )
                        break;
                        
                skipIf = 0;
                
                switch( i )
                {
                case 0:     // Pointerfield
                            if ( ! pointerFieldTypes() )
                                skipIf = 1;
                            break;
                case 1:     // SFPointerfield
                            if ( ( pointerFieldTypes() & 1 ) == 0 )
                                skipIf = 1;
                            break;
                case 2:     // MFPointerfield
                            if ( ( pointerFieldTypes() & 2 ) == 0 )
                                skipIf = 1;
                            break;
                case 3:     // Abstract
                            if ( ! abstract() )
                                skipIf = 1;
                            break;
                case 4:     // hasFields
                            if ( _fieldList.begin() == _fieldList.end() &&
                                ! decorator )
                                skipIf = 1;
                            break;

                case 5:     // hasPrivateFields
                            {       
                            list<Field>::iterator fieldIt;
        
                            if ( _fieldList.begin() == _fieldList.end() )
                            {
                                skipIf = 1;
                                break;
                            }
                                
                            for (   fieldIt = _fieldList.begin();
                                    fieldIt != _fieldList.end() && 
                                    fieldIt->access() != 2;
                                    fieldIt++ ) {}
                            if ( fieldIt == _fieldList.end() )
                                skipIf = 1;
                            }
                            break;
                case 6:     // hasProtectedFields
                            {       
                            list<Field>::iterator fieldIt;
        
                            if ( _fieldList.begin() == _fieldList.end() )
                            {
                                skipIf = 1;
                                break;
                            }
        
                            for (   fieldIt = _fieldList.begin();
                                    fieldIt != _fieldList.end() && 
                                    fieldIt->access() != 1;
                                    fieldIt++ ) {}
                            if ( fieldIt == _fieldList.end() )
                                skipIf = 1;
                            }
                            break;
                case 7:     // hasPublicFields
                            {       
                            list<Field>::iterator fieldIt;
        
                            if ( _fieldList.begin() == _fieldList.end() )
                            {
                                skipIf = 1;
                                break;
                            }
        
                            for (   fieldIt = _fieldList.begin();
                                    fieldIt != _fieldList.end() && 
                                    fieldIt->access() != 0;
                                    fieldIt++ ) {}
                            if ( fieldIt == _fieldList.end() && ! decorator)
                                skipIf = 1;
                            }
                            break;
                            
                case 8:     // isPrivate
                            if ( fieldIt->access() != 2 )
                                skipIf = 1;
                            break;
                case 9:     // isProtected
                            if ( fieldIt->access() != 1 )
                                skipIf = 1;
                            break;
                case 10:    // isPublic
                            if ( fieldIt->access() != 0 )
                                skipIf = 1;
                            break;
                case 11:    // hasDefaultHeader
                            if ( ! fieldIt->defaultHeader() || 
                                  *fieldIt->defaultHeader() == 0 )
                                skipIf = 1;
                            break;
                case 12:    // SystemComponent
                            if ( ! _systemComponent )
                                skipIf = 1;
                            break;
                case 13:    // isDecoratable
                            if ( ! _decoratable || decorator )
                                skipIf = 1;
                            break;
                case 14:    // Decorator
                            if ( ! decorator )
                                skipIf = 1;
                            break;
                case 15:    // Library
                            if ( !_library || strlen(_library) == 0 )
                                skipIf = 1;
                            break;
                           
                case 16:    // UseLocalIncludes
                            if ( !_useLocalIncludes )
                                skipIf = 1;
                            break;
                           
                case 17:    // parentsystemcomponent
                            if ( !_parentSystemComponent )
                                skipIf = 1;
                            break;
                           
                default:
                            cerr << "Unknown if clause \"" << s + 5 << "\"" 
                                 << endl;
                            break;
                }           
                if ( notElem )
                    skipIf = 1 - skipIf;    
            }
            else if ( ! strcmp( s, "@@else" ) )
            {
                skipIf = 1;
            }
            else if ( ! strcmp( s, "@@endif" ) )
            {
                skipIf = 0;
            }
            // unknown special??
            else if ( ! strncmp( s, "@@", 2 ) ) 
            {
                cerr << "FieldContainer::writeBaseCodeImp: unknown "
                     << "command " << s << " in line "
                     << *templ << "!!" << endl;
                // retCode = false;
                // break;
            }
        }
        else if ( skipFieldLoop )   // skip text processing
            continue;
        else // verbatim text
        {
            // replace @!classname!@ etc. with the names
            static char *keys[] = 
            { 
                "@!Classname",          
                "@!CLASSNAME", 
                "@!Libname",            
                "@!LIBNAME",
                "@!ParentHeaderPrefix",
                "@!Parent",             
                "@!PARENT",
                "@!FieldtypeInclude",
                "@!FieldTypedDefault",  
                "@!CARDINALITY",        
                "@!Fieldtype",
                "@!CapsFieldtypeClean",
                "@!CapsFieldtype",
                "@!fieldnameDesc",
                "@!fieldname",
                "@!Fieldname", 
                "@!FIELDNAME",
                "@!fieldvisibility",
                "@!Description",
                "@!Fielddescription", 
                "@!FieldSeparator",    
                "@!FieldDefaultHeader",
                "@!HeaderPrefix", 
                "@!FieldMethodType",
                "@!LocalMTInfluenceMask",
                NULL 
            };

            enum varE
            {  
                ClassnameE = 0,     
                CLASSNAMEE, 
                LibnameE,          
                LIBNAMEE,
                ParentHeaderPrefixE,
                ParentE,            
                PARENTE,
                FieldtypeIncludeE,
                FieldTypedDefaultE, 
                CARDINALITYE,       
                FieldtypeE,
                FieldtypeCapsCleanE,
                FieldtypeCapsE,
                fieldnameDescE,
                fieldnameE,         
                FieldnameE, 
                FIELDNAMEE,         
                fieldvisibilityE,
                DescriptionE,       
                FielddescriptionE, 
                FieldSeparatorE,    
                FieldDefaultHeaderE,
                HeaderPrefixE,      
                FieldMethodTypeE,
                LocalMTInfluenceE
            };

            char *values[sizeof(keys) / sizeof(char *)];
                    
            values[ClassnameE] = fcname;
            values[CLASSNAMEE] = fcnameUpper;
            values[LibnameE] = libname;
            values[LIBNAMEE] = libnameUpper;
            values[ParentE] = parentname;
            values[PARENTE] = parentnameUpper;
            values[DescriptionE] = (char*)(description);
            values[HeaderPrefixE] = (char*)(headerPrefix);
            values[ParentHeaderPrefixE] = (char*)(parentHeaderPrefix);
            values[FieldMethodTypeE] = (_decoratable && ! decorator) ? 
                                       (char*)"virtual" : (char*)"";

            values[LocalMTInfluenceE] = new char[32];

            sprintf(values[LocalMTInfluenceE], "0x%0x", _mtInfluenceMask);

            if ( inFieldLoop )
            {
                char * s;

                values[CARDINALITYE]        = fieldcardinality;
                values[FieldtypeE]          = strdup(fieldtype?fieldtype:"UNSET");
                values[FieldtypeCapsE]      = strdup(fieldtype?fieldtype:"UNSET");
                values[FieldtypeCapsCleanE] = strdup(fieldtype?fieldtype:"UNSET");
                values[fieldnameE]          = strdup(fieldname?fieldname:"UNSET");
                values[FieldnameE]          = fieldnameCaps;
                values[FIELDNAMEE]          = fieldnameUpper;
                values[fieldvisibilityE]    = (char*)(fieldIt->visibility() ? "false" : "true");
                values[fieldnameDescE]      = fieldnameDesc;

                values[FieldtypeCapsE][0] = toupper(values[FieldtypeCapsE][0]);

                if(strncmp(values[FieldtypeCapsCleanE], "std::", 5) == 0)
                {
                    char *tmpStrIn  = values[FieldtypeCapsCleanE] + 5;
                    char *tmpStrOut = values[FieldtypeCapsCleanE];

                    while(*tmpStrIn != '\0')
                    {
                        *tmpStrOut++ = *tmpStrIn++;
                    }

                    *tmpStrOut = '\0';

                    values[FieldtypeCapsCleanE][0] = toupper(values[FieldtypeCapsCleanE][0]);
                }
                else
                {
                    values[FieldtypeCapsCleanE][0] = toupper(values[FieldtypeCapsCleanE][0]);
                }

                if ( fieldIt->defaultValue() )
                {
                    s = new char [ strlen(fieldtype) + 
                                           1 + 
                                           strlen( fieldIt->defaultValue() ) +
                                           4];
                    strcpy( s, fieldtype );
                    strcat( s, "(" );
                    if(!strcmp(fieldtype, "std::string"))
                        strcat( s, "\"" );  
                    strcat( s, fieldIt->defaultValue() );
                    if(!strcmp(fieldtype, "std::string"))
                        strcat( s, "\"" );  
                    strcat( s, ")" );   
                    values[FieldTypedDefaultE] = s;     
                }
                else
                {
                    s = new char [CLASSNAMEE];
                    *s = 0;
                    values[FieldTypedDefaultE] = s; 
                }
                
                // FieldtypeInclude
                if ( ! fieldIt->header() || ! strcmp( fieldIt->header(), "auto" ) )
                {
                    char *valueStart = values[FieldtypeCapsE];

                    s = new char [ strlen(fieldtype) + 20];
                    
                    if (tolower(valueStart[0]) == 's' &&
                        tolower(valueStart[1]) == 't' &&
                        tolower(valueStart[2]) == 'd' &&
                                valueStart[3]  == ':' && 
                                valueStart[4]  == ':'
                       )
                    {
                        valueStart += 5;
                        *valueStart = toupper(*valueStart);
                    }

                    if ( _systemComponent )
                        strcpy( s, "OSG" );
                    else
                        strcpy( s, "OpenSG/OSG" );
                    strcat( s, valueStart );

                    // remove the Ptr suffix
                    if ( !strcmp( &s[strlen(s) - 3], "Ptr" ) )
                        s[strlen(s) - 3] = 0;
                    // Append 'Fields' to get the header
                    strcat( s, "Fields.h" );
                }
                else
                {
                    s = new char [ strlen(fieldIt->header()) + 1];
                    strcpy( s, fieldIt->header() );                 
                }
                
                // Do we need to add delimiters or are they in the fcd file
                // already?
                if(s[0] != '<' && s[0] != '"')
                {
                    int l = strlen(s);
                    char *s2 = new char [ l + 3];
                    s2[0] = '<';
                    memcpy(s2+1, s, l);
                    s2[l+1] = '>';
                    s2[l+2] = 0;
                    delete [] s;
                    s = s2;
                }
                
                values[FieldtypeIncludeE] = s;
                
                values[FielddescriptionE] = fielddescription;   

                if ( fieldIt == --_fieldList.end() )
                    values[FieldSeparatorE] = "";
                else
                    values[FieldSeparatorE] = ",";

                if ( fieldIt->defaultHeader() && *fieldIt->defaultHeader())
                {
                    s = new char [strlen(fieldIt->defaultHeader()) + 1];
                    strcpy(s, fieldIt->defaultHeader());

                    // Do we need to add delimiters or are they in the fcd file
                    // already?
                    if(s[0] != '<' && s[0] != '"')
                    {
                        int l = strlen(s);
                        char *s2 = new char [ l + 3];
                        s2[0] = '<';
                        memcpy(s2+1, s, l);
                        s2[l+1] = '>';
                        s2[l+2] = 0;
                        delete [] s;
                        s = s2;
                    }
                  
                    values[FieldDefaultHeaderE] = s;
                }
                else
                    values[FieldDefaultHeaderE] = "";
            }
            else
            {
                values[CARDINALITYE] = values[FieldtypeE] = values[FieldtypeCapsE] = 
                values[FieldtypeCapsCleanE] = values[fieldnameE] = values[FieldnameE] = 
                values[FIELDNAMEE] = values[fieldvisibilityE] = 
                values[FieldTypedDefaultE] = values[FieldtypeIncludeE] = 
                values[FielddescriptionE] = values[FieldSeparatorE] = 
                values[FieldDefaultHeaderE] = NULL;
            }


            char *cs = s, *ce = strchr( cs, '@' );

            while ( ce )
            {
                if ( !ce[1] || ce[1] != '!' )
                {
                    ce = strchr( ce + 1, '@' );
                    continue;
                }
                
                int i;
                for ( i = 0; keys[i] ; i++ )
                {
                    if ( ! strncmp( ce, keys[i], strlen( keys[i] ) ) )
                    {
                        int len = 0;
                        if ( ce[ strlen(keys[i]) ] == ':' )
                        {
                            len = atoi( ce + strlen(keys[i]) + 1 );
                        }
                        if ( ! values[i] ) 
                        {
                            cerr << "Replacement for " << keys[i] << "!@ is NULL"
                                 << " in line " << *templ << endl;
                        }
                        else
                        {
                            char *p;
                            for ( p = cs; p < ce; p++ )
                                out << *p;
                            if ( strlen( values[i] ) )
                                out << values[i];   
                            for ( int j = strlen( values[i] ); j < len; j++ )
                                out << ' '; 
                        }
                        ce = strchr( ce + 1, '@' ) + 1; // get behind the !@-string
                        cs = ce;
                        break;
                    }
                }

                if ( ! keys[i] )
                {
                    cerr << "No replacement found for " << ce << " in line " 
                         << *templ <<  endl;
                    ce++;
                }
                
                ce = strchr( ce, '@' );
            }
            
            if ( values[FieldTypedDefaultE] )   
                delete [] values[FieldTypedDefaultE];
                        
            if ( values[FieldtypeIncludeE] )    
                delete [] values[FieldtypeIncludeE];
                        
            if ( values[FieldDefaultHeaderE] &&
                 strlen(values[FieldDefaultHeaderE]) )    
                delete [] values[FieldDefaultHeaderE];
                
            if ( values[FieldtypeE] )   
                free( values[FieldtypeE] );

            if ( values[FieldtypeCapsE] )   
                free( values[FieldtypeCapsE] );
                
            if ( values[fieldnameE] )   
                free( values[fieldnameE] );

            delete values[LocalMTInfluenceE];

            out << cs << endl;
        }
    }

        
    if ( fieldnameCaps ) free( fieldnameCaps );
    if ( fieldnameUpper ) free( fieldnameUpper );
    if ( fieldnameDesc ) free( fieldnameDesc );
    free( fcnameUpper );
    free( libnameUpper );
    free( parentnameUpper );
    return retCode;
}


//----------------------------------------------------------------------
// Method: writeFields
// Author: dr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeCodeFields (const char *decFile)
{
    bool retCode = false;

    ofstream out;

    if (decFile)
        out.open(decFile);
 
    if (out) 
    {
        retCode = writeTempl( out, _name, _parentFieldContainer, false, 
                                FCPtrTemplate_h );
    }
 
    return retCode;
}

//----------------------------------------------------------------------
// Method: writeDec
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeBaseCodeDec (const char *decFile)
{
    bool retCode = false;

    ofstream out;

    if (decFile)
        out.open(decFile);
 
    if (out) 
    {
        retCode = writeTempl( out, _name, _parentFieldContainer, false, 
                                FCBaseTemplate_h );
    }
 
    return retCode;
}

//----------------------------------------------------------------------
// Method: writeDec
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeBaseCodeInl (const char *InlFile)
{
    bool retCode = false;

    ofstream out;

    if (InlFile)
        out.open(InlFile);
 
    if (out) 
    {
        retCode = writeTempl( out, _name, _parentFieldContainer, false, 
                                FCBaseTemplate_inl );
    }
 
    return retCode;
}
    

//----------------------------------------------------------------------
// Method: writeImp
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeBaseCodeImp ( const char *impFile)
{
    bool retCode = false;

    ofstream out;

    if (impFile)
        out.open(impFile);
 
    if (out) 
    {
        retCode = writeTempl( out, _name, _parentFieldContainer, false, 
                                FCBaseTemplate_cpp );
    }
 
    return retCode;
}


//----------------------------------------------------------------------
// Method: writeDec
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeCodeDec (const char *decFile)
{
    bool retCode = false;

    ofstream out;

    if (decFile)
        out.open(decFile);
 
    if (out) 
    {
        retCode = writeTempl( out, _name, _parentFieldContainer, false, 
                                FCTemplate_h );
    }
 
    return retCode;
}

//----------------------------------------------------------------------
// Method: writeInl
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeCodeInl (const char *decFile)
{
    bool retCode = false;

    ofstream out;

    if (decFile)
        out.open(decFile);
 
    if (out) 
    {
        retCode = writeTempl( out, _name, _parentFieldContainer, false, 
                                FCTemplate_inl );
    }
 
    return retCode;
}
    
//----------------------------------------------------------------------
// Method: writeImp
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeCodeImp ( const char *impFile)
{
    bool retCode = false;

    ofstream out;

    if (impFile)
        out.open(impFile);
 
    if (out) 
    {
        retCode = writeTempl( out, _name, _parentFieldContainer, false, 
                                FCTemplate_cpp );
    }
 
    return retCode;
}
    
//----------------------------------------------------------------------
// Method: writeDecorator
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeDecoratorBase ( const char *bdecFile, 
                                          const char *binlFile, 
                                          const char *bimpFile,
                                          const char *fldFile)
{
    bool retCode = false;

    if(!_decoratable)
        return true;

    char *name = new char [strlen(_name) + 10];
    sprintf(name,"%sDecorator", _name);

    ofstream out;

    if (bdecFile)
    {
        out.open(bdecFile);
 
        if (out) 
        {
            retCode = writeTempl( out, name, _name, true, 
                                    FCBaseTemplate_h );
        }
 
        out.close();
    }

    if (binlFile)
    {
        out.open(binlFile);
 
        if (out) 
        {
            retCode = writeTempl( out, name, _name, true, 
                                    FCBaseTemplate_inl );
        }
 
        out.close();
    }
 
    if (bimpFile)
    {
        out.open(bimpFile);
 
        if (out) 
        {
            retCode = writeTempl( out, name, _name, true, 
                                    FCBaseTemplate_cpp );
        }
 
        out.close();
    }
 
    if (fldFile)
    {
        out.open(fldFile);
 
        if (out) 
        {
            retCode = writeTempl( out, name, _name, true, 
                                    FCPtrTemplate_h );
        }
 
        out.close();
    }
   
    
 
    delete [] name;

    return retCode;
}
    
//----------------------------------------------------------------------
// Method: writeDecorator
// Author: jbehr
// Date:   Thu Jan  8 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::writeDecoratorCode ( const char *decFile, 
                                          const char *inlFile, 
                                          const char *impFile)
{
    bool retCode = false;

    if(!_decoratable)
        return true;

    char *name = new char [strlen(_name) + 10];
    sprintf(name,"%sDecorator", _name);

    ofstream out;

    if (decFile)
    {
        out.open(decFile);
 
        if (out) 
        {
            retCode = writeTempl( out, name, _name, true, 
                                    FCTemplate_h );
        }
 
        out.close();
    }

    if (inlFile)
    {
        out.open(inlFile);
 
        if (out) 
        {
            retCode = writeTempl( out, name, _name, true, 
                                    FCTemplate_inl );
        }
 
        out.close();
    }
 
    if (impFile)
    {
        out.open(impFile);
 
        if (out) 
        {
            retCode = writeTempl( out, name, _name, true, 
                                    FCTemplate_cpp );
        }
 
        out.close();
    }
  
    delete [] name;

    return retCode;
}


//----------------------------------------------------------------------
// Method: newField
// Author: jbehr
// Date:   Thu Jan  24 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
int FieldContainer::newField(const Field &part)
{
    int i = _fieldList.size();

  _fieldList.push_back(part); 
    
    return i;
}

//----------------------------------------------------------------------
// Method: delField
// Author: jbehr
// Date:   Thu Jan  24 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
void FieldContainer::delField(unsigned index)
{
    list<Field>::iterator partI;

    for (partI = _fieldList.begin(); partI != _fieldList.end(); partI++)
        if (!index--) {
            _fieldList.erase(partI);
            break;
        }
}

//----------------------------------------------------------------------
// Method: getField
// Author: jbehr
// Date:   Thu Jan  24 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
Field *FieldContainer::getField(unsigned index)
{
    list<Field>::iterator partI;

    for (partI = _fieldList.begin(); partI != _fieldList.end(); partI++)
        if (!index--) 
            return &(*partI);

    return 0;
}

//----------------------------------------------------------------------
// Method: moveFieldLeft
// Author: jbehr
// Date:   Thu Jan  24 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::moveFieldLeft(unsigned index)
{
    bool retCode = false;
    list<Field>::iterator partI,prevI,nextI;

    if (index > 0) {
        for ( partI = _fieldList.begin(); 
                    partI != _fieldList.end(); partI++)
            if (!index--) {
                nextI = partI;
                ++nextI;
                _fieldList.splice(prevI,_fieldList,partI,nextI);
                retCode = true;
            }
            else
                prevI = partI;
    }

    return retCode;
}

//----------------------------------------------------------------------
// Method: moveFieldRight
// Author: jbehr
// Date:   Thu Jan  24 19:53:04 1998
// Description:
//         
//----------------------------------------------------------------------
bool FieldContainer::moveFieldRight (unsigned index)
{
    return moveFieldLeft(index+1);
}
    
    
        

            

