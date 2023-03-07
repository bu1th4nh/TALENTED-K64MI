echo "Let's get fuck up!!!"

declare -a datasize=("128" "96" "144")
declare -a metrics=("MSE" "MAE" "MAPE")
declare -a cms=("PDTW0.01" "PDTW0.1" "PDTW0.5")
declare -a ks=(24 48 12)

for DATA_SIZE in ${datasize[@]}; do

    echo "Cleaning prev data"
    rm -rf /home/thanh10973/TALENTED-K64MI/MI4050/Project/LIFE_live/data/json/split-train/*
    rm -rf /home/thanh10973/TALENTED-K64MI/MI4050/Project/LIFE_live/data/json/split-test/*


    echo "Splitting data into train and test set with dataset size "$DATA_SIZE
    cd /home/thanh10973/TALENTED-K64MI/MI4050/Project/LIFE_live/
    python dataproc_train.py --T $DATA_SIZE
    python dataproc_test.py --T $DATA_SIZE

    echo "Running correlation matrix extraction" 
    cd /home/thanh10973/TALENTED-K64MI/MI4050/Project/LIFE_live/CME/
    python CME-PDTW --T $DATA_SIZE

    cd /home/thanh10973/TALENTED-K64MI/MI4050/Project/LIFE_live/LIFE/



    for k in ${ks[@]}; do
        echo "Running models with k = "$k
        for metric in ${metrics[@]}; do
            for C in ${cms[@]}; do
                python main.py --metric $metric --C $C --T $DATA_SIZE --batch_size $DATA_SIZE --k $k
            done
        done
    done
done












