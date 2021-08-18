# -*- coding: utf-8 -*-
"""
Created on Fri Jan 29 09:47:30 2021

@author: Grant
"""

import numpy as np
import math

n = 3
m = 2

c = np.array([[8.0, 10.0, 7.0]])

A = np.array([[1.0, 3.0, 2.0], [1.0, 5.0, 1.0]])

b = np.array([[10.0, 8.0]])

x = np.array([[8.0, 8.0, 6.0]])

s_new1 = np.array([[0.0, 0.0]])
for u2 in range(m):
    summation = 0.0
    for v2 in range(n):
        summation = summation + A[u2][v2] * x[0][v2]
    s_new1[0][u2] = abs(summation - b[0][u2])

s = s_new1

print(s)


#s = np.array([[2.0, 6.0]])

one = np.array([[1.0, 1.0]])

alpha = 1.0 / math.sqrt(m)

lambda_zero = 1 / math.exp(2)

l = 1 / math.exp(2)

k_limit = 10

k = 0

while k < k_limit:
    breaking = False
    while breaking == False:
        gradient_left = np.array([[0.0, 0.0, 0.0]])
        for a in range(n):
            gradient_left[0][a] = l * c[0][a]
    
        print(gradient_left)
    
        s_minus = np.array([[0.0, 0.0], [0.0, 0.0]])
        for r in range(m):
            s_minus[r][r] = 1 / s[0][r]
    
        gradient_right = np.dot(np.dot(A.T, s_minus), one.T)
    
        print(gradient_right)
    
        gradient = np.subtract(gradient_left, gradient_right.T)
    
        print(gradient)
    
    
    
        s_minus_minus = np.array([[0.0, 0.0], [0.0, 0.0]])
        for w in range(m):
            s_minus_minus[w][w] = 1 / (s[0][w])**2
    
        hessian = np.dot(np.dot(A.T, s_minus_minus), A)
    
        print(hessian)
    
        for u in range(n):
            for v in range(n):
                hessian[u][v] = 1 / hessian[u][v]
    
        print(np.linalg.pinv(hessian))
    
        hessian_inverse = np.linalg.pinv(hessian)
    
        subtraction = np.dot(hessian_inverse, gradient.T)
    
        print(subtraction)
    
        x_new = np.subtract(x, subtraction.T)
    
        print(x_new)
    
        s_new = np.array([[0.0, 0.0]])
        for u1 in range(m):
            summation = 0.0
            for v1 in range(n):
                summation = summation + A[u1][v1] * x_new[0][v1]
            s_new[0][u1] = abs(summation - b[0][u1])
            #s_new[0][u1] = summation - b[0][u1]
    
        print(s_new)   
        
        slack_sum = 0.0
        slack_sum_new = 0.0
        
        for e in range(n):
            if x_new[0][e] < 0:
                breaking = True
        
        """
        for y in range(m):
            slack_sum = slack_sum + s[0][y]
            slack_sum_new = slack_sum_new + s_new[0][y]
        
        if slack_sum_new > slack_sum:
            breaking = True
        """
        
        if breaking == True:
            break
        
        x = x_new
    
        s = s_new
    
    print()

    k = k + 1
    l = ((1 + alpha)**k) * lambda_zero

print(x)
print(s)