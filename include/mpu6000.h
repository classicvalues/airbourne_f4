/*
 * Copyright (c) 2017, James Jackson
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef MPU6000_H
#define MPU6000_H

#include "spi.h"
#include "system.h"

// Bits
#define MPU_BIT_SLEEP 0x40
#define MPU_BIT_H_RESET 0x80
#define MPU_BITS_CLKSEL 0x07
#define MPU_CLK_SEL_PLLGYROX 0x01
#define MPU_CLK_SEL_PLLGYROZ 0x03
#define MPU_EXT_SYNC_GYROX 0x02
#define MPU_BITS_FS_250DPS 0x00
#define MPU_BITS_FS_500DPS 0x08
#define MPU_BITS_FS_1000DPS 0x10
#define MPU_BITS_FS_2000DPS 0x18
#define MPU_BITS_FS_2G 0x00
#define MPU_BITS_FS_4G 0x08
#define MPU_BITS_FS_8G 0x10
#define MPU_BITS_FS_16G 0x18
#define MPU_BITS_FS_MASK 0x18
#define MPU_BITS_DLPF_CFG_256HZ 0x00
#define MPU_BITS_DLPF_CFG_188HZ 0x01
#define MPU_BITS_DLPF_CFG_98HZ 0x02
#define MPU_BITS_DLPF_CFG_42HZ 0x03
#define MPU_BITS_DLPF_CFG_20HZ 0x04
#define MPU_BITS_DLPF_CFG_10HZ 0x05
#define MPU_BITS_DLPF_CFG_5HZ 0x06
#define MPU_BITS_DLPF_CFG_2100HZ_NOLPF 0x07
#define MPU_BITS_DLPF_CFG_MASK 0x07
#define MPU_BIT_INT_ANYRD_2CLEAR 0x10
#define MPU_BIT_RAW_RDY_EN 0x01
#define MPU_BIT_I2C_IF_DIS 0x10
#define MPU_BIT_INT_STATUS_DATA 0x01
#define MPU_BIT_GYRO 0x04
#define MPU_BIT_ACC 0x02
#define MPU_BIT_TEMP 0x01

#define MPU_RA_XG_OFFS_TC 0x00  //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU_RA_YG_OFFS_TC 0x01  //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU_RA_ZG_OFFS_TC 0x02  //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU_RA_X_FINE_GAIN 0x03 //[7:0] X_FINE_GAIN
#define MPU_RA_Y_FINE_GAIN 0x04 //[7:0] Y_FINE_GAIN
#define MPU_RA_Z_FINE_GAIN 0x05 //[7:0] Z_FINE_GAIN
#define MPU_RA_XA_OFFS_H 0x06   //[15:0] XA_OFFS
#define MPU_RA_XA_OFFS_L_TC 0x07
#define MPU_RA_YA_OFFS_H 0x08 //[15:0] YA_OFFS
#define MPU_RA_YA_OFFS_L_TC 0x09
#define MPU_RA_ZA_OFFS_H 0x0A //[15:0] ZA_OFFS
#define MPU_RA_ZA_OFFS_L_TC 0x0B
#define MPU_RA_PRODUCT_ID 0x0C   // Product ID Register
#define MPU_RA_XG_OFFS_USRH 0x13 //[15:0] XG_OFFS_USR
#define MPU_RA_XG_OFFS_USRL 0x14
#define MPU_RA_YG_OFFS_USRH 0x15 //[15:0] YG_OFFS_USR
#define MPU_RA_YG_OFFS_USRL 0x16
#define MPU_RA_ZG_OFFS_USRH 0x17 //[15:0] ZG_OFFS_USR
#define MPU_RA_ZG_OFFS_USRL 0x18
#define MPU_RA_SMPLRT_DIV 0x19
#define MPU_RA_CONFIG 0x1A
#define MPU_RA_GYRO_CONFIG 0x1B
#define MPU_RA_ACCEL_CONFIG 0x1C
#define MPU_RA_FF_THR 0x1D
#define MPU_RA_FF_DUR 0x1E
#define MPU_RA_MOT_THR 0x1F
#define MPU_RA_MOT_DUR 0x20
#define MPU_RA_ZRMOT_THR 0x21
#define MPU_RA_ZRMOT_DUR 0x22
#define MPU_RA_FIFO_EN 0x23
#define MPU_RA_I2C_MST_CTRL 0x24
#define MPU_RA_I2C_SLV0_ADDR 0x25
#define MPU_RA_I2C_SLV0_REG 0x26
#define MPU_RA_I2C_SLV0_CTRL 0x27
#define MPU_RA_I2C_SLV1_ADDR 0x28
#define MPU_RA_I2C_SLV1_REG 0x29
#define MPU_RA_I2C_SLV1_CTRL 0x2A
#define MPU_RA_I2C_SLV2_ADDR 0x2B
#define MPU_RA_I2C_SLV2_REG 0x2C
#define MPU_RA_I2C_SLV2_CTRL 0x2D
#define MPU_RA_I2C_SLV3_ADDR 0x2E
#define MPU_RA_I2C_SLV3_REG 0x2F
#define MPU_RA_I2C_SLV3_CTRL 0x30
#define MPU_RA_I2C_SLV4_ADDR 0x31
#define MPU_RA_I2C_SLV4_REG 0x32
#define MPU_RA_I2C_SLV4_DO 0x33
#define MPU_RA_I2C_SLV4_CTRL 0x34
#define MPU_RA_I2C_SLV4_DI 0x35
#define MPU_RA_I2C_MST_STATUS 0x36
#define MPU_RA_INT_PIN_CFG 0x37
#define MPU_RA_INT_ENABLE 0x38
#define MPU_RA_DMP_INT_STATUS 0x39
#define MPU_RA_INT_STATUS 0x3A
#define MPU_RA_ACCEL_XOUT_H 0x3B
#define MPU_RA_ACCEL_XOUT_L 0x3C
#define MPU_RA_ACCEL_YOUT_H 0x3D
#define MPU_RA_ACCEL_YOUT_L 0x3E
#define MPU_RA_ACCEL_ZOUT_H 0x3F
#define MPU_RA_ACCEL_ZOUT_L 0x40
#define MPU_RA_TEMP_OUT_H 0x41
#define MPU_RA_TEMP_OUT_L 0x42
#define MPU_RA_GYRO_XOUT_H 0x43
#define MPU_RA_GYRO_XOUT_L 0x44
#define MPU_RA_GYRO_YOUT_H 0x45
#define MPU_RA_GYRO_YOUT_L 0x46
#define MPU_RA_GYRO_ZOUT_H 0x47
#define MPU_RA_GYRO_ZOUT_L 0x48
#define MPU_RA_EXT_SENS_DATA_00 0x49
#define MPU_RA_MOT_DETECT_STATUS 0x61
#define MPU_RA_I2C_SLV0_DO 0x63
#define MPU_RA_I2C_SLV1_DO 0x64
#define MPU_RA_I2C_SLV2_DO 0x65
#define MPU_RA_I2C_SLV3_DO 0x66
#define MPU_RA_I2C_MST_DELAY_CTRL 0x67
#define MPU_RA_SIGNAL_PATH_RESET 0x68
#define MPU_RA_MOT_DETECT_CTRL 0x69
#define MPU_RA_USER_CTRL 0x6A
#define MPU_RA_PWR_MGMT_1 0x6B
#define MPU_RA_PWR_MGMT_2 0x6C
#define MPU_RA_BANK_SEL 0x6D
#define MPU_RA_MEM_START_ADDR 0x6E
#define MPU_RA_MEM_R_W 0x6F
#define MPU_RA_DMP_CFG_1 0x70
#define MPU_RA_DMP_CFG_2 0x71
#define MPU_RA_FIFO_COUNTH 0x72
#define MPU_RA_FIFO_COUNTL 0x73
#define MPU_RA_FIFO_R_W 0x74
#define MPU_RA_WHO_AM_I 0x75

class MPU6000
{
public:
  void init(SPI *spi_drv);

  void read(float *accel_data, float *gyro_data, float *temp_data, uint64_t *time_us);
  void data_transfer_callback();
  void exti_cb();
  bool new_data();
  inline bool is_initialized() { return spi; }

private:
  void write(uint8_t reg, uint8_t data);
  bool new_data_ = false;
  uint64_t imu_timestamp_ = 0;
  SPI *spi{nullptr};
  GPIO exti_;
  GPIO cs_;
  float accel_scale_;
  float gyro_scale_;
  float acc_[3];
  float gyro_[3];
  float temp_;
};

#endif
