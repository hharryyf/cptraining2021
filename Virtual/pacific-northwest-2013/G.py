li = [1, 1, 2, 4]
for i in range(4, 69):
    li.append(li[-1] + li[-2] + li[-3] + li[-4])
T = int(input())
while T > 0:
    v = int(input())
    print(li[v])
    T -= 1