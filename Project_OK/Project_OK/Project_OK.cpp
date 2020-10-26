#include <iostream>

#include "Map.h"

void print_menu(const Map & m)
{
    std::cout <<"*********************************" << std::endl;
    std::cout << std::endl << "Aktualne punkty " << std::endl;
    m.Print_points();
    std::cout << std::endl << "Aktualne najlepsza droga " << std::endl;
    std::cout << "*********************************" << std::endl;
    m.Print_path_force();
    std::cout << "1.Dodaj punkt do mapy" << std::endl;
    std::cout << "2.Usun punkt z mapy" << std::endl;
    std::cout << "3.Aktualizuj droge" << std::endl;

}
void add_point(Map& m)
{
    int x, y;
    std::string name;

    std::cout << "Podaj nazwe: " << std::endl; std::cin >> name;
    std::cout << "Podaj wsp x: " << std::endl; std::cin >> x;
    std::cout << "Podaj wsp y: " << std::endl; std::cin >> y;
    m.Add_point(name, x, y);
    

}
void del_point(Map& m)
{
    std::string name;
    std::cout << "Podaj nazwe: " << std::endl; std::cin >> name;
    m.Del_point(name);
}
void count_path_force_alg(Map& m)
{
    m.Count_path();
}
int main()
{
    char choice;
    Map* k_map = new Map("Komiwoja¿er");

    while (true)
    {
        print_menu(*k_map);
        std::cin>>choice;
        switch (choice)
        {
        case '1':
            add_point(*k_map);
            break;
        case '2':
            del_point(*k_map);
            break;
        case '3':
            count_path_force_alg(*k_map);
            break;
        default:
            break;
        }
    }
}
