# Debugging make because avr does not strip dead objects
TARGET 	:= tron
ARCH	:= atmega32u4

# Sources
SOURCES := src/descriptors.c \
	   src/main.c \
	   src/timelib.c \
	   src/handler.c \
	   src/led_effects.c

# Options
OPTIONS := F_CPU=16000000 F_CLOCK=16000000 BOARD=BOARD_USER __AVR_ATmega32U4__

# Configurations (the first one is the default)
CONFIGS := release

# Configuration Specific Options
RELEASE_OPTIONS := CONFIG_RELEASE

include buildsystem/lufa.mk
