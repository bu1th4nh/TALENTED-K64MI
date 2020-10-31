import sympy as sym
import scipy as sci
import numpy as np
from math import *
import sys


#===================================================================================
# Phần thuật toán chính
class newton_mat_inversion:
#{
    max_attempt = 2;

    def __init__(self, A, n, eps):    # Khởi tạo
    #{
        self.A = np.reshape(np.array(A), (n, n));
        self.n = n;
        self.eps = eps;
        self.nr_iterations = 0;
    #}
    def norm(self, __A, __norm_type = 2):   # Chuẩn ma trận
    #{
        return np.linalg.norm(__A, __norm_type);
    #}
    def __refine_initial_approx(self):  # Tìm xấp xỉ đầu:
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
        while(attempt <= newton_mat_inversion.max_attempt):
        #{
            X = X @ (2 * E - A @ X);
            if(self.norm(E - A @ X) < 1): attempt += 1;
            self.nr_iterations += 1 * bool(attempt <= newton_mat_inversion.max_attempt);
        #}

        # Trả về ma trận xấp xỉ đầu
        return X;
    #}
    def __pure_newton(self, X_0):  # Lặp Newton nguyên bản
    #{

        # Gán các biến cơ bản
        norm_X0 = self.norm(X_0); # Do X_0 không đổi nên ta đặt 1 biến làm chuẩn của X_0
        E       = np.eye(self.n);
        A       = self.A;
        eps     = self.eps;
        

        # Bước 2 của thuật toán
        q2k = q = self.norm(E - A @ X_0);
        X = X_0;

        # Kiểm tra điều kiện hội tụ
        if(q >= 1):
        #{
            print("Xấp xỉ đầu không thỏa mãn nên không đưa ra được ma trận nghịch đảo.");
            return np.full((self.n, self.n), float("NaN"));
        #}


        # Lặp
        while(norm_X0 * q2k >= self.eps * (1 - q)):
        #{
            self.nr_iterations += 1;
            X = X @ (2 * E - A @ X);
            q2k = q2k ** 2
        #}

        # Đưa ra ma trận cuối cùng
        print(f"Newton iteration method ended after {self.nr_iterations} iterations", file=sys.stderr);
        return X;
    #}


    def improved_newton(self):  # PP Newton cải tiến với xấp xỉ đầu
    #{
        if(np.linalg.det(self.A) == 0):
        #{
            print("A không khả nghịch nên không đưa ra được ma trận nghịch đảo");
            return np.full((self.n, self.n), float("NaN"));
        #}
        return self.__pure_newton(self.__refine_initial_approx());
    #}
    def pure_newton(self, X_0):  # PP Newton nguyên bản
    #{
        if(np.linalg.det(self.A) == 0):
        #{
            print("A không khả nghịch nên không đưa ra được ma trận nghịch đảo");
            return np.full((self.n, self.n), float("NaN"));
        #}
        return self.__pure_newton(X_0);
    #}
#}


#===================================================================================
# Chương trình ví dụ
# A = np.random.rand(3,3);
# A = np.array([1, 3, 2, 7, 1, 9, 2, 5, 4]);
# A = np.reshape(A, (3, 3));
# uu = newton_mat_inversion(A, 3, 1e-10);
# A1 = uu.improved_newton();
# print(A1);
# print(A1 @ A);

# B = np.array([4, 0.24, -0.08, 0.09, 3, -0.15, 0.04, -0.08, 4]);
# B = np.reshape(B, (3, 3));
# vv = newton_mat_inversion(B, 3, 1e-10);
# B1 = vv.improved_newton();
# print(B1);
# print(B1 @ B);

# print(uu.A);
# print(vv.A);
