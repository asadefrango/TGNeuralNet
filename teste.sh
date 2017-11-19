#! /bin/bash
RED='\033[0;31m'
YELOW='\033[1;33m'
NC='\033[0m'
GREEN='\033[0;32m'
echo -e " ${GREEN} EXECUTANDO ${RED} CREATE  ${NC} "
./bin/create -e ./data/parametros_da_rede/par.txt  -s ./data/rede_neural/rede_neural.net 
echo -e " ${GREEN} FIM DE  ${YELLOW} CREATE  ${NC} "

echo -e " ${GREEN} EXECUTANDO ${RED} GEN_TRAIN ${NC}  "
./bin/gen_train -s ./data/arquivo_de_treino/dados_para_treino.dat -e ./data/binarios/1.bin -l ./data/lista_de_picks/picks.dat -i 100 -o 1 -p 50 -t 96 -d 2801 -x 0.0005
echo -e " ${GREEN} FIM DE  ${YELLOW} GEN_TRAIN ${NC} "

echo -e " ${GREEN} EXECUTANDO ${RED} TRAIN ${NC}  "
#./bin/train -s ./data/rede_neural_treinada/rede_treinada.net -e 0.0000000001 -r 1000 -m 10000 -t ./data/arquivo_de_treino/dados_para_treino.dat -n ./data/rede_neural/rede_neural.net 
./bin/train -s ./data/rede_neural_treinada/rede_treinada.net -e 0.000000001 -r 1000 -m 10000 -t ./data/arquivo_de_treino/exemplo.dat -n ./data/rede_neural/rede_neural.net 
echo -e " ${GREEN} FIM DE  ${YELLOW} TRAIN ${NC}  "

echo -e " ${GREEN} EXECUTANDO ${RED} EXEC_NEURAL ${NC}  "
./bin/exec -s ./data/arquivo_processado/final.asc -e ./data/binarios/1.bin -r ./data/rede_neural_treinada/rede_treinada.net
echo -e " ${GREEN} FIM DE  ${YELLOW} EXEC_NEURAL ${NC}  "
