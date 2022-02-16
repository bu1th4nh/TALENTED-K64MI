#/*==========================================================================================*\
# **                        _           _ _   _     _  _         _                            **
# **                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
# **                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
# **                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
# **                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
# \*==========================================================================================*/

###################################  INFORMATION ####################################
# 
# FILENAME    : debugtools.asm
# TITLE       : Tìm đường đi ngắn nhất trên đồ thị bằng thuật toán Dijkstra: Công cụ debug.
# AUTHOR      : bu1th4nh (Bùi Tiến Thành)								     
# DATE        : 2022-01-27
# DESCRIPTION : File này chứa các công cụ debug như in các mảng, kiểm tra CTDL và kiểm tra các giá trị.
# COPYRIGHT   : Copyright (C) 2022 by bu1th4nh https://github.com/bu1th4nh. All rights reserved.
# INPUT       : Không có.
# OUTPUT      : Không có.
# EXEC CMD    : java -jar .\Mars45.jar 1000000000 "main.asm"
# 
####################################### CODE #######################################
# Print whole array
.macro DEBUG___arr_print(%var_arr_target, %reg_size)
    .text
        subiu $sp, $sp, 4
        sw $a3, ($sp)

        li $a3, 0
        LOOP:
            read_from_var_array(%var_arr_target, $a3, $a0)
            li $v0, 1
            syscall
            spce

            addi $a3, $a3, 1
            blt $a3, %reg_size, LOOP
        
        lw $a3, ($sp)
        addiu $sp, $sp, 4
        endl
.end_macro

.macro DEBUG___arr2d_print(%var_arr_target, %var_sz, %reg_size)
    .text
        li $t0, 0
        LOOP:
            read_from_var_array(%var_sz, $t0, $t2)
            li $t1, 0
            
            print_int($t0)
            print_string(" ---> ")

            LOOP2:
                array_2d_read(%var_arr_target, $t0, $t1, $a0)
                li $v0, 1
                syscall
                spce

                addiu $t1, $t1, 1
                blt $t1, $t2, LOOP2

            endl
            addiu $t0, $t0, 1
            blt $t0, %reg_size, LOOP
.end_macro

.macro DEBUG___2x_arr2d_print(%var_arr_1, %var_arr_2, %var_sz, %reg_size)
    .text
        li $t0, 0
        LOOP:
            read_from_var_array(%var_sz, $t0, $t2)
            li $t1, 0
            
            print_int($t0)
            print_string(" ---> ")

            LOOP2:
                print_string("(")
                array_2d_read(%var_arr_1, $t0, $t1, $a0)
                li $v0, 1
                syscall

                print_string(" -- ")
                array_2d_read(%var_arr_2, $t0, $t1, $a0)
                li $v0, 1
                syscall

                print_string(")")
                spce

                addiu $t1, $t1, 1
                blt $t1, $t2, LOOP2

            endl
            addiu $t0, $t0, 1
            blt $t0, %reg_size, LOOP
.end_macro

