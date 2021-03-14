T = input()
T = int(T)

ops = ['+','*','-','=']
 
def solve(st):
    for i in range(0, 10):
        if str(i) not in st:
            ss = st.replace("?", str(i))
            wl = ss.split()
            bad = False
            for j in range(len(wl)):
                if len(wl[j]) and wl[j][0] not in ops:
                    if len(wl[j]) > 1 and wl[j][0] == '0':
                        bad = True
                        break
                    wl[j] = str(int(wl[j]))
            if bad:
                continue
            ss = ''.join(wl)
            if eval(ss) == True:
                return i
    return -1
 
while T > 0:
    s = input()
    s = s.replace("=", " == ")
    s = s.replace('+',' + ')
    s = s.replace('-', ' - ')
    s = s.replace('*', ' * ')
    print(solve(s))
    T -= 1