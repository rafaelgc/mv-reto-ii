/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TaskPool.hpp
 * Author: rafa
 *
 * Created on January 14, 2018, 3:00 AM
 */

#ifndef TASKPOOL_HPP
#define TASKPOOL_HPP

#include <thread>
#include <condition_variable>
#include <vector>
#include <mutex>
#include <queue>

#include "Task.hpp"
#include "Worker.hpp"

class TaskPool {
public:
    TaskPool();
    //TaskPool(const TaskPool& orig);
    virtual ~TaskPool();
    
    void addTask(Task& task);
    
    void work();
    void join();
protected:
private:
    std::queue<Task*> pendantTasks;
    
    std::thread threadManager;
    std::vector<Worker*> workers;
    int maxThreads;
    std::mutex mtx;
    
    std::condition_variable cv;
    std::unique_lock<std::mutex> uniqueLock;
};

#endif /* TASKPOOL_HPP */

