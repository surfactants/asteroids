#pragma once

#include <SFML/Window/Keyboard.hpp>

inline char keyToChar(sf::Event& event){
    #define KEY case sf::Keyboard::

    switch(event.key.code){
        KEY A: return 'a';
        KEY B: return 'b';
        KEY C: return 'c';
        KEY D: return 'd';
        KEY E: return 'e';
        KEY F: return 'f';
        KEY G: return 'g';
        KEY H: return 'h';
        KEY I: return 'i';
        KEY J: return 'j';
        KEY K: return 'k';
        KEY L: return 'l';
        KEY M: return 'm';
        KEY N: return 'n';
        KEY O: return 'o';
        KEY P: return 'p';
        KEY Q: return 'q';
        KEY R: return 'r';
        KEY S: return 's';
        KEY T: return 't';
        KEY U: return 'u';
        KEY V: return 'v';
        KEY W: return 'w';
        KEY X: return 'x';
        KEY Y: return 'y';
        KEY Z: return 'z';

        KEY Space: return ' ';

        KEY Numpad0:
        KEY Num0: return '0';

        KEY Numpad1:
        KEY Num1: return '1';

        KEY Numpad2:
        KEY Num2: return '2';

        KEY Numpad3:
        KEY Num3: return '3';

        KEY Numpad4:
        KEY Num4: return '4';

        KEY Numpad5:
        KEY Num5: return '5';

        KEY Numpad6:
        KEY Num6: return '6';

        KEY Numpad7:
        KEY Num7: return '7';

        KEY Numpad8:
        KEY Num8: return '8';

        KEY Numpad9:
        KEY Num9: return '9';

        default: return '$';
    }
}
