// ======================================================================
// \title  LinuxI2CDriverImpl.cpp
// \author tcanham
// \brief  cpp file for LinuxI2CDriver component implementation class
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

#include <Drv/LinuxI2CDriver/LinuxI2CDriverComponentImpl.hpp>
#include "Fw/Types/BasicTypes.hpp"
#include <Fw/Types/Assert.hpp>

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
//#include <i2c/smbus.h>
#include <errno.h>

//#define DEBUG_PRINT(x,...) printf(x,##__VA_ARGS__); fflush(stdout)
#define DEBUG_PRINT(x,...)

namespace Drv {

    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    void LinuxI2CDriverComponentImpl ::
      I2CConfig_handler(
          const NATIVE_INT_TYPE portNum,
          U32 busSpeed,
          U32 slaveAddr,
          U32 timeout
      )
    {
        if (this->m_fd == -1) {
            DEBUG_PRINT("initialized I2C too early\r\n");
            return;
        }
        
        m_addr = slaveAddr;
        
        //FIXME timeout is not supported (at all under linux?)
        //FIXME busSpeed is not supported (at all under linux?)
          
//         int ret = -1;
//         ioctl(this->m_fd, I2C_SLAVE, slaveAddr);
//         if (ret == -1) {
//             DEBUG_PRINT("ioctl fd %d failed. %d\n",this->m_fd,errno);
//             this->log_WARNING_HI_I2C_ConfigError(this->m_device,ret);
//         } else {
            DEBUG_PRINT("I2C fd %d WR freq successfully configured to %d\n",this->m_fd,busSpeed);
//         }
    }

    void LinuxI2CDriverComponentImpl::I2CReadWrite_handler(
            const NATIVE_INT_TYPE portNum, Fw::Buffer &writeBuffer,
            Fw::Buffer &readBuffer) {

        if (this->m_fd == -1) {
            return;
        }

        DEBUG_PRINT("Writing %d bytes to I2C\n",writeBuffer.getsize());

        NATIVE_INT_TYPE ret = -1;
        
        
        //we're going to ask to go two actions in our ioctl - a write (probably a register address), and then a read of the return data
        struct i2c_rdwr_ioctl_data msglist;
        struct i2c_msg msgs[2];

        msglist.nmsgs = 2;
        msglist.msgs = msgs;

        //write message
        msglist.msgs[0].addr = m_addr;
        msglist.msgs[0].len = writeBuffer.getsize();
        msglist.msgs[0].flags = 0;
        msglist.msgs[0].buf = ((unsigned char *)writeBuffer.getdata());
        
        //read message
        msglist.msgs[1].addr = m_addr;
        msglist.msgs[1].len = readBuffer.getsize();
        msglist.msgs[1].flags = I2C_M_RD | I2C_M_NOSTART; 
        msglist.msgs[1].buf = ((unsigned char *)readBuffer.getdata());

        
        DEBUG_PRINT("ioctl I2C_RDWR going to write %d and read %d from 0x%x\n", msglist.msgs[0].len, msglist.msgs[1].len, m_addr);
        
        ret = ioctl(this->m_fd,I2C_RDWR,&msglist);
          
        if (ret < 1) {
            DEBUG_PRINT("ioctl I2C_RDWR 0x%x failed. %d %s\n",this->m_fd,errno, strerror(errno));
            this->log_WARNING_HI_I2C_WriteError(this->m_device,
                                                this->m_addr,
                                                ret, 0, 0);
            return;
        }
        
        this->m_readBytes += readBuffer.getsize();
        this->m_writeBytes += writeBuffer.getsize();
        this->tlmWrite_I2C_ReadBytes(this->m_readBytes);
        this->tlmWrite_I2C_WriteBytes(this->m_writeBytes);

    }

    void LinuxI2CDriverComponentImpl::open(NATIVE_INT_TYPE device,
                                           I2CFrequency clock) {

        this->m_device = device;
        NATIVE_INT_TYPE fd;
        unsigned long funcs;

        // Open:
        char devName[256];
        snprintf(devName,sizeof(devName),"/dev/i2c-%d",device);
        // null terminate
        devName[sizeof(devName)-1] = 0;
        DEBUG_PRINT("Opening I2C device %s\n",devName);

        fd = ::open(devName, O_RDWR);
        if (fd == -1) {
            DEBUG_PRINT("open I2C device %d.%d failed. %d\n\r\n",device,errno);
            this->log_WARNING_HI_I2C_OpenError(device,fd);
            return;
        } else {
            DEBUG_PRINT("Successfully opened I2C device %s fd %d\n\r\n",devName,fd);
        }

        this->m_fd = fd;
        
        if (ioctl(fd, I2C_FUNCS, &funcs) < 0) {
          this->log_WARNING_HI_I2C_OpenError(device,fd);
          DEBUG_PRINT("failed to get I2C_FUNCS on %s\r\n",devName);
          return;
        }

        if (funcs & I2C_FUNC_I2C) {
          DEBUG_PRINT("I2C device %s supports I2C mode\r\n",devName);
        } else if (funcs & I2C_FUNC_SMBUS_WORD_DATA) {
          DEBUG_PRINT("I2C device %s supports SMBUS mode, but this drive only supports I2C mode\r\n",devName);
          this->log_WARNING_HI_I2C_OpenError(device,fd);
        } else {
          DEBUG_PRINT("I2C device %s supports neither SMBUS nor I2C mode, and cannot be used\r\n",devName);
          this->log_WARNING_HI_I2C_OpenError(device,fd);
        }
    
        
    }

    LinuxI2CDriverComponentImpl::~LinuxI2CDriverComponentImpl(void) {
        DEBUG_PRINT("Closing I2C device %d\n",this->m_fd);
        (void) close(this->m_fd);
    }

} // end namespace Drv
