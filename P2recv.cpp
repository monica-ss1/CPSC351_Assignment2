#include <iostream>
#include <fstream>
#include <cstring>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

static constexpr const char* QUEUE_NAME = "/cpsc351queue";
static constexpr size_t MAX_SIZE   = 4096;
static constexpr const char* MSG_STOP   = "STOP";

int main() {
    //Create the queue with size of 4096 and at most 10 messages
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MAX_SIZE;
    attr.mq_curmsgs = 0;
    
    // check
    mqd_t mq = mq_open(QUEUE_NAME, O_CREAT | O_RDONLY, 0644, &attr);
    if (mq == (mqd_t)-1) {
        perror("mq_open");
        exit(1);
    }

    char buffer[MAX_SIZE + 1];
    ssize_t bytes_read;
    
    //Ready the output file
    int out_fd = open("file_recv", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (out_fd == -1) {
        perror("open file_recv");
        mq_close(mq);
        mq_unlink(QUEUE_NAME);
        exit(1);
    }
    
    // loop
    while (true) {
        memset(buffer, 0, sizeof(buffer));
        unsigned int prio;
        bytes_read = mq_receive(mq, buffer, MAX_SIZE, &prio);
        if (bytes_read == -1) {
            perror("mq_receive");
            break;
        }

        if (prio == 2)
            break;

        if (write(out_fd, buffer, bytes_read) == -1) {
            perror("write");
            break;
        }
    }

    close(out_fd);
    mq_close(mq);
    mq_unlink(QUEUE_NAME);

    return 0;
}

