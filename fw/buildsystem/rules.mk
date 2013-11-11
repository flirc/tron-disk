### Implicit Source Rules ###
$(BUILDDIR)/%.o : %.c
	@mkdir -p $(@D)
	$(call OUTPUTINFO,CC,$<)
	$(Q)$(CC) -mmcu=$(ARCH) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o : %.m
	@mkdir -p $(@D)
	$(call OUTPUTINFO,OBJCC,$<)
	$(Q)$(CC) -mmcu=$(ARCH) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o : %.cpp
	@mkdir -p $(@D)
	$(call OUTPUTINFO,C++,$<)
	$(Q)$(CC) -mmcu=$(ARCH) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o : %.S
	@mkdir -p $(@D)
	$(call OUTPUTINFO,AS,$<)
	$(Q)$(CC) -mmcu=$(ARCH) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o : %.s
	@mkdir -p $(@D)
	$(call OUTPUTINFO,AS,$<)
	$(Q)$(AS) -mmcu=$(ARCH) $(ASFLAGS) $(CFLAGS) -c -o $@ $<

%.a :
	@mkdir -p $(@D)
	$(call OUTPUTINFO,AR,$@)
	$(Q)$(AR) crs $@ $^
