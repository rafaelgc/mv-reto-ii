#include <SFML/Graphics.hpp>
#include "App.hpp"

#include "Task.hpp"
#include "TaskPool.hpp"
#include "Worker.hpp"

class TestTask : public Task {
public:
    TestTask(std::string msg) { this->msg = msg; }
    bool work() {
        std::this_thread::sleep_for (std::chrono::seconds(2));
        std::cout << msg << " -> id = " << std::this_thread::get_id() << std::endl;
        return true;
    }
    
private:
    std::string msg;
};

int main()
{
    App app;
    app.run();
    
    
    /*TaskPool taskPool;
    
    TestTask t1("Hola 1.");
    TestTask t2("Hola 2.");
    
    TestTask t3("Hola 3.");
    TestTask t4("Hola 4.");
    
    TestTask t5("Hola 5.");
    TestTask t6("Hola 6.");
    
    taskPool.addTask(t1);
    taskPool.addTask(t2);
    taskPool.addTask(t3);
    taskPool.addTask(t4);
    taskPool.addTask(t5);
    taskPool.addTask(t6);
    
    taskPool.join();*/
    
    return 0;
}