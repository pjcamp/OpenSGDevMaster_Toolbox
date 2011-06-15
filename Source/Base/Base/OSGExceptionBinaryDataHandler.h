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

#ifndef _OSGEXCEPTIONBINARYDATAHANDLER_H_
#define _OSGEXCEPTIONBINARYDATAHANDLER_H_
#ifdef __sgi
#pragma once
#endif

#include "OSGConfig.h"
#include "OSGBaseDef.h"
#include "OSGBaseTypes.h"
#include "OSGException.h"
#include "OSGBaseFunctions.h"

#include <vector>
#include <list>
#include <string>

OSG_BEGIN_NAMESPACE

/*! \ingroup GrpBaseBase
    \ingroup GrpBaseBaseHelper
    \ingroup GrpLibOSGBase
    \nohierarchy
 */

class OSG_BASE_DLLMAPPING ExceptionBinaryDataHandler 
{
    /*==========================  PUBLIC  =================================*/

  public:

    /*---------------------------------------------------------------------*/
    /*! \name                   Exceptions                                 */
    /*! \{                                                                 */

    struct ReadError : public Exception 
    {
        ReadError(const Char8 *reason);
    };
    
    struct WriteError : public Exception 
    {
        WriteError(const Char8 *reason);
    };

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Constructors                               */
    /*! \{                                                                 */

    ExceptionBinaryDataHandler(UInt32 zeroCopyThreshold = 0,
                              bool   networkOrder      = true);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                   Destructors                                */
    /*! \{                                                                 */

    virtual ~ExceptionBinaryDataHandler(void); 

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Put                                   */
    /*! \{                                                                 */

    void put       (      void const   *src,   UInt32 size);
    void putAndFree(      MemoryHandle  src,   UInt32 size);

    void putValue  (const bool         &value              );
    void putValue  (const UInt8        &value              );
    void putValue  (const UInt16       &value              );
    void putValue  (const UInt32       &value              );
    void putValue  (const UInt64       &value              );
    void putValue  (const Int8         &value              );
    void putValue  (const Int16        &value              );
    void putValue  (const Int32        &value              );
    void putValue  (const Int64        &value              );
    void putValue  (const Real16       &value              );
    void putValue  (const Fixed32      &value              );
    void putValue  (const Real32       &value              );
    void putValue  (const Real64       &value              );
    void putValue  (const std::string  &value              );
#ifdef OSG_GLENUM_NEQ_UINT32
    void putValue  (const GLenum       &value              );
#endif

    void putValues (const bool         *value, UInt32 size);
    void putValues (const UInt8        *value, UInt32 size);
    void putValues (const UInt16       *value, UInt32 size);
    void putValues (const UInt32       *value, UInt32 size);
    void putValues (const UInt64       *value, UInt32 size);
    void putValues (const Int8         *value, UInt32 size);
    void putValues (const Int16        *value, UInt32 size);
    void putValues (const Int32        *value, UInt32 size);
    void putValues (const Int64        *value, UInt32 size);
    void putValues (const Real16       *value, UInt32 size);
    void putValues (const Fixed32      *value, UInt32 size);
    void putValues (const Real32       *value, UInt32 size);
    void putValues (const Real64       *value, UInt32 size);
    void putValues (const std::string  *value, UInt32 size);
#ifdef OSG_GLENUM_NEQ_UINT32
    void putValues (const GLenum       *value, UInt32 size);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                        Get                                   */
    /*! \{                                                                 */

    void get        (void         *dst,   UInt32 size) throw (ReadError);
    void getAndAlloc(MemoryHandle &src,   UInt32 size) throw (ReadError);

    void getValue   (bool         &value             ) throw (ReadError);
    void getValue   (UInt8        &value             ) throw (ReadError);
    void getValue   (UInt16       &value             ) throw (ReadError);
    void getValue   (UInt32       &value             ) throw (ReadError);
    void getValue   (UInt64       &value             ) throw (ReadError);
    void getValue   (Int8         &value             ) throw (ReadError);
    void getValue   (Int16        &value             ) throw (ReadError);
    void getValue   (Int32        &value             ) throw (ReadError);
    void getValue   (Int64        &value             ) throw (ReadError);
    void getValue   (Real16       &value             ) throw (ReadError);
    void getValue   (Fixed32      &value             ) throw (ReadError);
    void getValue   (Real32       &value             ) throw (ReadError);
    void getValue   (Real64       &value             ) throw (ReadError);
    void getValue   (std::string  &value             ) throw (ReadError);
#ifdef OSG_GLENUM_NEQ_UINT32
    void getValue   (GLenum       &value             ) throw (ReadError);
#endif

