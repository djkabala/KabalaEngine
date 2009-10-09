#ifndef FIELDCONTAINER_CLASS_DECLARATION
#define FIELDCONTAINER_CLASS_DECLARATION

/** .


@author jbehr, Thu Jan  8 19:53:04 1998

*/

#include <list>
#include <iostream>
#include <fstream>

#include "ActionType.h"
#include "Field.h"
#include "ProducedMethod.h"
#include "OSGXmlpp.h"

using namespace std;
using namespace xmlpp;

class FieldContainer {

    friend class Field;
    friend class ProducedMethod;

private:

    struct KeyDic;
    friend struct KeyDic;

    enum FieldKey 
    { 
        NAME_FIELD, 
        PARENT_FIELD, 
        PARENT_HEADER_FIELD, 
        PARENT_PRODUCER_FIELD, 
        LIBRARY_FIELD, 
        STRUCTURE_FIELD, 
        POINTERFIELDTYPES_FIELD, 
        TYPE_FIELD, 
        CARDINALITY_FIELD, 
        VISIBILITY_FIELD, 
        MT_INFLUENCE_FIELD, 
        DEFAULTVALUE_FIELD, 
        ACCESS_FIELD, HEADER_FIELD, 
        DEFAULTHEADER_FIELD, 
        SYSTEMCOMPONENT_FIELD,
        PARENTSYSTEMCOMPONENT_FIELD,
        DECORATABLE_FIELD,
        USELOCALINCLUDES_FIELD,
        PUBLIC_READ_FIELD,
        PRODUCED_EVENT_TYPE_FIELD,
        UNKNOWN_FIELD
    };

    struct KeyDic {
        FieldKey  key;
        const char      *name;
    };

    ///
    static KeyDic _keyDic[];

    enum NodeTokenKey 
    { 
        FIELD_CONTAINER_NODE_TOKEN, 
        FIELD_NODE_TOKEN, 
        PRODUCED_METHOD_NODE_TOKEN, 
        UNKNOWN_NODE_TOKEN
    };

    struct NodeTokenKeyDic {
        NodeTokenKey       key;
        const char      *name;
    };

    ///
    static NodeTokenKeyDic _nodeTokenKeyDic[];

    ///
    static const char _filePrefix[];

    ///
    static const char _descFileSuffix[];

    /// 
    static const char _decFileSuffix[];

    /// 
    static const char _inlFileSuffix[];

    ///
    static const char _impFileSuffix[];

    ///
    static const char _nil[];

    ///
    static const char *_pointerFieldTypesName[];

    ///
    static const char *_abstractName[];

  /// 
  char* _name;

  /// 
  char* _parentFieldContainer;
  
  /// 
  char* _parentFieldContainerHeader;

  /// 
  char* _parentProducer;

  /// 
  char* _description;

    ///
    char* _library;

    ///
    int _pointerFieldTypes;

    ///
    int _abstract;

    unsigned long _mtInfluenceMask;

    ///
    bool _systemComponent;

    ///
    bool _decoratable;

    ///
    bool _useLocalIncludes;

    ///
    bool _parentSystemComponent;

  ///
    std::list<Field> _fieldList;

  ///
    std::list<ProducedMethod> _producedMethodList;

    ///
    FieldKey findFieldKey (const char *key);

    ///
    NodeTokenKey findNodeTokenKey  ( const char *key);
    
    ///
    void putField ( std::ofstream &out, const char *prefix,
                                  FieldKey key, const char *value);

    /// last save name
    char *_fcdFileName;
    
protected:

public:

  /// Class Constructor
  FieldContainer (void);

  /// Class Copy Constructor
  FieldContainer (FieldContainer &obj);

  /// Class Descructor
  virtual ~FieldContainer (void);

    /// get the pointerFieldTypes string for the given index
    static const char *pointerFieldTypesStr(int index);

    /// get the abstract string for the given index
    static const char *abstractStr(int index);

    /// clear the attributes
    virtual void clear(void);

  /// get method for attribute name
  virtual char* name (void) { return _name; }

  /// set method for attribute name
  virtual void setName (const char* name);

  /// get method for attribute parentFieldContainer
  virtual char* parentFieldContainer (void) { return _parentFieldContainer; }

  /// set method for attribute parentFieldContainer
  virtual void setParentFieldContainer (const char* parentFieldContainer);

  /// get method for attribute parentFieldContainerHeader
  virtual char* parentFieldContainerHeader (void) { return _parentFieldContainerHeader; }

  /// set method for attribute parentFieldContainerHeader
  virtual void setParentFieldContainerHeader (const char* parentFieldContainerHeader);

  virtual bool isRootProducer(void) const {
return (_parentProducer==0) && (_producedMethodList.size()>0);}

  /// get method for attribute parentFieldContainerHeader
  virtual char* parentProducer (void) { return _parentProducer; }

