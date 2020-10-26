import sympy as sym
import scipy as sci
import numpy as np
from math import *
import sys


#===================================================================================
# Phần thuật toán chính
class newton_mat_inversion:
#{
    def __init__(self, A, n, eps):
    #{
        A = np.array(A);
        self.A = np.reshape(A, (n, n));
        self.n = n;
        self.eps = eps;
    #}
    def norm(self, __A, __norm_type = 2):
    #{
        return np.linalg.norm(__A, __norm_type);
    #}


    # PP Newton nguyên bản
    def pure_newton(self, X_0):
    #{
        # Gán các biến cơ bản
        norm_X0 = self.norm(X_0); # Do X_0 không đổi nên ta đặt 1 biến làm chuẩn của X_0
        E       = np.eye(self.n);
        A       = self.A;
        eps     = self.eps;

        # Bước 2 của thuật toán
        q = self.norm(E - A @ X_0);
        X = X_0;
        k = 0;

        # Lặp
        while(norm_X0 * (q ** (1 << k)) >= self.eps * (1 - q)):
        #{
            X = X @ (2 * E - A @ X);
            k = k + 1;
        #}

        # Đưa ra ma trận cuối cùng
        return X;
    #}

    # Tìm xấp xỉ đầu:
    def refine_initial_approx(self):
    #{
        # Gán các biến cơ bản
        E  = np.eye(self.n);
        A  = self.A;
        X  = self.A;
        
        # PP xấp xỉ đầu của Pan & Reif
        t1 = self.norm(X, 1);
        t2 = self.norm(X, inf);
        X  = (X / (t1 * t2)).T;

        # Hiệu chỉnh lại giá trị q của ma trận xấp xỉ đầu
        attempt = 0;
        max_attempt = 100;
        while(attempt <= max_attempt):
        #{
            X = X @ (2 * E - A @ X);
            if(self.norm(E - A @ X) < 1): attempt = attempt + 1;
        #}

        # Trả về ma trận xấp xỉ đầu
        return X;
    #}


    def improved_newton(self):
    #{
        return self.pure_newton(self.refine_initial_approx());
    #}
#}


#===================================================================================
# Chương trình ví dụ
A = np.random.rand(3,3);
A = np.array([1, 5, 2, 7, 6, 4, 0, 14, 2]);
A = np.reshape(A, (3, 3));
uu = newton_mat_inversion(A, 3, 1e-10);

print(uu.improved_newton());

