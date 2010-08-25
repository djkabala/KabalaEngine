
import re;
import logging;

from FCDElement import FCDElement;

class ProducedEvent(FCDElement):
    """Represents a <ProducedEvent/> element from a .fcd file.
    """
    
    def __init__(self):
        super(ProducedEvent, self).__init__();
        self.m_log              = logging.getLogger("ProducedEvent");
        self.m_fieldContainer   = None;
        self.initFCDDict();
    
    def initFCDDict(self):
        """Sets the fcd dictionary to default values.
        """
        self.setFCD("name",                           "",         True);
        self.setFCD("detailsType",                           "",         True);
        self.setFCD("detailsTypeNamespace",                           "",         True);
        self.setFCD("consumable",                    "true",         True);
        self.setFCD("description",                    "",         True);
        self.setFCD("fieldHeader",                    "(AUTO)",   True);
        self.setFCD("typeHeader",                     "(AUTO)",   True);
    
    def setFieldContainer(self, container):
        self.m_fieldContainer = container;
    
    def getFieldContainer(self):
        return self.m_fieldContainer;
    
    #
    # Common tests

    #
    # Fill out dictionary from in (fcd) dictionary
    
    def finalize(self):

        # -----------------------------------------------------------------
        # Type and Namespace
        # -----------------------------------------------------------------
            
        TypeRaw           = self.getFCD("detailsType");
        TypeRawCaps       = self._upcaseFirst(TypeRaw);
        
        Type              = self.getFCD("detailsType");
        TypeNS            = self.getFCD("detailsTypeNamespace");
        TypeCaps          = self._upcaseFirst(Type);
        
        if TypeNS != "" and not TypeNS.endswith("::"):
            TypeNS = TypeNS + "::"

        TypeCaps      = self._upcaseFirst(Type + "Ptr");
        Type          = Type + " *";
              
        self["Type"]          = Type;
        self["TypeNamespace"] = TypeNS;
        self["TypeNS"]        = TypeNS;
        self["TypeCaps"]      = TypeCaps;
        self["FullType"]      = TypeNS + Type;
        self["TypeRaw"]       = TypeRaw;
        self["EventDetailsType"]       = TypeRaw + "* const";

        # -----------------------------------------------------------------
        # Name
        # -----------------------------------------------------------------
          
        self["Name"]          = self.getFCD("name")[0].upper() + self.getFCD("name")[1:];
        self["DescName"]      = self.getFCD("name");
        
        self["consumable"]      = (self.getFCD("consumable") == "true");

        if self.getFCD("name") == "id":
            self.m_log.warning("finalize: invalid field name: >%s<", 
                               self.getFCD("name"))
            self["Name"] = self["Name"] + "_invalidProducedEventname"
            self["DescName"] = self["DescName"] + "_invalidProducedEventname"

                 
        if self.getFCD("description").strip() == "":
            self["Description"]     = "";
            self["SafeDescription"] = "\"\"";
        else:
            self["Description"]     = self._formatString    (self.getFCD("description"), 4)
            self["SafeDescription"] = self._formatSafeString(self.getFCD("description"), 8)
            
            
        fieldInclude = "";
        
        if ((self.getFCD("fieldHeader") == ""      ) or 
            (self.getFCD("fieldHeader") == "(AUTO)")   ):
            
            if self.getFieldContainer().isSystemComponent():
                fieldInclude = "OSG"
            else:
                fieldInclude = "OpenSG/OSG"

            fieldInclude = fieldInclude + TypeRawCaps               + "Fields.h"

            if(self.getFieldContainer().useLocalIncludes()):
                fieldInclude = "\"" + fieldInclude + "\""
            else:
                fieldInclude = "<" + fieldInclude + ">"

        else:
            if ((self.getFCD("fieldHeader").find("\"") == -1) and
                (self.getFCD("fieldHeader").find("<")  == -1)    ):
                fieldInclude = "\"" + self.getFCD("fieldHeader") + "\"";
            else:
                fieldInclude = self.getFCD("fieldHeader");

        self["FieldInclude"]     = fieldInclude
        self["needFieldInclude"] = True;     
        
        typeInclude = "";
        
        if ((self.getFCD("typeHeader") == "")      or
            (self.getFCD("typeHeader") == "(AUTO)")  ):

            if self.getFieldContainer().isSystemComponent():
                typeInclude = "OSG";
            else:
                typeInclude = "OpenSG/OSG";
        
            typeInclude = typeInclude + TypeRawCaps;
                 
            typeInclude = typeInclude.replace("Parent", "");
            typeInclude = typeInclude + ".h"

            if(self.getFieldContainer().useLocalIncludes()):
                typeInclude = "\"" + typeInclude + "\""
            else:
                typeInclude = "<" + typeInclude + ">"


        else:
            if ((self.getFCD("typeHeader").find("\"") == -1) and
                (self.getFCD("typeHeader").find("<")  == -1)    ):
                typeInclude = "\"" + self.getFCD("typeHeader") + "\"";
            else:
                typeInclude = self.getFCD("typeHeader");
        
        self["TypeInclude"]     = typeInclude;
        self["needTypeInclude"] = True;


    def _dumpValues(self):
        self.m_log.info("ProducedEvent dumpValues:");
        super(ProducedEvent, self)._dumpValues(self.m_log);
    
