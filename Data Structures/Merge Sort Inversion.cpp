ll merge(vector<ll> &arr, vector<ll> &temp, ll left, ll mid, ll right) {
    ll i = left, j = mid, k = left;
    ll inv_count = 0;

    while (i <= mid - 1 && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inv_count += (mid - i);  // all remaining in left half are > arr[j]
        }
    }

    while (i <= mid - 1)
        temp[k++] = arr[i++];
    while (j <= right)
        temp[k++] = arr[j++];

    for (ll idx = left; idx <= right; idx++)
        arr[idx] = temp[idx];

    return inv_count;
}

ll _mergeSort(vector<ll> &arr, vector<ll> &temp, ll left, ll right) {
    ll inv_count = 0;
    if (right > left) {
        ll mid = (left + right) / 2;

        inv_count += _mergeSort(arr, temp, left, mid);
        inv_count += _mergeSort(arr, temp, mid + 1, right);
        inv_count += merge(arr, temp, left, mid + 1, right);
    }
    return inv_count;
}

ll mergeSort(vector<ll> &arr) {
    vector<ll> temp(arr.size());
    return _mergeSort(arr, temp, 0, arr.size() - 1);
}