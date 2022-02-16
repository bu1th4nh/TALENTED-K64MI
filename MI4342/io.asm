#/*==========================================================================================*\
# **                        _           _ _   _     _  _         _                            **
# **                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
# **                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
# **                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
# **                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
# \*==========================================================================================*/

###################################  INFORMATION ####################################
# 
# Filename    : io.asm
# Title       : Tìm đường đi ngắn nhất trên đồ thị bằng thuật toán Dijkstra: Vào/ra.
# Author      : bu1th4nh (Bùi Tiến Thành)								     
# Date        : 2022-01-29
# Description : File này chứa thủ tục nhập các cạnh của đồ thị.
# Copyright   : Copyright (C) 2022 by bu1th4nh https://github.com/bu1th4nh. All rights reserved.
# Input       : Không có.
# Output      : Không có.
# Exec CMD    : java -jar .\Mars45.jar 1000000000 "main.asm"
# 
####################################### CODE #######################################
.macro enterEdge() # Read all the edges to edge list
    .text
        # print_string("Edge #")
        # print_int($s1)
        # print_string(": \n")


        # print_string("u = ")
        read_int($t0)
        write_to_var_array(ptr_edge_list_u, $s1, $t0)

        read_from_var_array(ptr_adj_size, $t0, $t1)
        addi $t1, $t1, 1
        write_to_var_array(ptr_adj_size, $t0, $t1)


        
        # print_string("v = ")
        read_int($t0)
        write_to_var_array(ptr_edge_list_v, $s1, $t0)

        read_from_var_array(ptr_adj_size, $t0, $t1)
        addi $t1, $t1, 1
        write_to_var_array(ptr_adj_size, $t0, $t1)



        # print_string("c = ")
        read_int($t0)
        write_to_var_array(ptr_edge_list_c, $s1, $t0)
.end_macro



