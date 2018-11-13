#! /bin/bash
etapa_criar_rede(){

	zenity --info --text="Escolha um local e um nome para salvar a nova rede!"

	nome=$(zenity --file-selection --save --title="Nova Rede")

	case $? in
		0)
			echo -e "\nARQUIVO \"$nome\" selecionado.\n";;
		1)
			echo -e "\nnenhum arquivo selecionado.\n"
			zenity --info --text="Nenhum arquivo selecionado! Não existe nada pra fazer!"
			exit
			;;
		-1)
			echo -e "\nAn unexpected error has occurred.\n"
			exit
			;;

	esac
	echo -e "\nnome do novo arquivo: $nome \n"

	arqpar="$(dirname "$nome")/par.txt"
	zenity --info --text="Escolha os parametros da rede! (salvo em $arqpar)"

	#arquivo parametros 
	touch "$arqpar"
	> "$arqpar"

	ncamadas=$(zenity --entry \
			--title="Numero de camadas" \
			--text="Entre com o numero de camadas(inteiro):" \
			--entry-text "3")

	case $? in
		0)
			echo -e "\nREDE COM  \"$ncamadas\" camadas.\n";;
		1)
			echo -e "\ncancelado\n"
			zenity --info --text="N de camadas zero! Não existe nada pra fazer!"
			exit ;;
		-1)
			echo -e "\nAn unexpected error has occurred.\n"
			exit
			;;

	esac

	# salva parametro
	echo "$ncamadas" >> "$arqpar"


	for (( i=0; i<$ncamadas; i++ )) do 

		camada=$(zenity --entry \
				--title="Numero de Neuronios na Camada..." \
				--text="Entre com o numero de neoronios na camada(inteiro)" \
				--entry-text "100")

		case $? in
			0)
				echo -e "\ncamada $i com  \"$camada\" neuronios.\n";;
			1)
				echo -e "\ncancelado\n"
				zenity --info --text="N de neuronios zero! Não existe nada pra fazer!"
				exit ;;
			-1)
				echo -e "\nAn unexpected error has occurred.\n"
				exit
				;;

		esac

		if [ "$camada" -eq "0"	]; then			

			echo -e "\ncancelado\n"
			zenity --info --text="N de neuronios zero! Não existe nada pra fazer!"
			exit 
		fi


		# salva parametro
		echo "$camada" >> "$arqpar"


	done
	atalhos=$(zenity --list \
			--title="Atalhos:" \
			--column="Rede Com Atalhos?" \
			"Sim" "Não")



	echo -e "\nrede com atalhos $atalhos\n"

	case "$atalhos" in 
		"Sim")
			# salva parametro
			echo "1" >> "$arqpar"
			echo -e "rede com atalhos ok\n"
			;;
		"Não")
			# salva parametro
			echo "0" >> "$arqpar"
			echo -e "rede sem atalhos ok\n"
			;;

		*)
			echo -e "saindo\n"
			exit
			;;
	esac

	for (( i=0; i<$ncamadas; i++ )) do 
		func_a=$(zenity --list\
				--width 530 \
				--height 530 \
				--radiolist \
				--text="funcao de ativação da camada $i" \
				--title="Função de ativação:" \
				--column="escolhido" \
				--column="numero" \
				--column="funcão de ativação" \
				"FALSE" 0 "FANN_LINEAR" "FALSE" 1 "FANN_THRESHOLD"	"FALSE" 2 "FANN_THRESHOLD_SYMMETRIC" 	"TRUE" 3  "FANN_SIGMOID" "FALSE" 4 "FANN_SIGMOID_STEPWISE" "FALSE" 5  "FANN_SIGMOID_SYMMETRIC" "FALSE" 6 "FANN_SIGMOID_SYMMETRIC_STEPWISE" "FALSE" 7 "FANN_GAUSSIAN" "FALSE" 8  "FANN_GAUSSIAN_SYMMETRIC" "FALSE" 9 "FANN_GAUSSIAN_STEPWISE" "FALSE" 10 "FANN_ELLIOT" "FALSE" 11 "FANN_ELLIOT_SYMMETRIC" "FALSE" 12 "FANN_LINEAR_PIECE"	"FALSE" 13 "FANN_LINEAR_PIECE_SYMMETRIC" "FALSE" 14 "FANN_SIN_SYMMETRIC" "FALSE" 15 "FANN_COS_SYMMETRIC" "FALSE" 16 "FANN_SIN" "FALSE" 17 "FANN_COS" )

		echo -e "ativacao camada $i $func_a \n"
		echo "$func_a" >> "$arqpar"

	done





	../../bin/create -e "$arqpar"  -s "$nome" 

	zenity --info --text="rede criada (salvo em $nome)"

}


