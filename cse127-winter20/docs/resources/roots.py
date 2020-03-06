# CSE 127 helper functions

# The below code is taken from SymPy
# Used under fair-use.
# https://raw.githubusercontent.com/sympy/sympy/733da515a7638bba4e08be366bf24c996ad84a61/sympy/core/power.py

from math import sqrt, trunc, log as _log

def integer_nthroot(y, n):
    """
    Return a tuple containing x = floor(y**(1/n))
    and a boolean indicating whether the result is exact (that is,
    whether x**n == y).

    >>> from sympy import integer_nthroot
    >>> integer_nthroot(16,2)
    (4, True)
    >>> integer_nthroot(26,2)
    (5, False)

    """
    y, n = int(y), int(n)
    if y < 0:
        raise ValueError("y must be nonnegative")
    if n < 1:
        raise ValueError("n must be positive")
    if y in (0, 1):
        return y, True
    if n == 1:
        return y, True
    if n == 2:
        x = trunc(sqrt(y))
        rem = y - x*x
        return int(x), not rem
    if n > y:
        return 1, False
    # Get initial estimate for Newton's method. Care must be taken to
    # avoid overflow
    try:
        guess = int(y**(1./n) + 0.5)
    except OverflowError:
        exp = _log(y, 2)/n
        if exp > 53:
            shift = int(exp - 53)
            guess = int(2.0**(exp - shift) + 1) << shift
        else:
            guess = int(2.0**exp)
    if guess > 2**50:
        # Newton iteration
        xprev, x = -1, guess
        while 1:
            t = x**(n - 1)
            xprev, x = x, ((n - 1)*x + y//t)//n
            if abs(x - xprev) < 2:
                break
    else:
        x = guess
    # Compensate
    t = x**n
    while t < y:
        x += 1
        t = x**n
    while t > y:
        x -= 1
        t = x**n
    return x, t == y

import base64

def integer_to_base64(z):
    '''Converts an arbitrarily long integer to a big-endian base64 encoding'''
    s = ("%x"%z)
    s = (('0'*(len(s)%2))+s)
    s = bytes.fromhex(s)
    return base64.b64encode(s)


def integer_to_bytes(n):
    '''Converts an arbitrarily long integer to bytes, big-endian'''
    negative = True if n < 0 else False
    out = list()
    while n > 0:
        out.append(n & 0xFF)
        n >>= 8
    if not negative:
        out.append(0x00)
    return bytes(reversed(out))

def bytes_to_integer(b):
    '''Converts big-endian bytes to an arbitrarily long integer'''
    out = 0
    for digit in b:
        out <<= 8
        assert(digit >= 0)
        out += digit
        assert(out >= 0)
    return out

