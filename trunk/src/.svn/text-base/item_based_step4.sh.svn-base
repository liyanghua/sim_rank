#!/usr/local/bin/bash

set -x

bizdate=`date +%Y%m%d --date="1 day ago"`
[[ ! -z "$1" ]] && export bizdate=$1

CUR_DIR=$(dirname $0)
source ${HOME}/.bash_profile
source ${CUR_DIR}/../conf/general.conf

lib_files=`ls ${CUR_DIR}/../lib/`
lib_extra_str=""
for file in $lib_files;
do
    lib_extra_str=$lib_extra_str" -file ${CUR_DIR}/../lib/${file}"
done

OUTPUT_NAME=item_based_step4
OUTPUT=${HPATH}/${OUTPUT_NAME}/$bizdate/
INPUT1=${HPATH}/item_based_step2/$bizdate/
INPUT2=${HPATH}/item_based_step3/$bizdate/

#input format: user_id \t item_id \t rating
${HADOOP_CMD} dfs -rmr $OUTPUT
${HADOOP_CMD} jar $(dirname $(which hadoop))/../contrib/streaming/hadoop-0.19.1-streaming.jar \
           -input $INPUT1 -input $INPUT2 -output $OUTPUT $lib_extra_str \
           -jobconf mapred.reduce.tasks=1 \
           -jobconf mapred.job.name="item based - step 4" \
           -mapper "item_based_step4_mapper" -file ${CUR_DIR}/item_based_step3_mapper \
           -reducer "item_based_step4_reducer" -file ${CUR_DIR}/item_based_step3_reducer \
           -jobconf file_flag="item_based_step3"

if [ $? -ne 0 ]
then
	exit 1
fi


#clean history data
YESTER_FOUR_DAY=`date --date="$bizdate 4 days ago" +%Y%m%d`
${HADOOP_CMD} dfs -test -e ${HPATH}/${OUTPUT_NAME}/$YESTER_FOUR_DAY/
if [ $? -eq 0 ]
then
    ${HADOOP_CMD} dfs -rmr ${HPATH}/${OUTPUT_NAME}/$YESTER_FOUR_DAY/
fi

exit 0
