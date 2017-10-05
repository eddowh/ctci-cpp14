/**
 * Counting number of inversions (adjacent swaps) required to sort.
 *
 *   Author: Eddo W. Hintoso
 *   E-mail: eddo.hintoso+github@gmail.com
 */


#include <vector>
#include <iostream>

using namespace std;

long long inversions = 0;

/** \brief Merge two sorted subvectors into one sorted (sub)vector.
  *
  * This is intended to be used as a helper function, since it requires specifiying indices.
  *
  * \param v The sub(vector) to be sorted.
  * \param tmp An auxiliary vector used to store elements of merged vectors.
  * \param l_start The leftmost index of the (sub)vector to be sorted.
  * \param r_end The rightmost index of the (sub)vector to be sorted.
  */
void _merge_halves (vector<int>& v, vector<int>& tmp, int l_start, int r_end)
{
    int l_end = (r_end + l_start) / 2;
    int r_start = l_end + 1;
    int size = r_end - l_start + 1;

    int l = l_start;
    int r = r_start;
    int i = l_start;

    while (l <= l_end && r <= r_end) {
        if (v[l] <= v[r]) {
            tmp[i] = v[l];
            l += 1;
        }
        else {
            inversions += l_end - l + 1;
            tmp[i] = v[r];
            r += 1;
        }
        i += 1;
    }

    // remaining elements from left half
    int size_l = l_end - l + 1;
    for (int k = 0; k < size_l; k++) {
        tmp[i+k] = v[l+k];
    }

    // remaining elements from right half
    int size_r = r_end - r + 1;
    for (int k = 0; k < size_r; k++) {
        tmp[i+k] = v[r+k];
    }

    // update the the sublist so it's sorted!
    for (int k = 0; k < size; k++) {
        v[l_start + k] = tmp[l_start + k];
    }
}

/** \brief Sort a list using the mergesort algorithm.
  *
  * This is intended to be used as a helper function, since it requires specifiying indices.
  *
  * \param v The sub(vector) to be sorted.
  * \param tmp An auxiliary vector used to store elements of merged vectors.
  * \param l_start The leftmost index of the (sub)vector to be sorted.
  * \param r_end The rightmost index of the (sub)vector to be sorted.
  */
void _mergesort (vector<int>& v, vector<int>& tmp, int l_start, int r_end)
{
    if (l_start >= r_end) return;
    int mid = (l_start + r_end) / 2;
    _mergesort(v, tmp, l_start, mid);
    _mergesort(v, tmp, mid + 1, r_end);
    _merge_halves(v, tmp, l_start, r_end);
}

/** \brief Sort a list using the mergesort algorithm.
  *
  * \param v The vector to be sorted.
  *
  * \return The sorted vector.
  */
void mergesort (vector<int>& v)
{
    vector<int> tmp (v.size());
    _mergesort(v, tmp, 0, v.size() - 1);
}

/** \brief Count the number of inversions (adjacent swaps) required to sort a vector.
  *
  * \param v The vector to be sorted, and whose sorting will tally the number of inversions.
  *
  * \return The number of inversions required for the sort.
  */
long long count_inversions (vector<int> v)
{
    inversions = 0;
    mergesort(v);
    return inversions;
}

int main ()
{
    int t;
    cin >> t;
    for (int a0 = 0; a0 < t; a0++) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int arr_i = 0;arr_i < n;arr_i++) {
           cin >> arr[arr_i];
        }
        cout << count_inversions(arr) << endl;
    }
    return 0;
}

