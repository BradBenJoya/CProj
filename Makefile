.PHONY: all configure build run clean rebuild

BUILD_DIR := build
TOOLCHAIN := $(CURDIR)/$(BUILD_DIR)/conan_toolchain.cmake

all: build

configure:
	conan profile detect --force
	conan install . --output-folder=$(BUILD_DIR) --build=missing
	cmake --fresh -S . -B $(BUILD_DIR) -G Ninja -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN) -DCMAKE_BUILD_TYPE=Release

build: configure
	cmake --build $(BUILD_DIR)

run: build
	./$(BUILD_DIR)/cproj

clean:
	rm -rf $(BUILD_DIR)

rebuild: clean build