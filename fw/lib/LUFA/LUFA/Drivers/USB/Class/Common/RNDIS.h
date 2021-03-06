/*
             LUFA Library
     Copyright (C) Dean Camera, 2009.
              
  dean [at] fourwalledcubicle [dot] com
      www.fourwalledcubicle.com
*/

/*
  Copyright 2009  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, and distribute this software
  and its documentation for any purpose and without fee is hereby
  granted, provided that the above copyright notice appear in all
  copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \ingroup Group_USBClassRNDIS
 *  @defgroup Group_USBClassRNDISCommon  Common Class Definitions
 *
 *  \section Module Description
 *  Constants, Types and Enum definitions that are common to both Device and Host modes for the USB
 *  RNDIS Class.
 *
 *  @{
 */

#ifndef _RNDIS_CLASS_COMMON_H_
#define _RNDIS_CLASS_COMMON_H_

	/* Includes: */
		#include "../../USB.h"
		#include "CDC.h"
		
		#include <string.h>
	
	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Macros: */
		/** Implemented RNDIS Version Major */
		#define REMOTE_NDIS_VERSION_MAJOR             0x01

		/** Implemented RNDIS Version Minor */
		#define REMOTE_NDIS_VERSION_MINOR             0x00
	
		/** RNDIS request to issue a host-to-device NDIS command */
		#define REQ_SendEncapsulatedCommand           0x00

		/** RNDIS request to issue a device-to-host NDIS response */
		#define REQ_GetEncapsulatedResponse           0x01
		
		/** Maximum size in bytes of a RNDIS control message which can be sent or received */
		#define RNDIS_MESSAGE_BUFFER_SIZE             128

		/** Maximum size in bytes of an Ethernet frame which can be sent or received */
		#define ETHERNET_FRAME_SIZE_MAX               1500
		
		/** Notification request value for a RNDIS Response Available notification */
		#define NOTIF_ResponseAvailable               1
		
	/* Enums: */
		/** Enum for the possible NDIS adapter states. */
		enum RNDIS_States_t
		{
			RNDIS_Uninitialized    = 0, /**< Adapter currently uninitialized */
			RNDIS_Initialized      = 1, /**< Adapter currently initialized but not ready for data transfers */
			RNDIS_Data_Initialized = 2, /**< Adapter currently initialized and ready for data transfers */
		};

		/** Enum for the NDIS hardware states */
		enum NDIS_Hardware_Status_t
		{
			NDIS_HardwareStatus_Ready, /**< Hardware Ready to accept commands from the host */
			NDIS_HardwareStatus_Initializing, /**< Hardware busy initializing */
			NDIS_HardwareStatus_Reset, /**< Hardware reset */
			NDIS_HardwareStatus_Closing, /**< Hardware currently closing */
			NDIS_HardwareStatus_NotReady /**< Hardware not ready to accept commands from the host */
		};
		
	/* Type Defines: */
		/** Type define for a physical MAC address of a device on a network */
		typedef struct
		{
			uint8_t       Octets[6]; /**< Individual bytes of a MAC address */
		} MAC_Address_t;

		/** Type define for an Ethernet frame buffer. */
		typedef struct
		{
			uint8_t       FrameData[ETHERNET_FRAME_SIZE_MAX]; /**< Ethernet frame contents */
			uint16_t      FrameLength; /**< Length in bytes of the Ethernet frame stored in the buffer */
			bool          FrameInBuffer; /**< Indicates if a frame is currently stored in the buffer */
		} Ethernet_Frame_Info_t;

		/** Type define for a RNDIS message header, sent before RNDIS messages */
		typedef struct
		{
			uint32_t MessageType; /**< RNDIS message type, a REMOTE_NDIS_*_MSG constant */
			uint32_t MessageLength; /**< Total length of the RNDIS message, in bytes */
		} RNDIS_Message_Header_t;

		/** Type define for a RNDIS packet message, used to encapsulate Ethernet packets sent to and from the adapter */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t DataOffset;
			uint32_t DataLength;
			uint32_t OOBDataOffset;
			uint32_t OOBDataLength;
			uint32_t NumOOBDataElements;
			uint32_t PerPacketInfoOffset;
			uint32_t PerPacketInfoLength;
			uint32_t VcHandle;
			uint32_t Reserved;
		} RNDIS_Packet_Message_t;

		/** Type define for a RNDIS Initialize command message */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
			
			uint32_t MajorVersion;
			uint32_t MinorVersion;
			uint32_t MaxTransferSize;
		} RNDIS_Initialize_Message_t;
		
		/** Type define for a RNDIS Initialize complete response message */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
			uint32_t Status;
			
			uint32_t MajorVersion;
			uint32_t MinorVersion;
			uint32_t DeviceFlags;
			uint32_t Medium;
			uint32_t MaxPacketsPerTransfer;
			uint32_t MaxTransferSize;
			uint32_t PacketAlignmentFactor;
			uint32_t AFListOffset;
			uint32_t AFListSize;
		} RNDIS_Initialize_Complete_t;
		
		/** Type define for a RNDIS Keepalive command message */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
		} RNDIS_KeepAlive_Message_t;

		/** Type define for a RNDIS Keepalive complete message */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
			uint32_t Status;
		} RNDIS_KeepAlive_Complete_t;

		/** Type define for a RNDIS Reset complete message */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t Status;

			uint32_t AddressingReset;
		} RNDIS_Reset_Complete_t;
		
		/** Type define for a RNDIS Set command message */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
			
			uint32_t Oid;
			uint32_t InformationBufferLength;
			uint32_t InformationBufferOffset;
			uint32_t DeviceVcHandle;
		} RNDIS_Set_Message_t;

		/** Type define for a RNDIS Set complete response message */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
			uint32_t Status;
		} RNDIS_Set_Complete_t;
		
		/** Type define for a RNDIS Query command message */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
			
			uint32_t Oid;
			uint32_t InformationBufferLength;
			uint32_t InformationBufferOffset;
			uint32_t DeviceVcHandle;
		} RNDIS_Query_Message_t;
		
		/** Type define for a RNDIS Query complete response message */
		typedef struct
		{
			uint32_t MessageType;
			uint32_t MessageLength;
			uint32_t RequestId;
			uint32_t Status;
			
			uint32_t InformationBufferLength;
			uint32_t InformationBufferOffset;
		} RNDIS_Query_Complete_t;
				
	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif
		
#endif

/** @} */
