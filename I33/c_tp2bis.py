import math

def add(x,y):
    return [(x[0]+y[0]) % 5, (x[1]+y[1])%5]

def multbyalpha(x):
    return [3*x[1] % 5, (x[0]+x[1])%5]

def mult(x,y):
    return [(x[0]*y[0]+3*x[1]*y[1]) % 5, (x[0]*y[1]+x[1]*y[0]+x[1]*y[1])%5]


def est_combinaison_lineaire(x,c,V):
    oncontinue = True
    i = 0
    while i < len(x) and oncontinue:
        s = 0
        for j in range(len(c)):
            s += c[j]*V[j][i]
        oncontinue = (s == x[i])
        i+=1
    return oncontinue

def norme(V):
	somme = 0
	for j in V:
		somme = somme + abs(j)
	return somme

def norme2(V):
	somme = 0
	for j in V:
		somme = somme + j*j
	return math.sqrt(somme)

def norme3(V):
    maxi = 0
    for j in V:
        if abs(j) > maxi:
            maxi = abs(j)
    return maxi