etapa_preparar_dados_de_treino(){



	zenity --info --text="Escolha selecione o arquivo bin de entrada."
	nome_entrada=$(zenity --file-selection --title="Arquivo de Entrada")
	echo -e "nome entrada $nome_entrada \n"

	zenity --info --text="Escolha um local e um nome para salvar o arquivo de saida."
	nome_saida=$(zenity --file-selection --save --title="Arquivo de Saida")
	echo -e "nome entrada $nome_saida \n"

	zenity --info --text="Escolha o arquivo com a lista de Picks."
	nome_lista=$(zenity --file-selection --title="Selecione a lista de picks")
	echo -e "nome entrada $nome_lista \n"
	
	
	numero_entrada=$(zenity --entry \
			--title="Numero de entradas" \
			--text="Entre com o número de neuronios na camada de entrada (inteiro):" \
			--entry-text "100")
	case $? in
		0)
			echo -e "\n numero entrada  \"$numero_entrada\"\n";;
		1)
			echo -e "\ncancelado\n"
			zenity --info --text="Não existe nada pra fazer!"
			exit ;;
		-1)
			echo -e "\nAn unexpected error has occurred.\n"
			exit
			;;

	esac
	echo -e "numero $numero_entrada \n"


	numero_saida=$(zenity --entry \
			--title="Numero de saidas" \
			--text="Entre com o número de neuronios na camada de saida (inteiro):" \
			--entry-text "1")
	case $? in
		0)
			echo -e "\n numero de saida  \"$numero_saida\"\n";;
		1)
			echo -e "\ncancelado\n"
			zenity --info --text="Não existe nada pra fazer!"
			exit ;;
		-1)
			echo -e "\nAn unexpected error has occurred.\n"
			exit
			;;

	esac
	echo -e "numero $numero_saida \n"
	
	posicao_janela=$(zenity --entry \
			--title="Posição do picks na janela" \
			--text="Posição do picks na janela" \
			--entry-text "50")
	case $? in
		0)
			echo -e "\n posicao na janela  \"$posicao_janela\"\n";;
		1)
			echo -e "\ncancelado\n"
			zenity --info --text="Não existe nada pra fazer!"
			exit ;;
		-1)
			echo -e "\nAn unexpected error has occurred.\n"
			exit
			;;

	esac

	echo -e "numero $posicao_janela \n"

	numero_tracos=$(zenity --entry \
			--title="Numero de Tracos" \
			--text="Entre com os numeros de tracos " \
			--entry-text "96")
	case $? in
		0)
			echo -e "\n numero de tracos  \"$numero_tracos\"\n";;
		1)
			echo -e "\ncancelado\n"
			zenity --info --text="Não existe nada pra fazer!"
			exit ;;
		-1)
			echo -e "\nAn unexpected error has occurred.\n"
			exit
			;;

	esac

	echo -e "numero $numero_tracos \n"
	numero_amostras=$(zenity --entry \
			--title="Numero de amostras" \
			--text="Entre com os numeros de amostras por traço" \
			--entry-text "2801")
	case $? in
		0)
			echo -e "\n numero de amostras  \"$numero_amostras\"\n";;
		1)
			echo -e "\ncancelado\n"
			zenity --info --text="Não existe nada pra fazer!"
			exit ;;
		-1)
			echo -e "\nAn unexpected error has occurred.\n"
			exit
			;;

	esac

	echo -e "numero $numero_amostras \n"
	taxa_amostragem=$(zenity --entry \
			--title="Taxa de amostragem" \
			--text="Entre com a taxa de amostragem" \
			--entry-text "0.0005")
	case $? in
		0)
			echo -e "\n taxa de amostragem \"$taxa_amostragem\"\n";;
		1)
			echo -e "\ncancelado\n"
			zenity --info --text="Não existe nada pra fazer!"
			exit ;;
		-1)
			echo -e "\nAn unexpected error has occurred.\n"
			exit
			;;

	esac

	echo -e "numero $taxa_amostragem \n"
}





ESCOLHA=$(zenity --list \
		--title="Tome uma ação:" \
		--text="Selecione o procedimento desejado"\
		--column="Ação" \
		"Criar Rede" "Preparar Dados de Treino" "Treinar Rede" "Executar")



echo -e "\n\n\niniciando etapa para \"$ESCOLHA\"\n"

case "$ESCOLHA" in 
	"Criar Rede")
		echo "etapa criacao\n"
		etapa_criar_rede
		;;
	"Preparar Dados de Treino")
		echo "Preparar dados de treino\n"
		etapa_preparar_dados_de_treino
		;;
	"Treinar Rede")
		echo "etapa treino\n"
		;;
	"Executar")
		echo "executar\n"
		;;
	*)
		echo "resto\n"
		;;
esac
