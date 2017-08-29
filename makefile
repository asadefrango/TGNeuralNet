COISAS= -O2 -Isrc/fann -Lsrc/fann -lfloatfann -lm 
all:	create train 

create: src/create_neural_net.c src/set_log.h src/api/API_net.h
	gcc  src/create_neural_net.c $(COISAS) -o bin/create
	@echo CREATE compilado

train: src/train_neural_net.c src/set_log.h src/api/API_net.h
	gcc src/train_neural_net.c $(COISAS) -o bin/train 
	@echo TRAIN compilado

clean: 
	@echo 'removendo arquivos'
		rm bin/create 

