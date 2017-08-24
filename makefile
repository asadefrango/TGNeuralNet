
all:	create 

create: src/create_neural_net.c src/set_log.h
	gcc -O2 -lm src/create_neural_net.c -o bin/create
	@echo CREATE compilando

clean: 
	@echo 'removendo arquivos'
		rm bin/create 

