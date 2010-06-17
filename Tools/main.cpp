

#include <string>
#include <iostream>

#ifndef FCD_TERM

#include "FieldContainerViewCtl.h"
#include <qapplication.h>

int main( int argc, char **argv )
{ 
    int retCode = -1;
    FieldContainer fc;
    bool writeBase = false, writeFC = false;
    std::string fcdFile, typeFile;
    std::string writePath;

#ifdef WIN32
     const char sep = '\\';
#else
     const char sep = '/';
#endif

    // Win32 doesn't have getopt, DIY
    do 
    {
        argc--, argv++;
        if ( argc && argv[0][0] == '-' )
        {
            switch (argv[0][1]) 
            {
            case 'd':
                if ( argc > 1 )
                {
                    fcdFile = argv[1];
                    argv++, argc--;
                }
                else
                {
                    std::cerr << "fcdEdit: -d but no argument given!" <<std::endl;
                    return 1;
                }                
                break;
            case 't':
                if ( argc > 1 )
                {
                    typeFile = argv[1];
                    argv++, argc--;
                }
                else
                {
                    std::cerr << "fcdEdit: -t but no argument given!" <<std::endl;
                    return 1;
                }                
                break;
            case 'b':
                writeBase = true;
                break;
            case 'f':
                writeFC = true;
                break;
            case 'p':
                if ( argc > 1 )
                {
                    writePath = argv[1];
                    argv++, argc--;
                    if(writePath[writePath.size()-1] != sep)
                        writePath += sep;
                }
                else
                {
                    std::cerr << "fcdEdit: -p but no argument given!" <<std::endl;
                    return 1;
                }                
                break;
             case 'h':
                std::cerr << "Usage: fcdEdit -d file.fcd -t file.ftd -bfh" << std::endl;
                std::cerr << "  -d file.fcd: load the field container description" << std::endl;
                std::cerr << "  -t file.ftd: load the field type description" << std::endl;
                std::cerr << "  -b write the field container base code files" << std::endl;
                std::cerr << "  -f write the field container code files" << std::endl;
                std::cerr << "  -p base code files output path" << std::endl;
                std::cerr << "  -h print usage" << std::endl;
                return 0;
                break;
            }
        }
        else
            break;
    }
    while (argc > 0);
        
    if ( argc )
        fcdFile = argv[ 0 ];
        
    if (typeFile.empty())
        Field::loadDefaultFieldTypeList();
    else
        Field::loadFieldTypeList(typeFile.c_str());

    if (writeBase || writeFC) 
    {
        if (fcdFile.empty())
            std::cerr << "ERROR: Can't write code without description" << std::endl;
        else 
        {
            fc.readDesc(fcdFile.c_str());
            fc.writeCode(writeBase,writeFC,writePath.c_str());
            retCode = 0;
        }
    }
    else 
    {
        QApplication app( argc, argv );
        FieldContainerViewCtl fCViewCtl( fcdFile.c_str() );
        app.setMainWidget(&fCViewCtl);
        fCViewCtl.show();
        retCode = app.exec();
    }

    return 0;
}

#else // FCD_TERM

#include "FieldContainer.h"

int main( int argc, char **argv )
{ 
    int retCode = -1;
    FieldContainer fc;
    bool writeBase = false, writeFC = false;
    const char *optstring = "d:t:bfh";
    std::string fcdFile, typeFile;
    std::string writePath;
    int opt = 0;

#ifdef WIN32
     const char sep = '\\';
#else
     const char sep = '/';
#endif

#if 0
    while (opt >= 0) {
        opt = getopt(argc,argv,optstring);
        switch (opt) {
        case 'd':
            fcdFile = optarg;
            break;
        case 't':
            typeFile = optarg;
            break;
        case 'b':
            writeBase = true;
            break;
        case 'f':
            writeFC = true;
            break;
        case 'p':
            writePath = optarg;
            if(writePath[writePath.size()-1] != sep)
                writePath += sep;
            break;
        case 'h':
            std::cerr << "Usage: fcdEdit -d file.fcd -t file.ftd -bfh" << std::endl;
            std::cerr << "  -d file.fcd: load the field container description" << std::endl;
            std::cerr << "  -t file.ftd: load the field type description" << std::endl;
            std::cerr << "  -b write the field container base code files" << std::endl;
            std::cerr << "  -f write the field container code files" << std::endl;
            std::cerr << "  -p base code files output path" << std::endl;
            std::cerr << "  -h print usage" << std::endl;
            return 0;
            break;
        }
    }
#endif

    // Win32 doesn't have getopt, DIY
    do 
    {
        argc--, argv++;
        if ( argc && argv[0][0] == '-' )
        {
            switch (argv[0][1]) 
            {
            case 'd':
                if ( argc > 1 )
                {
                    fcdFile = argv[1];
                    argv++, argc--;
                }
                else
                {
                    std::cerr << "fcdEdit: -d but no argument given!" <<std::endl;
                    return 1;
                }                
                break;
            case 't':
                if ( argc > 1 )
                {
                    typeFile = argv[1];
                    argv++, argc--;
                }
                else
                {
                    std::cerr << "fcdEdit: -t but no argument given!" <<std::endl;
                    return 1;
                }                
                break;
            case 'b':
                writeBase = true;
                break;
            case 'f':
                writeFC = true;
                break;
            case 'p':
                if ( argc > 1 )
                {
                    writePath = argv[1];
                    argv++, argc--;
                    if(writePath[writePath.size()-1] != sep)
                        writePath += sep;
                }
                else
                {
                    std::cerr << "fcdEdit: -p but no argument given!" <<std::endl;
                    return 1;
                }                
                break;
             case 'h':
                std::cerr << "Usage: fcdEdit -d file.fcd -t file.ftd -bfh" << std::endl;
                std::cerr << "  -d file.fcd: load the field container description" << std::endl;
                std::cerr << "  -t file.ftd: load the field type description" << std::endl;
                std::cerr << "  -b write the field container base code files" << std::endl;
                std::cerr << "  -f write the field container code files" << std::endl;
                std::cerr << "  -p base code files output path" << std::endl;
                std::cerr << "  -h print usage" << std::endl;
                return 0;
                break;
            }
        }
        else
            break;
    }
    while (argc > 0);

    if ( argc )
        fcdFile = argv[ 0 ];
        
    if (typeFile.empty())
        Field::loadDefaultFieldTypeList();
    else
        Field::loadFieldTypeList(typeFile.c_str());

    if (writeBase || writeFC) 
    {
        if (fcdFile.empty())
            std::cerr << "ERROR: Can't write code without description" << std::endl;
        else 
        {
            fc.readDesc(fcdFile.c_str());
            fc.writeCode(writeBase,writeFC,writePath.c_str());
            retCode = 0;
        }
    }

    return 0;
}

#endif





