# LUFA Options
#LUFA_PATH = /usr/local/CrossPack-AVR/lib/LUFA
LUFA_PATH = lib/LUFA

# LUFA library compile-time options
LUFA_OPTIONS += 	USE_NONSTANDARD_DESCRIPTOR_NAMES \
			NO_STREAM_CALLBACKS	\
			USB_DEVICE_ONLY	\
			FIXED_CONTROL_ENDPOINT_SIZE=8	\
			FIXED_NUM_CONFIGURATIONS=1	\
			USE_FLASH_DESCRIPTORS	\

CPPFLAGS += -I$(LUFA_PATH)
CPPFLAGS += $(addprefix -D ,$(LUFA_OPTIONS))
CPPFLAGS += -D USE_STATIC_OPTIONS="(USB_DEVICE_OPT_FULLSPEED \
			| USB_OPT_REG_ENABLED | USB_OPT_AUTO_PLL)"

SOURCES += 	$(LUFA_PATH)/LUFA/Drivers/USB/LowLevel/DevChapter9.c        \
			$(LUFA_PATH)/LUFA/Drivers/USB/LowLevel/Endpoint.c           \
			$(LUFA_PATH)/LUFA/Drivers/USB/LowLevel/Host.c               \
			$(LUFA_PATH)/LUFA/Drivers/USB/LowLevel/HostChapter9.c       \
			$(LUFA_PATH)/LUFA/Drivers/USB/LowLevel/LowLevel.c           \
			$(LUFA_PATH)/LUFA/Drivers/USB/LowLevel/Pipe.c               \
			$(LUFA_PATH)/LUFA/Drivers/USB/HighLevel/Events.c            \
			$(LUFA_PATH)/LUFA/Drivers/USB/HighLevel/USBInterrupt.c      \
			$(LUFA_PATH)/LUFA/Drivers/USB/HighLevel/USBTask.c           \
			$(LUFA_PATH)/LUFA/Drivers/USB/HighLevel/ConfigDescriptor.c  \

# LUFA FLAGS
CFLAGS += -funsigned-char
CFLAGS += -funsigned-bitfields
CFLAGS += -ffunction-sections
CFLAGS += -fpack-struct
CFLAGS += -fshort-enums
CFLAGS += -Wall
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wundef
CFLAGS += -std=gnu99

# LUFA Compatibility
OPTIONS += __ARCH__='"$(call TOUPPER,$(ARCH))"' __AVR_$(call TOUPPER,$(ARCH))__
