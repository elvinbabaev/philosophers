cmake_minimum_required(VERSION 3.17)
project(philosophers C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(philosophers
        utils/utils.c
        dinner.c
        error.c
        philo_init.c
        philo_one.c
        philo_one.h
        thread.c
        write_msg.c)
