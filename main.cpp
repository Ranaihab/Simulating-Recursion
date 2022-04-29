#include <iostream>
#include<stack>
using namespace std;
/**
 * Rana Ihab Ahmed      20190207
 * Amal Mohamed         11422019479019
 */

// Original Recursive Function
int F(int n)
{
    if(n<=1) return 1;
    int a=n+F(n-1);
    int b=n*F(n/2);
    int c=n-2-(a+b)%2;
    int d=F(c);
    return a+b+d;
}

// The function would be divided into 4 parts that's why we have 4 call types
enum CallType {f, Af, BCf, RETURN};

// Struct to encapsulate the function call of the function f
struct FCall
{
    CallType type;  // to decide which part we are doing now
    int arg;        // argument passed to parameter, used in f, Af, BCf
    int n;          // n which will be used in Af and BCF to compute a and b respectively and used as b in RETURN to compute the return value
    int a;          // value of a which will be used in BCf to compute c and in RETURN to compute the return value
};

// Non Recursive Function
int iterativeF(int n)
{
    int Return;     // will hold the return value after each call of function
    FCall call;     // encapsulate the whole subprogram
    call.type = f;  // since this call will only divide the subprogram into parts (as if calling them recursively), its type will be f
    call.arg = n;   // initialize the argument of call with the passed parameter n
    stack<FCall> s; // stack that will hold the unprocessed parts of the subprogram calls
    s.push(call);   // add the whole subprogram call to the stack

    while (!s.empty()) // while there still exists unprocessed parts in the stack
    {
        call = s.top(); // get the part at the top of the stack so it would be processed
        s.pop();        // remove what is on the top of the stack as it will be processed during this iteration

        if (call.type == RETURN) // calculate the value of d and the return value
        {
            int d = Return; // d = F(c), and F(c) is the return value from the previous executed part
            Return = call.a + call.n + d; // return a+b+d; b = call.n, a = call.a
            continue; // it already returned from the function so it would not execute the parts after the if which will divide the subprogram call into parts
        }
        if (call.type == Af) // execute the part which will compute a and the function call F(n/2), F(n/2) would be executed outside the if condition hence no continue;
        {
            int a = call.n + Return; // a = n + F(n-1), Return = F(n-1) (assigned from previous iteration), call.n + Return;
            s.top().a = a;           // update a of the next call(BCf)
        }
        else if (call.type == BCf)  // execute the part which will compute b, c and the function call F(c), F(c) would be executed outside the if condition hence no continue;
        {
            int b = call.n * Return;    // b = n * F(n/2), Return = F(n/2) (assigned from previous iteration), call.n * Return;
            int c = call.n - 2 - (call.a + b) % 2; // c = n - 2 - (a+b)%2
            s.top().a = call.a;     // update a of the next call(RETURN)
            s.top().n = b;          // update b of the next call(RETURN)
            call.arg = c;           // update arg of this call
        }
        // compute calls to the Function F. f, Af, BCf will all compute this part
        if (call.arg <= 1)  // base case of F
        {
            Return = 1;     // assign the return value
            continue;       // return from the function
        }
        // F(n-1)
        FCall f1;
        f1.type = f;
        f1.arg = call.arg - 1;

        // a = n + F(n-1) (would not compute F(n-1) here) , f(n/2)
        FCall af;
        af.type = Af;
        af.arg = call.arg / 2;
        af.n = call.arg;

        // b = n * f(n/2) (would not compute F(n/2) here) , c= n - 2 - (a+b)%2, F(c)
        FCall bcf;
        bcf.type = BCf;
        bcf.n = call.arg;

        // d = F(c) (would not compute F(c) here), return a+b+d
        FCall ret;
        ret.type = RETURN;

        // push all parts to the stack in reverse order
        s.push(ret);
        s.push(bcf);
        s.push(af);
        s.push(f1);

    }
    return Return;
}

int main()
{
    // Test Cases, from 1 to 20
    for(int i = 1; i < 21; i++)
        cout << "F(" << i << "): " << F(i) << ", iterativeF(" << i << "): " << iterativeF(i) << endl; // print values of recursive and iterative calls of function
    return 0;
}
