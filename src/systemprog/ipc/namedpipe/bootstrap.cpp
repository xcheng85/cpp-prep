#include <sys/stat.h> //mkfifo
#include <peer.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "usage: chat uid";
        return 1;
    }
    string filePath("/tmp/chat");
    // 0600: no user and group permissions
    mkfifo(filePath.c_str(), 0600);

    Peer p(string(argv[1]), filePath);
    p.run();
}