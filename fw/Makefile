include buildsystem/func.mk

# Set default flags
CPPFLAGS := -Iinclude -Isrc/usbdrv
#CFLAGS := -Wall -Os -Werror -Wno-unused-but-set-variable -Wno-unused-variable -Wno-unused-function
CFLAGS := -Wall -Os -Wno-unused-variable -Wno-unused-function -Wno-unused-but-set-variable
LDFLAGS := 

# include after default flags so config.mk can append to them
ifneq ($(MKTARGET),)
include $(MKTARGET)
else
include target.mk
endif

# Fuse Command
FUSE_COMMAND 	:= -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U \
				lock:w:$(XFUSE):m -U efuse:w:$(EFUSE):m

# Add all the libraries defined in config.mk to LDLIBS
LDLIBS := $(addprefix -l,$(LIBRARIES))

# Add all the frameworks defined in config.mk to LDFLAGS
#   This is only for objective-C in OSX, but it doesn't hurt us here assuming
#   no one defines FRAMEWORKS
LDFLAGS += $(addprefix -framework ,$(FRAMEWORKS))

# Verbose Option
ifeq ($(VERBOSE),1)
	Q :=
else
	Q := @
endif

# Configuration
ifeq ($(words $(CONFIGS)),0)
$(error Must specify at least one config in target makefile (MKTARGET))
endif
ifeq ($(CONFIG),)
CONFIG := $(word 1,$(CONFIGS))
endif
ifeq ($(findstring $(CONFIG),$(CONFIGS)),)
$(error Invalid config specified)
endif
OPTIONS += $($(call TOUPPER,$(CONFIG))_OPTIONS)

# Machine Name and Tool Versions
MACHINE := $(call USCORESUB,$(shell uname -sm))
CCNAME := $(call USCORESUB,$(notdir $(realpath $(shell which $(CC)))))

# Build Directory
BUILDDIR := buildresults/$(TARGET)/$(MACHINE)/$(CCNAME)/$(CONFIG)

# Add in the target name
OPTIONS += __TARGET__='"$(TARGET)"'

# Add the standard __ARCH__ global option
OPTIONS += __ARCH__='"$(call TOUPPER,$(ARCH))"' __ARCH_$(call TOUPPER,$(ARCH))__

# Add in the options
CPPFLAGS += $(addprefix -D,$(OPTIONS))

# Include the dependencies
ifneq ($(MAKECMDGOALS),clean)
sinclude $(addprefix $(BUILDDIR)/,$(call CONVERTEXT, d, $(SOURCES)))
endif

### Main Rule ###
.DEFAULT_GOAL := $(BUILDDIR)/$(TARGET).bin
$(BUILDDIR)/$(TARGET).bin $(BUILDDIR)/$(TARGET).hex : $(BUILDDIR)/$(TARGET).elf
all : $(BUILDDIR)/$(TARGET).bin $(BUILDDIR)/$(TARGET).hex

$(BUILDDIR)/$(TARGET).elf : \
		$(addprefix $(BUILDDIR)/,$(call CONVERTEXT, o, $(SOURCES)))
	$(call OUTPUTINFO,LINK,$@)
	$(call OUTPUTINFO,CONFIG,$(CONFIG))
	@mkdir -p $(@D)
	$(Q)$(CC) -mmcu=$(ARCH) $(LDFLAGS) $^ $(LDLIBS) -o $@


$(BUILDDIR)/$(TARGET).bin : $(BUILDDIR)/$(TARGET).elf
	@echo "[OBJCOPY]       $(TARGET).elf -> $(TARGET).bin"
	$(Q)$(OBJCOPY) -O binary -R .eeprom $< $@
#	@echo "[ENCRYPT]       $(TARGET).bin -> $(TARGET).bin"
#	$(Q)encryptImage -c include/keyFile.h -f $(BUILDDIR)/$(TARGET).bin -o \
#	$(BUILDDIR)/$(TARGET).bin 2>&1 1>/dev/null
#	@echo "[CP]            releases/$(TARGET)"
#	$(Q)cp $(BUILDDIR)/$(TARGET).bin releases/$(TARGET)$(BRANCH).bin

$(BUILDDIR)/$(TARGET).hex : $(BUILDDIR)/$(TARGET).elf
	@echo "[OBJCOPY]       $(TARGET).elf -> $(TARGET).hex"
	$(Q)$(OBJCOPY) -O ihex -R .eeprom $< $@

### Utility Rules ###
.PHONY : clean
clean :
	-rm -rf buildresults

.PHONY : program_fuse
program_fuse : 
	$(AVRDUDE) -F -c $(AVRDUDE_PROGRAMMER) $(STK_PORT) \
		-p $(AVRDUDE_TARGET) $(FUSE_COMMAND) -v


.PHONY : program
program : $(BUILDDIR)/$(TARGET).hex
	$(AVRDUDE) -V -c $(AVRDUDE_PROGRAMMER) $(STK_PORT) \
		-p $(AVRDUDE_TARGET) -U flash:w:$<:i -v

.PHONY : upgrade
upgrade: $(BUILDDIR)/$(TARGET).hex
	@echo "[DFU]           $(TARGET)" 
	$(Q)tron dfu
	$(Q)teensy_loader_cli -mmcu=$(ARCH) -w $(BUILDDIR)/$(TARGET).hex -v 2>&1

.PHONY : flash
flash: $(BUILDDIR)/$(TARGET).hex
	@echo "[DFU]           $(TARGET)" 
	$(Q)teensy_loader_cli -mmcu=$(ARCH) -w $(BUILDDIR)/$(TARGET).hex -v 2>&1

.PHONY : connect
connect : 
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMER) -F $(STK_PORT) \
		-p $(AVRDUDE_TARGET) -t

include buildsystem/autodep.mk
include buildsystem/rules.mk
