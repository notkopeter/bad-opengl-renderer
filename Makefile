TARGET   := main
BUILD    := build

CC       := gcc
CXX      := g++

SRC_DIR  := SRC
CPP_SRCS := $(wildcard $(SRC_DIR)/*.cpp)
C_SRCS   := $(wildcard $(SRC_DIR)/*.c)

OBJS     := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD)/%.o,$(CPP_SRCS)) \
            $(patsubst $(SRC_DIR)/%.c,$(BUILD)/%.o,$(C_SRCS))
DEPS     := $(OBJS:.o=.d)

# ---- Flags ----
INCLUDES := -IHEADERS -ILibraries/include
OPT      := -O2 -g
WARN     := -Wall -Wextra
DEPFLAGS := -MMD -MP

CFLAGS   := $(OPT) $(WARN) $(INCLUDES) $(DEPFLAGS)
CXXFLAGS := -std=c++17 $(OPT) $(WARN) $(INCLUDES) $(DEPFLAGS)

# GLFW: use system package (pkg-config) if present, else Libraries/lib
GLFW_LIBS := $(shell pkg-config --libs glfw3 2>/dev/null)
ifeq ($(GLFW_LIBS),)
  GLFW_LIBS := -LLibraries/lib -lglfw
endif

LDFLAGS  := -LLibraries/lib
LDLIBS   := $(GLFW_LIBS) -lGL -ldl -lpthread -lm

# ---- Rules ----
.PHONY: all run clean rebuild

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

$(BUILD)/%.o: $(SRC_DIR)/%.cpp | $(BUILD)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/%.o: $(SRC_DIR)/%.c | $(BUILD)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD):
	mkdir -p $(BUILD)

# Run from the project root so relative paths to SHADERS/ and TEXTURES/ work
run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD) $(TARGET)

rebuild: clean all

-include $(DEPS)