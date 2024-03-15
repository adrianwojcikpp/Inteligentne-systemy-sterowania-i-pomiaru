/**
 * @file registers.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "registers.h"

char const* GetErrorMessage(STEVAL_ERROR errorCode)
{
    switch(errorCode)
    {
        case BAD_FRAME_ID:
            return "BAD Frame ID. The Frame ID has not been recognized by the firmware.";
        case WRITE_ON_RO:
            return "Write on read-only. The master wants to write on a read-only register.";
        case READ_NOT_ALLOWED:
            return "Read not allowed. The value cannot be read.";
        case BAD_TARGET:
            return "Bad target drive. The target motor is not supported by the firmware.";
        case OUT_OF_RANGE:
            return "Out of range. The value used in the frame is outside the range expected by the firmware.";
        case BAD_CMD_ID:
            return "Bad command ID. The command ID has not been recognized";
        case OVERRUN_ERROR:
            return "Overrun error. The frame has not been received correctly because the transmission speed is too fast.";
        case TIMEOUT:
            return "Timeout error. The frame has not been received correctly and a timeout occurs. This kind of error usually occurs when the frame is not correct or is not correctly recognized by the firmware.";
        case BAD_CRC:
            return "Bad CRC. The computed CRC is not equal to the received CRC byte.";
        case BAD_TARGET_2:
            return "Bad target drive. The target motor is not supported by the firmware.";
        default:
            return "Unknown error.";
    }
} 