#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];

void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        printf("Philosopher %d is thinking.\n", id);
        sleep(rand() % 3);

        // 左のフォークを取る
        pthread_mutex_lock(&chopsticks[id]);
        printf("Philosopher %d picked up left chopstick.\n", id);

        // 右のフォークを取る
        pthread_mutex_lock(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d picked up right chopstick.\n", id);

        // 食事をする
        printf("Philosopher %d is eating.\n", id);
        sleep(rand() % 3);

        // 右のフォークを置く
        pthread_mutex_unlock(&chopsticks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d put down right chopstick.\n", id);

        // 左のフォークを置く
        pthread_mutex_unlock(&chopsticks[id]);
        printf("Philosopher %d put down left chopstick.\n", id);
    }
}

int main() {
    pthread_t threads[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];
    int i;

    // ミューテックスの初期化
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
        ids[i] = i;
    }

    // スレッドの作成
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&threads[i], NULL, philosopher, (void *)&ids[i]);
    }

    // 全てのスレッドが終了するのを待つ
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(threads[i], NULL);
    }

    // ミューテックスの破棄
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }
}
