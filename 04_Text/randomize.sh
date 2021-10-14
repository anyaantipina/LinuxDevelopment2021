#!/bin/bash
tput clear
readarray -t file

positions=readarray
row_numbers=''

all_symbols=0
in_file_positioins=''
rows_amount=${#file}
for((i=0;$i<${#file};i++)); do 
    row_numbers=`echo ${row_numbers} $i`; 
    column_numbers=''

    for((j=0;$j<${#file[$i]};j++)); do
        column_numbers=`echo ${column_numbers} $j`;
        let all_symbols=$all_symbols+1
        in_file_positioins=`echo ${in_file_positioins} $all_symbols`; 
    done
    positions[$i]=`shuf -e $column_numbers`
done

row_shufed=`shuf -e $row_numbers`
in_file_positioins_shufed=`shuf -e $in_file_positioins`

for((i=0;$i<${all_symbols};i++)); do
    let cut_pos=$i+1
    in_file_position=`echo $in_file_positioins_shufed | cut -f $cut_pos -d" "`

    tmp=$in_file_position
    row_number=0
    while [ $tmp -gt 0 ]; do
        let tmp=$tmp-${#file[$row_number]}
        let row_number=$row_number+1
    done
    if [[ $tmp -ne 0 ]]; then 
        let row_number=$row_number-1
        let column_number=$tmp+${#file[$row_number]}
    else 
        column_number=0
    fi
    if [ -n "$1" ]
    then
        sleep $1
    fi
    tput cup $row_number $column_number
    echo -n ${file[$row_number]:column_number:1}
done
