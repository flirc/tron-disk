CONFIGS := debug release

# Sources
SOURCES :=	src/main.c \
		src/cmds/version.c \
		lib/logging.c \
		lib/getline.c \
		lib/dict.c \
		lib/cmds.c \
		lib/cmds_script.c \
		lib/cmds_shell.c \
		lib/usb/usb.c \
		src/prepost.c \
		lib/hexdump.c \
		lib/timelib.h \
		src/cmds/device.c \

# Libraries
LIBRARIES := readline usb-1.0

# Version
include buildsystem/git.mk
OPTIONS += SCMVERSION='"$(SCMVERSION)"'
OPTIONS += SCMBRANCH='"$(SCMBRANCH)"'
CPPFLAGS += -DBUILD_DATE='"$(shell date)"'

# Release Config
ifeq ($(CONFIG),release)
# Options
OPTIONS += MAX_LOGLEVEL=3 DEFAULT_LOGLEVEL=2
# Flags
CFLAGS += -O2
endif

# Debug Config
ifeq ($(CONFIG),debug)
# Options
OPTIONS += MAX_LOGLEVEL=5 DEFAULT_LOGLEVEL=4
OPTIONS += LIBUSB_PRINTS
# Flags
CFLAGS += -O0 -g
endif

INSTALL_SCRIPT = targets/install
