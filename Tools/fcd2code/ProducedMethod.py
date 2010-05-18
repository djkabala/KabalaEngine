
import re;
import logging;

from FCDElement import FCDElement;

class ProducedMethod(FCDElement):
    """Represents a <ProducedMethod/> element from a .fcd file.
    """
    
    def __init__(self):
        super(ProducedMethod, self).__init__();
        self.m_log              = logging.getLogger("ProducedMethod");
        self.m_fieldContainer   = None;
        self.initFCDDict();
    
    def initFCDDict(self):
        """Sets the fcd dictionary to default values.
        """
        self.setFCD("name",                           "",         True);
        self.setFCD("type",                           "",         True);
        self.setFCD("typeNamespace",                           "",         True);
        self.setFCD("description",                    "",         True);
    
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
            
        TypeRaw           = self.getFCD("type");
        TypeRawCaps       = self._upcaseFirst(TypeRaw);
        
        Type              = self.getFCD("type");
        TypeNS            = self.getFCD("typeNamespace");
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

        # -----------------------------------------------------------------
        # Name
        # -----------------------------------------------------------------
          
        self["Name"]          = self.getFCD("name")[0].upper() + self.getFCD("name")[1:];
        self["DescName"]      = self.getFCD("name");

        if self.getFCD("name") == "id":
            self.m_log.warning("finalize: invalid field name: >%s<", 
                               self.getFCD("name"))
            self["Name"] = self["Name"] + "_invalidProducedMethodname"
            self["DescName"] = self["DescName"] + "_invalidProducedMethodname"

                 
        if self.getFCD("description").strip() == "":
            self["Description"]     = "";
            self["SafeDescription"] = "\"\"";
        else:
            self["Description"]     = self._formatString    (self.getFCD("description"), 4)
            self["SafeDescription"] = self._formatSafeString(self.getFCD("description"), 8)

    def _dumpValues(self):
        self.m_log.info("ProducedMethod dumpValues:");
        super(ProducedMethod, self)._dumpValues(self.m_log);
    
