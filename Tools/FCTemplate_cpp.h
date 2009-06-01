/* This is a template file for fcdEdit.
 * To create it from sample source,  cut'n'paste the source and apply the following
 * substitutions:
 * s|\|\\|g 
 * s|"|\"|g 
 * s|^|"| 
 * s|$|",|
 */

char *FCTemplate_cpp[]={
"/*---------------------------------------------------------------------------*\\",
" *                             Kabala Engine                                 *",
" *                                                                           *",
" *                                                                           *",
" *   contact: djkabala@gmail.com                                             *",
" *                                                                           *",
"\\*---------------------------------------------------------------------------*/",
"/*---------------------------------------------------------------------------*\\",
" *                                License                                    *",
" *                                                                           *",
" * This library is free software; you can redistribute it and/or modify it   *",
" * under the terms of the GNU General Public License as published            *",
" * by the Free Software Foundation, version 3.                               *",
" *                                                                           *",
" * This library is distributed in the hope that it will be useful, but       *",
" * WITHOUT ANY WARRANTY; without even the implied warranty of                *",
" * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *",
" * Library General Public License for more details.                          *",
" *                                                                           *",
" * You should have received a copy of the GNU General Public                 *",
" * License along with this library; if not, write to the Free Software       *",
" * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *",
" *                                                                           *",
"\\*---------------------------------------------------------------------------*/",
"/*---------------------------------------------------------------------------*\\",
" *                                Changes                                    *",
" *                                                                           *",
" *                                                                           *",
" *                                                                           *",
" *                                                                           *",
" *                                                                           *",
" *                                                                           *",
"\\*---------------------------------------------------------------------------*/",
"",
"//---------------------------------------------------------------------------",
"//  Includes",
"//---------------------------------------------------------------------------",
"",
"#include <stdlib.h>",
"#include <stdio.h>",
"",
"@@if !SystemComponent",
"@@if Library",
"#define KE_COMPILE@!LIBNAME!@LIB",
"",
"@@endif",
"@@endif",
"#include <@!HeaderPrefix!@OSGConfig.h>",
"",
"#include \"KE@!Classname!@.h\"",
"",
"OSG_BEGIN_NAMESPACE",
"",
"/***************************************************************************\\",
" *                            Description                                  *",
"\\***************************************************************************/",
"",
"/*! \\class osg::@!Classname!@",
"@!Description!@",
"*/",
"",
"/***************************************************************************\\",
" *                           Class variables                               *",
"\\***************************************************************************/",
"",
"/***************************************************************************\\",
" *                           Class methods                                 *",
"\\***************************************************************************/",
"",
"void @!Classname!@::initMethod (void)",
"{",
"}",
"",
"",
"/***************************************************************************\\",
" *                           Instance methods                              *",
"\\***************************************************************************/",
"",
"/*-------------------------------------------------------------------------*\\",
" -  private                                                                 -",
"\\*-------------------------------------------------------------------------*/",
"",
"/*----------------------- constructors & destructors ----------------------*/",
"",
"@!Classname!@::@!Classname!@(void) :",
"    Inherited()",
"{",
"}",
"",
"@!Classname!@::@!Classname!@(const @!Classname!@ &source) :",
"    Inherited(source)",
"{",
"}",
"",
"@!Classname!@::~@!Classname!@(void)",
"{",
"}",
"",
"/*----------------------------- class specific ----------------------------*/",
"",
"void @!Classname!@::changed(BitVector whichField, UInt32 origin)",
"{",
"    Inherited::changed(whichField, origin);",
"}",
"",
"void @!Classname!@::dump(      UInt32    , ",
"                         const BitVector ) const",
"{",
"    SLOG << \"Dump @!Classname!@ NI\" << std::endl;", 
"}",
"",
"",
"OSG_END_NAMESPACE",
"",
NULL};
