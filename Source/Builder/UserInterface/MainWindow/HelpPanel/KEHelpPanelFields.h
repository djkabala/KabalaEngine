/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *               Copyright (C) 2009-2010 by David Kabala                     *
 *                                                                           *
 *   authors:  David Kabala (djkabala@gmail.com)                             *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU General Public License as published            *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU General Public                 *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

/*****************************************************************************\
 *****************************************************************************
 **                                                                         **
 **                  This file is automatically generated.                  **
 **                                                                         **
 **          Any changes made to this file WILL be lost when it is          **
 **           regenerated, which can become necessary at any time.          **
 **                                                                         **
 *****************************************************************************
\*****************************************************************************/


#ifndef _KEHELPPANELFIELDS_H_
#define _KEHELPPANELFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGFieldContainerFields.h>
#include <OpenSG/OSGPointerSField.h>
#include <OpenSG/OSGPointerMField.h>


OSG_BEGIN_NAMESPACE

class HelpPanel;

OSG_GEN_CONTAINERPTR(HelpPanel);

/*! \ingroup GrpKabalaEngineFieldTraits
    \ingroup GrpLibOSGKabalaEngine
 */
template <>
struct FieldTraits<HelpPanel *> :
    public FieldTraitsFCPtrBase<HelpPanel *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<HelpPanel *>  Self;

    enum                        { Convertible = NotConvertible };

    static KE_KABALAENGINE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFHelpPanelPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFHelpPanelPtr"; }
};

template<> inline
const Char8 *FieldTraits<HelpPanel *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecHelpPanelPtr"; 
}

template<> inline
const Char8 *FieldTraits<HelpPanel *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecHelpPanelPtr"; 
}

template<> inline
const Char8 *FieldTraits<HelpPanel *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakHelpPanelPtr"; 
}

template<> inline
const Char8 *FieldTraits<HelpPanel *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdHelpPanelPtr"; 
}

template<> inline
const Char8 *FieldTraits<HelpPanel *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecHelpPanelPtr"; 
}

template<> inline
const Char8 *FieldTraits<HelpPanel *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecHelpPanelPtr"; 
}

template<> inline
const Char8 *FieldTraits<HelpPanel *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakHelpPanelPtr"; 
}

template<> inline
const Char8 *FieldTraits<HelpPanel *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdHelpPanelPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<HelpPanel *,
                      RecordedRefCountPolicy  > SFRecHelpPanelPtr;
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<HelpPanel *,
                      UnrecordedRefCountPolicy> SFUnrecHelpPanelPtr;
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<HelpPanel *,
                      WeakRefCountPolicy      > SFWeakHelpPanelPtr;
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<HelpPanel *,
                      NoRefCountPolicy        > SFUncountedHelpPanelPtr;


/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<HelpPanel *,
                      RecordedRefCountPolicy  > MFRecHelpPanelPtr;
/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<HelpPanel *,
                      UnrecordedRefCountPolicy> MFUnrecHelpPanelPtr;
/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<HelpPanel *,
                      WeakRefCountPolicy      > MFWeakHelpPanelPtr;
/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<HelpPanel *,
                      NoRefCountPolicy        > MFUncountedHelpPanelPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFRecHelpPanelPtr : 
    public PointerSField<HelpPanel *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFUnrecHelpPanelPtr : 
    public PointerSField<HelpPanel *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFWeakHelpPanelPtr :
    public PointerSField<HelpPanel *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFUncountedHelpPanelPtr :
    public PointerSField<HelpPanel *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFRecHelpPanelPtr :
    public PointerMField<HelpPanel *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFUnrecHelpPanelPtr :
    public PointerMField<HelpPanel *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFWeakHelpPanelPtr :
    public PointerMField<HelpPanel *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFUncountedHelpPanelPtr :
    public PointerMField<HelpPanel *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _KEHELPPANELFIELDS_H_ */
