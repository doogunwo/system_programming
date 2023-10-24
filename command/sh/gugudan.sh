#!/bin/bash

read -p "gugudan:" dan
for i in {1..9}; 
do
    result=$((dan*i))
    echo "$dan x $i = $result"
done