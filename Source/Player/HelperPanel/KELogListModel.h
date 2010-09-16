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

#ifndef _KELOGLISTMODEL_H_
#define _KELOGLISTMODEL_H_
#ifdef __sgi
#pragma once
#endif

#include "KELogListModelBase.h"
#include "Application/Logging/KELogEventDetailsFields.h"

OSG_BEGIN_NAMESPACE

/*! \brief LogListModel class. See \ref
           PageKabalaEngineLogListModel for a description.
*/

class KE_KABALAENGINE_DLLMAPPING LogListModel : public LogListModelBase
{
  protected:

    /*==========================  PUBLIC  =================================*/

  public:

    typedef LogListModelBase Inherited;
    typedef LogListModel     Self;

    /*---------------------------------------------------------------------*/
    /*! \name                      Sync                                    */
    /*! \{                                                                 */

    virtual void changed(ConstFieldMaskArg whichField,
                         UInt32            origin,
                         BitVector         details    );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0,
                      const BitVector  bvFlags  = 0) const;

    /*! \}                                                                 */

	virtual UInt32 getSize(void) const;

    virtual boost::any getElementAt(UInt32 index) const;

    boost::signals2::connection connectLogging(void);
    void disconnectLogging(void);
    /*=========================  PROTECTED  ===============================*/

  protected:

    // Variables should all be in LogListModelBase.

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    LogListModel(void);
    LogListModel(const LogListModel &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~LogListModel(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Init                                    */
    /*! \{                                                                 */

    static void initMethod(InitPhase ePhase);

    /*! \}                                                                 */
    /*! \name                       Sync                                   */
    /*! \{                                                                 */

    virtual void resolveLinks(void);

    /*! \}                                                                 */

    void handleLogEvent(LogEventDetails* const details);
    void updateSize(void);

    std::deque<std::string> _Logs;
    boost::signals2::connection _LogConnection;
    /*==========================  PRIVATE  ================================*/

  private:

    friend class FieldContainer;
    friend class LogListModelBase;

    // prohibit default functions (move to 'public' if you need one)
    void operator =(const LogListModel &source);
};

typedef LogListModel *LogListModelP;

OSG_END_NAMESPACE

#include "KELogListModelBase.inl"
#include "KELogListModel.inl"

#endif /* _KELOGLISTMODEL_H_ */
