#ifndef PRODUCED_METHOD_CLASS_DECLARATION
#define PRODUCED_METHOD_CLASS_DECLARATION

/** 
  @brief  ProducedMethod description
  @author dkabala

*/

#include <vector>
#include <string>

class ProducedMethod 
{

    private:

        char *_name;
        char *_producedEventType;
        char *_description;

    protected:

    public:

        /// Class Constructor
        ProducedMethod (void);

        /// Class Copy Constructor
        ProducedMethod (const ProducedMethod &obj);

        /// Class Descructor
        virtual ~ProducedMethod (void);

        /// get method for attribute name
        virtual char* name (void) const { return _name; }

        /// set method for attribute name
        virtual void setName (const char* name);

        /// get method for attribute type
        virtual char *producedEventType (void) const { return _producedEventType; }

        /// set method for attribute type
        virtual void setProducedEventType ( const char* typeStr );

        /// get method for attribute description
        virtual char* description (void) { return _description; }

        /// set method for attribute description
        virtual void setDescription ( const char* description);

        /// 
        virtual bool getLine (char *name);

        ///
        virtual ProducedMethod& operator= (const ProducedMethod &obj);

        ///
        virtual bool operator== (const ProducedMethod &obj);

};

typedef ProducedMethod* ProducedMethodP;

#endif // PRODUCED_METHOD_CLASS_DECLARATION


