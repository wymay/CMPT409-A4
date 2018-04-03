#include <iostream>
#include "math.h"

using namespace std;

#define MAXINPUT 65001
int primer[MAXINPUT] = {0};

bool testFermatOneEquation( int n, int a ){
    int res = 1;
    int exp = n;
    unsigned long long int base = a;
    base %= n;
    while( exp > 0 ){
        if( exp & 1 ) res = ( res * base ) % n;
        base = ( base * base ) % n;
        exp >>= 1;
    }
    if ( res == a ) return true;
    return false;
}

bool testFermatFullEquation( int n ){
    for( int i = 2; i < n; i++ ){
        if( !testFermatOneEquation( n, i ) ){
            cout << n << " is normal." << endl;
            return false;
        }
    }
    return true;
}

void updatePrimeTable(){
    int checkPoint = floor( sqrt( MAXINPUT ) );
    int i = 2;
    while( i <= checkPoint ){
        primer[i] = 1;
        for( int j = 2 * i; j <= MAXINPUT; j = j + i ){
            primer[j] = 2;
        }
        while( primer[i] != 0 ){
            i++;
        }
    }
} 

bool isPrimer( int n ){
    if( primer[n] == 2 ){
        return false;
    } else{
        return true;
    }
}

int main(){
    int n;
    cin >> n;
    updatePrimeTable();
    while( n != 0 ){
        if( isPrimer( n ) ){
            cout << n << " is normal." << endl;
        } else {
            if( testFermatFullEquation( n ) ){
                cout << "The number " << n << " is a Carmichael number." << endl;
            }
        }
        cin >> n;
    }
    return 0;
}