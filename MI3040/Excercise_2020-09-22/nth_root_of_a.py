# /*==========================================================================================*\
# **                        _           _ _   _     _  _         _                            **
# **                       | |__  _   _/ | |_| |__ | || |  _ __ | |__                         **
# **                       | '_ \| | | | | __| '_ \| || |_| '_ \| '_ \                        **
# **                       | |_) | |_| | | |_| | | |__   _| | | | | | |                       **
# **                       |_.__/ \__,_|_|\__|_| |_|  |_| |_| |_|_| |_|                       **
# \*==========================================================================================*/
#===================================================================================
# Libraries
import math
#import sys



#===================================================================================
# Global variable declaration
input_expr = 'x ** n - a';
global initialL;
global initialR;
global eps;
global sgn;
global a;
global n; 


#===================================================================================
# Functions and procedures
# Bisection Method for Roots Finding
def evaluate(x, evalString):
#{
    global n, a;
    return eval(evalString);
#}
def checkInputValidity(L, R, evalString):
#{
    #Check if a < b
    if(L > R): return 0;
    if(L == R and evaluate(L, evalString) != 0): return 0;

    #Check if f(a) * f(b) < 0
    fa = evaluate(L, evalString);
    fb = evaluate(R, evalString);
    if(fa * fb >= 0): return 0;
    
    return 1;
#}
def internal___bisectionMethod(initialLeftBound, initialRightBound, epsilon, evalString):
#{
    if(evaluate(initialLeftBound, evalString) == 0): return initialLeftBound;
    if(evaluate(initialRightBound, evalString) == 0): return initialRightBound;

    # Internal function 
    # Return root of f(x) = 0 which f(x), eps and range [a, b] are given.

    left  = initialLeftBound;
    right = initialRightBound;
    mid   = (left + right) / 2;
    lft_sign = 1 if evaluate(left, evalString) >= 0 else -1;


    while abs(right - left) >= epsilon:
    #{
        mid = (left + right) / 2;
        val = evaluate(mid, evalString);


        #print(left, mid, right, sep=',', file=sys.stderr)

        
        if(val == 0): return mid;
        if(val * lft_sign < 0):
            right = mid;
        else:
            left = mid;
    #}
    
    #print(left, mid, right, sep=',', file=sys.stderr)
    return mid;
#}


#--------------------------------------
# Solving Process
def checkSpecialCases():
#{
    global n, a, eps;

    if(n <= 0): 
    #{
        print("The solution does not exist due to n <= 0");
        return 0;
    #}
    if(n % 2 == 0 and a < 0):
    #{
        print("The solution does not exist in real number space");
        return 0;
    #}
    if(a == 1):
    #{
        print("The %d-th root of 1 is 1" % n);
        return 0;
    #}   
    if(a == 0):
    #{
        print("The %d-th root of 0 is 0" % n);
        return 0;
    #}

    return 1;
#}
def generateBounds():
#{
    global n, a, eps, sgn, initialL, initialR;

    sgn = 1;
    if(a < 0):
    #{
        sgn = -1;
        a = -a;
    #} 
    initialL = 0;
    initialR = max(1, a)+1;
#}
def computeOutput():
#{
    global n, a, eps, sgn, initialL, initialR;

    sol = sgn * internal___bisectionMethod(initialL, initialR, eps, input_expr);
    print("The %d-th root of %f is %f" % (n, a, sol));
#}


#--------------------------------------
# Wrapping functions
def EnterInput():
#{
    global n, a, eps;

    n = int(input("Please enter n = "));
    a = float(input("Please enter a = "));
    eps = float(input("Please enter error value eps = "));
#}
def Solve():
#{
    global n, a, eps, initialL, initialR, input_expr;

    if(checkSpecialCases() == 0): return;
    generateBounds();
    if(checkInputValidity(initialL, initialR, input_expr) == 0): return;
    computeOutput();
#}



#===================================================================================
# Main program
EnterInput();
Solve();