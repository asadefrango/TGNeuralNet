# Ferramentas para Rastreamento Automático de Primeiras Quebras em Dados Sísmicos
=================================================================================

Esse repositório contém uma coletânea de ferramentas e tem como objetivo detectar primeiras quebras de ondas em dados sismicos por meio de técnicas computacionais baseadas em **redes neurais**.

## Modo de usar
---------------
Para rastrear as primeiras quebras de onda de um dado sísimico em um arquivo binário do tipo: 

**float**
**float**
**float**
**.**
**.**
**.**
**float**
**float** 
**float**

é necessário o seguinte procedimento: 

1. Criar uma rede neural
1. Uma lista de picks para trino da rede neural
1. Gerar um arquivo de treino baseado na lista de picks e o arquivo de origem dos picks
1. Treinar a rede neural
1. Executar o processamento via rede neural em um arquivo binário



