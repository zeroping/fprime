// ====================================================================== 
// \title  RCServoImpl.cpp
// \author scott
// \brief  cpp file for RCServo component implementation class
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


#include <Drv/RCServo/RCServo/RCServoComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"

namespace Drv {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction 
  // ----------------------------------------------------------------------

  RCServoComponentImpl ::
#if FW_OBJECT_NAMES == 1
    RCServoComponentImpl(
        const char *const compName
    ) :
      RCServoComponentBase(compName)
#else
    RCServoImpl(void)
#endif
  {

  }

  void RCServoComponentImpl ::
    init(
        const NATIVE_INT_TYPE instance
    ) 
  {
    RCServoComponentBase::init(instance);
  }

  RCServoComponentImpl ::
    ~RCServoComponentImpl(void)
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void RCServoComponentImpl ::
    rcServo_handler(
        const NATIVE_INT_TYPE portNum,
        F32 value
    )
  {
    // TODO
  }

  // ----------------------------------------------------------------------
  // Command handler implementations 
  // ----------------------------------------------------------------------

  void RCServoComponentImpl ::
    RCServo_Set_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq,
        F32 value
    )
  {
    // TODO
  }

} // end namespace Drv
