/* 
 * C++ Program to Implement Solovay-Strassen Primality Test
 */
#include <cstring>
#include <iostream>
#include <cstdlib>
#define ll long long
using namespace std;
/* 
 * modular exponentiation
 */
ll modulo(ll base, ll exponent, ll mod)
{
    ll x = 1;
    ll y = base;
    while (exponent > 0)
    {
        if (exponent % 2 == 1)
            x = (x * y) % mod;
        y = (y * y) % mod;
        exponent = exponent / 2;
    }
    return x % mod;
}
/* 
 * calculates Jacobian(a/n) n>0 and n is odd 
 */
int calculateJacobian(ll a,ll n)
{
    if (!a) 
        return 0;
    int ans = 1;
    ll temp;
    if (a < 0)
    {
        a = -a;
        if (n % 4 == 3) 
            ans=-ans; 
    }
    if (a == 1) 
        return ans;
    while (a)
    {
        if (a < 0)
        {
            a = -a;
            if (n % 4 == 3) 
                ans = -ans;  
        }
        while (a % 2 == 0)
        {
            a = a / 2;
            if (n % 8 == 3 || n % 8 == 5) 
                ans = -ans;    
        }
        swap(a, n);
        if (a % 4 == 3 && n % 4 == 3) 
            ans = -ans;
        a = a % n;
        if (a > n / 2) 
            a = a - n; 
    }
    if (n == 1) 
        return ans;
    return 0; 
}
 
/* 
 * Solovay-Strassen Primality Test
 * Iterations determine the accuracy of the test 
 */
bool Solovoy(ll p, int iteration)
{
    if (p < 2) 
        return false;
    if (p != 2 && p % 2 == 0) 
        return false;
    for (int i = 0; i < iteration; i++)
    {
        ll a = rand() % (p - 1) + 1;
        ll jacobian = (p + calculateJacobian(a, p)) % p;
        ll mod = modulo(a, (p - 1) / 2, p);
        if (!jacobian || mod != jacobian)
        { 
            return false;
        }
    }
    return true;
}
//Main
int main()
{
    int iteration = 50;
    ll num;
    cout<<"Enter integr to test primality: ";
    cin>>num;
    if (Solovoy(num, iteration))
        cout<<num<<" is prime"<<endl;
    else
        cout<<num<<" is not prime"<<endl;
    return 0;
}