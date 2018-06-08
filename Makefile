#=====================================================================
# Macros
#=====================================================================
INCLUDES_ENGINE = -I./src/engine/allegro -I./src/engine/core -I./src/engine/utils -I./src/engine/socket
INCLUDES_GAME = -I./src/game/events -I./src/game/logic -I./src/game/renders -I./src/game/resources -I./src/game/communication
INCLUDES = $(INCLUDES_GAME) $(INCLUDES_ENGINE)
ALLEGRO = -lallegro_image -lallegro_ttf -lallegro_font -lallegro_primitives -lallegro
LIBS = -L./build -lbm_engine -lbm_game

#=====================================================================
# Iniciar compilacao
#=====================================================================
all: init engine game clean copy_statics exec clean_libs

init: 
	mkdir -p build

#=====================================================================
# Compilar executavel
#=====================================================================
exec: 
	gcc -g -o ./build/sincronia ./src/main.c $(INCLUDES) $(LIBS) $(ALLEGRO)

#=====================================================================
# Compile libs engine
#=====================================================================
engine: lib_engine

lib_engine: compile_engine
	ar rvs ./build/libbm_engine.a *.o

compile_engine:
	gcc -Wall -g -c ./src/engine/**/*.c $(INCLUDES)

#=====================================================================
# Compile libs game
#=====================================================================
game: lib_game

lib_game: compile_game
	ar rvs ./build/libbm_game.a *.o

compile_game:
	gcc -Wall -g -c ./src/game/**/*.c $(INCLUDES)

#=====================================================================
# Utils
#=====================================================================
clean:
	rm -f ./*.o

clean_libs:
	rm -f ./build/*.a

copy_statics:
	cp -a ./public ./build/Recursos