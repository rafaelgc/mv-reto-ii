/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Worker.hpp
 * Author: rafa
 *
 * Created on January 14, 2018, 3:42 PM
 */

#ifndef WORKER_HPP
#define WORKER_HPP

#include <mutex>
#include <condition_variable>

#include "Task.hpp"

class Worker {
public:
    Worker(std::condition_variable& poolCv);
    virtual ~Worker();
    
    bool setTask(Task& task);
    bool isFree() const;
    void work();
    void join();
    
private:
    std::thread thread;
    Task* task;
    std::mutex mtx;
    
    std::condition_variable cv;
    std::condition_variable *poolCv;
    std::unique_lock<std::mutex> uniqueLock;
};

#endif /* WORKER_HPP */

