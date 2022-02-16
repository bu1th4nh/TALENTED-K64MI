#/*==========================================================================================*\
# **                        _           _ _   _     _  _         _                            **
# **                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
# **                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
# **                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
# **                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
# \*==========================================================================================*/

###################################  INFORMATION ####################################
# 
# FILENAME    : main.asm
# TITLE       : Tìm đường đi ngắn nhất trên đồ thị bằng thuật toán Dijkstra
# AUTHOR      : bu1th4nh (Bùi Tiến Thành)								     
# DATE        : 2022-01-27
# DESCRIPTION : File chương trình chính
# COPYRIGHT   : Copyright (C) 2022 by bu1th4nh https://github.com/bu1th4nh. All rights reserved.
# INPUT       : * n - số đỉnh đồ thị,
#               * m - số cạnh đồ thị,
#               * start - đỉnh bắt đầu,
#               * desti - đỉnh kết thúc,
#               * m bộ 3 dòng liên tiếp nhau thể hiện 1 cạnh của đồ thị, có dạng sau:
#                   u --- đỉnh 1 của cạnh,
#                   v --- đỉnh 2 của cạnh,
#                   c --- trọng số của cạnh.
# OUTPUT      : Khoảng cách ngắn nhất giữa 2 đỉnh và hướng đi giữa 2 đỉnh đó.
# EXEC CMD    : java -jar .\Mars45.jar 1000000000 "main.asm"
# 
###################################### MACROES #####################################
.include "macro.asm"


################################### DATA SEGMENT ###################################
.data	# Data here
    n: .word 0 # Number of vertices         
    m: .word 0 # Number of edges 

    start: .word 0 # Start vertex
    desti: .word 0 # Destination vertex

    ptr_adj_dist: .word 0 # 2D Array for vertex component in adjacency list
    ptr_adj_vrtx: .word 0 # 2D Array for cost component in adjacency list
    ptr_adj_size: .word 0 # 1D Array for vertex degree in adjacency list

    ptr_edge_list_u: .word 0 # 1D Array for 1st vertex component in edge list
    ptr_edge_list_v: .word 0 # 1D Array for 2nd vertex component in edge list
    ptr_edge_list_c: .word 0 # 1D Array for cost component in edge list

    ptr_prio_queue_dist: .word 0 # 1-D Array for distance priority queue
    ptr_prio_queue_vrtx: .word 0 # 1-D Array for corresponding vertex priority queue
    prio_queue_size: .word 0     # Size of PQ

    ptr_distance: .word 0 # 1-D Array for distance
    ptr_trace: .word 0 # 1-D Array for trace


    CONST_INFINITY: .word 0x7FFFFFFF # 32bit infinity value

################################### SUPPORT FILES ###################################
.include "io.asm"
.include "operations.asm"
.include "priority_queue.asm"


.include "debugtools.asm"
####################################### CODE ########################################
.text	# PGM here
    Enter()
    convertToAdjacentcyList()
    Dijkstra(start, desti)
    PrintPath(start, desti)