    void getValues  (bool         *value, UInt32 size) throw (ReadError);
    void getValues  (UInt8        *value, UInt32 size) throw (ReadError);
    void getValues  (UInt16       *value, UInt32 size) throw (ReadError);
    void getValues  (UInt32       *value, UInt32 size) throw (ReadError);
    void getValues  (UInt64       *value, UInt32 size) throw (ReadError);
    void getValues  (Int8         *value, UInt32 size) throw (ReadError);
    void getValues  (Int16        *value, UInt32 size) throw (ReadError);
    void getValues  (Int32        *value, UInt32 size) throw (ReadError);
    void getValues  (Int64        *value, UInt32 size) throw (ReadError);
    void getValues  (Real16       *value, UInt32 size) throw (ReadError);
    void getValues  (Fixed32      *value, UInt32 size) throw (ReadError);
    void getValues  (Real32       *value, UInt32 size) throw (ReadError);
    void getValues  (Real64       *value, UInt32 size) throw (ReadError);
    void getValues  (std::string  *value, UInt32 size) throw (ReadError);
#ifdef OSG_GLENUM_NEQ_UINT32
    void getValues  (GLenum       *value, UInt32 size) throw (ReadError);
#endif

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Helper                                  */
    /*! \{                                                                 */

    virtual void forceCopy      (void      );
    virtual void forceDirectIO  (void      );

            void flush          (void      );

            void setNetworkOrder(bool value);
            bool getNetworkOrder(void      );

    /*! \}                                                                 */
    /*=========================  PROTECTED  ===============================*/

  protected:

    /*! \nohierarchy */

    struct MemoryBlock 
    {
      public:

        MemoryBlock             (MemoryHandle m, UInt32 s, UInt32 ds = 0);

        MemoryHandle getMem     (void                                   );
        void         setMem     (MemoryHandle m                         );

        UInt32       getSize    (void                                   );
        void         setSize    (UInt32 dataSize                        );

        UInt32       getDataSize(void                                   );
        void         setDataSize(UInt32 dataSize                        );

      private:

        MemoryHandle  _mem;
        UInt32        _size;
        UInt32        _dataSize;
    };

    typedef std::vector<MemoryBlock>  BuffersT;
    typedef std::list  <MemoryHandle> FreeMemT;

    /*---------------------------------------------------------------------*/
    /*! \name                      Member                                  */
    /*! \{                                                                 */

    BuffersT           _readBuffers;
    BuffersT           _writeBuffers;
    BuffersT           _zeroCopyBuffers;
    UInt32             _zeroCopyThreshold;

    FreeMemT           _freeMem;
    BuffersT::iterator _currentReadBuffer;
    UInt32             _currentReadBufferPos;
    BuffersT::iterator _currentWriteBuffer;
    UInt32             _currentWriteBufferPos;
    
    bool               _networkOrder;
    
    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Read                                    */
    /*! \{                                                                 */

            BuffersT::iterator readBufBegin(void                      );
            BuffersT::iterator readBufEnd  (void                      );
            void               readBufAdd  (MemoryHandle  mem, 
                                            UInt32        size,
                                            UInt32        dataSize = 0);
            void               readBufClear(void                      );

    virtual void               read        (MemoryHandle   src,
                                            UInt32         size       );

    virtual void readBuffer  (void) throw (ReadError);

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                          Write                               */
    /*! \{                                                                 */

            BuffersT::iterator writeBufBegin(void                     );
            BuffersT::iterator writeBufEnd  (void                     );
            void               writeBufAdd  (MemoryHandle mem, 
                                             UInt32       size,
                                             UInt32       dataSize = 0);
            void               writeBufClear(void                     );

    virtual void               write        (MemoryHandle   src,    
                                             UInt32         size      );
    virtual void               writeBuffer  (void                     );

    /*! \}                                                                 */
    /*---------------------------------------------------------------------*/
    /*! \name                      Helper                                  */
    /*! \{                                                                 */
    
    bool isReadBufferEmpty(void);
    
    /*! \}                                                                 */
    /*==========================  PRIVATE  ================================*/

  private:

    /*---------------------------------------------------------------------*/
    /*! \name                     Internal Helper                          */
    /*! \{                                                                 */

    void pushBuffer(void);
    void pullBuffer(void) throw (ReadError);
    void freeMem   (void);

    /*! \}                                                                 */
    /*!\brief prohibit default function (move to 'public' if needed)       */
    ExceptionBinaryDataHandler(const ExceptionBinaryDataHandler &source);
    /*!\brief prohibit default function (move to 'public' if needed)       */
    void operator =(const ExceptionBinaryDataHandler &source);
};

OSG_END_NAMESPACE

#ifndef WIN32
#include <netinet/in.h>
#endif

#include <sys/types.h>

#include "OSGBaseFunctions.h"

#include "OSGExceptionBinaryDataHandler.inl"

#endif /* _OSGEXCEPTIONBINARYDATAHANDLER_H_ */
