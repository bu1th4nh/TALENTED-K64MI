import sympy as sym
import scipy as sci
import numpy as np
from math import *
import sys


#===================================================================================
# Phần thuật toán chính
class gaussseidel_mat_inversion:
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
    def __getNorm(self, __A, __domination_status): # Tính chuẩn
    #{
        if(__domination_status == 1): return self.__norm(__A, inf);
        return self.__norm(__A, 1);
    #}
    def __get_S_coeff(self, __A, __domination_status): # Tính S
    #{
        if(__domination_status == 1): return 0;
        
        S = 0;
        n = int(__A.shape[0]);
        for i in range(n): 
        #{
            tmp = 0;
            for j in range(i, n): tmp += abs(__A[j, i]);
            S = max(S, tmp);
        #}

        return S;
    #}
    def __get_q_coeff(self, __A, __domination_status): # Tính q
    #{
        q = 0;
        n = int(__A.shape[0]);
        for i in range(n):
        #{
            Q1 = Q2 = 0;
            for j in range(n):
                if(__domination_status == 1):
                #{
                    if(j >= i-1): Q1 += abs(__A[i, j]);
                    else: Q2 += abs(__A[i, j]);
                #}
                else:
                #{
                    if(j <= i-1): Q1 += abs(__A[j, i]);
                    else: Q2 += abs(__A[j, i]);
                #}
            q = max(q, Q1 / (1 - Q2));
        #}
        return q;
    #}


    # Tiến trình lặp
    def _________next_iteration(self, old_X, B, T, relax_factor):
    #{
        n = int(B.shape[0]);
        new_X = np.zeros_like(B);
        for i in range(n):
        #{
            for j in range(i): new_X[i] += B[i, j] * new_X[j];
            for j in range(i, n): new_X[i] += B[i, j] * old_X[j];
            new_X[i] += T[i];
        #}

        return (1 - relax_factor) * old_X + relax_factor * new_X;
    #}
    def __predecessor_iteration(self, X_0, B, T, S, q, p, relax_factor): #SD công thức sai số tiên nghiệm
    #{
        X_1 = self._________next_iteration(X_0, B, T, relax_factor);
        predecessor_norm = self.__getNorm(X_1 - X_0, p);
        X = X_0;
        qk = 1;

        nr_iteration = 0;
        while(qk * predecessor_norm > self.eps * (1 - q) * (1 - S)):
        #{
            nr_iteration += 1;
            X   = self._________next_iteration(X, B, T, relax_factor);
            qk *= q;
        #}

        print(f"Predecessor Gauss-Seidel iteration method ended after {nr_iteration} iterations", file=sys.stderr);
        return X;
    #}
    def __successor_iteration(self, X_0, B, T, S, q, p, relax_factor): #SD công thức sai số hậu nghiệm
    #{
        new_X = self._________next_iteration(X_0, B, T, relax_factor);
        old_X = X_0;

        nr_iteration = 0;
        while(q * self.__getNorm(new_X - old_X, p) > self.eps * (1 - q) * (1 - S)):
        #{
            nr_iteration += 1;
            old_X = new_X;
            new_X = self._________next_iteration(old_X, B, T, relax_factor);
        #}

        print(f"Successor Gauss-Seidel iteration method ended after {nr_iteration} iterations", file=sys.stderr);
        return new_X;
    #}


    # PP lặp Gauss-Seidel với chế độ đánh giá tiên nghiệm hoặc hậu nghiệm và cải tiến hệ số điều chỉnh
    def gauss_seidel_iteration(self, mode = 1, relax_factor = 1):
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

        # Tính T, B, q, S
        T = np.diag(1 / np.diag(A));
        B = E - T @ A;
        S = self.__get_S_coeff(B, p);
        q = self.__get_q_coeff(B, p);
        
        print(q, S, file=sys.stderr);

        # Đưa ra ma trận cuối cùng
        if(mode == 1): return self.__predecessor_iteration(A, B, T, S, q, p, relax_factor);
        return self.__successor_iteration(A, B, T, S, q, p, relax_factor);
    #}
#}


#===================================================================================
# Chương trình ví dụ

# # A = np.random.rand(3,3) * 1000;
# A = np.array([4, 0.24, -0.08, 0.09, 3, -0.15, 0.04, -0.08, 4]);
# # A = np.array([1, 0, 0, 0, 4, 0, 0, 0, 2]);
# A = np.reshape(A, (3, 3));

# # print(A);

# uu = gaussseidel_mat_inversion(A, 3, 1e-10);
# A1 = uu.gauss_seidel_iteration(1);
# print(A1);
# print(A1 @ A);

# A2 = uu.gauss_seidel_iteration(2);
# print(A2);
# print(A2 @ A);

# A3 = uu.gauss_seidel_iteration(1);
# print(A3);
# print(A3 @ A);

# A4 = uu.gauss_seidel_iteration(2);
# print(A4);
# print(A4 @ A);
