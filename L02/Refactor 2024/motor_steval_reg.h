/**
  ******************************************************************************
  * @file    motor_steval_reg.h
  * @author  Jakub Walkowski
  * @author  AW		(adrian.wojcik@put.poznan.pl)
  * @version 3.0.0
  * @date    19-Mar-2024
  * @brief   Aeropendulum angular drive: STEVAL board registers 
  *
  ******************************************************************************
  */

#ifndef INC_MOTOR_STEVAL_REG_H_
#define INC_MOTOR_STEVAL_REG_H_

/**
 * @brief List of uart errors.
 */
typedef enum
{
    UART_OK =               0, /**< No errors. */
    UART_CONNECTION_ERROR = 1, /**< Connection error. */
    UART_FRAME_SIZE_ERROR = 2, /**< Wrong size of received frame. */
    UART_STEVAL_ERROR =     3, /**< Steval error. */
    UART_FRAME_ERROR =      4  /**< Wrong frame format. */
} UART_STATUS;
/**
 * @brief  List of error codes
 */
typedef enum
{
    BAD_FRAME_ID =      0x1, /**< BAD Frame ID. The Frame ID has not been recognized by the firmware */
    WRITE_ON_RO =       0x2, /**< Write on read-only. The master wants to write on a read-only register */
    READ_NOT_ALLOWED =  0x3, /**< Read not allowed. The value cannot be read. */
    BAD_TARGET =        0x4, /**< Bad target drive. The target motor is not supported by the firmware */
    OUT_OF_RANGE =      0x5, /**< Out of range. The value used in the frame is outside the range expected by the firmware. */
    BAD_CMD_ID =        0x7, /**< Bad command ID. The command ID has not been recognized */
    OVERRUN_ERROR =     0x8, /**< Overrun error. The frame has not been received correctly because the transmission speed is too fast. */
    TIMEOUT =           0x9, /**< Timeout error. The frame has not been received correctly and a timeout
                                  occurs. This kind of error usually occurs when the frame is not correct or is 
                                  not correctly recognized by the firmware. */
    BAD_CRC =           0xA, /**< Bad CRC. The computed CRC is not equal to the received CRC byte. */
    BAD_TARGET_2 =      0xB  /**< Bad target drive. The target motor is not supported by the firmware */

} STEVAL_ERROR;
/**
 * @brief List of relevant motor control register ids
 */
