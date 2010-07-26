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

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

OSG_BEGIN_NAMESPACE

template<typename TYPE>
inline
boost::optional<TYPE> ApplicationSettings::get_optional(const std::string& path) const
{
    return _PropertyTree.get_optional<TYPE>(path, settings_translator<TYPE>());
}

template<typename TYPE>
inline
TYPE ApplicationSettings::get(const std::string& path, const TYPE valueIfUndefined) const
{
    return _PropertyTree.get<TYPE>(path, valueIfUndefined, settings_translator<TYPE>());
}

template<typename TYPE>
inline
TYPE ApplicationSettings::get(const std::string& path) const
{
    return _PropertyTree.get_child(path).BOOST_NESTED_TEMPLATE get_value<TYPE>(settings_translator<TYPE>());
}

template<typename TYPE>
inline
std::vector<TYPE> ApplicationSettings::get_vec(const std::string& path) const
{
    std::vector<TYPE> Result;
    settings_translator<TYPE> tr;
    BOOST_FOREACH(boost::property_tree::ptree::value_type &v, const_cast<ApplicationSettings*>(this)->_PropertyTree.get_child(path))
        Result.push_back(tr.get_value(v.second.data()).get());
    return Result;
}

template<typename TYPE>
inline
void ApplicationSettings::put(const std::string& path, const TYPE& value, bool overwriteIfDefined)
{
    if(overwriteIfDefined || !_PropertyTree.get_optional<TYPE>(path, settings_translator<TYPE>()))
    {
        _PropertyTree.put(path, value, settings_translator<TYPE>());
    }
}

template<typename TYPE>
inline
void ApplicationSettings::put_vec(const std::string& path, const std::vector<TYPE>& value)
{
    BOOST_FOREACH(const TYPE &elem_value, value)
      _PropertyTree.put(path, elem_value, settings_translator<TYPE>());

}

// Custom extractor - converts data from string to T
template<class T> 
boost::optional<T> ApplicationSettings::settings_translator<T>::get_value(const std::string &str_value) const
{
    T value;
    const Char8* send_by_ref_temp = str_value.c_str();
    if(FieldTraits<T>::getFromCString(value, send_by_ref_temp))
    {
        return boost::optional<T>(value);
    }
    else
    {
        return boost::optional<T>();
    }
}

// Custom inserter - converts data from T to string
template<class T> 
std::string ApplicationSettings::settings_translator<T>::put_value(const T &value) const
{
    std::ostringstream StrStream;
    OutStream TheOutStream(StrStream);
    FieldTraits<T>::putToStream(value, TheOutStream);
    return StrStream.str();
}

// Custom extractor - converts data from string to T
//template<> 
//boost::optional<bool> ApplicationSettings::settings_translator<bool>::get_value(const std::string &str_value) const
//{
//    bool value;
//    const Char8* send_by_ref_temp = str_value.c_str();
//    if(FieldTraits2<bool>::getFromCString(value, send_by_ref_temp))
//    {
//        return boost::optional<bool>(value);
//    }
//    else
//    {
//        return boost::optional<bool>();
//    }
//}
//
//// Custom inserter - converts data from T to string
//template<> 
//std::string ApplicationSettings::settings_translator<bool>::put_value(const bool &value) const
//{
//    std::ostringstream StrStream;
//    OutStream TheOutStream(StrStream);
//    FieldTraits2<bool>::putToStream(value, TheOutStream);
//    return StrStream.str();
//}

OSG_END_NAMESPACE
