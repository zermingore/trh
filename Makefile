SHELL := /bin/bash
BUILD_DIR=./build


all:
	@ mkdir -p $(BUILD_DIR)
	@ cd $(BUILD_DIR) > /dev/null && cmake ..
	@ $(MAKE) -C $(BUILD_DIR)

distclean:
	rm -rf $(BUILD_DIR)/
