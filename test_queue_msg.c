#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "queuemsg.h"


pthread_t pthrd_capi;
pthread_t pthrd_zip;

void
sleep_ms(int tmout_ms) {
    struct timespec timeout_val;

    // Calculate timeout
    timeout_val.tv_sec = tmout_ms / 1000;
    timeout_val.tv_nsec = (tmout_ms % 1000) * 1000000; //convert ms to ns

    nanosleep(&timeout_val, NULL);
}

void *handle_capi(void *arg) {
    printf("handle_capi\n");
    while(1) {
        msg_lst_p rcv_msg = rcvMsgFromZIP();
        if (rcv_msg != NULL) {
            printf("capi <== : ");
            for (int i = 0; i < rcv_msg->dat_sz; i++) printf("%x ", rcv_msg->buf[i]);
            printf("\n");
            free(rcv_msg);
            sleep_ms(1000);
            uint8_t buff[8];
            printf("capi ==> : ");
            for (int i = 0; i < 8; i++) {
                buff[i] = rand() & 0xFF;
                printf("%x ", buff[i]);
            }
            printf("\n");
            sendMsg2ZIP(buff, 8);
        } else {
            sleep_ms(100);
        }
    }
}

void *handle_zip(void *arg) {
    printf("handle_zip\n");
    while (1) {
        msg_lst_p rcv_msg = rcvMsgFromCAPI();
        if (rcv_msg != NULL) {
            printf("zip  <== : ");
            for (int i = 0; i < rcv_msg->dat_sz; i++) printf("%x ", rcv_msg->buf[i]);
            printf("\n");
            free(rcv_msg);
            sleep_ms(500);
            uint8_t buff[8];
            printf("zip  ==> : ");
            for (int i = 0; i < 8; i++) {
                buff[i] = rand() & 0xFF;
                printf("%x ", buff[i]);
            }
            printf("\n");
            sendMsg2CAPI(buff, 8);
        } else {
            sleep_ms(500);
        }
    }
}

int
main(int argc, char **argv) {
    queueMsgInit();
    uint8_t buff[8];
    printf("main ==> : ");
    for (int i = 0; i < 8; i++) {
        buff[i] = rand() & 0xFF;
        printf("%x ", buff[i]);
    }
    printf("\n");
    sendMsg2CAPI(buff, 8);

    pthread_create(&pthrd_capi, NULL, handle_capi, NULL);
//    pthread_join(pthrd_capi, NULL);
    printf("HELOO\n");
    pthread_create(&pthrd_zip, NULL, handle_zip, NULL);
//    pthread_join(pthrd_zip, NULL);


    while (1) {
        sleep_ms(1000);
    }

    return 0;
}