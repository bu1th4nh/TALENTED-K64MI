#/*==========================================================================================*\
# **                        _           _ _   _     _  _         _                            **
# **                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
# **                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
# **                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
# **                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
# \*==========================================================================================*/

###################################  INFORMATION ####################################
# 
# FILENAME    : macro.asm
# TITLE       : Tìm đường đi ngắn nhất trên đồ thị bằng thuật toán Dijkstra: Macro bổ trợ.
# AUTHOR      : bu1th4nh (Bùi Tiến Thành)								     
# DATE        : 2022-01-28
# DESCRIPTION : File này chứa macro và công cụ hỗ trợ cho chương trình.
# COPYRIGHT   : Copyright (C) 2022 by bu1th4nh https://github.com/bu1th4nh. All rights reserved.
# INPUT       : Không có.
# OUTPUT      : Không có.
# EXEC CMD    : java -jar .\Mars45.jar 1000000000 "main.asm"
# 
####################################### CODE #######################################
####################################################################################
####################################### MISC #######################################
.macro gnr_syscall(%int)
    .text
        li $v0, %int
        syscall
.end_macro

#################################### LOAD/STORE ####################################
# reg_rtn = variable
.macro load_word_from_var(%reg_rtn, %variable)
    .text
        subiu $sp, $sp, 4
        sw $t9, ($sp)

        la $t9, %variable
        lw %reg_rtn, ($t9)

        lw $t9, ($sp)
        addiu $sp, $sp, 4
.end_macro
# variable = reg_store
.macro store_word_to_var(%reg_store, %variable)
    .text
        subiu $sp, $sp, 4
        sw $t9, ($sp)

        la $t9, %variable
        sw %reg_store, ($t9)

        lw $t9, ($sp)
        addiu $sp, $sp, 4
.end_macro



###################################### READ ######################################
# Integers
.macro read_int(%int)               # Read direct an int to register
    .text
        li $v0, 5
        syscall
        move %int, $v0
.end_macro

.macro read_int_to_var(%var)        # Read direct an int to a vars
    .text
        subiu $sp, $sp, 4
        sw $t8, ($sp)

        read_int($t8)
        store_word_to_var($t8, %var)

        lw $t8, ($sp)
        addiu $sp, $sp, 4
.end_macro




###################################### PRINT #####################################
# Strings/Chars
.macro endl                         # Print an end-of-line chars
    li $v0 11
    li $a0 '\n'
    syscall
.end_macro

.macro spce                         # Print a space chars
    li $v0 11
    li $a0 ' '
    syscall
.end_macro

.macro print_string(%str)           # Print a string
    .data
        mystring: .asciiz %str
    .text
        li $v0, 4
        la $a0, mystring
        syscall
.end_macro

# Integers
.macro print_int(%int)              # Print an int from register to stdout
    .text
        li $v0, 1
        move $a0, %int
        syscall
.end_macro


.macro print_int_from_var(%var) 
    .text
        subiu $sp, $sp, 4
        sw $t8, ($sp)

        load_word_from_var($t8, %var)
        print_int($t8)

        lw $t8, ($sp)
        addiu $sp, $sp, 4
.end_macro





###################################### LOOPS #####################################
# For loop: i = from; i <= to; ++i
.macro FOR(%iteration, %from, %to, %bodyMacro)      
    .text
        add %iteration, $zero, %from
        LOOP:
            %bodyMacro ()
            addi %iteration, %iteration, 1
            ble %iteration, %to, LOOP
.end_macro
# For loop: i = from; i < to; ++i
.macro FORl(%iteration, %from, %to, %bodyMacro)      
    .text
        add %iteration, $zero, %from
        LOOP:
            %bodyMacro ()
            addi %iteration, %iteration, 1
            blt %iteration, %to, LOOP
.end_macro




################################ 1-D ARRAYS ACCESS ################################
# reg_rtn = a[index]
.macro read_from_reg_array(%reg_ptr, %reg_index, %reg_rtn)
    .text
        # Store
        subiu $sp, $sp, 4
        sw $t8, ($sp)
        subiu $sp, $sp, 4
        sw $t9, ($sp)

        # Load arays pointer
        move $t8, %reg_ptr 

        # Shift index
        sll $t9, %reg_index, 2
        add $t8, $t8, $t9

        # Load values
        lw %reg_rtn, ($t8)

        # Restore
        lw $t9, ($sp)
        addiu $sp, $sp, 4
        lw $t8, ($sp)
        addiu $sp, $sp, 4
.end_macro
.macro read_from_var_array(%vars_ptr, %reg_index, %reg_rtn)
    .text
        # Store
        subiu $sp, $sp, 4
        sw $t8, ($sp)

        # Load arays pointer
        load_word_from_var($t8, %vars_ptr)
        read_from_reg_array($t8, %reg_index, %reg_rtn)

        # Restore
        lw $t8, ($sp)
        addiu $sp, $sp, 4
