#=====================================================================
# Definições
#=====================================================================
IP_SERVER="127.0.0.1"

#=====================================================================
# Definir cor
#=====================================================================
define colorecho
      @tput setaf $1
      @echo $2
      @tput sgr0
endef

#=====================================================================
# Macros
#=====================================================================
INCLUDES_ENGINE = -I./src/engine/allegro -I./src/engine/core -I./src/engine/utils -I./src/engine/socket
INCLUDES_GAME = -I./src/game/events -I./src/game/logic -I./src/game/renders -I./src/game/resources -I./src/game/communication
INCLUDES = $(INCLUDES_GAME) $(INCLUDES_ENGINE)
ALLEGRO = -lallegro_image -lallegro_ttf -lallegro_font -lallegro_primitives -lallegro
LIBS = -L./build -lbm_engine -lbm_game
CFLAGS = -DIP_SERVER='$(IP_SERVER)'

#=====================================================================
# Iniciar compilacao
#=====================================================================
all: init engine game clean copy_statics exec clean_libs
	$(info ) $(call colorecho,3,"Compilação finalizada com sucesso..." ) 

init: 
	$(call colorecho,3,"Trabalho Gerencia de Redes - Brendon Oliveira" ) $(info )
	@mkdir -p build

#=====================================================================
# Compilar executavel
#=====================================================================
exec: 
	$(call colorecho,6,"Compilando..." ) $(info )
	gcc -Wall -o ./build/sincronia ./src/main.c $(INCLUDES) $(LIBS) $(ALLEGRO)

#=====================================================================
# Compile libs engine
#=====================================================================
engine: lib_engine

lib_engine: compile_engine
	$(call colorecho,6,"ENGINE -> [2] - Criando biblioteca" )	$(info )
	ar rvs ./build/libbm_engine.a *.o

compile_engine:
	$(call colorecho,6,"ENGINE -> [1] - Compilando fontes da engine" ) $(info )
	gcc $(CFLAGS) -Wall -c ./src/engine/**/*.c $(INCLUDES)

#=====================================================================
# Compile libs game
#=====================================================================
game: lib_game

lib_game: compile_game
	$(call colorecho,6,"GAME -> [2] - Criando biblioteca" ) $(info )
	ar rvs ./build/libbm_game.a *.o

compile_game:
	$(call colorecho,6,"GAME -> [1] - Compilando fontes do game" ) $(info )
	gcc -Wall -Wno-format-extra-args -c ./src/game/**/*.c $(INCLUDES)

#=====================================================================
# Utils
#=====================================================================
clean:
	@rm -f ./*.o

clean_libs:
	@rm -f ./build/*.a

copy_statics:
	$(call colorecho,6,"Copiando arquivos estaticos" ) $(info )

	cp -a ./public ./build/Recursos