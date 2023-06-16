#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#define SHM_SIZE 1024

struct shared_data {
    int number;
};

extern struct shared_data *shared_data_ptr;  // Declare shared_data_ptr as an external variable

void create_shared_memory();
void attach_shared_memory();
void detach_shared_memory();
void remove_shared_memory();
void generate_random_number();

#endif
