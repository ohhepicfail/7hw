#include <iostream>
#include <cassert>


struct smth {
    int x_ ,y_;
    smth () = default;
    smth (int x, int y) : x_ (x), y_ (y) {}
    bool operator <= (const smth& that) { return x_ <= that.x_; }
};


template <typename T> T
kth_statistic (T* arr, unsigned narr, unsigned k);

template <typename T> void
merge_sort (T* arr, unsigned beg, unsigned end);


int main () {
    unsigned ndata = 4;
    smth data[] { {0,1}, {1,2}, {0,2}, {1,3} };

    for (unsigned i = 0; i < ndata; i++)
        std::cout << data[i].x_ << " " << data[i].y_ << std::endl;

    kth_statistic (data, ndata, 0);
    for (unsigned i = 0; i < ndata; i++)
        std::cout << i << " (" << data[i].x_ << ", " << data[i].y_ << ")\n";
    return 0;
}


template <typename T> T
kth_statistic (T* arr, unsigned narr, unsigned k) {
    assert (narr > k);
    merge_sort (arr, 0, narr);
    return arr[k];
}


template <typename T> void
merge_sort (T* arr, unsigned beg, unsigned end) {
    assert (beg < end);

    auto size = end - beg;
    if (size == 1)
        return;
    auto mid = beg + size / 2;
    merge_sort (arr, beg, mid);
    merge_sort (arr, mid, end);

    T* data = new T[size];
    auto b = beg;
    auto e = mid;
    decltype (beg) cur = 0;

    while (b < mid && e < end)
        if (arr[b] <= arr[e])
            data[cur++] = arr[b++];
        else
            data[cur++] = arr[e++];
    while (b < mid)
        data[cur++] = arr[b++];
    while (e < end)
        data[cur++] = arr[e++];

    std::copy (data, data + size, arr + beg);
    delete[] data;
}
