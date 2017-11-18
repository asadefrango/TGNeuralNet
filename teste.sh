#! /bin/bash
RED='\033[0;31m'
YELOW='\033[1;33m'
NC='\033[0m'
GREEN='\033[0;32m'
echo -e " ${GREEN} EXECUTANDO ${RED} CREATE  ${NC} "
./bin/create -e ./bin/net_par  -s ./bin/rede.net 
echo -e " ${GREEN} FIM DE  ${YELLOW} CREATE  ${NC} "

echo -e " ${GREEN} EXECUTANDO ${RED} GEN_TRAIN ${NC}  "
./bin/gen_train -s ./bin/treino.tra -e ./bin/1.bin -l ./bin/picks -i 100 -o 1 -p 50 -t 96 -d 2801 -x 0.0005
echo -e " ${GREEN} FIM DE  ${YELLOW} GEN_TRAIN ${NC} "

echo -e " ${GREEN} EXECUTANDO ${RED} TRAIN ${NC}  "
#./bin/train -s ./bin/rede_treinada.net -e 0.01 -r 1000 -m 10000 -t ./bin/treino.tra -n ./bin/rede.net
./bin/train -s ./bin/rede_treinada.net -e 0.01 -r 1000 -m 10000 -t ./bin/arquivo_treino.dat -n ./bin/rede.net
echo -e " ${GREEN} FIM DE  ${YELLOW} TRAIN ${NC}  "

echo -e " ${GREEN} EXECUTANDO ${RED} EXEC_NEURAL ${NC}  "
./bin/exec -s ./bin/linha_pick.asc -e ./bin/1.bin -r ./bin/rede_treinada.net 
echo -e " ${GREEN} FIM DE  ${YELLOW} EXEC_NEURAL ${NC}  "
