/*
 * Copyright 2013 Jason Kotzin, Flirc Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *
 *    2. Redistributions in binary form must reproduce the above
 *       copyright notice, this list of conditions and the following
 *       disclaimer in the documentation and/or other materials
 *       provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY ROBERT C. CURTIS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL ROBERT C. CURTIS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * The views and conclusions contained in the software and documentation
 * are those of the authors and should not be interpreted as representing
 * official policies, either expressed or implied, of Jason Kotzin.
 */

#ifndef __MAIN_H__
#define __MAIN_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cpluspuls */

/* Global Variables: */
extern volatile uint8_t dataToSend[];
extern volatile uint8_t dataReceived[];

/* Function Prototypes: */
void SetupHardware(void);
void Main_Task(void);
	
void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_UnhandledControlRequest(void);

void ReceiveDataFromHost(void);
void SendDataToHost(void);
void output_leds(uint8_t in, int out);

#define DEVICE_TO_HOST (REQDIR_DEVICETOHOST | REQTYPE_VENDOR | REQTYPE_STANDARD)
#define HOST_TO_DEVICE (REQDIR_HOSTTODEVICE | REQTYPE_VENDOR | REQTYPE_STANDARD)

#define CLAY_REQUEST ((USB_ControlRequest.bmRequestType & CONTROL_REQTYPE_TYPE) == REQTYPE_VENDOR && \
		(USB_ControlRequest.bmRequestType & CONTROL_REQTYPE_RECIPIENT) == REQREC_ENDPOINT) 

#define LEDS_OFF			0x1
#define UPGRADE	       			0x2

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __MAIN_H__ */
