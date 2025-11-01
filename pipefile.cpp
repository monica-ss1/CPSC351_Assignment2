#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(int argc, char** argv) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    int p[2]; 
    if (pipe(p) == -1) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        if (close(p[1]) == -1) {
            perror("close write");
            return 1;
        }

        int out = open("file_recv", O_CREAT|O_TRUNC|O_WRONLY, 0644);
        if (out == -1) {
            perror("open file file_recv");
            return 1;
        }

        char buf[4096];
        ssize_t n;

        while ((n = read(p[0], buf, sizeof buf)) > 0) {
            if (write(out, buf, n) == -1) {
                perror("write file file_recv");
                return 1;
            }
        }

        if (n == -1) {
            perror("read pipe");
            return 1;
        }

        if (close(out) == -1) {
            perror("closing file_recv");
            return 1;
        }

        if (close(p[0]) == -1) {
            perror("close read");
            return 1;
        }

        return 0;
    } else {
        if (close(p[0]) == -1) {
            perror("close read");
            return 1;
        }

        int in = open(argv[1], O_RDONLY);
        if (in == -1) {
            perror("open the input");
            close(p[1]);
            return 1;
        }

        char buf[4096];
        ssize_t n;

        while ((n = read(in, buf, sizeof buf)) > 0) {
            if (write(p[1], buf, n) == -1) {
                perror("write pipe");
                return 1;
            }
        }

        if (n == -1) {
            perror("read the input");
            return 1;
        }

        if (close(in) == -1) {
            perror("close input");
            return 1;
        }

        if (close(p[1]) == -1) {
            perror("close write");
            return 1;
        }

        if (wait(NULL) == -1) {
            perror("wait");
            return 1;
        }

        return 0;
    }
}
