/* 
 * File:   Semaphore.h
 * Author: toddgreener
 *
 * Created on March 10, 2014, 4:44 PM
 */

#ifndef SEMAPHORE_H
#define	SEMAPHORE_H

#include <mutex>
#include <condition_variable>
using namespace std;

class Semaphore{
private:
    mutex mtx;
    condition_variable cv;
    int count;

public:
    Semaphore();
    void signal();
    void wait();
};

#endif	/* SEMAPHORE_H */

