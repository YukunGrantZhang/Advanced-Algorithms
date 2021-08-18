# -*- coding: utf-8 -*-
"""
Created on Thu Jan 28 09:58:18 2021

@author: Grant
"""

import numpy as np
import math

c = np.array([8.0, 10.0, 7.0])

A = np.array([[1.0, 3.0, 2.0], [1.0, 5.0, 1.0]])

AK = np.array([[1.0, 0.0, 0.0], [0.0, 1.0, 1.0], [0.0, 1.0, 1.0]])

limit = np.array([10.0, 8.0])

ak = np.array([[2.0, 2.0, 2.0]])

m = 2
n = 3

feasibility = False

while (feasibility == False):
    check_ak_p = np.dot(A, ak.T)
    
    feasibility = True
    for a in range(m):
        if check_ak_p[a] > limit[a]:
            feasibility = False
    
    b_numerator = np.dot(AK, c)
    b_denominator = np.dot(np.dot(c.T, AK), AK)
    b = np.divide(b_numerator, b_denominator)
    
    b_matrix = np.array([b])
    
    ak_right = b
    
    for d in range(n):
        ak_right[d] = (1 / (n + 1)) * ak_right[d]
    
    ak = np.subtract(ak, ak_right)
    
    AK_right = np.dot(b_matrix.T, b_matrix)
    
    for g in range(n):
        for h in range(n):
            AK_right[g][h] = (2 / (n + 1)) * AK_right[g][h]
    
    AK_brackets = np.subtract(AK, AK_right)
    
    for i in range(n):
        for j in range(n):
            AK[i][j] = (n**2 / (n**2 - 1)) * AK_brackets[i][j]

print(ak)
print(AK)
    