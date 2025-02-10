.PHONY: all
.PHONY: run
.PHONY: clean
.PHONY: setup

LD  = x86_64-elf-ld
AS  = x86_64-elf-as
CC  = x86_64-elf-gcc
CXX = x86_64-elf-g++

CXX_SOURCES := $(shell find Kernel -type f -name "*.cpp")
ASM_SOURCES := $(shell find Kernel -type f -name "*.S")
HPP_SOURCES := $(shell find Kernel -type f -name "*.hpp")
CXX_OBJECTS := $(CXX_SOURCES:.cpp=.o)
ASM_OBJECTS := $(ASM_SOURCES:.S=.o)
TARGET      := build/calantha.bin
IMAGE       := build/calantha.iso

all: setup $(TARGET) $(IMAGE)

$(TARGET): $(CXX_OBJECTS) $(ASM_OBJECTS)
	$(CXX) \
	-T linker.ld \
	-o $(TARGET) \
	-ffreestanding \
	-O2 \
	-nostdlib \
  	$(addprefix build/, $(notdir $(CXX_OBJECTS))) \
 	$(addprefix build/, $(notdir $(ASM_OBJECTS))) \
 	-lgcc

%.o: %.cpp
	$(CXX) \
	-std=c++20 \
	-I. \
	-include Kernel/Misc/Global.hpp \
	-ffreestanding \
	-O0 \
	-Wall \
	-Wextra \
	-Werror \
	-fno-pie \
	-fno-stack-protector \
	-fno-stack-check \
	-c $< \
	-o build/$(notdir $@)

%.o: %.S
	$(AS) $< -o build/$(notdir $@)

clean:
	rm build/*.iso build/*.o build/*.bin \
	build/isodir/boot/calantha.bin &>/dev/null || true

run-no-image: $(TARGET)
	# NOTE: this doesn't actually work right now!
	# We need to generate ISO images to run the kernel.
	# As far as I know qemu doesn't support running multiboot2 kernels
	# directly, so this MAY never be possible, but I'll leave it here for now.
	qemu-system-x86_64 -kernel $(TARGET)

run: $(IMAGE)
	qemu-system-x86_64 \
	-cdrom $(IMAGE)	\
	-m 256M \
  	-vga std \

$(IMAGE): $(TARGET)
	grub-file --is-x86-multiboot2 $(TARGET)
	cp grub.cfg build/isodir/boot/grub/grub.cfg
	cp $(TARGET) build/isodir/boot/calantha.bin
	grub-mkrescue -o build/calantha.iso build/isodir

setup:
	mkdir -p build/isodir/boot/grub

	# Generate a dummy CMakeLists build script.
	# This is just so that code completion/clangd can function correctly,
	# we don't actually use Cmake for the build process.
	echo 'cmake_minimum_required(VERSION 3.28)' > CMakeLists.txt
	echo 'project(calantha)' >> CMakeLists.txt
	echo 'set(CMAKE_CXX_STANDARD 20)' >> CMakeLists.txt
	echo 'set(CMAKE_CXX_STANDARD_REQUIRED ON)' >> CMakeLists.txt

	echo 'add_executable(DUMMY ' >> CMakeLists.txt
	echo $(CXX_SOURCES) >> CMakeLists.txt
	echo $(HPP_SOURCES) >> CMakeLists.txt
	echo $(ASM_SOURCES) >> CMakeLists.txt
	echo ')' >> CMakeLists.txt

	echo 'target_include_directories(DUMMY PRIVATE $${CMAKE_CURRENT_SOURCE_DIR})' >> CMakeLists.txt
	echo 'target_compile_options(DUMMY PRIVATE -include Kernel/Misc/Global.hpp)' >> CMakeLists.txt

