// ====================================================================== 
// \title  RemoteAdrAdapterI2CImpl.cpp
// \author scott
// \brief  cpp file for RemoteAdrAdapterI2C component implementation class
//
// \copyright
// Copyright 2009-2015, by the California Institute of Technology.
// ALL RIGHTS RESERVED.  United States Government Sponsorship
// acknowledged. Any commercial use must be negotiated with the Office
// of Technology Transfer at the California Institute of Technology.
// 
// This software may be subject to U.S. export control laws and
// regulations.  By accepting this document, the user agrees to comply
// with all U.S. export laws and regulations.  User has the
// responsibility to obtain export licenses, or other export authority
// as may be required before exporting such information to foreign
// countries or providing access to foreign persons.
// ====================================================================== 


#include <Drv/RemoteAdrAdapterI2C/RemoteAdrAdapterI2CComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction 
  // ----------------------------------------------------------------------

  RemoteAdrAdapterI2CComponentImpl ::
#if FW_OBJECT_NAMES == 1
    RemoteAdrAdapterI2CComponentImpl(
        const char *const compName
    ) :
      RemoteAdrAdapterI2CComponentBase(compName)
#else
    RemoteAdrAdapterI2CImpl(void)
#endif
  {

  }

  void RemoteAdrAdapterI2CComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    ) 
  {
    RemoteAdrAdapterI2CComponentBase::init(instance);
  }

  RemoteAdrAdapterI2CComponentImpl ::
    ~RemoteAdrAdapterI2CComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void RemoteAdrAdapterI2CComponentImpl ::
    remoteAdrBufferWrite_handler(
        const NATIVE_INT_TYPE portNum,
        U8 baseaddr,
        Fw::Buffer &serBuffer
    )
  {
    // TODO
  }

  void RemoteAdrAdapterI2CComponentImpl ::
    remoteAdrWrite_handler(
        const NATIVE_INT_TYPE portNum,
        U8 baseaddr,
        U8 value
    )
  {
    // TODO
  }

  void RemoteAdrAdapterI2CComponentImpl ::
    remoteAdrBufferRead_handler(
        const NATIVE_INT_TYPE portNum,
        U8 baseaddr,
        Fw::Buffer &serBuffer
    )
  {
    // TODO
  }

  void RemoteAdrAdapterI2CComponentImpl ::
    remoteAdrRead_handler(
        const NATIVE_INT_TYPE portNum,
        U8 baseaddr,
        U8 *value
    )
  {
    // TODO
  }

} // end namespace Drv
