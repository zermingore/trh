BUILD_DIR=./build
PRJ_NAME=trh


all:
	@ mkdir -p $(BUILD_DIR)
	cmake -B $(BUILD_DIR)
	make -C $(BUILD_DIR)
	@ cp $(BUILD_DIR)/$(PRJ_NAME) ./

distclean:
	rm -rf $(BUILD_DIR)/
