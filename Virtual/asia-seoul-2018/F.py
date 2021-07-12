# not my code, Dallas coded it in contest
s = input().strip()
alph = [chr(x) for x in range(ord('a'),ord('z')+1)]
ops = ['+', '-', '*', '/', '%']
paren = ['(', ')']
prev_op = False
prev_alph = False
num_parens = 0
bad = False
for c in s:
    if not (c in alph or c in ops or c in paren):
        continue
    if c == '(':
        if prev_alph and not prev_op:
            bad = True
            break
        num_parens += 1
        prev_alph = False
        prev_op = False
    elif c == ')':
        if num_parens < 1 or prev_op or not prev_alph:
            bad = True
            break
        num_parens -= 1
        prev_alph = True
        prev_op = False
    elif c in ops:
        if prev_op or not prev_alph:
            bad = True
            break
        prev_op = True
        prev_alph = False
    elif c in alph:
        if prev_alph:
            bad = True
            break
        prev_alph = True
        prev_op = False
if num_parens != 0 or prev_op:
    bad = True
if bad:
    print('error')
    exit(0)

def rec(index):
    global s, alph, ops, paren
    i = index
    op_count = 0
    alph_count = 0
    while i < len(s):
        c = s[i]
        if not (c in alph or c in ops or c in paren):
            i += 1
            continue
        if c == '(':
            i = rec(i+1)
            if i < 0:
                return i
            alph_count += 1
        elif c == ')':
            if op_count == 1 and alph_count == 2:
                return i
            return -1
        elif c in ops:
            op_count += 1
        elif c in alph:
            alph_count += 1
        i += 1
    if (op_count == 1 and alph_count == 2):
        return i
    return -1
if rec(0) != -1:
    print('proper')
else:
    print('improper')