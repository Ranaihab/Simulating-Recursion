#include <iostream>
#include<stack>
/**
 * 11422019479019
 */

using namespace std;
enum CallType {
    f, Af, BCf, RETURN
};

struct FCall {
    CallType type;
    int arg;
    int n;      // n and b      int a = n + f(n-1)
    int a;
};

int F(int n) {
    int Return;
    FCall call;
    call.type = f;
    call.arg = n;
    stack<FCall> s;
    s.push(call);

    while (!s.empty()) {
        call = s.top();
        s.pop();
        if (call.type == RETURN) {
            int d = Return;
            Return = call.a + call.n + d; // a+b+d; b = call.n
            continue;
        }
        if (call.type == Af)
        {
            int a = call.n + Return; // n+f(n-1), f(n-1) = Return, call.n + Return;
            s.top().a = a;
        }
        else if (call.type == BCf)
        {
            int b = call.n * Return;
            int c = call.n - 2 - (call.a + b) % 2; // F(c)
            s.top().a = call.a;
            s.top().n = b;
            call.arg = c;
        }
        if (call.arg <= 1) {
            Return = 1;
            continue;
        }

        FCall f1; // f(n-1)
        f1.type = f;
        f1.arg = call.arg - 1;

        FCall af;   // a = n + Return , f(n/2)
        af.type = Af;
        af.arg = call.arg / 2;
        af.n = call.arg;

        FCall bcf; // b = n * f(n/2), f(n/2) = Return
        // c = n - 2-(a+b)%2
        // f(c)
        bcf.type = BCf;
        bcf.n = call.arg;

        FCall ret; // d= f(c), f(c) = Return
        // return a+b+d
        ret.type = RETURN;

        s.push(ret);
        s.push(bcf);
        s.push(af);
        s.push(f1);

    }
    return Return;
}

int f1(int n) {
    if (n <= 1) return 1;
    int a = n + f1(n - 1);
    int b = n * f1(n / 2);
    int c = n - 2 - (a + b) % 2;
    int d = f1(c);
    return a + b + d;
}

int main() {
    cout << f1(1) << endl;
    cout << f1(2) << endl;
    cout << f1(3) << endl;
    cout << f1(4) << endl;
    cout << f1(5) << endl;
    cout << f1(6) << endl;
    cout << f1(7) << endl;
    cout << f1(8) << endl;
    cout << f1(9) << endl;
    cout << f1(10) << endl;
    cout << f1(11) << endl;
    cout << f1(12) << endl;
    cout << f1(13) << endl;
    cout << f1(14) << endl;
    cout << f1(15) << endl;
    cout << f1(16) << endl;
    cout << f1(17) << endl;
    cout << f1(18) << endl;
    cout << f1(19) << endl;
    cout << f1(20) << endl;
    cout << "--------------------------" << endl;
    cout << F(1) << endl;
    cout << F(2) << endl;
    cout << F(3) << endl;
    cout << F(4) << endl;
    cout << F(5) << endl;
    cout << F(6) << endl;
    cout << F(7) << endl;
    cout << F(8) << endl;
    cout << F(9) << endl;
    cout << F(10) << endl;
    cout << F(11) << endl;
    cout << F(12) << endl;
    cout << F(13) << endl;
    cout << F(14) << endl;
    cout << F(15) << endl;
    cout << F(16) << endl;
    cout << F(17) << endl;
    cout << F(18) << endl;
    cout << F(19) << endl;
    cout << F(20) << endl;
    return 0;
}
