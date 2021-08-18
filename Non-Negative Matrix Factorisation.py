# -*- coding: utf-8 -*-
"""
Created on Mon Jan 25 10:11:05 2021

@author: Grant
"""

import numpy as np

n = 5
m = 6
k = 3

V = np.array([[4.0, 9.0, 11.0, 2.0, 4.0, 5.0], [5.0, 9.0, 21.0, 5.0, 7.0, 5.0], [4.0, 6.0, 15.0, 4.0, 5.0, 4.0],
			   [12.0, 29.0, 19.0, 2.0, 8.0, 17.0], [9.0, 22.0, 21.0, 3.0, 8.0, 12.0]])

W = np.array([[1.0, 1.0, 2.0], [2.0, 1.0, 3.0], [1.0, 1.0, 3.0], [1.0, 5.0, 1.0], [2.0, 1.0, 1.0]])

H = np.array([[1.0, 3.0, 6.0, 1.0, 1.0, 1.0], [2.0, 5.0, 1.0, 1.0, 1.0, 3.0], [2.0, 1.0, 3.0, 1.0, 3.0, 2.0]])

limit = 100

for t in range(limit):
    numerator_matrix1 = np.dot((W.T), V)
    denominator_matrix1 = np.dot(np.dot(W.T, W), H)
    
    H_NEW = H
    
    for a in range(k):
        for b in range(m):
            previous_h = H[a][b]
            
            numerator = numerator_matrix1[a][b]
            
            denominator = denominator_matrix1[a][b]
            
            temp1 = H[a][b] * numerator_matrix1[a][b] / denominator_matrix1[a][b]
            
            H_NEW[a][b] = temp1
    
    numerator_matrix2 = np.dot(V, H_NEW.T)
    denominator_matrix2 = np.dot(np.dot(W, H_NEW), H_NEW.T)
    
    W_NEW = W
    
    for c in range(n):
        for d in range(k):
            previous_w = W[c][d]
            
            numerator = numerator_matrix2[c][d]
            
            denominator = denominator_matrix2[c][d]
            
            temp2 = previous_w * numerator / denominator
            
            W_NEW[c][d] = temp2
    
    H = H_NEW
    W = W_NEW

print(W)
print()
print(H)
print()
print(np.dot(W, H))
    
            