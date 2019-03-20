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
#include <Drv/LinuxI2CDriver/LinuxI2CDriverComponentImpl.hpp>
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
        const NATIVE_INT_TYPE instance,
        U8 i2cAddress
    ) 
  {
    RemoteAdrAdapterI2CComponentBase::init(instance);
    _i2cAddress = i2cAddress;

  }

  RemoteAdrAdapterI2CComponentImpl ::
    ~RemoteAdrAdapterI2CComponentImpl(void)
  {

  }

  void RemoteAdrAdapterI2CComponentImpl ::
    setSlaveAddress()
  {
    if(_initialized) {
      return;
    }
  
    FW_ASSERT(isConnected_I2CConfig_OutputPort(0));
  
    I2CConfig_out((NATIVE_INT_TYPE)0, Drv::I2C_FREQUENCY_100KHZ, _i2cAddress, 100);
    _initialized = true;
  }
  
  
  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  Drv::RemoteAdrAdapterI2CStatus RemoteAdrAdapterI2CComponentImpl ::
    remoteAdrBufferWrite_handler(
        const NATIVE_INT_TYPE portNum,
        U8 baseaddr,
        Fw::Buffer &serBuffer
    )
  {
    return Drv::RemoteAdrAdapterI2CStatus(REMOTEADR_FAILED);
  }

  Drv::RemoteAdrAdapterI2CStatus RemoteAdrAdapterI2CComponentImpl ::
    remoteAdrWrite_handler(
        const NATIVE_INT_TYPE portNum,
        U8 baseaddr,
        U8 value
    )
  {
    setSlaveAddress();
    
    FW_ASSERT(isConnected_I2CReadWrite_OutputPort(0));
    
    /* We're going to address the device we want to talk to by its I2C address, then give a one-byte register address, then write one value into that register */
    
    U8 writeArr[2];
    writeArr[0] = baseaddr;
    writeArr[1] = value;

    Fw::Buffer toWriteBuf;
    toWriteBuf.setdata((U64)writeArr);
    toWriteBuf.setsize(sizeof(writeArr));
      
    
    Fw::Buffer toReadBuf;
    toReadBuf.setdata((U64)0);
    toReadBuf.setsize(0);
    
    I2CReadWrite_out((NATIVE_INT_TYPE)0, toWriteBuf, toReadBuf);
/*    
    if(toReadBuf.getsize() < sizeof(readArr)) {
      return Drv::RemoteAdrAdapterI2CStatus(REMOTEADR_FAILED);
    }
    */
    _nWrites += 1;
    tlmWrite_REMADR_Writes(_nWrites);
    
    return Drv::RemoteAdrAdapterI2CStatus(REMOTEADR_SUCCESS);
  }

  Drv::RemoteAdrAdapterI2CStatus RemoteAdrAdapterI2CComponentImpl ::
    remoteAdrBufferRead_handler(
        const NATIVE_INT_TYPE portNum,
        U8 baseaddr,
        Fw::Buffer &serBuffer
    )
  {
    return Drv::RemoteAdrAdapterI2CStatus(REMOTEADR_FAILED);
  }

  Drv::RemoteAdrAdapterI2CStatus RemoteAdrAdapterI2CComponentImpl ::
    remoteAdrRead_handler(
        const NATIVE_INT_TYPE portNum,
        U8 baseaddr,
        U8 *value
    )
  {
    setSlaveAddress();
    
    FW_ASSERT(isConnected_I2CReadWrite_OutputPort(0));
    
    /* We're going to address the device we want to talk to by its I2C address, then give a one-byte register address, then read one byte back as a response. */
    
    U8 writeArr[1];
    U8 readArr[1];
    writeArr[0] = baseaddr;

    Fw::Buffer toWriteBuf;
    toWriteBuf.setdata((U64)writeArr);
    toWriteBuf.setsize(sizeof(writeArr));
      
    
    Fw::Buffer toReadBuf;
    toReadBuf.setdata((U64)readArr);
    toReadBuf.setsize(sizeof(readArr));
    
    I2CReadWrite_out((NATIVE_INT_TYPE)0, toWriteBuf, toReadBuf);
    
    if(toReadBuf.getsize() < sizeof(readArr)) {
      return Drv::RemoteAdrAdapterI2CStatus(REMOTEADR_FAILED);
    }
    *value = ((U8*)(toReadBuf.getdata())) [0];
    
    _nReads += 1;
    tlmWrite_REMADR_Reads(_nReads);
    
    return Drv::RemoteAdrAdapterI2CStatus(REMOTEADR_SUCCESS);
  }

} // end namespace Drv
