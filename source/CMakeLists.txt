add_executable(diningphilosophers 
               cout.cpp
               fork.cpp
               philosopher.cpp
               table.cpp
               waiter.cpp
               main.cpp)
target_include_directories(diningphilosophers PRIVATE h)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(diningphilosophers PRIVATE Threads::Threads)

install(TARGETS diningphilosophers RUNTIME DESTINATION bin)
