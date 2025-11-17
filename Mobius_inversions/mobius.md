5.5 Mobius Function

1. Definition

The Mobius function $\mu(n)$ is a multiplicative function defined as:

$$\mu(n) = \begin{cases}
  1 & \text{if } n = 1 \\
  (-1)^k & \text{if } n \text{ is a product of } k \text{ distinct primes} \\
  0 & \text{if } n \text{ has a squared prime factor (i.e., is not square-free)}
\end{cases}$$

$\mu(6) = \mu(2 \cdot 3) = (-1)^2 = 1$

$\mu(7) = (-1)^1 = -1$

$\mu(12) = \mu(2^2 \cdot 3) = 0$

2. Fundamental Property (The "GCD Filter")

This is the most important identity for Mobius inversion. The sum of $\mu$ over all divisors of $n$ is $0$, unless $n=1$.

$$\sum_{d|n} \mu(d) = [n = 1]$$

This property is used to "filter out" all pairs except those with $\gcd=1$.

3. Mobius Inversion Formulas

This is the main tool. It lets you "invert" a function that is defined as a sum over its divisors or multiples.

Form 1: Divisor Sum (Standard)

If you know: $g(n) = \sum_{d|n} f(d)$

You can find $f(n)$: $f(n) = \sum_{d|n} \mu(d)g(n/d)$

Form 2: Multiple Sum (Dual / "Sum over Multiples")

If you know: $g(n) = \sum_{k=1, n|k} f(k)$

You can find $f(n)$: $f(n) = \sum_{k=1, n|k} \mu(k/n)g(k)$

Form 3: Divisor Block Sum (Common in CP)

If you know: $g(n) = \sum_{m=1}^n f(\lfloor n/m \rfloor)$

You can find $f(n)$: $f(n) = \sum_{m=1}^n \mu(m)g(\lfloor n/m \rfloor)$

4. Key Identities (Dirichlet Convolutions)

$\epsilon(n) = [n=1]$ (Identity element)

$\mathbf{1}(n) = 1$ (Constant 1 function)

$id(n) = n$ (Identity function)

These common relationships are just special cases of Mobius Inversion (Form 1):

$\epsilon = \mu * \mathbf{1} \quad \Longleftrightarrow \quad [n=1] = \sum_{d|n} \mu(d)$

$\phi = \mu * id \quad \Longleftrightarrow \quad \phi(n) = \sum_{d|n} \mu(d) \cdot \frac{n}{d}$

$id = \phi * \mathbf{1} \quad \Longleftrightarrow \quad n = \sum_{d|n} \phi(d)$

5. Sums with Multiplicative Functions

If $f$ is a multiplicative function:

$$\sum_{d|n} \mu(d)f(d) = \prod_{p \text{ prime, } p \mid n} (1 - f(p))$$

$$\sum_{d|n} \mu^2(d)f(d) = \prod_{p \text{ prime, } p \mid n} (1 + f(p))$$

6. Common ICPC Summation Problems

These are the most frequent applications you will see. They are used to solve "sum over all pairs" problems in $O(N \log N)$ or $O(N)$ with a sieve, or $O(\sqrt{N})$ per query if you precompute prefix sums.

Count Coprime Pairs ($i, j \le n$):

$$\sum_{i=1}^n \sum_{j=1}^n [\gcd(i, j) = 1] \quad = \quad \sum_{d=1}^n \mu(d) \lfloor n/d \rfloor^2$$

Sum of GCDs ($i, j \le n$):

$$\sum_{i=1}^n \sum_{j=1}^n \gcd(i, j) \quad = \quad \sum_{d=1}^n \phi(d) \lfloor n/d \rfloor^2$$
