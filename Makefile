#=====================================================================
# Macros
#=====================================================================
LIBS = -L./build -lbm_allegro -lcore -llogic -lresources
INCLUDES = -I./src/allegro -I./src/core -I./src/resources -I./src/logic
ALLEGRO = -lallegro_image -lallegro_ttf -lallegro_font -lallegro_primitives -lallegro

#=====================================================================
# Iniciar compilacao
#=====================================================================
all: init allegro logic resources core clean copy_statics exec clean_libs

init:
	rm -rf ./build
	mkdir -p build

#=====================================================================
# Compilar executavel
#=====================================================================
exec: 
	gcc -g -o ./build/sincronia ./src/main.c $(INCLUDES) $(LIBS) $(ALLEGRO)

#=====================================================================
# Compilar lib allegro
#=====================================================================
allegro: lib_allegro

lib_allegro: compile_allegro
	ar rvs ./build/libbm_allegro.a *.o
	
compile_allegro: 
	gcc -Wall -g -c ./src/allegro/*.c $(INCLUDES) 

#=====================================================================
# Compilar lib logic
#=====================================================================
logic: lib_logic

lib_logic: compile_logic
	ar rvs ./build/liblogic.a *.o
	
compile_logic: 
	gcc -Wall -g -c ./src/logic/*.c $(INCLUDES)

#=====================================================================
# Compilar lib resources
#=====================================================================
resources: lib_resources

lib_resources: compile_resources
	ar rvs ./build/libresources.a *.o
	
compile_resources: 
	gcc -Wall -g -c ./src/resources/*.c $(INCLUDES)

#=====================================================================
# Compilar lib core
#=====================================================================
core: lib_core lib_core

lib_core: compile_core
	ar rvs ./build/libcore.a *.o
	
compile_core: 
	gcc -Wall -g -c ./src/core/*.c $(INCLUDES)

#=====================================================================
# Utils
#=====================================================================
clean:
	rm -f *.o

clean_libs:
	rm -f ./build/*.a

copy_statics:
	cp -a ./public ./build/Recursos