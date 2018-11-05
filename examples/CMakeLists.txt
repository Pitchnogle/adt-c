# algorithms-c/examples/CMakeLists.txt
#

# A linked-list example
add_executable(list_example list_example.c ${SRC_DIR}/list.c)

# A doubly linked-list example
add_executable(dlist_example dlist_example.c ${SRC_DIR}/dlist.c)

# A circular linked-list example
add_executable(clist_example clist_example.c ${SRC_DIR}/clist.c)

# A stack example
add_executable(stack_example stack_example.c ${SRC_DIR}/stack.c ${SRC_DIR}/list.c)

# A queue example
add_executable(queue_example queue_example.c ${SRC_DIR}/queue.c ${SRC_DIR}/list.c)

# A chained hash table example
add_executable(hashtable_example hashtable_example.c ${SRC_DIR}/hashtable.c ${SRC_DIR}/list.c)
