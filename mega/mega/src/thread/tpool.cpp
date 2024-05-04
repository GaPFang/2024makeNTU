// #include "tpool.h"
// #include <stdio.h>
// #include <stdlib.h>

// TPOOL::TPOOL(int n_threads) {
//     this -> n_threads = n_threads;
//     this -> threads = new pthread_t[n_threads];
//     pthread_mutex_init(&this -> m_btBuf, NULL);
//     pthread_mutex_init(&this -> m_rfidBuf, NULL);
//     pthread_cond_init(&this -> c_btBuf, NULL);
//     pthread_cond_init(&this -> c_rfidBuf, NULL);
//     for (int i = 0; i < n_threads; i++) {
//         pthread_create(&this -> threads[i], NULL, this -> tpool_thread, this);
//     }
// }