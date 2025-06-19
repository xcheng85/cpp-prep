#include <stream.h>
// unix system header
#include <signal.h>
#include <chrono>

bool gTerminate = false;
int main(int argc, char **argv)
{
    using namespace std::chrono_literals;
    signal(SIGTERM, [](int sig)
           { gTerminate = true; });

    for (int i = 0; i < argc; i++)
    {
        std::cout << (*argv++) << std::endl;
    }
    constexpr int consumerGroupSize = 3;
    auto createSessionStream = std::make_unique<Stream>();
    createSessionStream->init(consumerGroupSize);
    while (!gTerminate)
    {
        auto task = std::make_shared<CreateSessionTask>();
        createSessionStream->publish(task);
        std::this_thread::sleep_for(120s);
    }
    return 0;
}