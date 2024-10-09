import random
import time
import math

bv = {'1':1, '0':0}
ch = {1:'1', 0:'0'}

def addition(a, b):
    res = ''
    i = len(a)-1
    j = len(b)-1
    carry = 0
    while i >= 0 and j >= 0:
        d = ord(a[i])+ord(b[j])-2*ord('0')+carry
        carry = d//2
        d = d%2
        res += chr(ord('0')+d)
        i-=1
        j-=1
    
    while i >= 0:
        d = ord(a[i])-ord('0')+carry
        carry = d//2
        d = d%2
        res += chr(ord('0')+d)
        i-=1
    
    while j >= 0:
        d = ord(b[j])-ord('0')+carry
        carry = d//2
        d = d%2
        res += chr(ord('0')+d)
        j-=1
    
    if carry:
        res += '1'
    
    return res[::-1]

def subtraction(a, b):
    # assuming a >= b
    res = ''
    borrow = 0
    i, j = len(a)-1, len(b)-1
    
    while i >= 0 and j >= 0:
        dif = ord(a[i]) - ord(b[j]) - borrow
        if dif < 0:
            borrow = 1
            dif += 2
        else:
            borrow = 0
        res += chr(ord('0')+dif)
        i-=1
        j-=1

    while i >= 0:
        dif = ord(a[i]) - ord('0') - borrow
        if dif < 0:
            borrow = 1
            dif += 2
        else:
            borrow = 0
        res += chr(ord('0')+dif)
        i-=1
    
    return res[::-1]

def shift_left(a, k):
    a = a + '0'*k
    return a.lstrip('0') or '0'

def shift_right(a, k):
    return a[:-k] or '0'

def grade_school_multiplication(a, b):
    res = '0'
    b = b[::-1]
    for d in b:
        if d == '1':
            res = addition(res, a)
        a = shift_left(a, 1)
        
    return res

def divideat(x, k):
    if len(x) > k:
        return x[:-k], x[-k:]
    else:
        return '0', x

