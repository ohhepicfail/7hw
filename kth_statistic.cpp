#include <iostream>
#include <cassert>
#include <cstdlib>
#include <ctime>

#define PRINT 0

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

void create_data (smth* data, unsigned ndata);
bool verify_data (smth* data, unsigned ndata);

int main () {
    unsigned ndata = 20;
    auto data = new smth[ndata];
    create_data (data, ndata);

    #if PRINT
    for (unsigned i = 0; i < ndata; i++)
        std::cout << data[i].x_ << " " << data[i].y_ << std::endl;
    #endif

    kth_statistic (data, ndata, 0);
    
    #if PRINT
    for (unsigned i = 0; i < ndata; i++)
        std::cout << "(" << data[i].x_ << ", " << data[i].y_ << ")\n";
    #endif
    
    assert (verify_data (data, ndata));
    std::cout << "\nsuccessfully\n\n";

    delete[] data;
    return 0;
}


void create_data (smth* data, unsigned ndata) {
    assert (data);

    srand (time (nullptr));

    auto cntr = new unsigned[ndata] ();

    for (unsigned i = 0; i < ndata; i++) {
        auto tmp =  rand () % (ndata / 2);
        data[i].x_ = tmp;
        data[i].y_ = cntr[tmp]++;
    }

    delete[] cntr;
}    


bool verify_data (smth* data, unsigned ndata) {
    assert (data);

    if (ndata <= 1)
        return true;

    for (unsigned i = 1; i < ndata; i++) {
        if (data[i - 1].x_ > data[i].x_)
            return false;
        if (data[i - 1].x_ < data[i].x_)
            continue;
        if (data[i - 1].y_ + 1 != data[i].y_)
            return false;
    }

    return true;
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



