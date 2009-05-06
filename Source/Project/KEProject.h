/*---------------------------------------------------------------------------*\
 *                             Kabala Engine                                 *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala (dkabala@vrac.iastate.edu)                        *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 3.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
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

#ifndef _KEPROJECT_H_
#define _KEPROJECT_H_
#ifdef __sgi
#pragma once
#endif

#include "KEConfig.h"

#include "KEProjectBase.h"

#include <OpenSG/Toolbox/OSGPathType.h>
#include <OpenSG/Input/OSGWindowEventProducerFields.h>

OSG_USING_NAMESPACE
KE_BEGIN_NAMESPACE

/*! \brief Project class. See \ref 
           PageKabalaEngineProject for a description.
*/

class KE_KABALAENGINELIB_DLLMAPPING Project : public ProjectBase
{
  private:

    typedef ProjectBase Inherited;

    /*==========================  PUBLIC  =================================*/
  public:

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(BitVector  whichField, 
                         ::osg::UInt32     origin    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      ::osg::UInt32     uiIndent = 0, 
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

	void start(void);

	void stop(void);

	void setActiveScene(ScenePtr TheScene);

	void setActiveBackground(BackgroundPtr TheBackground);

	void setActiveCamera(CameraPtr TheCamera);

	MFForegroundPtr &getActiveForegrounds(void);

	void setActiveNode(NodePtr TheNode);

	void save(const Path& ProjectFile);

	static ProjectPtr load(const Path& ProjectFile);

	static ProjectPtr create(const Path& ProjectFile);

	void save(void);

	void attachNames(void);

	WindowEventProducerPtr getEventProducer(void) const;
	
    /*=========================  PROTECTED  ===============================*/
  protected:
	  ViewportPtr createDefaultViewport(void) const;

    // Variables should all be in ProjectBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    Project(void);
    Project(const Project &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~Project(void); 

    /*! \}                                                                 */
    
    /*==========================  PRIVATE  ================================*/
  private:

    friend class FieldContainer;
    friend class ProjectBase;

    static void initMethod(void);

    // prohibit default functions (move to 'public' if you need one)

    void operator =(const Project &source);
};

typedef Project *ProjectP;

KE_END_NAMESPACE

#include "KEProjectBase.inl"
#include "KEProject.inl"

#endif /* _KEPROJECT_H_ */
