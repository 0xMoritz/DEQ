# Compiler and Linker
CC          := g++ -std=c++14

# The Target Binary Program
TARGET      := DEQ.bin

# The Directories, Source, Includes, Objects, Binary and Resources
SRCDIR      := src
BUILDDIR    := obj
SRCEXT      := cpp
DEPEXT      := d
OBJEXT      := o

# Flags
CFLAGS      := -Wall -O3 -g

# https://stackoverflow.com/questions/5178125/how-to-place-object-files-in-separate-subdirectory
#---------------------------------------------------------------------------------
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

# Default Make
all: resources $(TARGET)

# Remake
remake: cleaner all

#Make the Directories
directories:
	@mkdir -p $(BUILDDIR)

# Clean only Objects
clean:
	@$(RM) -rf $(BUILDDIR)

# Full Clean, Objects and Binaries
cleaner: clean
	@$(RM) -rf $(TARGET)

# Pull in dependency info for *existing* .o files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))

# Link
$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $^

# Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INCDEP) -MM $(SRCDIR)/$*.$(SRCEXT) > $(BUILDDIR)/$*.$(DEPEXT)
	@cp -f $(BUILDDIR)/$*.$(DEPEXT) $(BUILDDIR)/$*.$(DEPEXT).tmp
	@sed -e 's|.*:|$(BUILDDIR)/$*.$(OBJEXT):|' < $(BUILDDIR)/$*.$(DEPEXT).tmp > $(BUILDDIR)/$*.$(DEPEXT)
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.$(DEPEXT).tmp | fmt -1 | sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.$(DEPEXT)
	@rm -f $(BUILDDIR)/$*.$(DEPEXT).tmp

# Non-File Targets
.PHONY: all remake clean cleaner resources
