#/*==========================================================================================*\
# **                        _           _ _   _     _  _         _                            **
# **                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
# **                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
# **                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
# **                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
# \*==========================================================================================*/

###################################  INFORMATION ####################################
# 
# FILENAME    : priority_queue.asm
# TITLE       : Tìm đường đi ngắn nhất trên đồ thị bằng thuật toán Dijkstra: CTDL hàng đợi ưu tiên.
# AUTHOR      : bu1th4nh (Bùi Tiến Thành)								     
# DATE        : 2022-01-28
# DESCRIPTION : File này chứa cài đặt cho CTDL hàng đợi ưu tiên.
# COPYRIGHT   : Copyright (C) 2022 by bu1th4nh https://github.com/bu1th4nh. All rights reserved.
# INPUT       : Không có.
# OUTPUT      : Không có.
# EXEC CMD    : java -jar .\Mars45.jar 1000000000 "main.asm"
# 
####################################### CODE #######################################
####################################################################################
# Utilities
.macro priorityQueue.__getParent(%reg_curr_vrtx, %reg_rtn_parent)
    .text   
        subi %reg_rtn_parent, %reg_curr_vrtx, 1
        srl %reg_rtn_parent, %reg_rtn_parent, 1
.end_macro
.macro priorityQueue.__getLeftChild(%reg_curr_vrtx, %reg_rtn_lchild)
    .text   
        sll %reg_rtn_lchild, %reg_curr_vrtx, 1
        addi %reg_rtn_lchild, %reg_rtn_lchild, 1
.end_macro
.macro priorityQueue.__getRightChild(%reg_curr_vrtx, %reg_rtn_rchild)
    .text   
        sll %reg_rtn_rchild, %reg_curr_vrtx, 1
        addi %reg_rtn_rchild, %reg_rtn_rchild, 2
.end_macro


##############################################################################
# PQ Operations
# Insert
.macro priorityQueue.insert(%var_ptr_pq_key, %var_ptr_pq_value, %var_pq_size, %reg_vrtx, %reg_dist)
    .text
        subiu $sp, $sp, 4
        sw $t0, ($sp)
        subiu $sp, $sp, 4
        sw $t1, ($sp)
        subiu $sp, $sp, 4
        sw $t2, ($sp)
        subiu $sp, $sp, 4
        sw $t3, ($sp)
        

        # Extract, increase and re-save current size fom variable %var_pq_size
        li $t0, 0
        li $t1, 0

        load_word_from_var($t0, %var_pq_size)
        move $t1, $t0
        addi $t0, $t0, 1
        store_word_to_var($t0, %var_pq_size)
        li $t0, 0


        # Insert element to heap
        write_to_var_array(%var_ptr_pq_key, $t1, %reg_dist)
        write_to_var_array(%var_ptr_pq_value, $t1, %reg_vrtx)



        # Now declare $a1 as current vertex, $a0 as parent vertex of $a1
        # Adjust heap
        LOOP:
            blez $t1, LOOP_END
            priorityQueue.__getParent($t1, $t0)

            read_from_var_array(%var_ptr_pq_key, $t1, $t2) # Current
            read_from_var_array(%var_ptr_pq_key, $t0, $t3) # Parent
            ble $t3, $t2, LOOP_END

            array_swap(%var_ptr_pq_key, $t1, $t0)
            array_swap(%var_ptr_pq_value, $t1, $t0)
            move $t1, $t0

            j LOOP

        LOOP_END:

        lw $t3, ($sp)
        addiu $sp, $sp, 4
        lw $t2, ($sp)
        addiu $sp, $sp, 4    
        lw $t1, ($sp)
        addiu $sp, $sp, 4
        lw $t0, ($sp)
        addiu $sp, $sp, 4    
.end_macro


