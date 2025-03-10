###############################################################################
# Generic Makefile Template for C/C++ for use with STM32 Microcontrollers
#
# Copyright (c) 2016 - James Jackson
# All rights reserved.

# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#    * Redistributions of source code must retain the above copyright
#      notice, this list of conditions and the following disclaimer.
#    * Redistributions in binary form must reproduce the above copyright
#      notice, this list of conditions and the following disclaimer in the
#      documentation and/or other materials provided with the distribution.
#    * Neither the name of the <organization> nor the
#      names of its contributors may be used to endorse or promote products
#      derived from this software without specific prior written permission.

# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

TARGET = i2c_mag

BOARD ?= REVO

DEBUG ?= GDB

SERIAL_DEVICE ?= /dev/ttyUSB0

#################################
# GNU ARM Embedded Toolchain
#################################
CC=arm-none-eabi-gcc
CXX=arm-none-eabi-g++
LD=arm-none-eabi-ld
AR=arm-none-eabi-ar
AS=arm-none-eabi-as
CP=arm-none-eabi-objcopy
OD=arm-none-eabi-objdump
NM=arm-none-eabi-nm
SIZE=arm-none-eabi-size
A2L=arm-none-eabi-addr2line

#################################
# Working directories
#################################
ROOT          = ../..
SRC_DIR       = $(ROOT)/src
CMSIS_DIR     = $(ROOT)/lib/CMSIS
STDPERIPH_DIR = $(ROOT)/lib/STM32F4xx_StdPeriph_Driver
USBCORE_DIR   = $(ROOT)/lib/STM32_USB_Device_Library/Core
USBOTG_DIR    = $(ROOT)/lib/STM32_USB_OTG_Driver
USBCDC_DIR    = $(ROOT)/lib/STM32_USB_Device_Library/Class/cdc
VCP_DIR       = $(ROOT)/lib/vcp
STARTUP_DIR   = $(ROOT)/lib/startup
PRINTF_DIR    = $(ROOT)/lib/printf
BIN_DIR       = obj

#################################
# Source Files
#################################
VPATH := $(VPATH):$(STARTUP_DIR)
LDSCRIPT = $(STARTUP_DIR)/stm32f405.ld
ASOURCES = stm32f405.s

