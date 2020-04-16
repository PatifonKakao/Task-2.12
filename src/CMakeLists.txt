# задаем набор исходников
set(SOURCES
TCP_Sender_Receiver.h
TCP_Sender_Receiver.cpp
)

# создаем статическую библиотеку
add_library(TCP_Sender_Receiver_lib ${SOURCES})

# добавлем путь к исходникам для возожности подключения библиотеки
target_include_directories(TCP_Sender_Receiver_lib PUBLIC ${SRC_ROOT_DIR})

# группируем исходники по типу по категориям
source_group(TREE ${CMAKE_CURRENT_LIST_DIR} FILES ${SOURCES})

# В solution эта библиотека лежит в TCP_Sender_Receiver_prj
set_property(TARGET TCP_Sender_Receiver_lib PROPERTY FOLDER "TCP_Sender_Receiver_prj")

# включаем в сборку проекnа подпроект с тестами
add_subdirectory(tests)