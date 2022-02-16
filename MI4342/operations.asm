#/*==========================================================================================*\
# **                        _           _ _   _     _  _         _                            **
# **                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
# **                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
# **                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
# **                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
# \*==========================================================================================*/

###################################  INFORMATION ####################################
# 
# FILENAME    : operations.asm
# TITLE       : Tìm đường đi ngắn nhất trên đồ thị bằng thuật toán Dijkstra: Các thủ tục chính.
# AUTHOR      : bu1th4nh (Bùi Tiến Thành)								     
# DATE        : 2022-01-29
# DESCRIPTION : File này chứa các thủ tục chính và thuật toán lõi của chương trình.
# COPYRIGHT   : Copyright (C) 2022 by bu1th4nh https://github.com/bu1th4nh. All rights reserved.
# INPUT       : Không có.
# OUTPUT      : Không có.
# EXEC CMD    : java -jar .\Mars45.jar 1000000000 "main.asm"
# 
####################################### CODE #######################################
# Chuyển từ danh sách cạnh sang danh sách kề
.macro convertToAdjacentcyList() # Read all the edges to edge list
    .text
        subi $sp, $sp, 4
        sw $s0, ($sp)
        subi $sp, $sp, 4
        sw $s1, ($sp)
        subi $sp, $sp, 4
        sw $s2, ($sp)
        subi $sp, $sp, 4
        sw $s3, ($sp)
        subi $sp, $sp, 4
        sw $s4, ($sp)
        subi $sp, $sp, 4
        sw $s5, ($sp)
        subi $sp, $sp, 4
        sw $s6, ($sp)
        subi $sp, $sp, 4
        sw $s7, ($sp)  

        load_word_from_var($s0, n)
        load_word_from_var($s1, m)

        li $s2, 0
        LOOP:
            read_from_var_array(ptr_adj_size, $s2, $t0)
            malloc_regs($t1, $t0, $0)
            write_to_var_array(ptr_adj_vrtx, $s2, $t1)
            malloc_regs($t1, $t0, $0)
            write_to_var_array(ptr_adj_dist, $s2, $t1)

            addi $s2, $s2, 1
            blt $s2, $s0, LOOP

        li $s2, 0
        LOOP2:
            read_from_var_array(ptr_edge_list_u, $s2, $t0)
            read_from_var_array(ptr_edge_list_v, $s2, $t1)
            read_from_var_array(ptr_edge_list_c, $s2, $t2)


            read_from_var_array(ptr_distance, $t0, $s3)
            array_2d_write(ptr_adj_vrtx, $t0, $s3, $t1)
            array_2d_write(ptr_adj_dist, $t0, $s3, $t2)
            addiu $s3, $s3, 1
            write_to_var_array(ptr_distance, $t0, $s3)


            read_from_var_array(ptr_distance, $t1, $s3)
            array_2d_write(ptr_adj_vrtx, $t1, $s3, $t0)
            array_2d_write(ptr_adj_dist, $t1, $s3, $t2)
            addiu $s3, $s3, 1
            write_to_var_array(ptr_distance, $t1, $s3)


            addi $s2, $s2, 1
            blt $s2, $s1, LOOP2

        lw $s7, 0($sp)
        addi $sp, $sp, 4
        lw $s6, 0($sp)
        addi $sp, $sp, 4
        lw $s5, 0($sp)
        addi $sp, $sp, 4
        lw $s4, 0($sp)
        addi $sp, $sp, 4
        lw $s3, 0($sp)
        addi $sp, $sp, 4
        lw $s2, 0($sp)
        addi $sp, $sp, 4
        lw $s1, 0($sp)
        addi $sp, $sp, 4
        lw $s0, 0($sp)
        addi $sp, $sp, 4


        # # DEBUG
        # load_word_from_var($s0, n)
        # print_string("##################################################\n")
        # DEBUG___arr2d_print(ptr_adj_vrtx, ptr_adj_size, $s0)
        # print_string("##################################################\n")
        # DEBUG___arr2d_print(ptr_adj_dist, ptr_adj_size, $s0)
        # print_string("##################################################\n")
        # DEBUG___2x_arr2d_print(ptr_adj_vrtx, ptr_adj_dist, ptr_adj_size, $s0)   
        # # DEBUG
            
