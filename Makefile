CXX := g++
CXXFLAGS := -Wall -Wextra -Werror -Wno-c++11-extensions -std=c++11
LDFLAGS := -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib -lglfw -L/Users/${USER}/.brew/Cellar/glew/2.2.0_1/lib -lGLEW -framework OpenGL -framework CoreGraphics -framework CoreFoundation
INCLUDES := -I/Users/kvebers/.brew/Cellar/glew/2.2.0_1/include -I/Users/kvebers/.brew/Cellar/glfw/3.3.8/include -I$(shell brew --prefix glm)/include

SRCDIR := src
OBJDIR := obj
SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
TARGET := humangl

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(TARGET)

re: fclean all

install_deps:
	brew list glfw || brew install glfw
	brew list glew || brew install glew

.PHONY: all clean fclean re install_deps