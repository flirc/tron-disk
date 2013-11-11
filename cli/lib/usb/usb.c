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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ll.h>
#include <errno.h>

#include <libusb-1.0/libusb.h>
#include <logging.h>
#include <usb.h>
#include <hexdump.h>

#define	EOK		0

#define LEDS_OFF	0x1
#define UPGRADE		0x2

int device_set_dfu(libusb_device_handle *handle)
{
        uint8_t buffer[100];

	if (handle == NULL) {
		logerror("invalid device handle");
		return -ENXIO;
	}

	int result = libusb_control_transfer(handle,
			HOST_TO_DEVICE,
			UPGRADE,
			0,
			0,
			buffer,
			64,
			10);

        if (result != 64) {
                logerror("usb transfer failed, error code[%d]\n", result);
                return result;
	}
               
	return EOK;
}

int device_leds_off(libusb_device_handle *handle)
{
        uint8_t buffer[100];

	if (handle == NULL) {
		logerror("invalid device handle");
		return -ENXIO;
	}

	int result = libusb_control_transfer(handle,
			HOST_TO_DEVICE,
			LEDS_OFF,
			0,
			0,
			buffer,
			64,
			10);

        if (result != 64) {
                logerror("usb transfer failed, error code[%d]\n", result);
                return result;
        }

	return EOK;
}

libusb_device_handle *
open_usb_devices(uint32_t VID, uint32_t PID)
{
	libusb_device **devs;
	libusb_device *dev;
	libusb_device_handle *handle;
	struct libusb_device_descriptor desc;

	int  i = 0;
	int  rq;
	char str[256];

	if (libusb_init(NULL) < 0) {
		logerror("Could not initialize USB driver interface\n");
		return NULL;
	}

#ifdef CONFIG_DEBUG
	libusb_set_debug(NULL, 4);
#endif

	if (libusb_get_device_list(NULL, &devs) < 0) {
		logerror("Could not initialize USB device list\n");
		return NULL;
	}

	while ((dev = devs[i++]) != NULL) {

		if (libusb_get_device_descriptor(dev, &desc) < 0) {
			logerror("failed to get device descriptor");
			return NULL;
		}

		logdebug("\n%04x:%04x (bus %d, device %d)\n",
						desc.idVendor, desc.idProduct,
						libusb_get_bus_number(dev),
						libusb_get_device_address(dev));

		if (desc.idVendor != VID) {
			continue;
		}

		if (desc.idProduct != PID) {
			continue;
		}

		/* we have to open the handle to query Manufacture string */
		if ((rq = libusb_open(dev, &handle)) < 0)
			logerror("can't read mfg string, device may be open\n");

		if (!handle) {
			logerror("can't open USB device\n");
			continue;
		}

		logdebug("claiming interface: %d\n", DEF_IFACE);
		if ((rq = libusb_claim_interface(handle, DEF_IFACE)) < 0) {
			logerror("unable to claim interface: %d\n", DEF_IFACE);
			//continue;
		}

		/* check manufacturer string */
		rq = libusb_get_string_descriptor_ascii(handle,
						desc.iManufacturer,
						(unsigned char *) str,
						sizeof (str));

		if (rq < 0) {
			logerror("can't query product for device\n");
			libusb_close(handle);
			continue;
		}

		logdebug("Vendor: %s\n", str);
		logdebug(" [Vendor Match]\n");

		return handle;
	}

	libusb_free_device_list(devs, 1);
	return NULL;
}
