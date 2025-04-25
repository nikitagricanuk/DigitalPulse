# Paths
BOARD=esp8266:esp8266:nodemcuv2
PORT=/dev/cu.usbserial-0001
BUILD_DIR=build
FQBN=$(BOARD)
SKETCH_DIR=.

# Targets
all: compile

compile:
	arduino-cli compile \
		--fqbn $(FQBN) \
		--build-path $(BUILD_DIR) \
		--libraries ./lib \
		--build-property build.extra_flags="-Isrc" \
		$(SKETCH_DIR)

upload: compile
	arduino-cli upload \
		--fqbn $(FQBN) \
		--port $(PORT) \
		--input-dir $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)