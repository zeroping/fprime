// ======================================================================
// \title  Example/test/ut/GTestBase.cpp
// \author Auto-generated
// \brief  cpp file for Example component Google Test harness base class
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

#include "GTestBase.hpp"

namespace ExampleComponents {

  // ----------------------------------------------------------------------
  // Construction and destruction
  // ----------------------------------------------------------------------

  ExampleGTestBase ::
    ExampleGTestBase(
#if FW_OBJECT_NAMES == 1
        const char *const compName,
        const U32 maxHistorySize
#else
        const U32 maxHistorySize
#endif
    ) : 
        ExampleTesterBase (
#if FW_OBJECT_NAMES == 1
            compName,
#endif
            maxHistorySize
        )
  {

  }

  ExampleGTestBase ::
    ~ExampleGTestBase(void)
  {

  }

  // ----------------------------------------------------------------------
  // From ports
  // ----------------------------------------------------------------------

  void ExampleGTestBase ::
    assertFromPortHistory_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistorySize)
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Total size of all from port histories\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistorySize << "\n";
  }

  // ----------------------------------------------------------------------
  // From port: exampleOutput
  // ----------------------------------------------------------------------

  void ExampleGTestBase ::
    assert_from_exampleOutput_size(
        const char *const __ISF_callSiteFileName,
        const U32 __ISF_callSiteLineNumber,
        const U32 size
    ) const
  {
    ASSERT_EQ(size, this->fromPortHistory_exampleOutput->size())
      << "\n"
      << "  File:     " << __ISF_callSiteFileName << "\n"
      << "  Line:     " << __ISF_callSiteLineNumber << "\n"
      << "  Value:    Size of history for from_exampleOutput\n"
      << "  Expected: " << size << "\n"
      << "  Actual:   " << this->fromPortHistory_exampleOutput->size() << "\n";
  }

} // end namespace ExampleComponents
