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

#ifndef _KEAPPLICATIONSETTINGS_H_
#define _KEAPPLICATIONSETTINGS_H_
#ifdef __sgi
#pragma once
#endif

#include <OpenSG/OSGConfig.h>
#include "KEKabalaEngineDef.h"

#include <OpenSG/OSGBoostPathFields.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <boost/optional.hpp>
#include <sstream>

OSG_BEGIN_NAMESPACE

/*! \brief ApplicationSettings class. See \ref
           PageKabalaEngineApplicationSettings for a description.
*/

class KE_KABALAENGINE_DLLMAPPING ApplicationSettings
{
  protected:
    // Custom translator that works with most OpenSG types
    template<class T> 
    struct settings_translator
    {
    public:
        typedef settings_translator<T> type;
        typedef std::string            internal_type;
        typedef T                      external_type;

        // Custom extractor - converts data from string to T
        boost::optional<T> get_value(const std::string &str_value) const;

        // Custom inserter - converts data from T to string
        std::string put_value(const T &value) const;
    };


    boost::property_tree::ptree _PropertyTree;

    /*==========================  PUBLIC  =================================*/

  public:

    typedef ApplicationSettings     Self;
    typedef std::basic_istream<boost::property_tree::ptree::key_type::value_type> InputStreamType;
    typedef std::basic_ostream<boost::property_tree::ptree::key_type::value_type> OutputStreamType;

    /*---------------------------------------------------------------------*/
    /*! \name                  Constructors                                */
    /*! \{                                                                 */

    ApplicationSettings(void);
    ApplicationSettings(const ApplicationSettings &source);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ApplicationSettings(void);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                     Output                                   */
    /*! \{                                                                 */

    virtual void dump(      UInt32     uiIndent = 0) const;

    /*! \}                                                                 */

	bool writeXML(const BoostPath& FilePath);
    //bool writeXML(OutputStreamType& Stream);

	bool readXML(const BoostPath& FilePath);
    bool readXML(InputStreamType& Stream);
    
    template<typename TYPE>
    boost::optional<TYPE> get_optional(const std::string& path) const;

    template<typename TYPE>
    TYPE get(const std::string& path, const TYPE valueIfUndefined) const;

    template<typename TYPE>
    TYPE get(const std::string& path) const;

    template<typename TYPE>
    std::vector<TYPE> get_vec(const std::string& path) const;

    template<typename TYPE>
    void put(const std::string& path, const TYPE& value, bool overwriteIfDefined = true);

    template<typename TYPE>
    void put_vec(const std::string& path, const std::vector<TYPE>& value);

    /*=========================  PROTECTED  ===============================*/

  protected:

    /*

    basic
         data
             directory
         last_opened_project
         recent_projects
                        max
                        file

         window
               position
               size
               fullscreen

         default_mode

   author_data

   logging
          type
          level
          file
          header_elements

   builder

   player
         debugger
                 camera
                       near_plane
                       far_plane
                       fov
                 help_panel
                 heirarchy_panel
                 content_panel
                 undo_history
                             enable
                             max_length
                 lua
                    console
                           max_history
                 grid
                     draw
                     dimensions
                     segment_length
                     color
                 selected_node
                              volume_box
                                    draw
                                    color
                                    line_thickness
                              axis
                                  draw
                                  x_axis_color
                                  y_axis_color
                                  z_axis_color
                                  line_thickness
                                  relative_length
                             mesh
                                 draw
                                 color
                                 line_thickness

   startscreen


    */



    /*==========================  PRIVATE  ================================*/

  private:
};

template<> 
struct ApplicationSettings::settings_translator<std::string>
{
public:
    typedef settings_translator<std::string> type;
    typedef std::string            internal_type;
    typedef bool                      external_type;

    // Custom extractor - converts data from string to T
    boost::optional<std::string> get_value(const std::string &str_value) const
    {
        return boost::optional<std::string>(str_value);
    }


    // Custom inserter - converts data from T to string
    std::string put_value(const std::string &value) const
    {
        return value;
    }
};

template<> 
struct ApplicationSettings::settings_translator<bool>
{
public:
    typedef settings_translator<bool> type;
    typedef std::string            internal_type;
    typedef bool                      external_type;

    // Custom extractor - converts data from string to T
    boost::optional<bool> get_value(const std::string &str_value) const
    {
        const Char8* send_by_ref_temp = str_value.c_str();
        bool value(TypeTraits<bool>::getFromCString(send_by_ref_temp));

        return boost::optional<bool>(value);
    }


    // Custom inserter - converts data from T to string
    std::string put_value(const bool &value) const
    {
        std::string StrValue("");
        TypeTraits<bool>::putToString(value, StrValue);
        return StrValue;
    }
};

typedef ApplicationSettings *ApplicationSettingsP;

OSG_END_NAMESPACE

#include "KEApplicationSettings.inl"

#endif /* _KEAPPLICATIONSETTINGS_H_ */