.end_macro



# Truy vết
.macro Trace(%var_start_vrtx, %var_desti_vrtx)
    .text
        load_word_from_var($s0, n)
        # DEBUG___arr_print(ptr_trace, $s0)

        load_word_from_var($s0, %var_start_vrtx)
        load_word_from_var($s1, %var_desti_vrtx)
        bne $s0, $s1, DIJKSTRA_TRACE
        print_string("Trace: ")
        print_int($s0)
        print_string(" and ")
        print_int($s1)
        print_string("is the same.\n")

        j DIJKSTRA_END
        DIJKSTRA_TRACE:
            print_string("Shortest path from ")
            print_int($s0)
            print_string(" to ")
            print_int($s1)
            print_string(": ")

            DIJKSTRA_TRACE_LOOP:
                beq $s1, $s0, DIJKSTRA_TRACE_END
                print_int($s1)
                print_string(" <- ")
                read_from_var_array(ptr_trace, $s1, $s1)
                j DIJKSTRA_TRACE_LOOP


        DIJKSTRA_TRACE_END:
            print_int($s0)
            print_string(".\n")


        DIJKSTRA_END:
.end_macro


# Thuật toán Dijkstra
.macro Dijkstra(%var_start_vrtx, %var_desti_vrtx)
    .text
        subi $sp, $sp, 4
        sw $s0, ($sp)
        subi $sp, $sp, 4
        sw $s1, ($sp)
        subi $sp, $sp, 4
        sw $s2, ($sp)
        subi $sp, $sp, 4
        sw $s3, ($sp)
        subi $sp, $sp, 4
        sw $s4, ($sp)
        subi $sp, $sp, 4
        sw $s5, ($sp)
        subi $sp, $sp, 4
        sw $s6, ($sp)
        subi $sp, $sp, 4
        sw $s7, ($sp)
        

        load_word_from_var($s0, n)
        
        load_word_from_var($s1, CONST_INFINITY)
        var_array_set(ptr_distance, $s0, $s1)

        load_word_from_var($s1, %var_start_vrtx)
        write_to_var_array(ptr_distance, $s1, $0)

        li $s2, -1
        write_to_var_array(ptr_trace $s1, $s2)

        

        store_word_to_var($0, prio_queue_size)
        priorityQueue.insert(ptr_prio_queue_dist, ptr_prio_queue_vrtx, prio_queue_size, $s1, $0)

        DIJKSTRA_LOOP:
            # # DEBUG
            # print_string("--------------\n")
            # # DEBUG

            load_word_from_var($s1, prio_queue_size)
            blez $s1, DIJKSTRA_LOOP_END
            priorityQueue.pop(ptr_prio_queue_dist, ptr_prio_queue_vrtx, prio_queue_size, $s2, $s3)

            # # DEBUG
            # print_string("s2 = u = ")
            # print_int($s2)
            # print_string(", s3 = pq.top().first = ")
            # print_int($s3)
            # endl
            # # DEBUG


            read_from_var_array(ptr_distance, $s2, $s4) # s4 = dist[s2]
            bne $s4, $s3, DIJKSTRA_LOOP

            # # DEBUG
            # print_string(", s4 = d[u] = ")
            # print_int($s4)
            # endl
            # # DEBUG


            read_from_var_array(ptr_adj_size, $s2, $s0)
            li $s1, 0

            DIJKSTRA_ADJ_LOOP:
                array_2d_read(ptr_adj_vrtx, $s2, $s1, $s4)
                array_2d_read(ptr_adj_dist, $s2, $s1, $s5)
                read_from_var_array(ptr_distance, $s4, $s6)


                # # DEBUG
                # print_string("s4 = adj[u][i].v = ")
                # print_int($s4)
                # print_string(", s5 = adj[u][i].c = ")
                # print_int($s5)
                # print_string(", s6 = d[v] = ")
                # print_int($s6)
                # endl
                # # DEBUG



                add $s5, $s5, $s3

                # # DEBUG
                # print_string("s5 = d[u] + adj[u][i].c = ")
                # print_int($s5)
                # endl
                # # DEBUG

                bgt $s5, $s6, DIJKSTRA_ADJ_SKIP_VERTEX
                write_to_var_array(ptr_distance, $s4, $s5)
                write_to_var_array(ptr_trace, $s4, $s2)
                priorityQueue.insert(ptr_prio_queue_dist, ptr_prio_queue_vrtx, prio_queue_size, $s4, $s5)

                


                DIJKSTRA_ADJ_SKIP_VERTEX:
                addi $s1, $s1, 1
                blt $s1, $s0, DIJKSTRA_ADJ_LOOP

        j DIJKSTRA_LOOP

        DIJKSTRA_LOOP_END:

        # # DEBUG
        # load_word_from_var($s0, n)
        # DEBUG___arr_print(ptr_distance, $s0)
        # # DEBUG

        


        lw $s7, 0($sp)
        addi $sp, $sp, 4
        lw $s6, 0($sp)
        addi $sp, $sp, 4
        lw $s5, 0($sp)
        addi $sp, $sp, 4
        lw $s4, 0($sp)
        addi $sp, $sp, 4
        lw $s3, 0($sp)
        addi $sp, $sp, 4
        lw $s2, 0($sp)
        addi $sp, $sp, 4
        lw $s1, 0($sp)
        addi $sp, $sp, 4
        lw $s0, 0($sp)
        addi $sp, $sp, 4

