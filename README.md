# Philosophers

***The Dining Philosophers Problem*** is a classic synchronization problem in computer science that involves a group of philosophers sitting at a round table, each with a plate of spaghetti in front of them, and a fork on either side of their plate. The philosophers need two forks to eat their spaghetti, but there are only as many forks as there are philosophers, and each philosopher needs to grab both the fork to their left and the fork to their right in order to eat. The challenge is to create a solution that allows each philosopher to pick up their forks and eat without creating a deadlock, where each philosopher is waiting for the other to put down their fork.
___
## Requirements:
* gcc
* make

➜ Requirements installation for Debian distributions:
```
sudo apt-get install gcc make
```

## Installation
```
git clone https://github.com/irhesri/philo.git
```
➜ Solution using ***Multithreading [Mutexes]***:
```
cd philo
make
```
➜ Solution using ***Multiprocessing [Semaphores]***:
```
cd philo_bonus
make
```
## Usage
➜ Solution using ***Multithreading [Mutexes]***:
```
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```
➜ Solution using ***Multiprocessing [Semaphores]***:
```
./philo_bonus [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```
>Note: 
> * The time is in milliseconds
> * The last argument [number_of_times_each_philosopher_must_eat] is optional
> * Do not write the [ ]

## Features
* ***Synchronization***: The problem involves multiple threads/processes competing for shared resources.
* ***Deadlock prevention***: The solution must prevent a situation where each philosopher is waiting for the other to release their fork, causing a deadlock.
* ***Resource Allocation***: The philosophers need to acquire two forks to eat their spaghetti, but there are only as many forks as there are philosophers, making resource allocation a key part of the problem.
* ***Concurrency***: The solution must allow multiple philosophers to execute concurrently while preventing conflicts and ensuring fairness.
* ***Scalability***: The solution should work for any number of philosophers.
* ***Robustness***: The solution should be able to handle unexpected events such as errors or timeouts without crashing or causing other problems.

### ➜ Rules for solution using ***Multithreading [Mutexes]***:
* Each philosopher should be a thread.
* There is one fork between each pair of philosophers. Therefore, if there are several philosophers, each philosopher has a fork on their left side and a fork on their right side. If there is only one philosopher, there should be only one fork on the table.
* To prevent philosophers from duplicating forks, you should protect the forks state with a mutex for each of them.
### ➜ Rules for solution using ***Multiprocessing [Semaphores]***:
* All the forks are put in the middle of the table.
* They have no states in memory but the number of available forks is represented by a semaphore.
* Each philosopher should be a process. But the main process should not be a philosopher.

## Restrictions:
* Only the next functions are allowed:

➜ For the solution using ***Multithreading [Mutexes]***:
>memset, printf, malloc, free, write, usleep, gettimeofday, pthread_create, pthread_detach, pthread_join, pthread_mutex_init, pthread_mutex_destroy, pthread_mutex_lock, pthread_mutex_unlock

➜ For the solution using ***Multiprocessing [Semaphores]***:
>memset, printf, malloc, free, write, fork, kill, exit, pthread_create, pthread_detach, pthread_join, usleep, gettimeofday, waitpid, sem_open, sem_close, sem_post, sem_wait, sem_unlink
* Global variables are not allowed.
* A displayed state message should not be mixed up with another message.
* A message announcing a philosopher died should be displayed no more than 10 ms after the actual death of the philosopher.
* The philosophers should avoid dying
* The program must not have any data races.

## Conclusion:
By understanding the challenges of the dining philosophers problem and implementing the solutions, programmers can gain a deeper understanding of concurrency and synchronization in computer science, and some programming concepts like ***multithreading*** and ***multiprocessing***.
