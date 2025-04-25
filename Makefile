# Configuration
BOARD=esp8266:esp8266:nodemcuv2
PORT=/dev/cu.usbserial-0001
FQBN=$(BOARD)
BUILD_DIR=build
SRC_DIR=src
SKETCH=$(SRC_DIR)/main.ino

# Default target
all: compile

# Compile sketch
compile:
	arduino-cli compile \
		--fqbn $(FQBN) \
		--build-path $(BUILD_DIR) \
		--libraries ./lib \
		$(SRC_DIR)

# Upload firmware (depends on compile)
upload: compile
	arduino-cli upload \
		--fqbn $(FQBN) \
		--port $(PORT) \
		--input-dir $(BUILD_DIR)

# Clean build folder
clean:
	rm -rf $(BUILD_DIR)