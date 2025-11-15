/// Codeforces Hello 2024 D

#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define PII pair<ll,ll>
#define ff first
#define ss second
#define INF 10e17

void print_array(vector<ll> &a){
    ll n = a.size();
    for (ll i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << endl;
}
struct node{
    ll val;
    node *left, *right;
    node(ll v){
        val = v;
        left = nullptr;
        right = nullptr;
    }
};

struct cmp {
    bool operator() (const node *a, const node *b) const {
        return a->val < b->val;   //descending
    }
};

int main(){

    ll t;
    cin >> t;
    while (t--){
        ll x, n;
        cin >> n;
        priority_queue<node*, vector<node*>, cmp> P;
        cin >> x;
        node *newnode = new node(x);
        node *prevnode = newnode;
        P.push(newnode);

        /// FIRST BUILD THE PRIORITY QUEUE
        for (ll i = 1; i < n; i++){
            cin >> x;
            newnode = new node(x);
            newnode->left = prevnode;
            prevnode->right = newnode;
            prevnode = newnode;
            P.push(newnode);
        }

        bool deleted;
        node *currentnode;
        node *leftnode;
        node *rightnode;

        /* NOW KEEP POPPING THE LARGEST ELEMENT
        (2 valid cases,
         1. There is a good neighbor which is just 1 less than the element (Right or left)

         2. If a neighbor is equal, that means there is a chance. We can get rid of it and check for the neighbor;
         If ultimately neighbor works out, it will work out as well.
        EXCEPTION: If the only things we are left with, are the equal elements (no way to reduce now); that would happen if all are zeros.

        If they are all equal to some other number, no need to worry because ultimately that number will be the last left number
            and will fall in last check: LAST STANDING VALUE HAS TO BE ZERO
                                                 */
        while (P.size() != 1){
            currentnode = P.top();
            leftnode = currentnode->left;
            rightnode = currentnode->right;
            deleted = false;
            if (leftnode != nullptr){
                // if equal delete too (duplicates together do not matter)
                if (currentnode->val == (leftnode->val) + 1)
                    deleted = true;
            }
            if (rightnode != nullptr){
                if (currentnode->val == (rightnode->val) + 1)
                    deleted = true;
            }

            if (!deleted && currentnode->val != 0){
                if ((leftnode != nullptr && currentnode->val == leftnode->val) ||
                    (rightnode != nullptr && currentnode->val == rightnode->val ))
                    deleted = true;
            }

            if (deleted){
                if (leftnode != nullptr)
                    leftnode->right = rightnode;
                if (rightnode != nullptr)
                    rightnode->left = leftnode;

                P.pop();
            }
            else
                break;
        }
        currentnode = P.top();
        if (deleted && currentnode->val == 0)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
    return 0;
}
