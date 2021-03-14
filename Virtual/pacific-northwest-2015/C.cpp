n = int(input().strip())
orders = []
maxL = 0
for i in range(n):
    li = input().strip().split()
    li[0] = li[0][:-1]
    li = list(map(lambda x: -1 if x=="upper" else 0 if x=="middle" else 1 if x=="lower" else x,li))
    orders.append([li[1:-1],li[0]])
    maxL = max(maxL,len(li)-1)
for i in range(n):
    if len(orders[i][0]) < maxL:
        tem = [0]*(maxL-len(orders[i][0]))
        tem.extend(orders[i][0])
        orders[i][0] = tem
    orders[i][0] = orders[i][0][::-1]
orders.sort()
for i in range(n):
    # print(orders[i])
    print(orders[i][1])