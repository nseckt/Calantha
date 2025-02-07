LD  = x86_64-elf-ld
AS  = x86_64-elf-as
CC  = x86_64-elf-gcc
CXX = x86_64-elf-g++

CXX_SOURCES := $(shell find Kernel -type f -name "*.cpp")
ASM_SOURCES := $(shell find Kernel -type f -name "*.S")
CXX_FLAGS   := -std=c++20 -IKernel -ffreestanding -O2 -Wall -Wextra
CXX_OBJECTS := $(CXX_SOURCES:.cpp=.o)
ASM_OBJECTS := $(ASM_SOURCES:.S=.o)
TARGET      := build/calantha.bin
IMAGE       := build/calantha.iso
LINK_FLAGS  := -T linker.ld -o $(TARGET) -ffreestanding -O2 -nostdlib

all: setup $(TARGET) $(IMAGE)

$(TARGET): $(CXX_OBJECTS) $(ASM_OBJECTS)
	$(CXX) \
	$(LINK_FLAGS) \
 	$(addprefix build/, $(notdir $(CXX_OBJECTS))) \
 	$(addprefix build/, $(notdir $(ASM_OBJECTS))) \
 	-lgcc

%.o: %.cpp
	$(CXX) \
	$(CXX_FLAGS) \
	-c $< \
	-o build/$(notdir $@)

%.o: %.S
	$(AS) $< -o build/$(notdir $@)

clean:
	rm build/*.iso build/*.o build/*.bin \
	build/isodir/boot/calantha.bin &>/dev/null || true

run-no-image: $(TARGET)
	qemu-system-x86_64 -kernel $(TARGET)

run: $(IMAGE)
	qemu-system-x86_64 -cdrom $(IMAGE)

$(IMAGE): $(TARGET)
	grub-file --is-x86-multiboot2 $(TARGET)
	cp grub.cfg build/isodir/boot/grub/grub.cfg
	cp $(TARGET) build/isodir/boot/calantha.bin
	grub-mkrescue -o build/calantha.iso build/isodir

setup:
	mkdir -p build/isodir/boot/grub

.PHONY: all run clean setup