1. 输入数据：
1.1:query,doc,点击数目
1.2: 初始query相似度,可以设置为0

2. 分成7个hadoop job 完成，其中第6到第7个job可以循环迭代（一般迭代4轮）
2.1 general.sh. 输入：query,doc原始点击数据。输出：每个query或者doc的邻接表
2.2 count.sh. 输入：query,doc原始点击数据。 输出： 每个query或者doc自己和自己的相似度（此处恒为1）
2.3 sim_rank_step1.sh. 输入包括两个部分：每个query或者doc的邻接表，初始query相似度。输出：（q1,q2,q1的邻接表）
2.4 sim_rank_step2.sh. 输入包括两个部分：每个query或者doc的邻接表，初始query相似度。输出：（q1,q2,q2的邻接表）
2.5 sim_rank_step3.sh. join sim_rank_step1.sh的输出和sim_rank_step2.sh的输出。得到：q1,q2,q1的邻接表,q2的邻接表

# 迭代开始
2.6 sim_rank_step4.sh. join sim_rank_step3.sh的输出和初始query相似度，得到每对query pair或者doc pair的邻居的相似度的贡献
2.7 sim_rank_step5.sh. join sim_rank_step3.sh的输出和sim_rank_step4.sh的输出。根据公式：

sim(obj1,obj2) = C/N(obj1) * N(obj2) sum{sum{sim(i,j)}} for i in E(obj1) and j in E(obj2)

其中，N(obj1)表示和obj1关联的obj2的数目，N(obj2)意思类似
      E(obj1)表示和obj1关联的obj2的集合，E(obj2)意思类似

这个job会更新相似度矩阵，然后进行下一轮的迭代计算
