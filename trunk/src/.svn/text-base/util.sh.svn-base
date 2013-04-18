#!/usr/local/bin/bash

CUR_DIR="`dirname $0`"

CONF_FILE=${CUR_DIR}/term_level_ctr_conf
# parse the conf file
tag=""
special_index=26
while read line
do
    c=${line:0:1}
    if [ $c == "#" ]; then # ignore the comments
        continue
    fi
    arr=()
    for i in $(echo $line | tr "," "\n")
    do
        arr+=("$i")
    done
    tmp=${arr[0]}
    tag=${tmp//:/,}

    length=${#arr[*]} 
    if [ $length -gt 2 ];then
        for j in $(echo ${arr[2]} | tr ":" "\n") 
        do
            if [ $j == ${special_index} ]; then
                tag=${tag},q
            fi
        done
    fi
    echo $tag
done < ${CONF_FILE}

