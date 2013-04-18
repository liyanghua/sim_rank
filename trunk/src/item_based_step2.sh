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

OUTPUT_NAME=item_based_step2
OUTPUT=${HPATH}/${OUTPUT_NAME}/$bizdate/
INPUT=${HPATH}/item_based_step1/$bizdate/


${HADOOP_CMD} dfs -rmr $OUTPUT
${HADOOP_CMD} jar $(dirname $(which hadoop))/../contrib/streaming/hadoop-0.19.1-streaming.jar \
           -input $INPUT -output $OUTPUT $lib_extra_str \
           -jobconf mapred.reduce.tasks=1 \
           -jobconf mapred.job.name="item based - step 2" \
           -cacheArchive "${OLDPATH}/AliWS-1.0.0.5.jar#AliWS-1.0.0.5" \
           -mapper 'cat'
           -reducer './item_based_step2_reducer' -file ${CUR_DIR}/item_based_step2_reducer


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
