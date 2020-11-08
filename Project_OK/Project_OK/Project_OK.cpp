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
    std::cout << "4.Dodaj wiele wierzcholkow" << std::endl;
    std::cout << "5.Wylosuj wierzcholek startowy" << std::endl;
    std::cout << "6.Ustal wierzcholek startowy" << std::endl;
    std::cout << "7.Generuj losowa instancje poczatkowa" << std::endl;
    std::cout << "8.Usun wszystkie punkty" << std::endl;
    std::cout << "Komenda e konczy dzialanie programu" << std::endl;

}
void add_point(Map& m)
{
    int x, y;
    std::string name;

    std::cout << "Podaj nazwe: " << std::endl; std::cin >> name;
    std::cout << "Podaj wsp x: " << std::endl; std::cin >> x;
    std::cout << "Podaj wsp y: " << std::endl; std::cin >> y;
    m.Add_point(name, std::move(x), std::move(y));
 
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
void add_multiple(Map& m)
{
    int rows;
    int x, y;
    std::string name;
    printf("Podaj ilosc dodawanych wierzcholkow: ");
    std::cin >> rows;
    printf("Podaj punkty w formacie <nazwa> <x> <y>\n");
    for (int i = 0; i < rows; i++)
    {
        std::cin >> name;
        std::cin >> x;
        std::cin >> y;
        m.Add_point(name, std::move(x), std::move(y));
    }
}
void random_begin(Map& m)
{
    m.Random_begin();
}
void custom_begin(Map& m)
{
    printf("Podaj nazwe wierzcholka startowego: ");
    std::string first;
    std::cin >> first;
    m.Custom_begin(first);
}
void del_all_p(Map& m)
{
    m.Del_all_points();
}
void gen_instance(Map& m)
{
    int h_much, m_x, m_y;
    printf("Podaj ilosc dodawanych wierzcholkow: ");
    std::cin >> h_much;
    printf("Podaj max x: ");
    std::cin >> m_x;
    printf("Podaj max y: ");
    std::cin >> m_y;
    m.Generating_instance(h_much, m_x, m_y);
    m.Print_points();
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
        case '4':
            add_multiple(*k_map);
            break;
        case '5':
            random_begin(*k_map);
            break;
        case '6':
            custom_begin(*k_map);
            break;
        case '7':
            gen_instance(*k_map);
            break;
        case '8':
            del_all_p(*k_map);
            break;
        default:
            break;
        }
        if (choice == 'e')
        {
            break;
        }
    }
}
