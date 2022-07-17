#include "shell.hpp"
#include <iostream>
#include "texture_manager.hpp"

void preload(){
    Texture_Manager::populate();
}

int main(){
    preload();
    Shell shell;
        shell.run();
    return 0;
}
