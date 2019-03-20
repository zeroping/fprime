// ====================================================================== 
// \title  AccelMPU9250Impl.cpp
// \author scott
// \brief  cpp file for AccelMPU9250 component implementation class
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


#include <Drv/AccelMPU9250/AccelMPU9250ComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <Drv/AccelMPU9250/MPU9250Reg.hpp>

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction 
  // ----------------------------------------------------------------------

  AccelMPU9250ComponentImpl ::
#if FW_OBJECT_NAMES == 1
    AccelMPU9250ComponentImpl(
        const char *const compName
    ) :
      AccelMPU9250ComponentBase(compName)
#else
    AccelMPU9250Impl(void)
#endif
  {

  }

  void AccelMPU9250ComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    ) 
  {
    AccelMPU9250ComponentBase::init(instance);
  }

  AccelMPU9250ComponentImpl ::
    ~AccelMPU9250ComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void AccelMPU9250ComponentImpl ::
    Run_handler(
        const NATIVE_INT_TYPE portNum,
        NATIVE_UINT_TYPE context
    )
  {
    // TODO
    Fw::Time now = getTime();
    
    printf("accel component tick %d %d %d\r\n", now.getTimeBase(), now.getSeconds(), now.getUSeconds());
    
    if(!_initialized)
    {
      printf("performing accel init\r\n");
    
      U8 whoamibyte = 0;
      remoteAdrRead_out(0, MPU9250_REG_WHOAMI, &whoamibyte);
      FW_ASSERT(whoamibyte == 0x71);
      
      
      remoteAdrWrite_out(0, MPU9250_REG_PWR_MGMT_1, MPU9250_BITS_H_RESET);
      remoteAdrWrite_out(0, MPU9250_REG_PWR_MGMT_1, 0);
      remoteAdrWrite_out(0, MPU9250_REG_PWR_MGMT_2, MPU9250_BITS_USER_CTRL_I2C_MST_RST);
//       remoteAdrWrite_out(0, MPU9250_REG_FIFO_EN, MPU9250_BITS_FIFO_ENABLE_TEMP_OUT  |
//                                       MPU9250_BITS_FIFO_ENABLE_GYRO_XOUT |
//                                       MPU9250_BITS_FIFO_ENABLE_GYRO_YOUT |
//                                       MPU9250_BITS_FIFO_ENABLE_GYRO_ZOUT |
//                                       MPU9250_BITS_FIFO_ENABLE_ACCEL);
      remoteAdrWrite_out(0, MPU9250_REG_CONFIG, MPU9250_BITS_GYRO_DLPF_CFG_184HZ | MPU9250_BITS_CONFIG_FIFO_MODE_STOP );
      remoteAdrWrite_out(0, MPU9250_REG_GYRO_CONFIG, MPU9250_BITS_FS_250DPS);
      m_gyroRawToRadS = 250.0f / 32768.0f * MPU9250_PI / 180.0f;
      remoteAdrWrite_out(0, MPU9250_REG_ACCEL_CONFIG,  MPU9250_BITS_ACCEL_CONFIG_2G);
      m_accelRawToMS2 = 1.0f / 2048.0f;
      remoteAdrWrite_out(0, MPU9250_REG_ACCEL_CONFIG2, MPU9250_BITS_ACCEL_BW_LTE_460HZ | MPU9250_BITS_ACCEL_DLPF_CFG_460HZ);
      //TODO get the magnetometer to work, although it will be a mess due to the secondary interface stuff
      
      remoteAdrWrite_out(0, MPU9250_REG_INT_ENABLE , MPU9250_BITS_INT_EN_RAW_DATA_RDY );
      //remoteAdrWrite_out(0, MPU9250_REG_USER_CTRL,  MPU9250_BITS_USER_CTRL_FIFO_RST |  MPU9250_BITS_USER_CTRL_FIFO_EN; );
      _initialized = true;
    }
    
    
    U8 accelbyte = 0;
    remoteAdrRead_out(0, MPU9250_REG_ACCEL_XOUT_H, &accelbyte);
    //We have (probably) gotten an accelerometer update
    
    m_updates+=1;
    tlmWrite_ACCELMPU9250_Updates(m_updates);
    
    printf("accel value %d\r\n", accelbyte);
    
    //tlmWrite_ACCELMPU9250_LastAccelData();
    
    
  }
  
  
  
  // ----------------------------------------------------------------------
  // Command handler implementations 
  // ----------------------------------------------------------------------

  void AccelMPU9250ComponentImpl ::
    ACCELMPU9250_ReadID_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        U8 value
    )
  {
    // TODO
    printf("accel component asked to read an ID\r\n");
    
    U8 whoamibyte = 0;
    remoteAdrRead_out(0, MPU9250_REG_WHOAMI, &whoamibyte);
    
    printf("accel component got back %x\r\n", whoamibyte);
    
    //this->remoteAdrRead();
    
  }

} // end namespace Drv
