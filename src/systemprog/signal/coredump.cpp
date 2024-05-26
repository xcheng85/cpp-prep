#include <signal.h>
#include <iostream>

using namespace std;

// xiao     2662183 96.4  0.0   6336  3072 pts/1    R+   20:43   0:19 ./signal-coredump
// pid: 2662183
// trigger SIGTERM
// kill -15 2662183

//  ./signal-coredump 
// tear down
// Aborted (core dumped)


// coredumpctl info -1
// coredumpctl -o test.coredump dump /home/xiao/github.com/xcheng85/cpp-prep/build/bin/systemprog/signal/signal-coredump

int main()
{
    signal(SIGTERM, [](int sig)
           {
               cout << "tear down" << endl;
               abort(); // with core dump
           });
    while(true){

    }
    cout << "normal exit" << endl;
    return 0;
}