# KARATSUBA ALGORITHM
def karatsuba_multiplication(a, b):
    m, n = len(a), len(b)
    if m > n:
        return karatsuba_multiplication(b, a)
    
    # base case
    if m == 0:
        return '0'
    elif m == 1 and a[0] == '0':
        return '0'
    elif m == 1 and a[0] == '1':
        return b

    # divide step
    # write a as a1*2^n/2+a0
    # write b as b1*2^n/2+b0
    n = max(n, m)
    a1,a0 = divideat(a, n//2)
    b1,b0 = divideat(b, n//2)

    # conqure step
    a1plusa0 = addition(a1, a0)
    b1plusb0 = addition(b1, b0)
    p = karatsuba_multiplication(a1plusa0, b1plusb0)
    a1b1 = karatsuba_multiplication(a1, b1)
    a0b0 = karatsuba_multiplication(a0, b0)

    # combine step
    p = subtraction(p, addition(a1b1, a0b0))
    p = shift_left(p, n//2)
    p = addition(p, a0b0)
    a1b1 = shift_left(a1b1, 2*(n//2))
    return addition(p, a1b1)


def split_in_three(x, l):
    a, b, c = '0', '0', x
    if len(x) > l:
        b, c = x[:-l], x[-l:]
    if len(b) > l:
        a, b = b[:-l], b[-l:]
    
    return a.lstrip('0') or '0', b.lstrip('0') or '0', c.lstrip('0') or '0'

def divisionby3(x):
    x = x.lstrip('0')
    if len(x) == 0:
        return '0'

    res = ''
    y = 0
    for b in x:
        y = y * 2 + ord(b)-ord('0')
        if y >= 3:
            res += '1'
            y -= 3
        else:
            res += '0'
    
    return res.lstrip('0') or '0'

def multiply(a, b):
    return grade_school_multiplication(a, b)

def toom_cook_multiplication(A, B):
    A = A.lstrip('0') or '0'
    B = B.lstrip('0') or '0'
    m, n = len(A), len(B)
    if m > n:
        return toom_cook_multiplication(B, A)
    
    # base case
    if m == 0:
        return '0'
    elif m == 1 and A[0] == '0':
        return '0'
    elif m == 1 and A[0] == '1':
        return B
    elif min(m, n) < 6:
        return multiply(A, B)

    # divide
    n = max(n, m)
    a, b, c = split_in_three(A, n//3)
    d, e, f = split_in_three(B, n//3)

    # conqure
    # x = 0
    x0 = toom_cook_multiplication(c, f)

    # x = 1
    fx = addition(a, addition(b, c)) 
    gx = addition(d, addition(e, f))
    x1 = toom_cook_multiplication(fx, gx)

    # x = -1
    fx = subtraction(addition(a, c), b)
    gx = subtraction(addition(d, f), e)
    x2 = toom_cook_multiplication(fx, gx)

    # x = 2
    fx = addition(shift_left(a, 2), c)
    fx = addition(fx, shift_left(b, 1))
    gx = addition(shift_left(d, 2), f)
    gx = addition(gx, shift_left(e, 1))
    x3 = toom_cook_multiplication(fx, gx)

    # x = inf
    x4 = toom_cook_multiplication(a, d)

    # interpolation
    r0 = x0
    r2 = subtraction(shift_right(addition(x1, x2), 1), addition(x0, x4))
    r4 = x4
    r3 = addition(multiply('11', x0), x3)
    _r3 = addition(addition(multiply('11', x1), x2), multiply('1100', x4))
    r3 = shift_right(subtraction(r3, _r3), 1)
    r3 = divisionby3(r3)
    r1 = subtraction(shift_right(subtraction(x1, x2), 1), r3)

    # combine
    k = n // 3
    res = r4
    res = addition(shift_left(res,k), r3)
    res = addition(shift_left(res,k), r2)
    res = addition(shift_left(res,k), r1)
    res = addition(shift_left(res,k), r0)

    return res


def correctness_test(alg, max_num, test_count):
    failed = 0
    failed_cases = []
    for _ in range(test_count):
        ai = random.randint(0, max_num)
        bi = random.randint(0, max_num)
        resi = ai*bi
        
        abin = bin(ai)[2:]
        bbin = bin(bi)[2:]
        
        start_time = time.time()
        resbin = alg(abin, bbin)
        end_time = time.time()
        time_taken = end_time - start_time
        eqres = int(resbin, 2)

        if resi != eqres:
            failed+=1
            failed_cases.append([ai, bi, resi, abin, bbin, resbin, eqres])

    if failed:
        print('X:', failed)
        print(failed_cases)
    else:
        print('!')

def compare():
    tests = int(input())
    for test_no in range(tests):
        a = input()
        b = input()


        print('*************TEST', test_no, '*******************')
        print('Input size:', len(a))

        print('Execution time:')

        print('Grade school multiplication: ', end='')
        if len(a)*len(b) < 10000000:
            start_time = time.time()
            res = grade_school_multiplication(a, b)
            end_time = time.time()

            time_taken = int((end_time - start_time)*1000000)
            print(time_taken, 'ms')
        else:
            print('INF')

        print('Karatsuba multiplication: ', end='')
        if pow(len(a), math.log(3,2)) < 10000000:
            start_time = time.time()
            res = karatsuba_multiplication(a, b)
            end_time = time.time()

            time_taken = int((end_time - start_time)*1000000)
            print(time_taken, 'ms')
        else:
            print('INF')

        print('Toom cook multiplication: ', end='')
        if pow(len(a), math.log(5,3)) < 10000000:
            start_time = time.time()
            res = toom_cook_multiplication(a, b)
            end_time = time.time()

            time_taken = int((end_time - start_time)*1000000)
            print(time_taken, 'ms')
        else:
            print('INF')


if __name__ == "__main__":
    # compare()
    # correctness_test(multiply, int(1e18), 100)
    # correctness_test(karatsuba_multiplication, int(1e18), 100)
    correctness_test(toom_cook_multiplication, int(1e4), 10)