# Pop
.macro priorityQueue.pop(%var_ptr_pq_key, %var_ptr_pq_value, %var_pq_size, %reg_rtn_vrtx, %reg_rtn_dist)
    .text
        # Save current temp. vars      
        subiu $sp, $sp, 4
        sw $t7, ($sp)   
        subiu $sp, $sp, 4
        sw $t6, ($sp)   
        subiu $sp, $sp, 4
        sw $t5, ($sp)   
        subiu $sp, $sp, 4
        sw $t4, ($sp)   
        subiu $sp, $sp, 4
        sw $t3, ($sp)   
        subiu $sp, $sp, 4
        sw $t2, ($sp)
        subiu $sp, $sp, 4
        sw $t1, ($sp)
           
        

        # Get value of PQ's top
        read_from_var_array(%var_ptr_pq_key, $0, %reg_rtn_dist)
        read_from_var_array(%var_ptr_pq_value, $0, %reg_rtn_vrtx)

        # Load PQ size as $t7 and temporary value 1 as $t6
        load_word_from_var($t7, %var_pq_size)
        li $t6, 1

        # Check if PQ size greater than 1. 
        bgt $t7, $t6, PQ_POP_CONTINUE
        
        # If PQ size equals 1, return
        store_word_to_var($0, %var_pq_size)
        j PQ_POP_END
        

        # Otherwise:
        PQ_POP_CONTINUE:
            # Replace top value of PQ as bottom value
            load_word_from_var($t6, CONST_INFINITY)
            write_to_var_array(%var_ptr_pq_key, $0, $t6)
            write_to_var_array(%var_ptr_pq_value, $0, $t6)
            load_word_from_var($t6, %var_pq_size)

            
            # Adjust size and heap
            subi $t7, $t7, 1
            store_word_to_var($t7, %var_pq_size)
            array_swap(%var_ptr_pq_key, $0, $t7)
            array_swap(%var_ptr_pq_value, $0, $t7)
            

            li $t1, 0 # t1: current node
            li $t2, 0 # t2: smallest of L, R, current node
            PQ_POP_ADJ_HEAP:
                move $t2, $t1 # Initially t2 set as current node

                priorityQueue.__getLeftChild($t1, $t3)          # t3: L node
                bge $t3, $t7 CHECK_NEXT_CHILD                   # if t3 >= (t7=size), skip to next child
                read_from_var_array(%var_ptr_pq_key, $t2, $t4)  # t4 = key[t2 = smallest]
                read_from_var_array(%var_ptr_pq_key, $t3, $t5)  # t5 = key[t3 = L]
                bge $t5, $t4, CHECK_NEXT_CHILD                  # if key[t3 = L] >= key[t2 = smallest], skip to next child
                move $t2, $t3                                   # Update t2 <- t3(L)

                CHECK_NEXT_CHILD:
                priorityQueue.__getRightChild($t1, $t3)         # t3: R node
                bge $t3, $t7 FINALIZE                           # if t3 >= (t7=size), skip to next child
                read_from_var_array(%var_ptr_pq_key, $t2, $t4)  # t4 = key[t2 = smallest]
                read_from_var_array(%var_ptr_pq_key, $t3, $t5)  # t5 = key[t3 = R]
                bge $t5, $t4, FINALIZE                          # if key[t3 = R] >= key[t2 = smallest], skip to next child
                move $t2, $t3                                   # Update t2 <- t3(R)

                FINALIZE:
                beq $t2, $t1, PQ_POP_END
                
                # # DEBUG
                # print_string("Swap between ")
                # print_int($t1)
                # print_string(" and ")
                # print_int($t2)
                # endl
                # # DEBUG

                array_swap(%var_ptr_pq_key, $t1, $t2)
                array_swap(%var_ptr_pq_value, $t1, $t2)
                move $t1, $t2
                j PQ_POP_ADJ_HEAP




        PQ_POP_END:
        # Load current temp. vars
        lw $t1, ($sp)
        addiu $sp, $sp, 4
        lw $t2, ($sp)
        addiu $sp, $sp, 4
        lw $t3, ($sp)
        addiu $sp, $sp, 4
        lw $t4, ($sp)
        addiu $sp, $sp, 4
        lw $t5, ($sp)
        addiu $sp, $sp, 4
        lw $t6, ($sp)
        addiu $sp, $sp, 4
        lw $t7, ($sp)
        addiu $sp, $sp, 4
.end_macro