.end_macro
# vars_ptr[reg_index] = reg_val
.macro write_to_reg_array(%reg_ptr, %reg_index, %reg_val)
    .text
        # Store
        subiu $sp, $sp, 4
        sw $t8, ($sp)
        subiu $sp, $sp, 4
        sw $t9, ($sp)

        # Load arays pointer
        move $t8, %reg_ptr

        # Shift index
        sll $t9, %reg_index, 2
        add $t8, $t8, $t9

        # Load values
        sw %reg_val, ($t8)

        # Restore
        lw $t9, ($sp)
        addiu $sp, $sp, 4
        lw $t8, ($sp)
        addiu $sp, $sp, 4
.end_macro
.macro write_to_var_array(%vars_ptr, %reg_index, %reg_val)
    .text
        # Store
        subiu $sp, $sp, 4
        sw $t8, ($sp)

        # Load arays pointer
        load_word_from_var($t8, %vars_ptr)
        write_to_reg_array($t8, %reg_index, %reg_val)

        # Restore
        lw $t8, ($sp)
        addiu $sp, $sp, 4
.end_macro


################################ 2-D ARRAYS ACCESS ################################
# Vars only
.macro array_2d_read(%var_ptr, %reg_i_value, %reg_j_value, %reg_rtn_value)
    .text
        # Store
        subiu $sp, $sp, 4
        sw $t7, ($sp)

        read_from_var_array(%var_ptr, %reg_i_value, $t7)
        read_from_reg_array($t7, %reg_j_value, %reg_rtn_value)

        # Restore
        lw $t7, ($sp)
        addiu $sp, $sp, 4

.end_macro
.macro array_2d_write(%var_ptr, %reg_i_value, %reg_j_value, %reg_value)
    .text
        # Store
        subiu $sp, $sp, 4
        sw $t7, ($sp)

        read_from_var_array(%var_ptr, %reg_i_value, $t7)
        write_to_reg_array($t7, %reg_j_value, %reg_value)

        # Restore
        lw $t7, ($sp)
        addiu $sp, $sp, 4

.end_macro



################################# ARRAYS OPERATIONS ################################
# a = vector<T>(n = const, 0)
.macro reg_array_set(%reg_ptr, %reg_size, %reg_val)
    .text
        # Store
        subiu $sp, $sp, 4
        sw $t7, ($sp)
        
        
        li $t7, 0
        LOOP:
            write_to_reg_array(%reg_ptr, $t7, %reg_val)
            addi $t7, $t7, 1
            blt $t7, %reg_size, LOOP
        
        lw $t7, ($sp)
        addiu $sp, $sp, 4
.end_macro
.macro var_array_set(%var_ptr, %reg_size, %reg_val)
    .text
        # Store
        subiu $sp, $sp, 4
        sw $t7, ($sp)
        
        li $t7, 0
        LOOP:
            write_to_var_array(%var_ptr, $t7, %reg_val)
            addi $t7, $t7, 1
            blt $t7, %reg_size, LOOP
        
        lw $t7, ($sp)
        addiu $sp, $sp, 4
.end_macro


# a = b
.macro array_copy(%vars_arr_source_ptr, %var_arr_target_ptr, %reg_size)
    .text
        # Store
        subiu $sp, $sp, 4
        sw $t0, ($sp)
        subiu $sp, $sp, 4
        sw $t7, ($sp)
        
        li $t7, 0
        LOOP:
            read_from_array(%var_arr_target_ptr, $t7, $t0)
            write_to_array(%var_arr_target_ptr, $t7, $t0)
            addi $t7, $t7, 1
            blt $t7, %reg_size, LOOP
        
        lw $t7, ($sp)
        addiu $sp, $sp, 4
        lw $t0, ($sp)
        addiu $sp, $sp, 4
        
.end_macro

# swap(a[i], a[j])
.macro array_swap(%vars_arr, %reg_lhs, %reg_rhs)
    .text
        load_word_from_var($a2, %vars_arr)
        sll $a0, %reg_lhs, 2
        add $a0, $a0, $a2
        sll $a1, %reg_rhs, 2
        add $a1, $a1, $a2
        
        lw $a2, ($a0)
        lw $a3, ($a1)
        sw $a2, ($a1)
        sw $a3, ($a0)
.end_macro


################################ MEMORY ALLOCATION ###############################
# a = vector<int>(size, val)
.macro malloc_regs(%reg_arr_target, %reg_size, %reg_default_value)
    .text
        subiu $sp, $sp, 4
        sw $t8, ($sp)

        sll $a0, %reg_size, 2
        li $v0, 9
        syscall
        move %reg_arr_target, $v0

        lw $t8, ($sp)
        addiu $sp, $sp, 4

        reg_array_set(%reg_arr_target, %reg_size, %reg_default_value)
.end_macro
.macro malloc(%var_arr_target, %reg_size, %reg_default_value)
    .text
        subiu $sp, $sp, 4
        sw $t8, ($sp)

        sll $a0, %reg_size, 2
        li $v0, 9
        syscall
        la $t8, %var_arr_target
        sw $v0, ($t8)

        lw $t8, ($sp)
        addiu $sp, $sp, 4

        var_array_set(%var_arr_target, %reg_size, %reg_default_value)
.end_macro



