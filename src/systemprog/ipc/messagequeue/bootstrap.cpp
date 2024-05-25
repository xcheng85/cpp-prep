#include <peer.h>
#include <mqueue.h>
#include <sys/stat.h> // permission bit

template <size_t MAX_MESSAGES, size_t MAX_MSG_SIZE>
mq_attr MessageAttribute()
{
    // order must comply
    return mq_attr{
        .mq_flags = 0,
        .mq_maxmsg = MAX_MESSAGES,
        .mq_msgsize = MAX_MSG_SIZE,
        .mq_curmsgs = 0,
    };
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        cerr << "usage: chat uid mqwrite mqread" << endl;
        return 1;
    }

    auto uid = argv[1], pathw = argv[2], pathr = argv[3];

    mqd_t peerWrite, peerRead;

    mq_attr attr{MessageAttribute<10, 256>()};

    // Read permission bit for the owner of the file. On many systems this bit is 0400
    // Write permission bit for the owner of the file. Usually 0200.
    // Read permission bit for the group owner of the file. Usually 040.
    // Write permission bit for the group owner of the file. Usually 020.

    peerWrite = mq_open(pathw, O_WRONLY | O_CREAT, "0660", &attr);
    if (peerWrite == -1)
    {
        perror("Write Peer cannot open");
        return 1;
    }

    peerRead = mq_open(pathr, O_RDONLY | O_CREAT, "0660", &attr);
    if (peerRead == -1)
    {
        perror("READ Peer cannot open");
        return 1;
    }
    string s(uid);
    Peer<10, 256> p(s, peerWrite, peerRead);
    p.run();
}