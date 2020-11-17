cmake_minimum_required(VERSION 3.17)
project(philosophers C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(philosophers
        philo_one/utils/utils.c
        philo_one/dinner.c
        philo_one/error.c
        philo_one/philo_init.c
        philo_one/philo_one.c
        philo_one/philo_one.h
        philo_one/thread.c
        philo_one/write_msg.c)
