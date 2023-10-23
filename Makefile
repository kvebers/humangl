NAME = humangl
CFLAGS =  -Wno-deprecated-declarations -Wno-macro-redefined -Wno-c++11-extensions -std=c++11
GLFW = -I/Users/${USER}/.brew/Cellar/glfw/3.3.8/include -L/Users/${USER}/.brew/Cellar/glfw/3.3.8/lib -lglfw -framework OpenGL -framework CoreGraphics -framework CoreFoundation
GLEW = -I/Users/${USER}/.brew/Cellar/glew/2.2.0_1/include -L/Users/${USER}/.brew/Cellar/glew/2.2.0_1/lib -lGLEW -framework OpenGL

GLAD = glad.o
GLADLIB = gcc -c src/includes/glad/glad.c -Ilibs

EXEC = ./scop

# Vertex and Fragment shader source files
VERTEX_SOURCE = ../src/shader/vertexSource.vertex
FRAGMENT_SOURCE = ../src/shader/fragmentSource.fragment

# RS = ../resources/
# TX = ../textures/

# Texture files
# TEXTURE_OK = ${TX}ok.jpeg
# TEXTURE_COLORS = ${TX}colors.jpeg
# TEXTURE_SKULL = ${TX}skull.jpeg
# TEXTURE_CAMEL = ${TX}camel.jpeg
# TEXTURE_UVMAP = ${TX}uvmap.jpeg
# TEXTURE_TREX = ${TX}trex.jpeg
# TEXTURE_PUMPKIN = ${TX}pumpkin.png
# TEXTURE_MONSTER = ${TX}monster.jpeg

# TEXTURES = ${TEXTURE_OK} ${TEXTURE_COLORS} ${TEXTURE_CAMEL} \
# 		   ${TEXTURE_SKULL} ${TEXTURE_TREX} ${TEXTURE_UVMAP} \
# 		   ${TEXTURE_MONSTER} ${TEXTURE_PUMPKIN} \

# Object files
# OBJECT_42 = ${RS}42.obj
# OBJECT_TEAPOT = ${RS}teapot.obj
# OBJECT_SPIDER = ${RS}spider.obj
# OBJECT_SKULL = ${RS}skull.obj
# OBJECT_AXE = ${RS}axe.obj
# OBJECT_ARMOR = ${RS}armor.obj
# OBJECT_ALIENANIMAL = ${RS}alienanimal.obj
# OBJECT_BUILDING = ${RS}building.obj
# OBJECT_STARWARS = ${RS}sw.obj
# OBJECT_HEILBRONN = ${RS}hb.obj
# OBJECT_CAMEL = ${RS}Camel.obj
# OBJECT_CASTLE = ${RS}castle.obj
# OBJECT_TREX = ${RS}trex.obj
# OBJECT_PUMPKIN = ${RS}pumpkin.obj
# OBJECT_HOUSE = ${RS}ohouse.obj
# OBJECT_PARROT = ${RS}parrot.obj
# OBJECT_TCP = ${RS}tcp.obj
# OBJECT_PLANE = ${RS}plane.obj
# OBJECT_SCULP = ${RS}sculp.obj
# OBJECT_MONSTER = ${RS}monster.obj

REBUILD = make re
RM		= rm -rf
CC		= c++
SRC_DIR = src/
OBJ_DIR = objects/

SRC = humangl \
	  glfw \
	  camera \
	  render \
	  object \
	  texture \
	  keyPress \
	  renderText \
	  shader/shader \
	  processObjFile \

# Imgui source files to compile
IMGUI =	includes/imgui/imgui \
		includes/imgui/imgui_demo \
		includes/imgui/imgui_draw \
		includes/imgui/imgui_tables \
		includes/imgui/imgui_widgets \
		includes/imgui/imgui_impl_glfw \
		includes/imgui/imgui_impl_opengl3 \

SRCS	= $(addprefix $(SRC_DIR), $(addsuffix .cpp, $(SRC)))
OBJS	= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC)))
IMGUI_SRCS	= $(addprefix $(SRC_DIR), $(addsuffix .cpp, $(IMGUI)))
IMGUI_OBJS	= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(IMGUI)))
all: $(NAME)

$(NAME): $(OBJS) ${IMGUI_OBJS}
	@echo "$(YELLOW)Compiling..$(COLOR_END)"
	@${GLADLIB}
	@$(CC) $(CFLAGS) $(GLEW) $(GLFW) ${GLAD} $(OBJS) ${IMGUI_OBJS} -o $(NAME)
	@echo "$(GREEN)The project is compiled..$(COLOR_END)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)Cleaning...$(COLOR_END)"
	@$(RM) $(OBJ_DIR)
	@echo "$(GREEN)Cleaning done.$(COLOR_END)"


fclean: clean
	@echo "$(YELLOW)Cleaning everything...$(COLOR_END)"
	@$(RM) $(NAME) home_shrubbery
	@echo "$(GREEN)Cleaning done.$(COLOR_END)"

re:
	@echo "$(YELLOW)Recompiling...$(COLOR_END)"
	@make fclean
	@rm -rf ${OBJ_DIR}
	@make all
	@echo "$(GREEN)The project has been recompiled.$(COLOR_END)"

# Test options



.PHONY: all clean fclean re

COLOR_END = \033[0;39m
CYAN3 = \033[1;4;96m
YELLOW = \033[1;33m
PURPLE = \033[1;35m
BWhite = \033[1;37m
RED = \033[1;91m
GREEN = \033[1;92m
CYAN2 = \x1B[1;36m
CYAN = \033[1;96m