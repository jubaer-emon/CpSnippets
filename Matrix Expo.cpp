#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

#define sz 5000
#define M 998244353
ll A[sz][sz];
ll mat[sz][sz];

void multiply(ll a[sz][sz], ll b[sz][sz], ll n)
{
    // Creating an auxiliary matrix to store elements
    // of the multiplication matrix
    ll mul[sz][sz];
    for (ll i = 0; i < n; i++)
    {
        for (ll j = 0; j < n; j++)
        {
            mul[i][j] = 0;
            for (ll k = 0; k < n; k++){
                ll tmp = (a[i][k]*b[k][j]) % M;
                mul[i][j] = (mul[i][j] + tmp) % M;
            }
        }
    }

    // storing the multiplication result in a[][]
    for (ll i=0; i<n; i++)
        for (ll j=0; j<n; j++)
            a[i][j] = mul[i][j];  // Updating our matrix
}

ll power(ll Q[sz][sz], ll n, ll p)
{
    if (p==1)
        return 0;

    power(Q, n, p/2);

    multiply(Q, Q, n);  // Q * Q

    if (p%2 != 0)
        multiply(Q, A, n);

    return Q[0][0];
}

int main() {
    //ios_base::sync_with_stdio(0);
    //cin.tie(0);

    ll n, m, k, x, y;
    cin >> n >> m >> k;

    for (ll i = 0; i < n; i++){
        for (ll j = 0; j < n; j++){
            A[i][j] = 1;
            mat[i][j] = 1;
        }
        A[i][i] = 0;
        mat[i][i] = 0;
    }


    for (ll i = 0; i < m; i++){
        cin >> x >> y;
        x--; y--;
        A[x][y] = A[y][x] = 0;
        mat[x][y] = mat[y][x] = 0;
    }

    cout << power(mat, n, k) << endl;
    return 0;
}
