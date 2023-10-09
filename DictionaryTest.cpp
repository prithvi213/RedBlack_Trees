/* Name: Prithvi Arunshankar
 * CruzID: parunsha
 * Assignment: pa8
*/
#include<string>
#include"Dictionary.h"


using namespace std;

int main() {
    Dictionary X, Y;
    X.setValue("a", 1);
    X.setValue("b", 5);
    X.setValue("e", 10);
    X.setValue("h", 15);
    X.setValue("f", 20);
    X.setValue("i", 200);
    X.begin();
    cout << X.currentKey() << endl;

    Y.setValue("i", 200);
    Y.setValue("f", 20);
    Y.setValue("h", 15);
    Y.setValue("e", 10);
    Y.setValue("b", 5);
    Y.setValue("a", 1);
    Y.begin();
    cout << Y.currentKey() << endl;

    string xStr = X.pre_string();
    string yStr = Y.pre_string();
    bool eqStr = (xStr == yStr);
    cout << eqStr << endl;
    cout << "X's pre string: " <<  X.pre_string();
    cout << "Y's pre string: " <<  Y.pre_string();

    Dictionary B;
    B.setValue("a", 1);
    B.setValue("b", 5);
    B.setValue("f", 34);
    cout << B.to_string();
    B.end();
    B.prev();
    B.prev();
    B.prev();
    cout << B.hasCurrent() << endl;

    Dictionary A;
    A.setValue("c", 3);
    A.setValue("a", 1);
    A.setValue("b", 2);
    cout << A.to_string();
    A.remove("a");
    cout << A.to_string();
    A.setValue("e", 5);
    cout << A.to_string();
    A.remove("c");
    cout << A.to_string();
    
    Dictionary D;
    D.setValue("l", 1);
    cout << D.to_string();
    D.setValue("a", 23);
    cout << D.to_string();
    D.setValue("m", 4);
    cout << D.to_string();
    D.setValue("b", 3);
    cout << D.to_string();
    D.setValue("0", 4);
    cout << D.to_string();
    D.setValue("d", 4);
    cout << D.to_string();
    D.setValue("e", 4);
    cout << D.to_string();
    D.setValue("k", 4);
    cout << D.to_string();
    D.setValue("q", 4);
    cout << D.to_string();
    D.setValue("s", 4);
    cout << D.to_string();
    D.setValue("t", 4);
    cout << D.to_string();

    D.remove("l");
    D.remove("q");
    D.remove("s");
    D.remove("t");
    D.remove("d");
    cout << D.to_string();
    cout << D.pre_string() << endl;
    cout << D.size() << endl;
    D.begin();
    cout << D.getValue("b") << endl;
    
    Dictionary E = D;
    E.remove("m");
    cout << E << endl;

    Dictionary F;
    F.setValue("a", 1);
    F.setValue("b", 5);
    F.setValue("c", 16);
    F.setValue("d", 176);
    F.setValue("e", 3214);
    F.begin();
    cout << F.currentKey() << endl;
    F.next();
    cout << F.currentKey() << endl;
    F.next();
    cout << F.currentKey() << endl;

    Dictionary G;
    G.setValue("a", 1);
    G.setValue("b", 5);
    G.setValue("e", 10);
    G.end();
    G.setValue("h", 15);
    G.setValue("f", 20);
    G.setValue("i", 100);
    G.end();
    cout << G.currentKey() << endl;
    G.prev();
    cout << G.currentKey() << endl;
    G.prev();
    cout << "current key: " << G.currentKey() << ", current value: " << G.currentVal() << endl;

    cout << G.pre_string() << endl;
    cout << G.to_string() << endl;

    Dictionary H;
    H.setValue("a", 1);
    H.setValue("b", 5);
    H.setValue("e", 10);
    H.setValue("h", 15);
    H.setValue("f", 20);
    H.setValue("i", 100);
    cout << H.to_string();
    H.begin();
    H.remove("a");

    bool has_a = H.hasCurrent();

    if(has_a) {
        cout << "Current exists: true" << endl;
    } else {
        cout << "Current exists: false" << endl;
    }

    H.clear();
    cout << "Size of H: " << H.size() << endl;
    A.clear();
    B.clear();
    D.clear();
    E.clear();
    F.clear();
    G.clear();
    X.clear();
    Y.clear();
}
