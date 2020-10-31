import sympy as sym
import scipy as sci
import numpy as np
from math import *
import sys


#===================================================================================
# Phần thuật toán chính
class jacobi_mat_inversion:
#{
    def __init__(self, A, n, eps):
    #{
        self.A = np.reshape(np.array(A), (n, n));
        self.eps = eps;
        self.n = n;
    #}
    def __norm(self, __A, __norm_type = 2):
    #{
        return np.linalg.norm(__A, __norm_type);
    #}


    def __getNorm(self, __A, __domination_status): # Tính chuẩn
    #{
        if(__domination_status == 1): return self.__norm(__A, inf);
        return self.__norm(__A, 1);
    #}
    def __checkDomination(self, __A): # Kiểm tra tính chéo trội
    #{
        n = int(__A.shape[0]);
        row_dom = col_dom = 1;

        for i in range(n):
        #{
            sum_row = sum_col = 0;
            for j in range(n): 
                if(i != j):
                    sum_row += abs(__A[i, j]);
                    sum_col += abs(__A[j, i]);

            if(sum_row >= abs(__A[i, i])): row_dom = 0;
            if(sum_col >= abs(__A[i, i])): col_dom = 0;
        #}

        if(row_dom == 1): return 1;
        if(col_dom == 1): return -1;
        return 0;
    #}
    def __getLambda(self, __domination_status, __A): # Tính lambda
    #{
        if(__domination_status == 1): return 1;

        n = int(__A.shape[0]);
        maxA = minA = __A[0, 0];
        for i in range(n): 
        #{
            maxA = max(maxA, __A[i, i]);
            minA = min(minA, __A[i, i]);
        #}

        return maxA / minA;
    #}


    # Tiến trình lặp
    def __predecessor_iteration(self, X_0, B, T, q, lda, p): #SD công thức sai số tiên nghiệm
    #{
        predecessor_norm = self.__getNorm((B @ X_0 + T) - X_0, p);
        X  = X_0;
        qk = 1;

        nr_iteration = 0;
        while(lda * qk * predecessor_norm > self.eps * (1 - q)):
        #{
            nr_iteration += 1;
            X   = B @ X + T;
            qk *= q;
        #}

        print(f"Predecessor Jacobi iteration method ended after {nr_iteration} iterations", file=sys.stderr);
        return X;
    #}
    def __successor_iteration(self, X_0, B, T, q, lda, p): #SD công thức sai số hậu nghiệm
    #{
        old_X = X_0;
        new_X = B @ X_0 + T;

        nr_iteration = 0;
        while(lda * q * self.__getNorm(new_X - old_X, p) > self.eps * (1 - q)):
        #{
            nr_iteration += 1;
            old_X = new_X;
            new_X = B @ old_X + T;
        #}

        print(f"Successor Jacobi iteration method ended after {nr_iteration} iterations", file=sys.stderr);
        return new_X;
    #}


    # PP lặp Jacobi với chế độ đánh giá tiên nghiệm hoặc hậu nghiệm
    def jacobi_iteration(self, mode = 1):
    #{
        # Gán các biến cơ bản
        A = self.A;
        n = self.n;
        E = np.eye(self.n);

        # chốt 141: Kiểm tra chéo trội và khả nghịch
        p = self.__checkDomination(A);
        if(np.linalg.det(self.A) == 0):
        #{
            print("A không khả nghịch nên không đưa ra được ma trận nghịch đảo");
            return np.full((self.n, self.n), float("NaN"));
        #}
        if(p == 0): 
        #{
            print("A không chéo trội nên không đưa ra được ma trận nghịch đảo. Đề xuất: PP Newton");
            return np.full((self.n, self.n), float("NaN"));
        #}

        # Tính T, B, p, q
        T          = np.diag(1 / np.diag(A));
        B          = E - T @ A;
        q          = self.__getNorm(B, p);
        var_lambda = self.__getLambda(p, A);


        # Đưa ra ma trận cuối cùng
        if(mode == 1): return self.__predecessor_iteration(A, B, T, q, var_lambda, p);
        return self.__successor_iteration(A, B, T, q, var_lambda, p);
    #}
#}


#===================================================================================
# Chương trình ví dụ

# A = np.random.rand(3,3) * 1000;
# A = np.array([4, 0.24, -0.08, 0.09, 3, -0.15, 0.04, -0.08, 4]);
# A = np.reshape(A, (3, 3));

# print(A);

# uu = jacobi_mat_inversion(A, 3, 1e-10);
# A1 = uu.jacobi_iteration(1);
# print(A1);
# print(A1 @ A);
# A2 = uu.jacobi_iteration(2);
# print(A2);
# print(A2 @ A);