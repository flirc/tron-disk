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

#ifndef I__USB_API_H__
#define I__USB_API_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <libusb-1.0/libusb.h>
#include <ll.h>

/* default USB interface, don't touch this */
#ifndef DEF_IFACE
#define DEF_IFACE	(0)
#endif

/* bmRequest */
#define DEVICE_TO_HOST (LIBUSB_ENDPOINT_IN  | LIBUSB_REQUEST_TYPE_VENDOR)
#define HOST_TO_DEVICE (LIBUSB_ENDPOINT_OUT | LIBUSB_REQUEST_TYPE_VENDOR)

/**
 * dfu() puts device in DFU mode
 *
 * @param handle - pointer to device handle
 *
 * @return      RC_SUCCESS   - write completed successfully
 * @return      LIBUSB_ERR   - libusb error code
 * @return      ENXIO        - invalid USB handle
 * @return      RC_BAD_PARAM - buffer address invalid
 */
int device_set_dfu(libusb_device_handle *handle);

/**
 * device_leds_off() puts device in DFU mode
 *
 * @param handle - pointer to device handle
 *
 * @return      RC_SUCCESS   - write completed successfully
 * @return      LIBUSB_ERR   - libusb error code
 * @return      ENXIO        - invalid USB handle
 * @return      RC_BAD_PARAM - buffer address invalid
 */
int device_leds_off(libusb_device_handle *handle);

/**
 * open_usb_devices() opens specified device
 *
 * @param handle - pointer to device handle
 *
 * @return      RC_SUCCESS   - write completed successfully
 * @return      LIBUSB_ERR   - libusb error code
 * @return      ENXIO        - invalid USB handle
 * @return      RC_BAD_PARAM - buffer address invalid
 */
libusb_device_handle *open_usb_devices(uint32_t VID, uint32_t PID);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* I__USB_API_H__ */
