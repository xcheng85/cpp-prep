#include <sys/mman.h> // for mapped io
#include <iostream>
#include <iterator>
#include <format>
#include <vector>
#include <algorithm>
#include <memory> //addressof

using namespace std;

template <typename T>
class MMapAllocator
{
public:
    using value_type = T;
    // no area di
    MMapAllocator() noexcept
    {
    }

    template <class U>
    MMapAllocator(const MMapAllocator<U> &other) noexcept
    {
    }

    MMapAllocator(const MMapAllocator &) = default;
    MMapAllocator &operator=(const MMapAllocator &) = default;

    template <typename U>
    struct rebind
    {
        using other = MMapAllocator<U>;
    };
    // real two apis matters
    // allocate n object
    T *allocate(size_t n)
    {
        // MAP_SHARED: IPC
        // MAP_PRIVATE: non-ipc, copy on write
        // MAP_ANONYMOUS: mapping is not backed by file

        cout << format("allocating {} bytes\n", sizeof(T) * n);
        void *ptr = mmap(0, sizeof(T) * n,
                         PROT_READ | PROT_WRITE,
                         MAP_PRIVATE | MAP_ANONYMOUS,
                         -1, // no fd
                         0); // offset 0
        if (ptr == MAP_FAILED)
        {
            throw std::bad_alloc();
        }
        return static_cast<T *>(ptr);
    }
    // start from address and remove n objects
    void deallocate(T *p, size_t n) noexcept
    {
        cout << format("deallocating {} bytes \n", sizeof(T) * n);
        // closing the file descriptor does not unmap the region.
        munmap(p, sizeof(T) * n);
    }

    // template <class U>
    // auto operator==(const MMapAllocator<U> &other) const noexcept
    // {
    //     return _arena == other._arena;
    // }
    // template <class U>
    // auto operator!=(const MMapAllocator<U> &other) const noexcept
    // {
    //     return !(*this == other);
    // }
    // template <class U>
    // friend struct MMapAllocator;

private:
    // at least as strict (as large) as that of every scalar type
    // std::max_align_t is usually synonymous with the largest scalar type, which is long double
    // static constexpr size_t _alignment = alignof(std::max_align_t);
};

int main()
{
    vector<int, MMapAllocator<int>> v{1, 2, 3, 4, 5};
    std::copy(begin(v), end(v), ostream_iterator<int>(cout, " "));
    return 0;
}