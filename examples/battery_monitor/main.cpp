/*
 * Copyright (c) 2020, Richard Henrichsen
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

#include "analog_digital_converter.h"
#include "analog_pin.h"
#include "battery_monitor.h"
#include "printf.h"
#include "system.h"
#include "vcp.h"

VCP *vcpPtr = NULL;

static void _putc(void *p, char c)
{
  (void)p; // avoid compiler warning about unused variable
  vcpPtr->put_byte(c);
}

int main()
{
  systemInit();

  VCP vcp;
  vcp.init();
  vcpPtr = &vcp;
  init_printf(NULL, _putc);

  AnalogDigitalConverter adc;
  adc.init(&adc_config[0]);

  BatteryMonitor monitor;
  monitor.init(battery_monitor_config, &adc, 15.701, 27.322);

  while (true)
  {
    float voltage = monitor.read_voltage();
    float current = monitor.read_current();
    printf("%f;\t%f\n", voltage, current);
    delay(500);
  }
}