enum class STEVAL_REGISTERS 
{
    NO_REG          = -1,   /**< No registry */
    TARGET          = 0x0,  /**< Target motor, RW */
    FLAGS           = 0x1,  /**< Flags, R */
    STATUS          = 0x2,  /**< Status, R */
    MODE            = 0x3,  /**< Control mode, RW */
    SPEED_REF       = 0x4,  /**< Speed reference, R */
    SPEED_KP        = 0X5,  /**< Speed KP, RW */
    SPEED_KI        = 0X6,  /**< Speed KI, RW */
    SPEED_KD        = 0x7,  /**< Speed KD, RW */
    TOR_REF         = 0x8,  /**< Torque reference (Iq), RW */
    TOR_KP          = 0x9,  /**< Torque KP, RW */
    TOR_KI          = 0xA,  /**< Torque KI, RW */
    TOR_KD          = 0xB,  /**< Torque KD, RW */
    FLUX_REF        = 0xC,  /**< Flux reference (Id), RW */
    FLUX_KP         = 0xD,  /**< Flux KP, RW */
    FLUX_KI         = 0xE,  /**< Flux KI, RW */
    FLUX_KD         = 0xF,  /**< Flux KD, RW */
    OBS_C1          = 0x10, /**< Observer C1, RW */
    OBS_C2          = 0x11, /**< Observer C2, RW */
    C_OBS_C1        = 0x12, /**< Cordic Observer C1, RW */
    C_OBS_C2        = 0x13, /**< Cordic Observer C2, RW */
    PLL_KI          = 0x14, /**< PLL KI , RW */
    PLL_KP          = 0x15, /**< PLL KP, RW */
    FLUX_WEAK_KP    = 0x16, /**< Flux weakening KP, RW */
    FLUX_WEAK_KI    = 0x17, /**< Flux weakening KI, RW */
    FLUX_WEAK_BUS   = 0x18, /**< Flux weakening BUS Voltage allowed percentage reference, RW */
    BUS_VOL         = 0x19, /**< Bus Voltage, R */
    HEATSINK_TEMP   = 0x1A, /**< Heatsink temperature, R */
    MOTOR_POWER     = 0x1B, /**< Motor power, R */
    DAC_OUT1        = 0x1C, /**< DAC Out 1, R */
    DAC_OUT2        = 0x1D, /**< DAC Out 2, R */
    SPEED_MEAS      = 0x1E, /**< Speed measured, R */
    TOR_MEAS        = 0x1F, /**< Torque measured (Iq), R */
    FLUX_MEAS       = 0x20, /**< Flux measured (Id), R */
    FLUX_WBV        = 0x21, /**< Flux weakening BUS Voltage allowed percentage measured, R */
    RS_NUM          = 0x22, /**< Revup stage numbers, R */
    MAX_APP_SPEED   = 0x3F, /**< Maximum application speed, R */
    MIN_APP_SPEED   = 0x40, /**< Minimum application speed, R */
    IQ_REF          = 0x41, /**< Iq reference in speed mode, W */   
    EXP_BEMF_PLL    = 0x42, /**< Expected BEMF level (PLL), R */
    OBS_BEMF_PLL    = 0x43, /**< Observed BEMF level (PLL), R */
    EXP_BEMF_CORDIC = 0x44, /**< Expected BEMF level (CORDIC), R */
    OBS_BEMF_CORDIC = 0x45, /**< Observed BEMF level (CORDIC), R */
    FF_1Q           = 0x46, /**< Feedforward (1Q), RW */
    FF_1D           = 0x47, /**< Feedforward (1D), RW */
    FF_2            = 0x48, /**< Feedforward (2), RW */
    FF_VQ           = 0x49, /**< Feedforward (VQ), R */
    FF_VD           = 0x4A, /**< Feedforward (VD), R */
    FF_VQ_PI_OUT    = 0x4B, /**< Feedforward (VQ PI out), R */
    FF_VD_PI_OUT    = 0x4C, /**< Feedforward (VD PI out), R */
    RAMP_FIN_SPEED  = 0x5B, /**< Ramp final speed, RW */
    RAMP_DUR        = 0x5C, /**< Ramp duration, RW */
    //Commands:
    START_MOTOR     = 0x1, /**< Indicates the user request to start the motor regardless the state of the motor. */
    STOP_MOTOR      = 0x2, /**< Indicates the user request to stop the motor regardless the state of the motor. */
    STOP_RAMP       = 0x3, /**< Indicates the user request to stop the execution of the speed ramp that is currently executed */
    START_STOP      = 0x6, /**< Indicates the user request to start the motor if the motor is still, or to stop the motor if it runs. */
    FAULT_ACT       = 0x7, /**< Communicates the user acknowledges of the occurred fault conditions. */
    ENCODER_ALIGN   = 0x8  /**< Indicates the user request to perform the encoder alignment procedure. */
};
/**
 * @brief List of relevant motor control register payload length
 */
