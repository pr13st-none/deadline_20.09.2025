#include <iostream>
#include <fstream>

char* alphabet = "zxcvbnmasdfghjklqwertyuiop";

bool is_in(char* word_in_x, char* word_out_x) {
    size_t size_word_in = 0;
    int same_count = 0;
    for (char* i = word_in_x; *i != '\0'; ++i) {
        size_word_in++;
        for (char* j = word_out_x; *j != '\0'; ++j) {
            if (*i == *j) {
                same_count++;
                break;
            }
        }
    }
    return (size_word_in == same_count);
}

bool full_is(char* first, char* second) {
    size_t size_first = 0;
    size_t size_second = 0;
    for (char* i = first; *i != '\0'; ++i) {
        size_first++;
    }
    for (char* i = second; *i != '\0'; ++i) {
        size_second++;
    }
    if (size_first != size_second) return false;
    for (int i = 0; i < size_first; i++) {
        if (first[i] != second[i]) return false;
    }
    return true;
}


bool error(int error_num) {
    switch (error_num) {
        case 1:
            std::cout << "arguments??" << std::endl;
            break;
        case 2:
            std::cout << "word error" << std::endl;
            break;
        case 3:
            std::cout << "file error (name)" << std::endl;
            break;
        case 4:
            std::cout << "file error (path)" << std::endl;
            break;
        default:
            std::cout << "unknown error.." << std::endl;
            break;
    }
    return false;
}


//void rules() {  }

signed main(int argc, char* argv[]) {

    // 0 --word .. --file ..
    if (argc < 5) return (int)error(1);

    bool command_word = false;
    char* word;
    bool command_file = false;
    char* file_name;

    for (int i = 1; i < argc - 1; i++) {
        if (full_is(argv[i], "--word") && is_in(argv[i + 1], alphabet)) {
            command_word = true;
            word = argv[i + 1];
        }
        if (full_is(argv[i], "--file") && is_in(".", argv[i + 1])) {
            command_file = true;
            file_name = argv[i + 1];
        }
    }

    if (!command_word) return (int)error(2);
    if (!command_file) return (int)error(3);


    //std::cout << word << std::endl;
    //std::cout << file_name << " " << right_path(file_name) << std::endl;
    
    // ))
    size_t path_size = 0;
    for (char* i = file_name; *i != '\0'; ++i) {
        path_size++;
    }
    char new_path[path_size + 4];
    new_path[0] = '.';
    new_path[1] = '.';
    new_path[2] = '/';
    for (int i = 3; i < path_size + 3; i++) {
        new_path[i] = file_name[i - 3];
    }
    for (int i = path_size + 3; new_path[i] != '\0'; i++) {
        new_path[i] = '\0';
    }
    // 2 часа времени..

    std::ifstream input_file(new_path);

    if (!input_file.is_open()) return (int)error(4);

    char word_now[256];
    while (input_file >> word_now) {
        if (is_in(word, word_now)) {
            std::cout << word_now << ' ';
        } 
    } std::cout << std::endl;

    input_file.close();
}
