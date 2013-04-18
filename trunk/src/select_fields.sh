#!/bin/bash

#ower_id,user_id,item_type,item_id,count,nick_name
#awk -F'\1' '{print $1"\t"$2"\t"$3"\t"$4"\t"$7"\t"$8}'
awk -F'\t' '{print $1}'
