/*---------------------------------------------------------------------------*\
 *                                OpenSG                                     *
 *                                                                           *
 *                                                                           *
 *             Copyright (C) 2000-2002 by the OpenSG Forum                   *
 *                                                                           *
 *                            www.opensg.org                                 *
 *                                                                           *
 *   contact: dirk@opensg.org, gerrit.voss@vossg.org, jbehr@zgdv.de          *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
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

#ifndef _BINSOCKETMESSAGE_INL_
#define _BINSOCKETMESSAGE_INL_

OSG_BEGIN_NAMESPACE

/*---------------------------------------------------------------------*/
/*                      write message                                  */

inline void BinaryMessage::putUInt32(const UInt32  value)
{
    UInt32 net = osgHostToNet<UInt32>(value);
    _buffer.insert(_buffer.end(),
                   reinterpret_cast<UInt8*>(&net),
                   reinterpret_cast<UInt8*>(&net) + sizeof(net));
}

inline void BinaryMessage::putInt32 (const Int32  value)
{
    Int32 net = osgHostToNet<Int32>(value);
    _buffer.insert(_buffer.end(),
                   reinterpret_cast<UInt8*>(&net),
                   reinterpret_cast<UInt8*>(&net) + sizeof(net));
}

inline void BinaryMessage::putUInt16(const UInt16  value)
{
    UInt16 net = osgHostToNet<UInt16>(value);
    _buffer.insert(_buffer.end(),
                   reinterpret_cast<UInt8*>(&net),
                   reinterpret_cast<UInt8*>(&net) + sizeof(net));
}

inline void BinaryMessage::putInt16 (const Int16  value)
{
    Int16 net = osgHostToNet<Int16>(value);
    _buffer.insert(_buffer.end(),
                   reinterpret_cast<UInt8*>(&net),
                   reinterpret_cast<UInt8*>(&net) + sizeof(net));
}

inline void BinaryMessage::putUInt8 (const UInt8   value)
{
    _buffer.push_back(value);
}

inline void BinaryMessage::putInt8  (const Int8   value)
{
    UInt8 v = static_cast<const UInt8>(value);
    _buffer.push_back(v);
}

inline void BinaryMessage::putString(const std::string &value)
{
    putUInt32(value.size());
    if(value.size())
    {
        const UInt8 *s = reinterpret_cast<const UInt8*>(value.c_str());
        const UInt8 *e = s + value.size();
        _buffer.insert(_buffer.end(), s, e);
    }
}

inline void BinaryMessage::putReal32(const Real32  value)
{
    UInt32 net = osgHostToNetFP(value);

    _buffer.insert(_buffer.end(),
                   reinterpret_cast<UInt8*>(&net),
                   reinterpret_cast<UInt8*>(&net) + sizeof(net));
}

/*---------------------------------------------------------------------*/
/*                      read message                                   */

inline void BinaryMessage::getUInt32(UInt32  &value)
{
    UInt32 net = *reinterpret_cast<UInt32*>(&_buffer[_pos]);
    value = osgNetToHost<UInt32>(net);
    _pos += sizeof(net);
}

inline void BinaryMessage::getInt32 (Int32  &value)
{
    Int32 net = *reinterpret_cast<Int32*>(&_buffer[_pos]);
    value = osgNetToHost<Int32>(net);
    _pos += sizeof(net);
}

inline void BinaryMessage::getUInt16(UInt16  &value)
{
    UInt16 net = *reinterpret_cast<UInt16*>(&_buffer[_pos]);
    value = osgNetToHost<UInt16>(net);
    _pos += sizeof(net);
}

inline void BinaryMessage::getInt16 (Int16  &value)
{
    Int16 net = *reinterpret_cast<Int16*>(&_buffer[_pos]);
    value = osgNetToHost<Int16>(net);
    _pos += sizeof(net);
}

inline void BinaryMessage::getUInt8 (UInt8   &value)
{
    value = _buffer[_pos++];
}

inline void BinaryMessage::getInt8  (Int8   &value)
{
    value = _buffer[_pos++];
}

inline void BinaryMessage::getString(std::string &value)
{
    UInt32 size;
    getUInt32(size);

    if(size)
    {
// error if [] checks index
//        value.assign(reinterpret_cast<char*>(&_buffer[_pos       ]),
//                     reinterpret_cast<char*>(&_buffer[_pos + size]) );

        value.assign(reinterpret_cast<char*>(&(_buffer[_pos])), size);

        _pos += size;
    }
    else
    {
        value.erase();
    }
}

inline void BinaryMessage::getReal32(Real32  &value)
{
    UInt32 net = getUInt32();
    
    value = osgNetToHostFP(net);
}

inline UInt32 BinaryMessage::getUInt32(void)
{
    UInt32 value;
    getUInt32(value);
    return value;
}

inline Int32  BinaryMessage::getInt32 (void)
{
    Int32 value;
    getInt32(value);
    return value;
}

inline UInt16 BinaryMessage::getUInt16(void)
{
    UInt16 value;
    getUInt16(value);
    return value;
}

inline Int16  BinaryMessage::getInt16 (void)
{
    Int16 value;
    getInt16(value);
    return value;
}

inline UInt8  BinaryMessage::getUInt8 (void)
{
    UInt8 value;
    getUInt8(value);
    return value;
}

inline Int8   BinaryMessage::getInt8  (void)
{
    Int8 value;
    getInt8(value);
    return value;
}

inline std::string BinaryMessage::getString(void)
{
    std::string value;
    getString(value);
    return value;
}

inline Real32 BinaryMessage::getReal32(void)
{
    Real32 value;
    getReal32(value);
    return value;
}

OSG_END_NAMESPACE

#endif
