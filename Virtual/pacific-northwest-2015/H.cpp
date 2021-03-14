n,S = map(int,input().strip().split())
max_iter = 100
sorting = []
for i in range(n):
    x,y,st = input().strip().split()
    x = float(x)
    y = float(y)
    curS = S
    tem = [0]*max_iter
    for j in range(max_iter):
        # print(curS,x,y)
        if x > curS/2:
            if y > curS/2:
                tem[j] = 2
                x -= curS/2
                y -= curS/2
                temx = x
                x = y
                y = temx
            else:
                tem[j] = 3
                x -= curS
                y -= curS/2
                x = -x
                y = -y
        elif y > curS/2:
            tem[j] = 1
            y -= curS/2
            temx = x
            x = y
            y = temx
        else:
            tem[j] = 0
        curS /= 2
        temx = x
        x = y
        y = temx
    sorting.append([tem,st])
sorting.sort()
for i in range(n):
    print(sorting[i][1])