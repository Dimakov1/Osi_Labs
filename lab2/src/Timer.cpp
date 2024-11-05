#include "Timer.h"

Timer::Timer(){
    start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer(){
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> time = end - start;
    std::cout << "Время выполнения: " << time.count() << " секунд\n"; 
}
