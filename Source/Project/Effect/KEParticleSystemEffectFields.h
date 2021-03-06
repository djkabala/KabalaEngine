/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *               Copyright (C) 2009-2010 by David Kabala                     *
 *                                                                           *
 *   authors:  Robert Goetz (rdgoetz@iastate.edu)                            *
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


#ifndef _KEPARTICLESYSTEMEFFECTFIELDS_H_
#define _KEPARTICLESYSTEMEFFECTFIELDS_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGFieldContainerFields.h>
#include <OpenSG/OSGPointerSField.h>
#include <OpenSG/OSGPointerMField.h>


OSG_BEGIN_NAMESPACE

class ParticleSystemEffect;

OSG_GEN_CONTAINERPTR(ParticleSystemEffect);

/*! \ingroup GrpKabalaEngineFieldTraits
    \ingroup GrpLibOSGKabalaEngine
 */
template <>
struct FieldTraits<ParticleSystemEffect *> :
    public FieldTraitsFCPtrBase<ParticleSystemEffect *>
{
  private:

    static DataType             _type;

  public:

    typedef FieldTraits<ParticleSystemEffect *>  Self;

    enum                        { Convertible = NotConvertible };

    static KE_KABALAENGINE_DLLMAPPING DataType &getType(void);

    template<typename RefCountPolicy> inline
    static const Char8    *getSName     (void);

//    static const char *getSName(void) { return "SFParticleSystemEffectPtr"; }
    template<typename RefCountPolicy> inline
    static const Char8    *getMName     (void);

//    static const char *getMName(void) { return "MFParticleSystemEffectPtr"; }
};

template<> inline
const Char8 *FieldTraits<ParticleSystemEffect *, 0>::getSName<RecordedRefCountPolicy>(void)
{
    return "SFRecParticleSystemEffectPtr"; 
}

template<> inline
const Char8 *FieldTraits<ParticleSystemEffect *, 0>::getSName<UnrecordedRefCountPolicy>(void)
{
    return "SFUnrecParticleSystemEffectPtr"; 
}

template<> inline
const Char8 *FieldTraits<ParticleSystemEffect *, 0>::getSName<WeakRefCountPolicy>(void)
{
    return "SFWeakParticleSystemEffectPtr"; 
}

template<> inline
const Char8 *FieldTraits<ParticleSystemEffect *, 0>::getSName<NoRefCountPolicy>(void)
{
    return "SFUnrefdParticleSystemEffectPtr"; 
}

template<> inline
const Char8 *FieldTraits<ParticleSystemEffect *, 0>::getMName<RecordedRefCountPolicy>(void)
{
    return "MFRecParticleSystemEffectPtr"; 
}

template<> inline
const Char8 *FieldTraits<ParticleSystemEffect *, 0>::getMName<UnrecordedRefCountPolicy>(void)
{
    return "MFUnrecParticleSystemEffectPtr"; 
}

template<> inline
const Char8 *FieldTraits<ParticleSystemEffect *, 0>::getMName<WeakRefCountPolicy>(void)
{
    return "MFWeakParticleSystemEffectPtr"; 
}

template<> inline
const Char8 *FieldTraits<ParticleSystemEffect *, 0>::getMName<NoRefCountPolicy>(void)
{
    return "MFUnrefdParticleSystemEffectPtr"; 
}


#ifndef DOXYGEN_SHOULD_SKIP_THIS
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<ParticleSystemEffect *,
                      RecordedRefCountPolicy  > SFRecParticleSystemEffectPtr;
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<ParticleSystemEffect *,
                      UnrecordedRefCountPolicy> SFUnrecParticleSystemEffectPtr;
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<ParticleSystemEffect *,
                      WeakRefCountPolicy      > SFWeakParticleSystemEffectPtr;
/*! \ingroup GrpKabalaEngineFieldSFields */
typedef PointerSField<ParticleSystemEffect *,
                      NoRefCountPolicy        > SFUncountedParticleSystemEffectPtr;


/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<ParticleSystemEffect *,
                      RecordedRefCountPolicy  > MFRecParticleSystemEffectPtr;
/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<ParticleSystemEffect *,
                      UnrecordedRefCountPolicy> MFUnrecParticleSystemEffectPtr;
/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<ParticleSystemEffect *,
                      WeakRefCountPolicy      > MFWeakParticleSystemEffectPtr;
/*! \ingroup GrpKabalaEngineFieldMFields */
typedef PointerMField<ParticleSystemEffect *,
                      NoRefCountPolicy        > MFUncountedParticleSystemEffectPtr;




#else // these are the doxygen hacks

/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFRecParticleSystemEffectPtr : 
    public PointerSField<ParticleSystemEffect *,
                         RecordedRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFUnrecParticleSystemEffectPtr : 
    public PointerSField<ParticleSystemEffect *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFWeakParticleSystemEffectPtr :
    public PointerSField<ParticleSystemEffect *,
                         WeakRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldSFields \ingroup GrpLibOSGKabalaEngine */
struct SFUncountedParticleSystemEffectPtr :
    public PointerSField<ParticleSystemEffect *,
                         NoRefCountPolicy> {};


/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFRecParticleSystemEffectPtr :
    public PointerMField<ParticleSystemEffect *,
                         RecordedRefCountPolicy  > {};
/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFUnrecParticleSystemEffectPtr :
    public PointerMField<ParticleSystemEffect *,
                         UnrecordedRefCountPolicy> {};
/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFWeakParticleSystemEffectPtr :
    public PointerMField<ParticleSystemEffect *,
                         WeakRefCountPolicy      > {};
/*! \ingroup GrpKabalaEngineFieldMFields \ingroup GrpLibOSGKabalaEngine */
struct MFUncountedParticleSystemEffectPtr :
    public PointerMField<ParticleSystemEffect *,
                         NoRefCountPolicy        > {};



#endif // these are the doxygen hacks

OSG_END_NAMESPACE

#endif /* _KEPARTICLESYSTEMEFFECTFIELDS_H_ */