# Search path and source files for the CMSIS sources
VPATH	 := $(VPATH):$(CMSIS_DIR)/CM4/CoreSupport
VPATH  := $(VPATH):$(CMSIS_DIR)/CM4/DeviceSupport/ST/STM32F4xx
CMSIS_SRC	 = 	$(notdir $(wildcard $(CMSIS_DIR)/CM4/CoreSupport/*.c)) \
              $(notdir $(wildcard $(CMSIS_DIR)/CM4/DeviceSupport/ST/STM32F4xx/*.c))

# Search path and source files for the ST stdperiph library and exclude files we don't need
VPATH		:= $(VPATH):$(STDPERIPH_DIR)/src
STDPERIPH_SRC	 = $(notdir $(wildcard $(STDPERIPH_DIR)/src/*.c))
EXCLUDES = stm32f4xx_crc.c \
           stm32f4xx_can.c \
           stm32f4xx_fmc.c \
           stm32f4xx_fsmc.c \
           stm32f4xx_sai.c \
           stm32f4xx_cec.c \
           stm32f4xx_dsi.c \
           stm32f4xx_flash_ramfunc.c \
           stm32f4xx_fmpi2c.c \
           stm32f4xx_lptim.c \
           stm32f4xx_qspi.c
STDPERIPH_SRC := $(filter-out ${EXCLUDES}, $(STDPERIPH_SRC))


# Search path and source files for the USB libraries and ignore files we don't need
VPATH		:= $(VPATH):$(USBCORE_DIR)/src:$(USBOTG_DIR)/src:$(USBCDC_DIR)/src
USBCORE_SRC = $(notdir $(wildcard $(USBCORE_DIR)/src/*.c))
USBOTG_SRC = $(notdir $(wildcard $(USBOTG_DIR)/src/*.c))
USBCDC_SRC = $(notdir $(wildcard $(USBCDC_DIR)/src/*.c))
EXCLUDES	= usb_bsp_template.c \
            usb_conf_template.c \
            usb_hcd_int.c \
            usb_hcd.c \
            usb_otg.c \
            usbd_cdc_if_template.c
USBCDC_SRC := $(filter-out ${EXCLUDES}, $(USBCDC_SRC))
USBOTG_SRC := $(filter-out ${EXCLUDES}, $(USBOTG_SRC))

# Add VCP source files
VPATH := $(VPATH):$(VCP_DIR)
VCP_SRC = $(notdir $(wildcard $(VCP_DIR)/*.c))

# Add printf source files
VPATH := $(VPATH):$(PRINTF_DIR)
PRINTF_SRC = printf.cpp

# Make a list of source files and includes
VPATH := $(VPATH):$(SRC_DIR)
CSOURCES =  $(CMSIS_SRC) \
            $(STDPERIPH_SRC) \
            $(USBCORE_SRC) \
            $(USBOTG_SRC) \
            $(USBCDC_SRC) \
            $(PROCESSOR_SRC) \
            $(VCP_SRC) \
            system.c \
            system_stm32f4xx.c


CXXSOURCES = $(PRINTF_SRC) \
			 gpio.cpp \
             led.cpp \
             main.cpp \
             vcp.cpp \
             i2c.cpp \
             hmc5883l.cpp

INCLUDE_DIRS =  $(SRC_DIR) \
                $(ROOT)/include \
                $(STDPERIPH_DIR)/inc \
                $(USBOTG_DIR)/inc \
                $(USBCORE_DIR)/inc \
                $(USBCDC_DIR)/inc \
                $(CMSIS_DIR)/CM4/CoreSupport \
                $(CMSIS_DIR)/CM4/DeviceSupport/ST/STM32F4xx \
                $(CMSIS_DIR)/CM4/DeviceSupport/ST/STM32F4xx/Include \
                $(PRINTF_DIR) \
                $(VCP_DIR)

$(info VPATH = $(VPATH))

#################################
# Object List
#################################
OBJECTS=$(addsuffix .o,$(addprefix $(BIN_DIR)/$(TARGET)/,$(basename $(ASOURCES))))
OBJECTS+=$(addsuffix .o,$(addprefix $(BIN_DIR)/$(TARGET)/,$(basename $(CSOURCES))))
OBJECTS+=$(addsuffix .o,$(addprefix $(BIN_DIR)/$(TARGET)/,$(basename $(CXXSOURCES))))

#################################
# Target Output Files
#################################
TARGET_ELF=$(BIN_DIR)/$(TARGET).elf
TARGET_HEX=$(BIN_DIR)/$(TARGET).hex
TARGET_BIN=$(BIN_DIR)/$(TARGET).bin

#################################
# Debug Config
#################################
ifeq ($(DEBUG), GDB)
$(info ************  BUILDING DEBUG SYMBOLS ************)
DEBUG_FLAGS = -ggdb3
OPTIMIZE = -Og
else
$(info ************  BUILDING RELEASE ************)
DEBUG_FLAGS = -g0
OPTIMIZE = -O3
LTO_FLAGS = -flto -fuse-linker-plugin $(OPTIMIZE)
endif

#################################
# Flags
#################################

#CXX_STRICT_FLAGS += -std=c++11 -pedantic -pedantic-errors -Werror -Wall -Wextra \
#  -Wcast-align -Wcast-qual -Wdisabled-optimization -Wformat=2 -Wlogical-op -Wmissing-include-dirs \
#  -Wredundant-decls -Wshadow -Wstrict-overflow=5 -Wswitch-default -Wundef -Wunused -Wvariadic-macros \
#  -Wctor-dtor-privacy -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Wstrict-null-sentinel
FILE_SIZE_FLAGS += -ffunction-sections -fdata-sections -fno-exceptions
CXX_FILE_SIZE_FLAGS = $(C_FILE_SIZE_FLAGS) -fno-rtti

MCFLAGS=-mcpu=cortex-m4 -mthumb -march=armv7e-m -mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant -Wdouble-promotion
DEFS=-DSTM32F40_41xxx -D__CORTEX_M4 -D__FPU_PRESENT -DWORDS_STACK_SIZE=200 -DUSE_STDPERIPH_DRIVER -DTARGET_$(BOARD)
CFLAGS=-c $(MCFLAGS) $(DEFS) $(OPTIMIZE) $(DEBUG_FLAGS) $(FILE_SIZE_FLAGS) $(addprefix -I,$(INCLUDE_DIRS)) -std=c99
CXXFLAGS=-c $(MCFLAGS) $(DEFS) $(OPTIMIZE) $(DEBUG_FLAGS) $(CXX_FILE_SIZE_FLAGS) $(CXX_STRICT_FLAGS) $(addprefix -I,$(INCLUDE_DIRS)) -std=c++11
LDFLAGS =-T $(LDSCRIPT) $(MCFLAGS) -lm -lc --specs=nano.specs --specs=rdimon.specs $(ARCH_FLAGS)  $(LTO_FLAGS)  $(DEBUG_FLAGS) -static  -Wl,-gc-sections

#################################
# Build
#################################
$(TARGET_BIN): $(TARGET_HEX)
	$(CP) -I ihex -O binary $< $@

$(TARGET_HEX): $(TARGET_ELF)
	$(CP) -O ihex --set-start 0x8000000 $< $@

$(TARGET_ELF): $(OBJECTS)
	$(CXX) -o $@ $^ $(LDFLAGS)
	$(SIZE) $(TARGET_ELF)

$(BIN_DIR)/$(TARGET)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo %% $(notdir $<)
	@$(CXX) -c -o $@ $(CXXFLAGS) $<

$(BIN_DIR)/$(TARGET)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo %% $(notdir $<)
	@$(CC) -c -o $@ $(CFLAGS) $<

$(BIN_DIR)/$(TARGET)/%.o: %.s
	@mkdir -p $(dir $@)
	@echo %% $(notdir $<)
	@$(CC) -c -o $@ $(CFLAGS) $<


#################################
# Recipes
#################################
.PHONY: all flash clean

clean:
	rm -f $(OBJECTS) $(TARGET_ELF) $(TARGET_HEX) $(BIN_DIR)/output.map

flash: $(TARGET_BIN)
	dfu-util -a 0 -s 0x08000000 -D $(TARGET_BIN)
