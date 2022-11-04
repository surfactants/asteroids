#include <input/key_char.hpp>

std::map<sf::Keyboard::Key, std::string> Convert_Key::to_string;
std::map<std::string, sf::Keyboard::Key> Convert_Key::to_key;

Convert_Key::Convert_Key(){
    if(to_string.empty()){
        init();
    }
}

std::string Convert_Key::toString(sf::Keyboard::Key key){
    return to_string[key];
}

sf::Keyboard::Key Convert_Key::toKey(std::string str){
    sf::Keyboard::Key key{ sf::Keyboard::Unknown };
    if(to_key.contains(str)){
        key = to_key[str];
    }
    return key;
}

void Convert_Key::init(){
    #define MAP_INSERT(x) to_string.insert({sf::Keyboard::x, std::string(#x)}); to_key.insert({std::string(#x), sf::Keyboard::x});

    MAP_INSERT(Unknown);
    MAP_INSERT(A);
    MAP_INSERT(B);
    MAP_INSERT(C);
    MAP_INSERT(D);
    MAP_INSERT(E);
    MAP_INSERT(F);
    MAP_INSERT(G);
    MAP_INSERT(H);
    MAP_INSERT(I);
    MAP_INSERT(J);
    MAP_INSERT(K);
    MAP_INSERT(L);
    MAP_INSERT(M);
    MAP_INSERT(N);
    MAP_INSERT(O);
    MAP_INSERT(P);
    MAP_INSERT(Q);
    MAP_INSERT(R);
    MAP_INSERT(S);
    MAP_INSERT(T);
    MAP_INSERT(U);
    MAP_INSERT(V);
    MAP_INSERT(W);
    MAP_INSERT(X);
    MAP_INSERT(Y);
    MAP_INSERT(Z);
    MAP_INSERT(Num0);
    MAP_INSERT(Num1);
    MAP_INSERT(Num2);
    MAP_INSERT(Num3);
    MAP_INSERT(Num4);
    MAP_INSERT(Num5);
    MAP_INSERT(Num6);
    MAP_INSERT(Num7);
    MAP_INSERT(Num8);
    MAP_INSERT(Num9);
    MAP_INSERT(Escape);
    MAP_INSERT(LControl);
    MAP_INSERT(LShift);
    MAP_INSERT(LAlt);
    MAP_INSERT(LSystem);
    MAP_INSERT(RControl);
    MAP_INSERT(RShift);
    MAP_INSERT(RAlt);
    MAP_INSERT(RSystem);
    MAP_INSERT(Menu);
    MAP_INSERT(LBracket);
    MAP_INSERT(RBracket);
    MAP_INSERT(SemiColon);
    MAP_INSERT(Comma);
    MAP_INSERT(Period);
    MAP_INSERT(Quote);
    MAP_INSERT(Slash);
    MAP_INSERT(BackSlash);
    MAP_INSERT(Tilde);
    MAP_INSERT(Equal);
    MAP_INSERT(Dash);
    MAP_INSERT(Space);
    MAP_INSERT(Return);
    MAP_INSERT(BackSpace);
    MAP_INSERT(Tab);
    MAP_INSERT(PageUp);
    MAP_INSERT(PageDown);
    MAP_INSERT(End);
    MAP_INSERT(Home);
    MAP_INSERT(Insert);
    MAP_INSERT(Delete);
    MAP_INSERT(Add);
    MAP_INSERT(Subtract);
    MAP_INSERT(Multiply);
    MAP_INSERT(Divide);
    MAP_INSERT(Left);
    MAP_INSERT(Right);
    MAP_INSERT(Up);
    MAP_INSERT(Down);
    MAP_INSERT(Numpad0);
    MAP_INSERT(Numpad1);
    MAP_INSERT(Numpad2);
    MAP_INSERT(Numpad3);
    MAP_INSERT(Numpad4);
    MAP_INSERT(Numpad5);
    MAP_INSERT(Numpad6);
    MAP_INSERT(Numpad7);
    MAP_INSERT(Numpad8);
    MAP_INSERT(Numpad9);
    MAP_INSERT(F1);
    MAP_INSERT(F2);
    MAP_INSERT(F3);
    MAP_INSERT(F4);
    MAP_INSERT(F5);
    MAP_INSERT(F6);
    MAP_INSERT(F7);
    MAP_INSERT(F8);
    MAP_INSERT(F9);
    MAP_INSERT(F10);
    MAP_INSERT(F11);
    MAP_INSERT(F12);
    MAP_INSERT(F13);
    MAP_INSERT(F14);
    MAP_INSERT(F15);
    MAP_INSERT(Pause);

    static_assert(sf::Keyboard::KeyCount == 101, "Number of SFML keys has changed");
    #undef MAP_INSERT
}
