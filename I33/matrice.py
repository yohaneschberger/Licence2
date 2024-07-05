def gaussian_elimination_partial_pivot(A):
    n = len(A)
    m = len(A[0])
    i = 0
    for j in range(m):
        pivot = i
        for k in range(i,n):
            if abs(A[k][j]) > abs(A[pivot][j]):
                pivot = k
        if pivot != i:
            A[i], A[pivot] = A[pivot], A[i]
        pivot_value = A[i][j]
        for k in range(i+1, n):
            eliminator = A[k][j] / pivot_value
            A[k][j] = 0
            for l in range(j+1, m):
                A[k][l] -= eliminator * A[i][l]
        i += 1
    return A


A = [[1,2,3],[4,5,6],[7,8,9]]
print(gaussian_elimination_partial_pivot(A))
