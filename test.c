#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// スレッドで実行される関数
void *routine(void *arg) {
    printf("スレッドが開始されました。\n");
    sleep(2); // 2秒待機
    printf("スレッドが終了します。\n");
    return NULL;
}

int main(void) {
    pthread_t thread;
    pthread_attr_t attr;

    // スレッド属性の初期化
    int ret = pthread_attr_init(&attr);
    if (ret != 0) {
        fprintf(stderr, "スレッド属性の初期化に失敗しました。エラーコード: %d\n", ret);
        return 1;
    }

    // スレッドを分離状態に設定
    ret = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    if (ret != 0) {
        fprintf(stderr, "分離属性の設定に失敗しました。エラーコード: %d\n", ret);
        return 1;
    }

    // スレッドの作成
    ret = pthread_create(&thread, &attr, routine, NULL);
    if (ret != 0) {
        fprintf(stderr, "スレッドの作成に失敗しました。エラーコード: %d\n", ret);
        return 1;
    }

    // スレッド属性オブジェクトの破棄
    ret = pthread_attr_destroy(&attr);
    if (ret != 0) {
        fprintf(stderr, "スレッド属性の破棄に失敗しました。エラーコード: %d\n", ret);
        return 1;
    }

    // メインスレッドがすぐに終了する
    printf("メインスレッドが終了します。\n");
    // sleepを入れることでスレッドの動作確認ができる
    sleep(3); // スレッドが終了するのを待つために3秒待機
    return 0;
}