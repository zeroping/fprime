// ====================================================================== 
// \title  RemoteAdrAdapterI2CImpl.hpp
// \author scott
// \brief  hpp file for RemoteAdrAdapterI2C component implementation class
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

#ifndef RemoteAdrAdapterI2C_HPP
#define RemoteAdrAdapterI2C_HPP

#include "Drv/RemoteAdrAdapterI2C/RemoteAdrAdapterI2CComponentAc.hpp"

namespace Drv {

  class RemoteAdrAdapterI2CComponentImpl :
    public RemoteAdrAdapterI2CComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object RemoteAdrAdapterI2C
      //!
      RemoteAdrAdapterI2CComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object RemoteAdrAdapterI2C
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0, /*!< The instance number*/
          U8 i2cAddress = 1
      );

      //! Destroy object RemoteAdrAdapterI2C
      //!
      ~RemoteAdrAdapterI2CComponentImpl(void);

    PRIVATE:

      void setSlaveAddress();
    
      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for remoteAdrBufferWrite
      //!
      Drv::RemoteAdrAdapterI2CStatus remoteAdrBufferWrite_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 baseaddr, /*!< The address that the first byte of the buffer will be read from, with read sequentially increasing from there*/
          Fw::Buffer &serBuffer /*!< Buffer containing data to write at remote address. We will attempt to write as many bytes as there are in the buffer.*/
      );

      //! Handler implementation for remoteAdrWrite
      //!
      Drv::RemoteAdrAdapterI2CStatus remoteAdrWrite_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 baseaddr, /*!< The device address that the value byte will be written to*/
          U8 value /*!< Value to write at the given address*/
      );

      //! Handler implementation for remoteAdrBufferRead
      //!
      Drv::RemoteAdrAdapterI2CStatus remoteAdrBufferRead_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 baseaddr, /*!< The address that the first byte of the buffer will be read from, with read sequentially increasing from there*/
          Fw::Buffer &serBuffer /*!< Buffer containing data to write at remote address. We will attempt to write as many bytes as there are in the buffer.*/
      );

      //! Handler implementation for remoteAdrRead
      //!
      Drv::RemoteAdrAdapterI2CStatus remoteAdrRead_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 baseaddr, /*!< The device address that we will read from*/
          U8 *value /*!< value to be filled with the byte that we get back from the device.*/
      );
      
      U8 _i2cAddress; /**< The I2C bus address of the device we're communicating with */
      bool _initialized = false;
      U32 _nReads = 0;
      U32 _nWrites = 0;
      
    };

} // end namespace Drv

#endif
