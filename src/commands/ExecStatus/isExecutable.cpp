#include <unistd.h>
#include <string>

bool isExecutable(std::string path) {
    const char* peth = path.c_str();
    return access(peth, X_OK) == 0;
}
