#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cstring>
#include <cstdlib>

void copyFile(const char *source, const char *destination) {
    int sourceFD = open(source, O_RDONLY);
    if (sourceFD == -1) {
        perror("Error opening source file");
        exit(1);
    }

    int destFD = open(destination, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
    if (destFD == -1) {
        perror("Error opening destination file");
        close(sourceFD);
        exit(1);
    }

    ssize_t bytesRead;
    while ((bytesRead = read(sourceFD, buf, BUF_SIZE)) > 0) {
        if (write(destFD, buf, bytesRead) != bytesRead) {
            perror("Error writing to destination file");
            close(sourceFD);
            close(destFD);
            exit(1);
        }
    }

    if (bytesRead == -1) {
        perror("Error reading from source file");
        close(sourceFD);
        close(destFD);
        exit(1);
    }

    close(sourceFD);
    close(destFD);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <source file> <destination file>" << std::endl;
        return 1;
    }

    copyFile(argv[1], argv[2]);
    return 0;
}
