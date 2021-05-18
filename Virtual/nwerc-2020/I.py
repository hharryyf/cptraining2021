# not my code, implemented by Dallas
n = int(input().strip())
d = list(map(int,input().strip().split()))
t = []
for i in range(3):
    t.append(list(map(int,input().strip().split())))
spotRanges = [[[[0,0] for y in range(n)] for z in range(n)] for x in range(3)]
for i in range(3):
    for j in range(n):
        spotRanges[i][j][j][1] = t[i][j]
        for k in range(1,n):
            spotRanges[i][j][(j+k)%n][0] = spotRanges[i][j][(j+k-1)%n][1] + d[(j+k-1)%n]
            spotRanges[i][j][(j+k)%n][1] = spotRanges[i][j][(j+k)%n][0] + t[i][(j+k)%n]
properRanges = [[[[-1,-1] for y in range(n)] for z in range(3)] for x in range(3)]
for i in range(3):
    for j in range(3):
        if (i>=j):
            continue
        for k in range(n):
            start = 0
            end = 0
            for l in range(1,n):
                good = True
                for m in range(n):
                    aRange = spotRanges[i][k][m]
                    bRange = spotRanges[j][(k+l)%n][m]
                    if (bRange[0] <= aRange[0] < bRange[1] or aRange[0] <= bRange[0] < aRange[1]):
                        good = False
                        break
                if good:
                    if start == 0:
                        start = l
                    end = l
            if start:
                properRanges[i][j][k][0] = (k+start)%n
                properRanges[i][j][k][1] = (k+end)%n
def interTwo(x,y):
    if x[0] == -1 or y[0] == -1:
        return -1
    z = [max(x[0],y[0]),min(x[1],y[1])]
    # print(x,y,z)
    if z[1] >= z[0]:
        return z[0]
    return -1
def intersect(startA,startB):
    aRange = properRanges[0][2][startA]
    if aRange[0] == -1:
        return -1
    if aRange[1] < aRange[0]:
        aBel = [aRange[0],n-1]
        aAb = [0,aRange[1]]
    else:
        aBel = [aRange[0],aRange[1]]
        aAb = [-1,-1]
    bRange = properRanges[1][2][startB]
    if bRange[0] == -1:
        return -1
    if bRange[1] < bRange[0]:
        bBel = [bRange[0],n-1]
        bAb = [0,bRange[1]]
    else:
        bBel = [bRange[0],bRange[1]]
        bAb = [-1,-1]
    return max(
        [interTwo(aBel,bBel),interTwo(aBel,bAb),interTwo(aAb,bBel),interTwo(aAb,bAb)]
    )
for i in range(n):
    aRange = properRanges[0][1][i]
    if aRange[1] < aRange[0]:
        aBel = [aRange[0],n-1]
        aAb = [0,aRange[1]]
    else:
        aBel = [aRange[0],aRange[1]]
        aAb = [-1,-1]
    for j in range(n):
        if (i==j):
            continue
        if not (aBel[0] <= j <= aBel[1] or aAb[0] <= j <= aAb[1]):
            continue
        c = intersect(i,j)
        if c != -1:
            print(i+1,j+1,c+1)
            exit(0)
print("impossible")