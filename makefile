COISAS= -O0 -Isrc/fann -g -Lsrc/fann -lfloatfann -lm 
all:	create train exec gen_train 

create: src/create_neural_net.c src/set_log.h src/api/API_net.h
	gcc  src/create_neural_net.c $(COISAS) -o bin/create
	@echo CREATE compilado

train: src/train_neural_net.c src/set_log.h src/api/API_net.h
	gcc src/train_neural_net.c $(COISAS) -o bin/train 
	@echo TRAIN compilado

exec: src/exec_neural_net.c src/set_log.h src/api/API_net.h
	gcc src/exec_neural_net.c $(COISAS) -o bin/exec 
	@echo EXEC compilado

gen_train: src/make_train.c src/set_log.h src/api/API_net.h
	gcc src/make_train.c $(COISAS) -o bin/gen_train 
	@echo GEN_TRAIN compilado
clean: 
	@echo 'removendo arquivos'
		rm bin/create 
		rm bin/train
		rm bin/exec
		rm bin/gen_train