.end_macro



# Khởi tạo và nhập liệu
.macro Init()
    .text
        load_word_from_var($s0, m)
        malloc(ptr_edge_list_u, $s0, $zero)
        malloc(ptr_edge_list_v, $s0, $zero)
        malloc(ptr_edge_list_c, $s0, $zero)

        
        
        load_word_from_var($s0, n)
        malloc(ptr_adj_dist, $s0, $zero)
        malloc(ptr_adj_vrtx, $s0, $zero)
        malloc(ptr_adj_size, $s0, $zero)
        malloc(ptr_distance, $s0, $zero)
        malloc(ptr_trace, $s0, $zero)
        
        sll $s0, $s0, 2
        load_word_from_var($s1, CONST_INFINITY)
        malloc(ptr_prio_queue_vrtx, $s0, $s1)
        malloc(ptr_prio_queue_dist, $s0, $s1)


.end_macro

.macro Enter()
    .text
        # print_string("Please enter n = ")
        read_int_to_var(n)
        # print_string("Please enter m = ")
        read_int_to_var(m)
        # print_string("Please enter start vertex: ")
        read_int_to_var(start)
        # print_string("Please enter target vertex: ")
        read_int_to_var(desti)

        Init()
        load_word_from_var($s0, m)
        FORl($s1, 0, $s0, enterEdge)

.end_macro




# Xuất dữ liệu
.macro PrintPath(%var_start_vrtx, %var_desti_vrtx)
    .text

        # Print output
        load_word_from_var($s7, CONST_INFINITY)
        load_word_from_var($s0, %var_start_vrtx)
        load_word_from_var($s1, %var_desti_vrtx)
        read_from_var_array(ptr_distance, $s1, $s2)

        bge $s2, $s7, RTN_NO_PATH


        print_string("Shortest distance from ")
        print_int($s0)
        print_string(" to ")
        print_int($s1)
        print_string(" is: ")
        print_int($s2)
        endl

        Trace(%var_start_vrtx, %var_desti_vrtx)
        j PGM_END

        RTN_NO_PATH:
            print_string("There is no path from ")
            print_int($s0)
            print_string(" to ")
            print_int($s1)
            endl


        PGM_END:

.end_macro