.PHONY: all
.PHONY: run
.PHONY: clean
.PHONY: setup
.PHONY: debug

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
ARCH        := x86_64

CXX_FLAGS := -ffreestanding \
	-O2 -Wall -Wextra -Werror \
	-fno-pie \
	-fno-strict-aliasing \
	-fno-exceptions \
	-fno-rtti \
	-fno-stack-protector \
	-fno-stack-check \
	-fno-PIC \
	-ffunction-sections \
	-fdata-sections \
	-m64 \
	-march=x86-64 \
	-mno-80387 \
	-mno-mmx \
	-mno-sse \
	-mno-sse2 \
	-mno-red-zone \
	-mcmodel=kernel

LD_FLAGS := -Wl,--build-id=none \
	-nostdlib \
	-static \
	-z max-page-size=0x1000 \
	-Wl,--gc-sections \
	-lgcc

all: setup $(TARGET) $(IMAGE)

$(TARGET): $(CXX_OBJECTS) $(ASM_OBJECTS)
	$(CXX) \
		-T linker.ld \
		-o $(TARGET) \
		$(LD_FLAGS) \
		$(CXX_FLAGS) \
		$(addprefix build/, $(notdir $(CXX_OBJECTS))) \
		$(addprefix build/, $(notdir $(ASM_OBJECTS))) \

%.o: %.cpp
	$(CXX) \
		-std=c++20 \
		-I. -include Kernel/Misc/Global.hpp \
		$(CXX_FLAGS) \
		-c $< \
		-o build/$(notdir $@)

%.o: %.S
	$(AS) $< -o build/$(notdir $@)

clean:
	rm -rf ./build

run: setup $(TARGET) $(IMAGE)
	qemu-system-x86_64 \
		-m 2G \
		-boot d \
		-vga std \
		-serial stdio \
		-cdrom $(IMAGE)	\

$(IMAGE): $(TARGET)
	grub-file --is-x86-multiboot2 $(TARGET)
	cp -v grub.cfg build/isodir/boot/grub/grub.cfg
	cp -v $(TARGET) build/isodir/boot/calantha.bin
	grub-mkrescue -o build/calantha.iso build/isodir

setup:
	mkdir -p build/isodir/boot/grub

	# Generate a dummy CMakeLists build script.
	# This is just so that code completion/clangd can function correctly for
	# editors like Clion. we don't actually use Cmake for the build process.
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

