# not my code, Dallas coded it in contest
n = int(input().strip())
for i in range(n):
    s = input().strip()
    if s.endswith('a'):
        s += 's'
    elif s.endswith('i') or s.endswith('y'):
        s = s[:-1]+'ios'
    elif s.endswith('l'):
        s += 'es'
    elif s.endswith('n'):
        s = s[:-1]+'anes'
    elif s.endswith('ne'):
        s = s[:-2]+'anes'
    elif s.endswith('o'):
        s += 's'
    elif s.endswith('r'):
        s += 'es'
    elif s.endswith('t'):
        s += 'as'
    elif s.endswith('u'):
        s += 's'
    elif s.endswith('v'):
        s += 'es'
    elif s.endswith('w'):
        s += 'as'
    else:
        s += 'us'
    print(s)