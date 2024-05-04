// #include <pthread.h>

// class TPOOL {
//     public:
//         TPOOL(int n_threads);
//         void *tpool_thread(void *arg);
//     private:
//         pthread_t btThread;
//         pthread_t rfidThread;
//         int n_threads;
//         char btBuf[1024];
//         char rfidBuf[1024];
//         pthread_mutex_t m_btBuf;
//         pthread_mutex_t m_rfidBuf;
//         pthread_cond_t c_btBuf;
//         pthread_cond_t c_rfidBuf;
// };