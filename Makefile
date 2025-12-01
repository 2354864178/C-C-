# 编译器与编译选项
CXX = g++
CXXFLAGS = -Wall -Wextra -g
LDFLAGS = 

# 目录定义（新增 TEST_DIR）
SRC_DIR = src
TEST_DIR = test
INCLUDE_DIR = include
BUILD_DIR = build
OUTPUT_DIR = output
TARGET = $(OUTPUT_DIR)/main
LOG_FILE = $(OUTPUT_DIR)/test.log
VLOG_FILE = $(OUTPUT_DIR)/test_verbose.log

SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(TEST_DIR)/*.cpp)

OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(wildcard $(SRC_DIR)/*.cpp)) \
       $(patsubst $(TEST_DIR)/%.cpp, $(BUILD_DIR)/test/%.o, $(wildcard $(TEST_DIR)/*.cpp))

all: $(TARGET)

run: all
	@# 如果通过 make 传入 TEST_VERBOSE=1，则把它导出到环境中并运行
ifeq ($(TEST_VERBOSE),1)
	TEST_VERBOSE=1 $(TARGET)
else
	$(TARGET)
endif

run-verbose: all
	TEST_VERBOSE=1 $(TARGET)

# 把运行输出写入日志（非详细）
run-log: all | $(OUTPUT_DIR)
	@echo "正在运行测试并将输出写入 $(LOG_FILE)"
	@$(TARGET) > $(LOG_FILE) 2>&1 || (echo "测试失败，详见 $(LOG_FILE)"; exit 1)
	@echo "日志已写入 $(LOG_FILE)，以下是日志内容："
	@cat $(LOG_FILE)

# 把详细运行输出写入日志（包括 stderr）
run-verbose-log: all | $(OUTPUT_DIR)
	@echo "正在运行详细测试并将输出写入 $(VLOG_FILE)"
	@TEST_VERBOSE=1 $(TARGET) > $(VLOG_FILE) 2>&1 || (echo "详细测试失败，详见 $(VLOG_FILE)"; exit 1)
	@echo "详细日志已写入 $(VLOG_FILE)，以下是日志内容："
	@cat $(VLOG_FILE)

$(OUTPUT_DIR) $(BUILD_DIR) $(BUILD_DIR)/test:
	mkdir -p $@  # mkdir -p 会递归创建，支持同时创建多个目录

$(TARGET): $(OBJS) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)
	@echo "可执行文件已生成：$@"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

$(BUILD_DIR)/test/%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)/test
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(OUTPUT_DIR)
	@echo "已清理中间文件和输出文件"

.PHONY: all clean
