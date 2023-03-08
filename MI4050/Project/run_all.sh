echo "Let's get fuck up!!!"

declare -a datasize=("128")
declare -a metrics=("MAPE" "MSE" "MAE")
declare -a cms=("PDTW0.01" "PDTW0.1" "PDTW0.5")
declare -a ks=(24 48)


# cd /home/thanh10973/TALENTED-K64MI/MI4050/Project/LIFE_live/CME/
# python CME_PDTW.py --T 128


for DATA_SIZE in ${datasize[@]}; do
    cd /home/thanh10973/TALENTED-K64MI/MI4050/Project/LIFE_live/LIFE/
    
    k=24
    echo "Running models with k = "$k
    for metric in ${metrics[@]}; do
        for C in ${cms[@]}; do
            python main.py --metric $metric --C $C --T $DATA_SIZE --batch_size 192 --k $k
        done
    done

    k=48
    echo "Running models with k = "$k
    for metric in ${metrics[@]}; do
        for C in ${cms[@]}; do
            python main.py --metric $metric --C $C --T $DATA_SIZE --batch_size 128 --k $k
        done
    done
    
done












