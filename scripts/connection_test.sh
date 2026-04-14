#!/bin/bash
for i in $(seq 1 10000);
do
    echo "1+$i" | nc localhost 8080 &
    echo "finished $i"
done

wait
