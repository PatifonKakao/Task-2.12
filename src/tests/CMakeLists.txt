# задаем набор исходников
set(SOURCES
    tests.cpp
)

# создаем исполняемый файл
add_executable(prj_test ${SOURCES})

# подключаем библиотеки:
# 1. Тестируемая библиотека
# 2. gest
target_link_libraries(prj_test PUBLIC TCP_Sender_Receiver_lib)
target_link_libraries(prj_test PUBLIC gtest_main)

# В solution эта библиотека лежит в tests/prj_test
set_property(TARGET prj_test PROPERTY FOLDER "tests/prj_test")