import math
(n, p, s, v) = tuple(input().split())
n = int(n)
p = float(p)
s = float(s)
v = float(v)
low, high = 1e-10, 70

def calc(c):
    return 1.0 * n * (math.log2(n))**(math.sqrt(2.0) * c) / (p * 1e9) + s * (1 + 1.0 / c) / v

for i in range(0, 400):
    midl = low + (high - low) / 3
    midr = high - (high - low) / 3
    if (midl > midr):
        continue
    if (calc(midl) <= calc(midr)):
        high = midr
    else:
        low = midl

ans = calc(low)

print(str(round(ans, 10)) + " " + str(round(low, 10)))
