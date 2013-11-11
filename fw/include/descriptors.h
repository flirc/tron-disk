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

#ifndef I__DESCRIPTORS_H__
#define I__DESCRIPTORS_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cpluspuls */

#include <LUFA/Drivers/USB/USB.h>
#include <avr/pgmspace.h>

/* Global Defines */
#define IN_EP                       1
#define OUT_EP                      2
#define IN_EP_SIZE                  64
#define OUT_EP_SIZE                 64

/** 
 * Type define for the device configuration descriptor structure. This must be
 * defined in the application code, as the configuration descriptor contains 
 * several sub-descriptors which vary between devices, and which describe the
 * device's usage to the host.
 */
typedef struct
{
	USB_Descriptor_Configuration_Header_t Config;
	USB_Descriptor_Interface_t            Interface;
	USB_Descriptor_Endpoint_t             DataINEndpoint;
	USB_Descriptor_Endpoint_t             DataOUTEndpoint;
} USB_Descriptor_Configuration_t;

/* External Variables: */
extern USB_Descriptor_Configuration_t const ConfigurationDescriptor;

/* Macros: */

/* Function Prototypes: */
uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex,
		void** const DescriptorAddress) ATTR_WARN_UNUSED_RESULT
						ATTR_NON_NULL_PTR_ARG(3);

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* I__DESCRIPTORS_H__ */
