# 编译器与编译选项
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
LDFLAGS = 

# 目录定义
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
OUTPUT_DIR = output
TARGET = $(OUTPUT_DIR)/main

# 源文件与目标文件
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# 默认目标：构建可执行文件
all: $(TARGET)

# 确保输出目录存在（仅作为顺序依赖，不强制重建）
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# 构建可执行文件：依赖目标文件和output目录
$(TARGET): $(OBJS) | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ $(LDFLAGS)
	@echo "可执行文件已生成：$@"

# 编译源文件为目标文件（自动创建build目录）
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# 清理目标
clean:
	rm -rf $(BUILD_DIR) $(OUTPUT_DIR)
	@echo "已清理中间文件和输出文件"

# 伪目标声明（避免与同名文件冲突）
.PHONY: all clean