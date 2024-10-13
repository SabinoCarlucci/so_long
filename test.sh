#!/bin/bash

# Dai i permessi necessari con chmod +x test.sh prima di fare ./test.sh
# test.sh, so_long e /maps devono essere sullo stesso livello

MAPS_DIR="./maps"

maps=("aaaaaa.ber" "ber.bertoldo" "char.ber" "door.ber" "file.txt" "rect.ber" "walls.ber" "ber" "cep.ber" "door2.ber" "empty.ber" "line_empty.ber" "unreach.ber")

success_count=0  # Contatore delle mappe con output di successo
total_maps=${#maps[@]}  # Numero totale di mappe

run_with_timeout() {
    map_name=$1
    timeout 0.1 ./so_long "$MAPS_DIR/$map_name" > output.log 2>&1
    if [[ $? -eq 124 ]]; then
        echo -e "❌ \e[31mERRORE: Il programma e' stato eseguito con $map_name\e[0m"
    else
        echo -e "✅ \e[32m$(cat output.log)\e[0m"
        ((success_count++))  # Incrementa il contatore per ogni successo
    fi
}

# Loop su tutte le mappe
for map in "${maps[@]}"; do
    echo "./so_long $map"
    run_with_timeout "$map"
    echo ""
done

# Verifica finale sul numero di successi
if [[ $success_count -eq $total_maps ]]; then
    echo "Bravo, tutte le mappe invalide restituiscono errore."
else
    echo "Male, non hai gestito correttamente tutti i casi."
fi

