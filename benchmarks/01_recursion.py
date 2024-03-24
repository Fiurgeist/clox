import time

def fib(n):
  if n < 2:
    return n
  return fib(n - 1) + fib(n - 2)


start = time.perf_counter()
print(fib(40))
print(time.perf_counter() - start)