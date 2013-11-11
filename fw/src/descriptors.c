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

#include <descriptors.h>

USB_Descriptor_Device_t const PROGMEM DeviceDescriptor =
{
	.Header = {
		.Size = sizeof(USB_Descriptor_Device_t),
		.Type = DTYPE_Device
	},
		
	.USBSpecification = VERSION_BCD(01.10),
	.Class            = 0x00,
	.SubClass         = 0x00,
	.Protocol         = 0x00,
				
	.Endpoint0Size = FIXED_CONTROL_ENDPOINT_SIZE,
		
	.VendorID      = 0x20A0,
	.ProductID     = 0x0005,
	.ReleaseNumber = 0x0000,
		
	.ManufacturerStrIndex = 0x01,
	.ProductStrIndex      = 0x02,
	.SerialNumStrIndex    = 0x03,
		
	.NumberOfConfigurations = FIXED_NUM_CONFIGURATIONS
};

USB_Descriptor_Configuration_t const PROGMEM ConfigurationDescriptor =
{
	.Config = {
		.Header = {
			.Size = sizeof(USB_Descriptor_Configuration_Header_t),
			.Type = DTYPE_Configuration
		},

		.TotalConfigurationSize =
			sizeof(USB_Descriptor_Configuration_t),

		.TotalInterfaces = 1,

		.ConfigurationNumber   = 1,
		.ConfigurationStrIndex = NO_DESCRIPTOR,
			
		.ConfigAttributes = (USB_CONFIG_ATTR_BUSPOWERED | 
						USB_CONFIG_ATTR_SELFPOWERED),
		
		.MaxPowerConsumption = USB_CONFIG_POWER_MA(100)
	},
		
	.Interface = {
		.Header = {
			.Size = sizeof(USB_Descriptor_Interface_t),
			.Type = DTYPE_Interface
		},

		.InterfaceNumber  = 0x00,
		.AlternateSetting = 0x00,
		.TotalEndpoints   = 2,

		.Class    = 0xFF,
		.SubClass = 0x00,
		.Protocol = 0x00,
			
		.InterfaceStrIndex = NO_DESCRIPTOR
	},

	.DataINEndpoint = {
		.Header = {
			.Size = sizeof(USB_Descriptor_Endpoint_t),
			.Type = DTYPE_Endpoint
		},

		.EndpointAddress   = (ENDPOINT_DESCRIPTOR_DIR_IN | IN_EP),
		.Attributes        = EP_TYPE_BULK,
		.EndpointSize      = IN_EP_SIZE,
		.PollingIntervalMS = 0x00
	},

	.DataOUTEndpoint = {
		.Header = {
			.Size = sizeof(USB_Descriptor_Endpoint_t),
			.Type = DTYPE_Endpoint
		},

		.EndpointAddress    = (ENDPOINT_DESCRIPTOR_DIR_OUT | OUT_EP),
		.Attributes         = EP_TYPE_BULK,
		.EndpointSize       = OUT_EP_SIZE,
		.PollingIntervalMS  = 0x00
	}
};

USB_Descriptor_String_t const PROGMEM LanguageString =
{
	.Header = {
		.Size = USB_STRING_LEN(1),
		.Type = DTYPE_String
	},
		
	.UnicodeString = {
		LANGUAGE_ID_ENG
	}
};

USB_Descriptor_String_t const PROGMEM ManufacturerString =
{
	.Header = {
		.Size = USB_STRING_LEN(5),
		.Type = DTYPE_String
	},
		
	.UnicodeString = L"flirc"
};

USB_Descriptor_String_t const PROGMEM ProductString =
{
	.Header = {
		.Size = USB_STRING_LEN(4),
		.Type = DTYPE_String
	},
		
	.UnicodeString = L"tron"
};

USB_Descriptor_String_t const PROGMEM SerialNumberString  =
{
	.Header = {
		.Size = USB_STRING_LEN(12),
		.Type = DTYPE_String
	},
		
	.UnicodeString = L"000000000000"
};

uint16_t CALLBACK_USB_GetDescriptor(const uint16_t wValue, const uint8_t wIndex,
		void** const DescriptorAddress)
{
	const uint8_t  DescriptorType   = (wValue >> 8);
	const uint8_t  DescriptorNumber = (wValue & 0xFF);

	void *Address = NULL;
	uint16_t Size = NO_DESCRIPTOR;

	switch (DescriptorType) {
	case DTYPE_Device: 
		Address = (void*)&DeviceDescriptor;
		Size    = sizeof(USB_Descriptor_Device_t);
		break;
	case DTYPE_Configuration: 
		Address = (void*)&ConfigurationDescriptor;
		Size    = sizeof(USB_Descriptor_Configuration_t);
		break;
	case DTYPE_String: 
		switch (DescriptorNumber) {
		case 0x00: 
			Address = (void*)&LanguageString;
			Size = pgm_read_byte(&LanguageString.Header.Size);
			break;
		case 0x01: 
			Address = (void*)&ManufacturerString;
			Size = pgm_read_byte(&ManufacturerString.Header.Size);
			break;
		case 0x02: 
			Address = (void*)&ProductString;
			Size = pgm_read_byte(&ProductString.Header.Size);
			break;
		case 0x03:
			Address = (void*)&SerialNumberString;
			Size = pgm_read_byte(&SerialNumberString.Header.Size);
			break;
		}

		break;
	}

	*DescriptorAddress = Address;
	return Size;
}
