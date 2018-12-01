#include <iostream>

int main(int argc, char** argv){
    int input;

    while(true){

        std::cout << "enter integer number : ";
        std::cin >> input;
        if(!std::cin.good()){
            std::cout << "not integer number !!" << "\n";
            std::cin.clear();
            std::cin.ignore(1024,'\n');
            continue;
        }

        if(input % 15 == 0)
            std::cout << "fizzbuzz" << "\n";
        else if(input % 3 == 0)
            std::cout << "fizz" << "\n";
        else if(input % 5 == 0)
            std::cout << "buzz" << "\n";
        else 
            std::cout << input << "\n";
            
    }

    return 0;
}