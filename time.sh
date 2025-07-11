#!/bin/bash

arquivo_saida="output/crime_and_punishment.txt"
soma=0
count=10

echo "Executando 10 vezes..."

for i in $(seq 1 $count); do
    echo "Execução $i..."
    ./freq dictionary_redblack crime_and_punishment.txt

    # Aguarda o arquivo ser atualizado (só por precaução)
    sleep 0.5

    # Extrai o número da linha com "Tempo total (ms):"
    tempo=$(grep "Tempo total (ms):" "$arquivo_saida" | grep -oP '\d+')

    echo "Tempo: $tempo ms"

    soma=$((soma + tempo))
done

media=$(echo "scale=2; $soma / $count" | bc)

echo "---------------------------"
echo "Média dos tempos: $media ms"