BUILDDIR = build

TOOLS = tools

SOURCES += src/aftertouch/aftertouch.c
SOURCES += src/flash/flash.c src/flash/settings.c
SOURCES += src/led/led.c src/led/palettes.c
SOURCES += src/send/send.c
SOURCES += src/sysex/sysex.c src/sysex/messages.c
SOURCES += src/other/challenge.c src/other/conversion.c src/other/tempo.c

SOURCES += src/modes/mode.c
SOURCES += src/modes/normal/performance.c src/modes/normal/ableton.c src/modes/normal/note.c src/modes/normal/drum.c src/modes/normal/fader.c src/modes/normal/programmer.c src/modes/normal/piano.c src/modes/normal/text.c
SOURCES += src/modes/special/boot.c src/modes/special/setup.c src/modes/special/editor.c src/modes/special/scale.c src/modes/special/puyo.c src/modes/special/idle.c

SOURCES += src/app.c
SOURCES += src/test.cpp

INCLUDES += -Iinclude -I

LIB = lib/launchpad_pro.a

OBJECTS = $(addprefix $(BUILDDIR)/, $(addsuffix .o, $(basename $(SOURCES))))

# output files
SYX = $(BUILDDIR)/cfw.syx
ELF = $(BUILDDIR)/cfw.elf
HEX = $(BUILDDIR)/cfw.hex
HEXTOSYX = $(BUILDDIR)/hextosyx

# tools
HOST_GPP = g++
CC = arm-none-eabi-gcc
CPP = arm-none-eabi-g++
#LD = arm-none-eabi-gcc
LD = arm-none-eabi-g++
OBJCOPY = arm-none-eabi-objcopy

CXFLAGS = -Os -g -Wall -I.\
-D_STM32F103RBT6_  -D_STM3x_  -D_STM32x_ -mthumb -mcpu=cortex-m3 \
-fsigned-char  -DSTM32F10X_MD -DUSE_STDPERIPH_DRIVER -DHSE_VALUE=6000000UL \
-DCMSIS -DUSE_GLOBAL_CONFIG   -g3 -ffunction-sections  -mlittle-endian \
$(INCLUDES) -o

CFLAGS = -std=c99 $(CXFLAGS)
CPPFLAGS = -std=c++0x $(CXFLAGS)

LDSCRIPT = stm32_flash.ld

LDFLAGS += -T$(LDSCRIPT) -u _start -u _Minimum_Stack_Size  -mcpu=cortex-m3 -mthumb -specs=nano.specs -specs=nosys.specs -nostdlib -Wl,-static  -g3 -N -nostartfiles -Wl,--gc-sections

all: $(SYX)

# build the final sysex file from the ELF - run the simulator first
$(SYX): $(HEX) $(HEXTOSYX)
	./$(HEXTOSYX) $(HEX) $(SYX)

# build the tool for conversion of ELF files to sysex, ready for upload to the unit
$(HEXTOSYX):
	$(HOST_GPP) -Ofast -std=c++0x -I./$(TOOLS)/libintelhex/include ./$(TOOLS)/libintelhex/src/intelhex.cc $(TOOLS)/hextosyx.cpp -o $(HEXTOSYX)

$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(ELF): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS) $(LIB)

DEPENDS := $(OBJECTS:.o=.d)

-include $(DEPENDS)

$(BUILDDIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -MMD -o $@ $<

$(BUILDDIR)/%.o: %.cpp
	mkdir -p $(dir $@)
	$(CPP) -c $(CPPFLAGS) -MMD -o $@ $<

clean:
	rm -rf $(BUILDDIR)
