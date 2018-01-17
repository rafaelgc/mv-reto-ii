/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TaskPool.cpp
 * Author: rafa
 * 
 * Created on January 14, 2018, 3:00 AM
 */

#include "TaskPool.hpp"

#include <iostream>

TaskPool::TaskPool() : uniqueLock(mtx) {
    maxThreads = 2;
    stopped = false;
    
    threadManager = std::thread(&TaskPool::work, this);
    
    for (int i = 0; i < maxThreads; i++) {
        workers.push_back(new Worker(cv));
    }
    
}

TaskPool::~TaskPool() {
    for (auto t : workers) {
        delete t;
    }
}

void TaskPool::addTask(Task& task) {
    this->pendantTasks.push(&task);
    cv.notify_all();
}

void TaskPool::work() {
    while (!stopped) {
        // Si hay tareas pendientes se asignan a los trabajadores
        // hasta que estén todos ocupados.
        while (pendantTasks.size() > 0) {
            Task* t = pendantTasks.front();
            bool success = false;
            // Se busca algún hilo trabajador que pueda realizar la tarea.
            for (auto it = workers.begin(); it != workers.end(); ++it) {
                // Si setTask devuelve true significa que el trabajador
                // realizará la tarea.
                if ((*it)->setTask(*t)) {
                    pendantTasks.pop();
                    success = true;
                    break;
                }
                
                
            }
            
            // Si no quedan trabajadores libres se sale del bucle.
            if (!success) { break; }
            
            // Si ningún trabajador puede realizar la tarea simplemente
            // se mantendrá en la cola esperando que algún trabajador
            // termine.
            
        }
        
        cv.wait(uniqueLock);
    }
}

void TaskPool::join() {
    threadManager.join();
    for (auto t : workers) {
        t->join();
    }
}

void TaskPool::stop() {
    stopped = true;
    
    for (auto it = workers.begin(); it != workers.end(); ++it) {
        (*it)->stop();
    }
    
    cv.notify_all();
}