#include <typeinfo>
#include <cassert>
#include <iostream>
#include <vector>

#include "holding.hh"

typedef add_comp<Accountancy, Exchange_office>::type small_company;
typedef add_comp<multiply_comp<Hunting_shop, 10>::type, multiply_comp<Exchange_office, 20>::type>::type money;
typedef add_comp<multiply_comp<Hunting_shop, 30>::type, multiply_comp<Exchange_office, 10>::type>::type guns;
typedef add_comp<add_comp<multiply_comp<Accountancy, 2>::type, Exchange_office>::type, Hunting_shop>::type tmp;
typedef multiply_comp<Accountancy, 10>::type tmp2;

int main() {
    Group<Accountancy> s1;
    Group<money> s2(20);
    Group<money> s3(20);
    Group<Exchange_office> s4;
    Group<guns> s5(20);

    // Dodanie dwóch przedsiębiorstw w celu utworzenia większej firmy, która następnie zostaje przekształcona w grupę.
    assert(typeid(Group<add_comp<Accountancy, Exchange_office>::type>::company_type) == typeid(small_company));

    // łączenie grup s1 oraz s4, oraz sprawdzanie rozmiaru utworzonej grupy
    assert(join_groups(s1, s4).get_size() == 1);

    // porównywanie typów dwóch firm
    assert(typeid(join_groups(s1, s4).company) == typeid(small_company));

    // sprawdzanie rozmiaru utworzonych grup
    assert((s2 + s3).get_size() == 40);
    assert((s2 += s2).get_size() == 40);
    assert(s2.get_size() == 40);

    // porównywanie dwóch grup
    assert(s2 > s3);

    // porównywanie typów dwóch firm powstałych w wyniku bardzej złożonych operacji
    assert(typeid(split(s3).company) == typeid(add_comp<multiply_comp<Hunting_shop, 5>::type,multiply_comp<Exchange_office, 10>::type>::type));

    // sprawdzanie rozmiaru
    assert(split(s3).get_size() == 20);

    // porównywanie typów dwóch firm
    assert(typeid(split(split(s3)).company)
        == typeid(add_comp<multiply_comp<Hunting_shop, 2>::type,
                           multiply_comp<Exchange_office, 5>::type>::type));

    // sprawdzanie rozmiarów
    assert(split(split(s3)).get_size() == 20);
    assert((s2 - s3).get_size() == 20);
    assert((s3 - s2).get_size() == 0);

    // Przykład na to, że aukcja może nie mieć zwycięzcy.
    assert(solve_auction(s1, s2, s5) == false);

    std::cout << "Gra gitara!" << std::endl;
}

