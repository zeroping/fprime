// ====================================================================== 
// \title  RCServoImpl.hpp
// \author scott
// \brief  hpp file for RCServo component implementation class
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

#ifndef RCServo_HPP
#define RCServo_HPP

#include "Drv/RCServo/RCServo/RCServoComponentAc.hpp"

namespace Drv {

  class RCServoComponentImpl :
    public RCServoComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object RCServo
      //!
      RCServoComponentImpl(
#if FW_OBJECT_NAMES == 1
          const char *const compName /*!< The component name*/
#else
          void
#endif
      );

      //! Initialize object RCServo
      //!
      void init(
          const NATIVE_INT_TYPE instance = 0 /*!< The instance number*/
      );

      //! Destroy object RCServo
      //!
      ~RCServoComponentImpl(void);

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for rcServo
      //!
      void rcServo_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 value 
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations 
      // ----------------------------------------------------------------------

      //! Implementation for RCServo_Set command handler
      //! Sets the RC Servo output to the value given
      void RCServo_Set_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          F32 value /*!< The value to set, in the range 0-1, with 0 representing a 1ms peroid, and 1 representing a 2ms period.*/
      );


    };

} // end namespace Drv

#endif
