#include <sys/mman.h> // shm based on memory-mapped io
#include <sys/stat.h> 
#include <fcntl.h> // for permission related
#include <unistd.h> // ftruncate
#include <peer.h>

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cerr << "usage: chat uid wShmId rShmId";
        return 1;
    }
    auto uid = argv[1], wShmId = argv[2], rShmId = argv[3];
    // READ AND WRITE
    // TRUNC to 0 bytes if exists
    // READ/WRITE permission for the owner
    auto wFd = shm_open(wShmId, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    auto rFd = shm_open(rShmId, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (wFd == -1 || rFd == -1)
    {
        perror("Failed to open shm");
        return 10;
    }
    constexpr size_t storageSize = 64;
    if (ftruncate(wFd, storageSize) == -1)
    {
        perror("Failed to resize the shm fd");
        return 20;
    }
    // addr is NULL, then the kernel chooses the (page-aligned)
    // mapsize: storageSize,
    // desired memory protection
    // Shared between processes
    // file-backed
    // no offset
    void *wAddress = mmap(NULL, storageSize, PROT_WRITE, MAP_SHARED, wFd, 0);
    void *rAddress = mmap(NULL, storageSize, PROT_READ, MAP_SHARED, rFd, 0);
    // MAP_FAILED: (void *) -1
    if (wAddress == MAP_FAILED || rAddress == MAP_FAILED)
    {
        perror("Failed to mmap the shm");
        return 30;
    }
    constexpr size_t messageSize = 128;
    Peer<messageSize> p(string(uid), wAddress, rAddress);
    p.run();
    return 0;
}