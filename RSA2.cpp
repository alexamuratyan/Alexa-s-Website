#include <iostream>
#include <assert.h>
#include <math.h>


using namespace std;

//1a) Implement Euclidean Algorithm for calculating greatest common diviser. Followed my own thinking
int EuclidAlgGCD (int a, int b) 
{
  if (a == 0) 
    return b; 
  return EuclidAlgGCD(b % a, a); 
}

//1b) Extended Euclidean Algorithm
// precondition: a >=b>=0 */
// postcondition: return d=gcd (a,b), s and t are set so that d=sa+tb*/
int ExtendedEuclidAlgGCD (int a, int b, int & s, int & t)
{
  if (a==0)
  {
      
      s=0;
      t=1; 
      return b;
  }

  int s1, t1;

  // when this returns,
  // s1*b + t1*(a%b = d)
  int d = ExtendedEuclidAlgGCD (b%a, a, s1, t1);

  int q = b/a;
  s = t1 - (q * s1);
  t = s1;
  assert (d == s * a + b * t);
  return d;
  
} 

// 2) Write a function that returns the inverse modulo.
// n>1, a is nonnegative 
// a <= n 
// a and n are relative prime to each other 
// return s such that a*s mod n is 1 
int inverse (int a, int n)
{
    int s, t; 
    int d = ExtendedEuclidAlgGCD (n, a, s ,t);
    

    if (d==1)
    {
        return(t%n); // t might be negative, use mod() to reduce to an integer between 0 and n-1 
    }
    else
    {
        cout <<"a,n are not relative privme!\n";
        
    }

    return 0;

}

//4) Write a function that returns a number that is relative prime with the given number
//return a integer that is relative prime with n, and greater than 1 
//i.e., the gcd of the returned int and n is . Note: Although gcd (n,n-1)=1, we don't want to return n-1. instead search for another relative prime of n, calling the GCD function of yours to test if the number is relatively prime with n 

int RelativePrime (int n) 
{
    int a = 3;
    int s;
    int t;


    if (ExtendedEuclidAlgGCD(n, 2, s, t) == 1)
        {
            return 2;
        }

    
    while(true)
    {
        if (ExtendedEuclidAlgGCD(n, a, s, t)== 1)
        {

            return a;
        }
        a+=2;
        
    }
}      

int exp(int x, int y)
{
    if (y == 0)
        return 1;
    if (y==1)
        return x;
    return (x* exp(x, y-1));
}

int mod (int a, int n)
{
  if (a>=0)
    return a%n;

  else 
    return a%n+n;  
}

// Return M^d mod PQ 
int encode (int M, int d, int PQ) 
{
    int pow = exp(M,d);
    return(mod(pow,PQ));
}    


//Return C^e mod PQ 
int Decode (int C, int e, int PQ)
{
    int pow = exp(C,e);
    return(mod(pow,PQ));
}


int main() 
{
    
  int a = 88, b = 11, s, t; 
    cout << "1a) Implement Euclidean Algorithm for calculating the greatest common divisor: GCD(" << a << ", " << b << ") = " << EuclidAlgGCD(a, b) << endl; 

    cout << "1b) Implement the extended Euclidean Algorithm to find not only the greatest common divisor of two integers, but also find the integer coefficients that expresses the gcd in terms of the integers: " << ExtendedEuclidAlgGCD(88, 11, s, t);
    cout<<"= "<<s <<"*"<< a<<" + "<<t <<"*"<< b<<endl;

    cout << "2) Finding the inverse modulo of (12,5) = " << inverse(12,5) << endl;

    cout << "4) Return a number that is relative prime to 12: " << RelativePrime(12) << endl;
    
    
    const int P=7;
    const int Q=5;
    int PQ = P * Q;
    int M1, C, d, e; 
    int x = (P-1) * (Q-1); 
    int M;

    d = RelativePrime(x);
    e = inverse(d,x);

    cout << "5) Practice with RSA algorithm. Enter an integer smaller than " <<PQ << endl;
    cin >> M,

    cout << "x : "<< x << endl;
    cout << "d: "<< d << endl;
    cout << "PQ: "<< PQ << endl;
    cout << "e : "<< e << endl;
    C = encode (M, d, PQ);
    cout << "C : "<< C << endl;
    M1 = Decode (C, e, PQ);
    cout << "M1 : "<< M1 << endl;
    assert(M==M1);
}