  /// set method for attribute parentFieldContainerHeader
  void setParentProducer (const char* parentProducer );

  /// get method for attribute description
  virtual char* description (void) { return _description; }

  /// set method for attribute description
  virtual void setDescription (const char* description);

  /// get method for attribute library
  virtual char* library (void) { return _library; }

  /// set method for attribute library
  virtual void setLibrary (const char* library);
    
  /// get method for attribute pointerFieldTypes
  virtual int pointerFieldTypes (void) { return _pointerFieldTypes; }
    
  /// get method for attribute abstract
  virtual int abstract (void) { return _abstract; }

  /// set method for attribute pointerFieldTypes
  virtual void setPointerFieldTypes (int pointerFieldTypes) 
        { _pointerFieldTypes = pointerFieldTypes; }

  /// set method for attribute abstract
  virtual void setAbstract (int abstract) 
        { _abstract = abstract; }

  /// set method for attribute pointerFieldTypes
    virtual void setPointerFieldTypes (const char *str);

  /// set method for attribute abstract
    virtual void setAbstract (const char *str);
    
  /// get method for attribute systemComponent
  virtual bool systemComponent (void) { return _systemComponent; }

  /// set method for attribute systemComponent
    virtual void setSystemComponent (const char *str);

  /// set method for attribute systemComponent
  virtual void setSystemComponent (bool systemComponent) 
        { _systemComponent = systemComponent; }
    
    
  /// get method for attribute systemComponent
  virtual bool decoratable (void) { return _decoratable; }

  /// set method for attribute systemComponent
    virtual void setDecoratable (const char *str);

  /// set method for attribute systemComponent
  virtual void setDecoratable (bool val) 
        { _decoratable = val; }
    
  /// 
  virtual bool useLocalIncludes (void) { return _useLocalIncludes; }

  /// 
    virtual void setUseLocalIncludes (const char *str);
 
  ///  
  virtual void setUseLocalIncludes (bool val) 
        { _useLocalIncludes = val; }
   
  /// get method for attribute parentSystemComponent
  virtual bool parentSystemComponent (void) { return _parentSystemComponent; }

  /// set method for attribute systemComponent
    virtual void setParentSystemComponent (const char *str);

  /// set method for attribute systemComponent
  virtual void setParentSystemComponent (bool parentSystemComponent) 
        { _parentSystemComponent = parentSystemComponent; }

  ///
  std::list<Field> &fieldList(void) { return _fieldList; }

  ///
  std::list<ProducedMethod> &producedMethodList(void) { return _producedMethodList; }

    ///
    Field *getField(unsigned index);

    /// 
    virtual bool readDesc (const char *fileName = 0);

    /// 
    virtual bool readFieldDesc (xmlnodelist::const_iterator nI, list<Field>::iterator &npI);
    
    ///
    virtual bool readProducedMethodDesc (xmlnodelist::const_iterator nI, list<ProducedMethod>::iterator &pmI);

    ///
    virtual bool writeTempl ( std::ofstream & out, char *fcname, 
                                char *parentname, char *parentheader, bool decorator,
                                const char ** templ  );

    ///
    virtual bool writeDesc (const char *fileName = 0);

    ///
    virtual bool writeCode ( bool base, bool fc, const char *path = 0 );

    ///
    virtual bool writeCodeFields (const char *ptrFile);

    ///
    virtual bool writeBaseCodeDec (const char *decFile);

    ///
    virtual bool writeBaseCodeInl (const char *InlFile);

    ///
    virtual bool writeBaseCodeImp ( const char *impFile);

    ///
    virtual bool writeCodeDec ( const char *decFile );                                                                      
    ///
    virtual bool writeCodeInl ( const char *InlFile );                                                                      
    ///
    virtual bool writeCodeImp ( const char *impFile );

    virtual bool writeDecoratorBase ( const char *bdecFile, 
                                      const char *binlFile, 
                                      const char *bimpFile,
                                      const char *fldFile);

    virtual bool writeDecoratorCode ( const char *decFile, 
                                      const char *inlFile, 
                                      const char *impFile);
    /// 
    static const char *filePrefix(void) { return _filePrefix; }

    /// 
    static const char *decFileSuffix(void) { return _decFileSuffix; }

    ///
    static const char *inlFileSuffix(void) { return _inlFileSuffix; }

    ///
    static const char *impFileSuffix(void) { return _impFileSuffix; }

  /// create a new field and returns the index;
    int newField (const Field &newField);

    ///
    void delField(unsigned index);

    ///
    bool moveFieldLeft (unsigned index);

    ///
    bool moveFieldRight (unsigned index);

    ///
    unsigned numOfFields(void) { return _fieldList.size(); }


};

typedef FieldContainer* FieldContainerP;

#endif // FIELDCONTAINER_CLASS_DECLARATION
