# implemented by Dallas in contest, not my code
combs = [[0,1],[0,2],[0,3],[1,2],[1,3],[2,3]]
cur_res = [0,0,0,0]
results = [[3,0],[0,3],[1,1]]
out = {}
def recurse(cur_ind):
    if cur_ind >= len(combs):
        ouf = ''.join(list(map(str,cur_res)))
        if ouf in out:
            out[ouf] += 1
        else:
            out[ouf] = 1
        return
    for res in results:
        cur_res[combs[cur_ind][0]] += res[0]
        cur_res[combs[cur_ind][1]] += res[1]
        recurse(cur_ind+1)
        cur_res[combs[cur_ind][0]] -= res[0]
        cur_res[combs[cur_ind][1]] -= res[1]
    return
recurse(0)
# print(out)
T = int(input().strip())
for casen in range(1,T+1):
    abcd = list(map(int,input().strip().split()))
    abcd.sort()
    abcd = ''.join(list(map(str,abcd)))
    print("Case #"+str(casen)+": ",end="")
    # print(abcd)
    if not (abcd in out):
        print("Wrong Scoreboard")
    elif out[abcd] > 1:
        print("No")
    else:
        print("Yes")