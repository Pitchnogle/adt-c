# algorithms-c/examples/CMakeLists.txt
#

# A linked-list example
add_executable(list_example list_example.c ${SRC_DIR}/list.c)

# A doubly linked-list example
add_executable(dlist_example dlist_example.c ${SRC_DIR}/dlist.c)