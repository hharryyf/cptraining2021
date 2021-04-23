a = [0,0,0,4,7]
for i in range(5, 10001):
    a.append(a[i-1] + a[i-2])

while True:
    n = -1
    try:
        n = input()
        print(a[n])
    except EOFError:
        break
