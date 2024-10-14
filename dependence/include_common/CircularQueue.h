#ifndef CircularQueue_H
#define CircularQueue_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <mutex>
#include <condition_variable>

template <typename T>
class CircularQueue
{
private:
    std::vector<T>          queue;    // 使用 std::vector 代替原生指针
    int                     front;    // 队列头部指针
    int                     rear;     // 队列尾部指针
    int                     capacity; // 队列的容量
    int                     size;     // 当前队列中元素个数
    bool                    stopped;  // 停止标志
    std::mutex              mtx;      // 互斥锁
    std::condition_variable cv;       // 条件变量

public:
    // 默认构造函数，队列容量默认为10
    CircularQueue(int capacity = 10)
        : front(0)
        , rear(0)
        , capacity(capacity)
        , size(0)
        , stopped(false)
    {
        queue.resize(capacity); // 初始化队列大小
    }

    // 插入队列
    bool enqueue(const T & value)
    {
        std::unique_lock<std::mutex> lock(mtx);

        // 如果队列已停止，返回false
        if (stopped)
        {
            return false;
        }

        // 等待直到队列不满或被停止
        cv.wait(lock, [this] {
            return !isFull() || stopped;
        });

        if (stopped)
        {
            return false;
        }

        queue[rear] = value;
        rear        = (rear + 1) % capacity;
        size++;
        cv.notify_all(); // 通知所有等待的线程
        return true;
    }

    // 取出队列
    bool dequeue(T & value)
    {
        std::unique_lock<std::mutex> lock(mtx);

        // 等待直到队列不为空或被停止
        cv.wait(lock, [this] {
            return !isEmpty() || stopped;
        });

        // 如果队列已停止并且为空，返回false
        if (stopped && isEmpty())
        {
            return false;
        }

        value = queue[front];
        front = (front + 1) % capacity;
        size--;
        cv.notify_all(); // 通知所有等待的线程
        return true;
    }

    // 停止队列
    void stop()
    {
        std::lock_guard<std::mutex> lock(mtx);
        stopped = true;
        cv.notify_all(); // 通知所有等待的线程
    }

    bool isEmpty() const
    {
        return size == 0;
    }

    bool isFull() const
    {
        return size == capacity;
    }

    int getSize() const
    {
        return size;
    }

    bool isStopped() const
    {
        return stopped;
    }
};

#endif
