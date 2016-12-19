cmake_minimum_required(VERSION 3.6)
project(FreeRTOS_Sim_master)

set(CMAKE_CXX_STANDARD 11)

include_directories(Demo/include)
include_directories(Project)
include_directories(Source/include)
include_directories(Source/portable/GCC/POSIX)

set(SOURCE_FILES
    Demo/AbortDelay.c
    Demo/BlockQ.c
    Demo/blocktim.c
    Demo/countsem.c
    Demo/death.c
    Demo/dynamic.c
    Demo/EventGroupsDemo.c
    Demo/flop.c
    Demo/GenQTest.c
    Demo/integer.c
    Demo/IntSemTest.c
    Demo/PollQ.c
    Demo/QPeek.c
    Demo/QueueOverwrite.c
    Demo/QueueSet.c
    Demo/QueueSetPolling.c
    Demo/recmutex.c
    Demo/semtest.c
    Demo/TaskNotify.c
    Demo/TimerDemo.c
    Project/main.c
    Source/portable/GCC/POSIX/port.c
    Source/portable/MemMang/heap_3.c
    Source/croutine.c
    Source/event_groups.c
    Source/list.c
    Source/queue.c
    Source/tasks.c
    Source/timers.c)

add_executable(FreeRTOS_Sim_master ${SOURCE_FILES})