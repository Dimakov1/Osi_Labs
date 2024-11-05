#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

int Sum(int a, int b){

    this_thread::sleep_for(chrono::milliseconds(2000));

    cout << "ID потока = " << this_thread::get_id() << " =========\tSum STARTED\t=========\n";

    this_thread::sleep_for(chrono::milliseconds(5000));

    cout << "ID потока = " << this_thread::get_id() << " =========\tSum STOPPED\t=========\n";

    return a + b;
}


int main(){

    int result;

    thread th([&result]() {result = Sum(2, 5); });

    for (int i = 0; i < 10; i++){
        cout << "ID потока = " << this_thread::get_id() << "\tmain works\t" << i << '\n';
        this_thread::sleep_for(chrono::milliseconds(500));
    }
    th.join();
    cout << "Sum result = " << result << '\n';
    
}