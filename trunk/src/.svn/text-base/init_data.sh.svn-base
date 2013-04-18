bizdate=`date +%Y%m%d --date="1 day ago"` && [[ ! -z "$1" ]] && export bizdate=$1
hadoop dfs -rm /group/tbsc-dev/yichen/recommender_algo/sim_rank_sim/${bizdate}/*
hadoop dfs -put sim_rank_sim /group/tbsc-dev/yichen/recommender_algo/sim_rank_sim/${bizdate}/

