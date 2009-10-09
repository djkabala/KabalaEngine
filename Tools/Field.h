#ifndef FIELD_CLASS_DECLARATION
#define FIELD_CLASS_DECLARATION

/** 
@brief  Field description
@author jbehr, Thu Jan  8 19:55:06 1998

*/

#include <vector>
#include <string>

class Field 
{

  private:

    static const char *_defaultTypeName[];
    static const char *_cardinalityName[];
    static const char *_visibilityName [];
    static const char *_mtInfluenceName[];
    static const char *_accessName     [];

    static std::vector<std::string> _typeName;


    char *_name;
    int   _cardinality;
    char *_type;
    int   _visibility;
    int   _mtInfluence;
    char *_defaultValue;
    char *_defaultHeader;
    char *_description;
    char *_header;
    int   _access;
    bool   _publicRead;

  protected:

  public:

  /// Class Constructor
  Field (void);

  /// Class Copy Constructor
  Field (const Field &obj);

  /// Class Descructor
  virtual ~Field (void);

    /// init the type list with the default types, return the type count
    static int loadDefaultFieldTypeList(void);

    /// load the field type list for the given file, return the type count
    static int loadFieldTypeList(const char *fileName);

    /// get the type string for the given index
    static const char *typeStr (int index);

    /// get the cardinality string for the given index
    static const char *cardinalityStr (int index);

    /// get the visibility string for the given index
    static const char *visibilityStr (int index);

    /// get the visibility string for the given index
    static const char *accessStr (int index);

    /// get the cardinality string
    const char *cardinalityStr (void);

    /// get the visibility string
    const char *visibilityStr (void);

    /// get the visibility string
    const char *accessStr (void);

  /// get method for attribute name
  virtual char* name (void) const { return _name; }

  /// set method for attribute name
  virtual void setName (const char* name);

  /// get method for attribute type
  virtual int cardinality (void) const { return _cardinality; }

  /// set method for attribute type
  virtual void setCardinality (int c) { _cardinality = c; }

    /// set method for attribute type
    virtual void setCardinality (const char *cardinalityStr);

  /// get method for attribute type
  virtual char *type (void) const { return _type; }

  /// set method for attribute type
    virtual void setType ( const char* typeStr );

  /// get method for attribute visibility
  virtual int visibility (void) const { return _visibility; }

  /// set method for attribute visibility
  virtual void setVisibility (int visibility) 
        { _visibility = visibility; }

    /// set method for attribute visibility
    virtual void setVisibility (const char *visibilityStr);

    virtual int  getMTInfluence(      void              );
    virtual void setMTInfluence(const char *influenceStr);

    /// get method for attribute type
    virtual char *defaultValue (void) { return _defaultValue; }

    /// set method for attribute type
    virtual void setDefaultValue ( const char *defaultValue);

  /// get method for attribute defaultHeader
  virtual char* defaultHeader (void) { return _defaultHeader; }

  /// set method for attribute defaultHeader
  virtual void setDefaultHeader (const char* defaultHeader);

  /// get method for attribute description
  virtual char* description (void) { return _description; }

  /// set method for attribute description
  virtual void setDescription ( const char* description);

  /// get method for attribute header
  virtual char* header (void) { return _header; }

  /// set method for attribute header
  virtual void setHeader ( const char* header);

  /// get method for attribute public read
  virtual bool publicRead (void) const { return _publicRead; }

  /// set method for attribute publicRead
  virtual void setPublicRead ( bool publicRead){_publicRead = publicRead; }
  virtual void setPublicRead (const char* str );

  /// get method for attribute access
  virtual int access (void) const { return _access; }

  /// set method for attribute access
  virtual void setAccess (int access) 
        { _access = access; }

    /// set method for attribute visibility
    virtual void setAccess (const char *accessStr);

  /// 
  virtual bool getLine (char *name);

    ///
    virtual Field& operator= (const Field &obj);

    ///
    virtual bool operator== (const Field &obj);

};

typedef Field* FieldP;

#endif // FIELD_CLASS_DECLARATION


