
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>
#include "queuemsg.h"

int
enQueue(
    pthread_mutex_t *mutex,
    msg_lst_t **head,
    uint8_t *buf,
    uint16_t dat_sz
) {
    msg_lst_t *ent;     //Pointer to list entry
    msg_lst_t *temp;

    ent = (msg_lst_t *) malloc(sizeof(msg_lst_t) + dat_sz);

    if (!ent)
        return -1;

    ent->dat_sz = dat_sz;
    memcpy(ent->buf, buf, dat_sz);

    if (mutex) {
        pthread_mutex_lock(mutex);
    }

    if (*head == NULL) {
        ent->next = NULL;
        *head = ent;
        if (mutex) {
            pthread_mutex_unlock(mutex);
        }
        return 0;
    }

    temp = *head;
    while (temp->next) {
        temp = temp->next;
    }

    temp->next = ent;
    ent->next = NULL;

    if (mutex) {
        pthread_mutex_unlock(mutex);
    }

    return 0;
}

msg_lst_p
deQueue(
    pthread_mutex_t *mutex,
    msg_lst_t **head
) {
    msg_lst_t *first_entry;  //The entry at the beginning of the list

    if (mutex) {
        pthread_mutex_lock(mutex);
    }

    first_entry = *head;

    if (*head == NULL) {
        if (mutex) {
            pthread_mutex_unlock(mutex);
        }
        return NULL;
    }

    *head = (*head)->next;
    if (mutex) {
        pthread_mutex_unlock(mutex);
    }

    return first_entry;
}

pthread_mutex_t zip_mutex;
pthread_mutex_t capi_mutex;
msg_lst_p zip_lst;
msg_lst_p capi_lst;

void
sendMsg2ZIP(
    uint8_t *msg,
    uint16_t len
) {
    int ret = enQueue(&zip_mutex, &zip_lst, msg, len);
    if (ret != 0) {
        printf("sendMsg2ZIP ERR %d", ret);
    }
}

msg_lst_p
rcvMsgFromCAPI() {
    return deQueue(&zip_mutex, &zip_lst);
}

void
sendMsg2CAPI(
        uint8_t *msg,
        uint16_t len
) {
    enQueue(&capi_mutex, &capi_lst, msg, len);
}

msg_lst_p
rcvMsgFromZIP() {
    return deQueue(&capi_mutex, &capi_lst);
}

void
queueMsgInit() {
    pthread_mutex_init(&capi_mutex, NULL);
    pthread_mutex_init(&zip_mutex, NULL);

    static msg_lst_t capi;
    static msg_lst_t zip;
//    capi_lst = &capi;
//    zip_lst = &zip;
//    capi_lst->next = NULL;
//    zip_lst->next = NULL;
}
