// ====================================================================== 
// \title  AccelMPU9250Impl.hpp
// \author scott
// \brief  hpp file for AccelMPU9250 component implementation class
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

#ifndef AccelMPU9250_HPP
#define AccelMPU9250_HPP

#include "Drv/AccelMPU9250/AccelMPU9250ComponentAc.hpp"

namespace Drv {

  class AccelMPU9250ComponentImpl :
    public AccelMPU9250ComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object AccelMPU9250
      //!
      AccelMPU9250ComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object AccelMPU9250
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object AccelMPU9250
      //!
      ~AccelMPU9250ComponentImpl(void);


    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for Run
      //!
      void Run_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          NATIVE_UINT_TYPE context /*!< The call order*/
      );
   
    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations 
      // ----------------------------------------------------------------------

      //! Implementation for ACCELMPU9250_ReadID command handler
      //! Reads the WHOAMI byte to make sure that we have a working accelerometer
      void ACCELMPU9250_ReadID_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          U8 value /*!< The value read from the WHOAMI byte*/
      );
    
      bool _initialized = false;
      F32 m_gyroRawToRadS = 0;
      F32 m_accelRawToMS2 = 0;
      F32 MPU9250_PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;
      U32 m_updates = 0;
      
    };

} // end namespace Drv

#endif
