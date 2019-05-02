// ======================================================================
// \title  LinuxPwmDriverImpl.cpp
// \author tcanham
// \brief  cpp file for LinuxPwmDriver component implementation class
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


#include <Drv/PWM/LinuxPwmDriver/LinuxPwmDriverComponentImpl.hpp>
#include <Fw/Types/BasicTypes.hpp>
#include <Os/TaskString.hpp>

// TODO make proper static constants for these
#define SYSFS_PWM_DIR "/sys/class/pwm"
#define MAX_BUF 64

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>

//#define DEBUG_PRINT(x,...) printf(x,##__VA_ARGS__); fflush(stdout)
#define DEBUG_PRINT(x,...)

namespace Drv {


// Code modified from https://developer.ridgerun.com/wiki/index.php?title=Gpio-int-test.c
    /****************************************************************
    * pwm_export
    ****************************************************************/
    int pwm_export(unsigned int pwmchip, unsigned int channel)
    {
        int fd, len;
        char buf[MAX_BUF];

        // TODO(mereweth) - check npwm

        len = snprintf(buf, sizeof(buf),
                       SYSFS_PWM_DIR  "/pwmchip%d/export",
                       pwmchip);
        FW_ASSERT(len > 0, len);

        fd = open(buf, O_WRONLY);
        if (fd < 0) {
            DEBUG_PRINT("pwm/export error!\n");
            return -1;
        }

        // TODO check value of len
        len = snprintf(buf, sizeof(buf), "%d", channel);
        (void) write(fd, buf, len); // TODO check return value
        (void) close(fd);

        /* NOTE(mereweth) - this is to allow systemd udev to make
         * necessary filesystem changes after exporting
         */
        usleep(100 * 1000);

        return 0;
    }

    /****************************************************************
     * pwm_unexport
     ****************************************************************/
    int pwm_unexport(unsigned int pwmchip, unsigned int channel)
    {
        int fd, len;
        char buf[MAX_BUF];

        // TODO(mereweth) - check npwm

        len = snprintf(buf, sizeof(buf),
                       SYSFS_PWM_DIR  "/pwmchip%d/unexport",
                       pwmchip);
        FW_ASSERT(len > 0, len);

        fd = open(buf, O_WRONLY);
        if (fd < 0) {
            DEBUG_PRINT("pwm/unexport error!\n");
            return -1;
        }

        // TODO check value of len
        len = snprintf(buf, sizeof(buf), "%d", channel);
        (void) write(fd, buf, len); // TODO check return value
        (void) close(fd);

        /* NOTE(mereweth) - this is to allow systemd udev to make
         * necessary filesystem changes after unexporting
         */
        usleep(100 * 1000);

        return 0;
    }

/*
TODO(mereweth)

When a PWM channel is exported a pwmX directory will be created in the
pwmchipN directory it is associated with, where X is the number of the
channel that was exported. The following properties will then be available:

  period
    The total period of the PWM signal (read/write).
    Value is in nanoseconds and is the sum of the active and inactive
    time of the PWM.

  duty_cycle
    The active time of the PWM signal (read/write).
    Value is in nanoseconds and must be less than the period.

  polarity
    Changes the polarity of the PWM signal (read/write).
    Writes to this property only work if the PWM chip supports changing
    the polarity. The polarity can only be changed if the PWM is not
    enabled. Value is the string "normal" or "inversed".

  enable
    Enable/disable the PWM signal (read/write).

	- 0 - disabled
	- 1 - enabled
*/

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

    void LinuxPwmDriverComponentImpl ::
      pwmConfig_handler(
          const NATIVE_INT_TYPE portNum,
          PwmConfig pwmConfig
      )
    {
        if (-1 == this->m_fd) {
            this->log_WARNING_HI_PWM_Init_Error(m_pwmchip, portNum);
            return;
        }

        int fd, len;
        char buf[MAX_BUF];

        len = snprintf(buf, sizeof(buf),
                       SYSFS_PWM_DIR  "/pwm%d-%d/period",
                       m_pwmchip, m_pwmchannel);
        FW_ASSERT(len > 0, len);

        fd = open(buf, O_WRONLY);
        if (fd < 0) {
          this->log_WARNING_HI_PWM_Init_Error(m_pwmchip, m_pwmchannel);
          return;
        }

        // TODO check value of len
        len = snprintf(buf, sizeof(buf), "%d", pwmConfig.period);
        (void) write(fd, buf, len); // TODO check return value
        (void) close(fd);
      
        m_periodInUsecs = pwmConfig.period;
    }

    void LinuxPwmDriverComponentImpl ::
      pwmSetDuty_handler(
          const NATIVE_INT_TYPE portNum,
          PwmSetDutyCycle pwmSetDutyCycle
      )
    {
      
        int fd, len;
        char buf[MAX_BUF];

        len = snprintf(buf, sizeof(buf),
                       SYSFS_PWM_DIR  "/pwm%d-%d/duty_cycle",
                       m_pwmchip, m_pwmchannel);
        FW_ASSERT(len > 0, len);

        fd = open(buf, O_WRONLY);
        if (fd < 0) {
          this->log_WARNING_HI_PWM_Init_Error(m_pwmchip, m_pwmchannel);
          return;
        }

        // TODO check value of len
        len = snprintf(buf, sizeof(buf), "%d", pwmConfig.period);
        (void) write(fd, buf, len); // TODO check return value
        (void) close(fd);
      
        m_periodInUsecs = pwmConfig.period;
      
    }

    bool LinuxPwmDriverComponentImpl ::
      open(NATIVE_UINT_TYPE pwmchip,
           NATIVE_UINT_TYPE channel,
           NATIVE_UINT_TYPE period_in_usecs) {
        // TODO check for invalid pwm device?

        this->m_pwmchip = pwmchip;
        this->m_pwmchannel = channel;
        
        pwm_export(m_pwmchip, m_pwmchannel);
        pwmSetPeriod_handler(0, period_in_usecs);
        pwmSetDuty_handler(0, 0);

        //enable the channel
        int fd, len;
        char buf[MAX_BUF];

        len = snprintf(buf, sizeof(buf),
                       SYSFS_PWM_DIR  "/pwm%d-%d/enable",
                       m_pwmchip, m_pwmchannel);
        FW_ASSERT(len > 0, len);

        fd = open(buf, O_WRONLY);
        if (fd < 0) {
          this->log_WARNING_HI_PWM_Init_Error(m_pwmchip, m_pwmchannel);
          return false;
        }
        len = snprintf(buf, sizeof(buf), "1");
        (void) write(fd, buf, len); // TODO check return value
        (void) close(fd);

        return true;
    }

    LinuxPwmDriverComponentImpl ::
      ~LinuxPwmDriverComponentImpl(void)
    {
        pwm_unexport(m_pwmchip, m_pwmchannel);
    }

} // end namespace Drv