###################################################################################################
# Debug PQ
.macro DEBUG___PQ()
    .text
        li $s0, 20
        li $t0, 0
        load_word_from_var($s1, CONST_INFINITY)
        malloc(ptr_prio_queue_dist, $s0, $s1)
        malloc(ptr_prio_queue_vrtx, $s0, $s1)
        store_word_to_var($t0, prio_queue_size)

        
        print_string("Initial PQ size: ")
        print_int_from_var(prio_queue_size)
        endl



        li $s2, 3
        li $s3, 0
        priorityQueue.insert(ptr_prio_queue_dist, ptr_prio_queue_vrtx, prio_queue_size, $s3, $s2)
        li $s0, 20
        # DEBUG___arr_print(ptr_prio_queue_dist, $s0)
        
    print_string("==============================================================================================\n")

        li $s2, 2
        li $s3, 1
        priorityQueue.insert(ptr_prio_queue_dist, ptr_prio_queue_vrtx, prio_queue_size, $s3, $s2)
        li $s0, 20
        # DEBUG___arr_print(ptr_prio_queue_dist, $s0)
        
    print_string("==============================================================================================\n")

        li $s2, 15
        li $s3, 2
        priorityQueue.insert(ptr_prio_queue_dist, ptr_prio_queue_vrtx, prio_queue_size, $s3, $s2)
        li $s0, 20
        # DEBUG___arr_print(ptr_prio_queue_dist, $s0)
        
    print_string("==============================================================================================\n")
        
        li $s2, 5
        li $s3, 3
        priorityQueue.insert(ptr_prio_queue_dist, ptr_prio_queue_vrtx, prio_queue_size, $s3, $s2)
        li $s0, 20
        # DEBUG___arr_print(ptr_prio_queue_dist, $s0)
        
    print_string("==============================================================================================\n")
        
        li $s2, 4
        li $s3, 4
        priorityQueue.insert(ptr_prio_queue_dist, ptr_prio_queue_vrtx, prio_queue_size, $s3, $s2)
        li $s0, 20
        # DEBUG___arr_print(ptr_prio_queue_dist, $s0)
        
    print_string("==============================================================================================\n")
        
        li $s2, 45
        li $s3, 5
        priorityQueue.insert(ptr_prio_queue_dist, ptr_prio_queue_vrtx, prio_queue_size, $s3, $s2)
        load_word_from_var($s0, prio_queue_size)
        DEBUG___arr_print(ptr_prio_queue_dist, $s0)
        

    print_string("==============================================================================================\n")
    print_string("==============================================================================================\n")
    print_string("Size: ")
    print_int_from_var(prio_queue_size)
    endl
    print_string("==============================================================================================\n")
    print_string("==============================================================================================\n")



        
        priorityQueue.pop(ptr_prio_queue_dist, ptr_prio_queue_vrtx, prio_queue_size, $s3, $s2)
        li $s0, 20
        load_word_from_var($s0, prio_queue_size)
        
        li $s0, 20
        DEBUG___arr_print(ptr_prio_queue_dist, $s0)

        print_string("Size: ")
        print_int_from_var(prio_queue_size)
        endl
        print_string("Pop #01: K=")
        print_int($s2)
        print_string(", V=")
        print_int($s3)
        endl

        
    print_string("==============================================================================================\n")


        
        priorityQueue.pop(ptr_prio_queue_dist, ptr_prio_queue_vrtx, prio_queue_size, $s3, $s2)
        li $s0, 20
        load_word_from_var($s0, prio_queue_size)
        
        li $s0, 20
        DEBUG___arr_print(ptr_prio_queue_dist, $s0)

        print_string("Size: ")
        print_int_from_var(prio_queue_size)
        endl
        print_string("Pop #02: K=")
        print_int($s2)
        print_string(", V=")
        print_int($s3)
        endl

        
    print_string("==============================================================================================\n")


        
        priorityQueue.pop(ptr_prio_queue_dist, ptr_prio_queue_vrtx, prio_queue_size, $s3, $s2)
        li $s0, 20
        load_word_from_var($s0, prio_queue_size)
        
        li $s0, 20
        DEBUG___arr_print(ptr_prio_queue_dist, $s0)

        print_string("Size: ")
        print_int_from_var(prio_queue_size)
        endl
        print_string("Pop #03: K=")
        print_int($s2)
        print_string(", V=")
        print_int($s3)
        endl

        
    print_string("==============================================================================================\n")


        
        priorityQueue.pop(ptr_prio_queue_dist, ptr_prio_queue_vrtx, prio_queue_size, $s3, $s2)
        li $s0, 20
        load_word_from_var($s0, prio_queue_size)
        
        li $s0, 20
        DEBUG___arr_print(ptr_prio_queue_dist, $s0)

        print_string("Size: ")
        print_int_from_var(prio_queue_size)
        endl
        print_string("Pop #04: K=")
        print_int($s2)
        print_string(", V=")
        print_int($s3)
        endl

        
    print_string("==============================================================================================\n")


        
        priorityQueue.pop(ptr_prio_queue_dist, ptr_prio_queue_vrtx, prio_queue_size, $s3, $s2)
        li $s0, 20
        load_word_from_var($s0, prio_queue_size)
        
        li $s0, 20
        DEBUG___arr_print(ptr_prio_queue_dist, $s0)

        print_string("Size: ")
        print_int_from_var(prio_queue_size)
        endl
        print_string("Pop #05: K=")
        print_int($s2)
        print_string(", V=")
        print_int($s3)
        endl

        
    print_string("==============================================================================================\n")


        
        priorityQueue.pop(ptr_prio_queue_dist, ptr_prio_queue_vrtx, prio_queue_size, $s3, $s2)
        li $s0, 20
        load_word_from_var($s0, prio_queue_size)
        
        li $s0, 20
        DEBUG___arr_print(ptr_prio_queue_dist, $s0)

        print_string("Size: ")
        print_int_from_var(prio_queue_size)
        endl
        print_string("Pop #06: K=")
        print_int($s2)
        print_string(", V=")
        print_int($s3)
        endl

        
    print_string("==============================================================================================\n")

.end_macro

###################################################################################################
# Legacy
# .macro debugEnter()
#     .text
#         print_string("a[")
#         print_int($s1)
#         print_string("] = ")
# 
#         read_int($t0)
#         write_to_array(ptr_edge_list_u, $s1, $t0)
# .end_macro
# .macro debugSum()
#     .text
#         read_from_array(ptr_edge_list_u, $s1, $t0)
#         add $s2, $s2, $t0
# .end_macro