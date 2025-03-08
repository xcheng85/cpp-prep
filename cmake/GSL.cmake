include(FetchContent)

FetchContent_Declare(GSL
    GIT_REPOSITORY "https://github.com/microsoft/GSL"
    GIT_TAG "v4.1.0"
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(GSL)