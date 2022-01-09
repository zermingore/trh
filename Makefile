BUILD_DIR=./build
PRJ_NAME=trh

all: gtk


gtk:
	@ mkdir -p $(BUILD_DIR)
	cmake src/gtk/CMakeLists.txt -B $(BUILD_DIR) -D PRJ_ROOT=$(shell pwd)
	$(MAKE) -C $(BUILD_DIR)
	@ cp $(BUILD_DIR)/$(PRJ_NAME) ./


debug:
	@ mkdir -p $(BUILD_DIR)
	cmake src/gtk/CMakeLists.txt -DCMAKE_BUILD_TYPE=Debug -B $(BUILD_DIR)
	$(MAKE) -C $(BUILD_DIR)
	@ cp $(BUILD_DIR)/$(PRJ_NAME) ./


distclean:
	rm -rf $(BUILD_DIR)/
