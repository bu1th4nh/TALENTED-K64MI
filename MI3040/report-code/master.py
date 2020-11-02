from termcolor import colored
import sympy as sym
import scipy as sci
import numpy as np
from math import *
import sys



from gauss_seidel import *
from jacobian import *
from newton import *

n = 3;
factor = 1.25;
epsilon = 1e-14;

# A = np.random.rand(n,n)*1 + 1000 * np.eye(n);
A = np.reshape(np.loadtxt('input.txt'), (n, n));


print("=========================== welcome to The Matrix by bu1th4nh ===========================");
print("   ");
print(colored("                 ___.         ____  __  .__        _____        .__                      ", 'red'));
print(colored("                 \_ |__  __ _/_   |/  |_|  |__    /  |  |  ____ |  |__                   ", 'red'));
print(colored("                  | __ \|  |  \   \   __\  |  \  /   |  |_/    \|  |  \                  ", 'red'));
print(colored("                  | \_\ \  |  /   ||  | |   Y  \/    ^   /   |  \   Y  \                 ", 'red'));
print(colored("                  |___  /____/|___||__| |___|  /\____   ||___|  /___|  /                 ", 'red'));
print(colored("                      \/                     \/      |__|     \/     \/                  ", 'red'));
print("   ");


iA = np.linalg.inv(A);
uu = newton_mat_inversion(A, n, epsilon);
vv = jacobi_mat_inversion(A, n, epsilon);
ww = gaussseidel_mat_inversion(A, n, epsilon);
print("======================================= Ma trận A =======================================");
print(A);
print("------Kiểm tra: Hàm nội bộ của Python------");
print(iA);
print("===================================== Newton Method =====================================");
A1 = uu.improved_newton();
print(colored(A1, 'red'));
print("--------------Kiểm tra ngược--------------");
print(colored(A @ A1, 'blue'));
print(f'Error: {np.linalg.norm(A1 - iA)}');
print("===================================== Jacobi Method =====================================");
B1 = vv.jacobi_iteration(1);
print(colored(B1, 'red'));
print("--------------Kiểm tra ngược--------------");
print(colored(A @ B1, 'blue'));
print(f'Error: {np.linalg.norm(B1 - iA)}');
B2 = vv.jacobi_iteration(2);
print(colored(B2, 'red'));
print("--------------Kiểm tra ngược--------------");
print(colored(A @ B2, 'blue'));
print(f'Error: {np.linalg.norm(B2 - iA)}');
print("================================== Gauss-Seidel Method ==================================");
C1 = ww.gauss_seidel_iteration(1);
print(colored(C1, 'red'));
print("--------------Kiểm tra ngược--------------");
print(colored(A @ C1, 'blue'));
print(f'Error: {np.linalg.norm(C1 - iA)}');
C2 = ww.gauss_seidel_iteration(2);
print(colored(C2, 'red'));
print("--------------Kiểm tra ngược--------------");
print(colored(A @ C2, 'blue'));
print(f'Error: {np.linalg.norm(C2 - iA)}');
print(f"=============== SOR Improvement Method with relaxation factor = {factor} ===============");
D1 = ww.gauss_seidel_iteration(1, factor);
print(colored(D1, 'red'));
print("--------------Kiểm tra ngược--------------");
print(colored(A @ D1, 'blue'));
print(f'Error: {np.linalg.norm(D1 - iA)}');
D2 = ww.gauss_seidel_iteration(2, factor);
print(colored(D2, 'red'));
print("--------------Kiểm tra ngược--------------");
print(colored(A @ D2, 'blue'));
print(f'Error: {np.linalg.norm(D2 - iA)}');