enum class STEVAL_REGISTERS_LEN
{
    EXE_CMD         = 1, /**< Payload length on execute command */
    GET             = 1, /**< Payload length on get register value */
    TARGET          = 3, /**< Target motor, RW */
    FLAGS           = 3, /**< Flags, R */
    STATUS          = 3, /**< Status, R */
    MODE            = 3, /**< Control mode, RW */
    SPEED_REF       = 3, /**< Speed reference, R */
    SPEED_KP        = 3, /**< Speed KP, RW */
    SPEED_KI        = 3, /**< Speed KI, RW */
    SPEED_KD        = 3, /**< Speed KD, RW */
    TOR_REF         = 3, /**< Torque reference (Iq), RW */
    TOR_KP          = 3, /**< Torque KP, RW */
    TOR_KI          = 3, /**< Torque KI, RW */
    TOR_KD          = 3, /**< Torque KD, RW */
    FLUX_REF        = 3, /**< Flux reference (Id), RW */
    FLUX_KP         = 3, /**< Flux KP, RW */
    FLUX_KI         = 3, /**< Flux KI, RW */
    FLUX_KD         = 3, /**< Flux KD, RW */
    OBS_C1          = 3, /**< Observer C1, RW */
    OBS_C2          = 3, /**< Observer C2, RW */
    C_OBS_C1        = 3, /**< Cordic Observer C1, RW */
    C_OBS_C2        = 3, /**< Cordic Observer C2, RW */
    PLL_KI          = 3, /**< PLL KI , RW */
    PLL_KP          = 3, /**< PLL KP, RW */
    FLUX_WEAK_KP    = 3, /**< Flux weakening KP, RW */
    FLUX_WEAK_KI    = 3, /**< Flux weakening KI, RW */
    FLUX_WEAK_BUS   = 3, /**< Flux weakening BUS Voltage allowed percentage reference, RW */
    BUS_VOL         = 3, /**< Bus Voltage, R */
    HEATSINK_TEMP   = 3, /**< Heatsink temperature, R */
    MOTOR_POWER     = 3, /**< Motor power, R */
    DAC_OUT1        = 2, /**< DAC Out 1, R */
    DAC_OUT2        = 2, /**< DAC Out 2, R */
    SPEED_MEAS      = 5, /**< Speed measured, R */
    TOR_MEAS        = 3, /**< Torque measured (Iq), R */
    FLUX_MEAS       = 3, /**< Flux measured (Id), R */
    FLUX_WBV        = 3, /**< Flux weakening BUS Voltage allowed percentage measured, R */
    RS_NUM          = 2, /**< SRevup stage numbers, R */
    MAX_APP_SPEED   = 5, /**< Maximum application speed, R */
    MIN_APP_SPEED   = 5, /**< Minimum application speed, R */
    IQ_REF          = 3, /**< Iq reference in speed mode, W */   
    EXP_BEMF_PLL    = 3, /**< Expected BEMF level (PLL), R */
    OBS_BEMF_PLL    = 3, /**< Observed BEMF level (PLL), R */
    EXP_BEMF_CORDIC = 3, /**< Expected BEMF level (CORDIC), R */
    OBS_BEMF_CORDIC = 3, /**< Observed BEMF level (CORDIC), R */
    FF_1Q           = 5, /**< Feedforward (1Q), RW */
    FF_1D           = 5, /**< Feedforward (1D), RW */
    FF_2            = 5, /**< Feedforward (2), RW */
    FF_VQ           = 3, /**< Feedforward (VQ), R */
    FF_VD           = 3, /**< Feedforward (VD), R */
    FF_VQ_PI_OUT    = 3, /**< Feedforward (VQ PI out), R */
    FF_VD_PI_OUT    = 3, /**< Feedforward (VD PI out), R */
    RAMP_FIN_SPEED  = 5, /**< Ramp final speed, RW */
    RAMP_DUR        = 3, /**< Ramp duration, RW */
    RAMP_EXE        = 6  /**< PL for exe ramp frame */
};
/**
 * @brief List of starting frame codes
 */
enum class FRAME_CODES
{
    SET         = 0x1, /**< Set register frame. It is used to write a value into a relevant motor control variable. */
    GET         = 0x2, /**< Get register frame. It is used to read a value from a relevant motor control variable. */
    EXE         = 0x3, /**< Execute command frame. It is used to send a command to the motor control object. */
    INFO        = 0x6, /**< Get board info. It is used to retrieve information about the firmware currently running on the microcontroller. */
    EXE_RAMP    = 0x7, /**< Exec ramp. It is used to execute a speed ramp. */
    GET_REVUP   = 0x8, /**< Get revup data. It is used to retrieve the revup parameters. */
    SET_REVUP   = 0x9, /**< Set revup data. It is used to set the revup parameters. */
    SET_REF     = 0xA, /**< Set current references. It is used to set the current reference. */
    RECEIVE     = 0xF0,/**< Frame code for received frames. */
    ERROR       = 0xFF /**< Frame with error, error code store in data. */
};

#endif /* INC_MOTOR_STEVAL_REG_H_ */