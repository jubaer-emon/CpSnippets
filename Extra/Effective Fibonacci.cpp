
// [Fn+1] = [1 1][ Fn ] = [1 1]^n [F1]
// [ Fn ]   [1 0][Fn-1] = [1 0]   [F0]
//
// [Fn+1  Fn ] = [1 1]^n
// [ Fn  Fn-1]   [1 0]
ll fibb(ll n) {
    vvl mat({
        {1,1},
        {1,0}});
    return pwr(mat,n)[0][1];
}
