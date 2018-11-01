# algorithms-c/examples/CMakeLists.txt
#

# A linked-list example
add_executable(list_example list_example.c ${SRC_DIR}/list.c)

# A doubly linked-list example
add_executable(dlist_example dlist_example.c ${SRC_DIR}/dlist.c)

# A circular linked-list example
add_executable(clist_example clist_example.c ${SRC_DIR}/clist.c)