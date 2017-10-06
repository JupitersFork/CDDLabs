#include "Semaphore.h"
#include <iostream>
#include <thread>

void taskOne(std::shared_ptr<Semaphore> alpha, std::shared_ptr<Semaphore>  omega){
  std::cout <<"I ";
  std::cout << "must ";
  omega->Signal();
  alpha->Wait();
  std::cout << "print ";
  std::cout << "first"<<std::endl;
  omega->Signal();
}

void taskTwo(std::shared_ptr<Semaphore> alpha, std::shared_ptr<Semaphore>  omega){
  omega->Wait(); 
  std::cout <<"This ";
  std::cout << "will ";
  alpha->Signal();
  omega->Wait();
  std::cout << "appear ";
  std::cout << "second"<<std::endl;
}

int main(void){
  std::thread threadOne, threadTwo;
  std::shared_ptr<Semaphore> alpha( new Semaphore);
  std::shared_ptr<Semaphore> omega( new Semaphore);
  /**< Launch the threads  */
  threadOne=std::thread(taskTwo,alpha, omega);
  threadTwo=std::thread(taskOne,alpha, omega);
  std::cout << "Launched from the main\n";
  threadOne.join();
  threadTwo.join();
  return 0;
}
