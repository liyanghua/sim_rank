#!/bin/bash

CUR_DIR="`dirname $0`"
source ${CUR_DIR}/../conf/general.conf
source ${HOME}/.bash_profile

bizdate=`date +%Y%m%d --date="1 day ago"` && [[ ! -z "$1" ]] && export bizdate=$1
iter_num=1 && [[ ! -z "$2" ]] && export iter_num=$2

# generate the data

sh ${CUR_DIR}/query_doc_click.sh $bizdate
[ $?  -ne 0 ] && echo "Failed to run query_doc_click.sh" && exit 1

sh ${CUR_DIR}/query_select.sh $bizdate
[ $?  -ne 0 ] && echo "Failed to run query_select.sh" && exit 1

sh ${CUR_DIR}/general.sh $bizdate
[ $?  -ne 0 ] && echo "Failed to generate Adjacency matrix: general.sh" && exit 1

sh ${CUR_DIR}/count.sh $bizdate
[ $?  -ne 0 ] && echo "Failed to run count.sh" && exit 1


sh ${CUR_DIR}/sim_rank_step1.sh $bizdate
[ $?  -ne 0 ] && echo "Failed to run sim_rank_step1.sh" && exit 1

sh ${CUR_DIR}/sim_rank_step2.sh $bizdate
[ $?  -ne 0 ] && echo "Failed to run sim_rank_step2.sh" && exit 1


sh ${CUR_DIR}/sim_rank_step3.sh $bizdate
[ $?  -ne 0 ] && echo "Failed to run sim_rank_step3.sh" && exit 1

OUTPUT_NAME=sim_rank_sim
OUTPUT=${HPATH}/${OUTPUT_NAME}/$bizdate/
for (( i=0; i<$iter_num; i++)); do
    sh ${CUR_DIR}/sim_rank_step4.sh $bizdate
    [ $?  -ne 0 ] && echo "Failed to run sim_rank_step4.sh" && exit 1

    sh ${CUR_DIR}/sim_rank_step5.sh $bizdate
    [ $?  -ne 0 ] && echo "Failed to run sim_rank_step5.sh" && exit 1

    # for debug
    [ -f $CUR_DIR/sim_rank_sim_step_$i ] && rm -rf $CUR_DIR/sim_rank_sim_step_$i
    ${HADOOP_CMD} dfs -getmerge $OUTPUT $CUR_DIR/sim_rank_sim_step_$i
done

exit 0
