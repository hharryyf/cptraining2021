# not my code, implemented by Dallas
n,k=map(int,input().strip().split())
d,s=map(int,input().strip().split())
out = (n*d-k*s)/(n-k)
if 0 <= out <= 100:
    print(out)
else:
    print("impossible")