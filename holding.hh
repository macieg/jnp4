#ifndef HOLDINGHH
#define HILDINGHH

#include <iostream>

/*
 * Domyslne wartosci przedsiebiorstw.
 */
#define ACC_DEFAULT 50
#define HS_DEFAULT 150
#define EXO_DEFAULT 15

/*
 * Pomocnicze funkcje constexpr z podstawowymi operacjami arytmetycznymi.
 */
constexpr unsigned int c_minus(unsigned int a, unsigned int b) //nie mam pewnosci co do koniecznosci uzywania tych constexpr, w innym wypadku mamy problemy z kompilacją
{
	return (a > b) ? (a-b) : 0;
}

constexpr unsigned int c_divide(unsigned int a, unsigned int b)
{
	return (b != 0) ? a/b : 0;
}

unsigned int divide(unsigned int a, unsigned int b)
{
	return (b != 0) ? a/b : 0;
}

unsigned int minus(unsigned int a, unsigned int b)
{
	return (a > b) ? (a-b) : 0;
}

/*
 * Typ Company.
 */
template <unsigned int _acc, unsigned int _hs, unsigned int _exo>
class Company {
	public:
		static const unsigned int acc = _acc;
		static const unsigned int hs = _hs;
		static const unsigned int exo = _exo;
};

/*
 * Firmy skladajace sie tylko z jednego przedsiabiorstwa.
 */
typedef Company<1, 0, 0> Accountancy;
typedef Company<0, 1, 0> Hunting_shop;
typedef Company<0, 0, 1> Exchange_office;

/*
 * Struktura reprezentujaca polacznie dwoch firm - C1 i C2.
 */
template<class C1, class C2> struct add_comp {
	typedef Company<
		C1::acc + C2::acc,
		C1::hs + C2::hs,
		C1::exo + C2::exo
			> type;
};

/*
 * Struktura reprezentujaca firme C1 pomniejszona o C2.
 */
template<class C1, class C2> struct remove_comp {
	typedef Company
		<
		c_minus(C1::acc, C2::acc),
		c_minus(C1::hs, C2::hs),
		c_minus(C1::exo, C2::exo)
			> type;
};

/*
 * Struktura reprezentujaca firme C1 powiekszona n-krotnie.
 */
template<class C1, int n> struct multiply_comp {
	typedef Company
		<
		C1::acc * n,
		C1::hs * n,
		C1::exo * n
			> type;
};

/*
 * Struktura rozbijajaca firme C1 na n mniejszych (calkowitoliczbowo, reszta przepada).
 */
template<class C1, int n> struct split_comp {
	typedef Company
		<
		c_divide(C1::acc, n),
		c_divide(C1::hs, n),
		c_divide(C1::exo, n)
			> type;
};

/*
 * Struktura reprezentujaca firme C z powiekszona o jeden liczba wszystkich przedsiebiorstw wchodzacych w sklad firmy.
 */
template<class C> struct additive_expand_comp {
	typedef Company
		<
		C::acc + 1,
		C::hs + 1,
		C::exo + 1
			> type;
};

/*
 * Struktura reprezentujaca firme C z pomniejszona o jeden liczba wszystkich przedsiebiorstw wchodzaczych w sklad firmy.
 */
template<class C> struct additive_rollup_comp {
	typedef Company
		<
		c_minus(C::acc, 1),
		c_minus(C::hs, 1),
		c_minus(C::exo, 1)
			> type;
};

/*
 * Klasa reprezentujaca grupe rownowaznych firm.
 */
template<class C> class Group {
	private:

		unsigned int company_number;
		unsigned int acc_val;
		unsigned int hs_val;
		unsigned int exo_val;
	public:		

		/*
		 * Definicja typu reprezentujacego strukture pojedynczej firmy.
		 */
		typedef C company_type;

		/*
		 * Zmienna statyczna.
		 */
		static company_type company;

		/*
		 * Konstruktor domyslny tworzacy grupe skladajaca sie z n firm.
		 */
		Group(unsigned int n = 1)
		{
			company_number = n;
			acc_val = ACC_DEFAULT;
			hs_val = HS_DEFAULT;
			exo_val = EXO_DEFAULT;
		}

		/*
		 * Konstruktor kopiujacy.
		 */
		Group(Group<C> const& g)
		{ 
			company_number = g.get_size();
			acc_val = g.get_acc_val;
			hs_val = g.get_hs_val;
			exo_val = g.exo_val;
		}	

		/*
		 * Ustawia nowa wartosc biur podatkowych.
		 */
		void set_acc_val(unsigned int i)
		{
			acc_val = i;
		}

		/*
		 * Ustawia nowa wartosc sklepow mysliwskich.
		 */
		void set_hs_val(unsigned int i)
		{
			hs_val = i;
		}

		/*
		 * Ustawia nowa wartosc kantorow.
		 */
		void set_exo_val(unsigned int i)
		{
			exo_val = i;
		}

		/*
		 * Metoda zwracajaca wartosc biura rachunkowego.
		 */		
		unsigned int get_acc_val() const 
		{
			return acc_val;
		}

		/*
		 * Metoda zwracajaca wartosc sklepu mysliwskiego.
		 */		
		unsigned int get_hs_val() const 
		{
			return hs_val;
		}

		/*
		 * Metoda zwracajaca wartosc kantoru.
		 */
		unsigned int get_exo_val() const
		{
			return exo_val;
		}

		/*
		 * Metoda zwracajaca wartosc grupy.
		 */
		unsigned int const& get_value() const
		{
			return ((acc_val * C::acc) + (hs_val * C::hs) + (exo_val * C::exo)) 
				* company_number; 
		}

		/*
		 * Metoda dodajaca do liczby firm w grupie liczbe firm z drugiej grupy.
		 * Wartosc pojedynczego przedsiebiorstwa w nowej grupie liczymy jako srednia 
		 * wazona wartosci firm z sumowanych grup.
		 */
		Group& operator+=(Group<C> const& g) //z tymi operatorami mam troche watpliwosci, do weryfikacji
		{
			acc_val = divide((C::acc * acc_val + g.company.acc * g.get_acc_val()),
					(C::acc + g.company.acc));
			hs_val = divide((C::hs * acc_val + g.company.hs * g.get_hs_val()),
					(C::hs + g.company.hs));
			exo_val = divide((C::exo * exo_val + g.company.exo * g.get_exo_val()),
					(C::exo + g.company.exo));
			company_number += g.get_size();
			return *this;
		}

		/*
		 * Metoda zwracajaca nowa grupe o liczbie firm rownej sumie liczb firm z dwoch grup.
		 */
		Group operator+(Group<C> const& g)//ten trick jest moim zdaniem ok
		{			
			return *this += g;
		}

		/*
		 * Metoda zodejmujaca od liczby firm z grupy liczbe firm z drugiej grupy.
		 * Wartosc pojedynczego przedsiebiorstwa w nowej grupie liczymy jako srednia 
		 * wazona wartosci firm z sumowanych grup.
		 */
		Group& operator-=(Group<C> const& g)
		{
			acc_val = divide(
					minus(C::acc * acc_val, g.company.acc * g.get_acc_val()),
					(C::acc - g.company.acc)
					);
			hs_val = divide(
					minus(C::hs * acc_val - g.company.hs * g.get_hs_val()),
					(C::hs - g.company.hs)
				       );
			exo_val = divide(
					minus(C::exo * exo_val, g.company.exo * g.get_exo_val()),
					(C::exo - g.company.exo)
					);

			company_number = minus(company_number, g.get_size());
			company_number = 0;

			return *this;
		}

		/*
		 * Metoda zwracajaca nowa grupe o liczbie firm rownej roznicy liczb firm z dwoch grup.
		 */
		Group operator-(Group<C> const& g)
		{
			return *this -= g;
		}

		/*
		 * Metoda zwiekszajaca liczbe firm w grupie i razy.
		 * Przy mnozeniu grupy przez n wartosc pojedynczego przedsiebiorstwa
		 * ulega zmniejszeniu n razy.
		 */
		Group& operator*=(unsigned int i)
		{
			company_number *= i;
			acc_val = divide(acc_val, i);
			hs_val = divide(hs_val, i);
			exo_val = divide(exo_val, i);	
		}

		/*
		 * Metoda zwracajaca grupe o liczbie firm i razy wiekszej.
		 * Przy mnozeniu grupy przez n wartosc pojedynczego przedsiebiorstwa
		 * ulega zmniejszeniu n razy.
		 */
		Group operator*(unsigned int i)
		{
			return *this *= i;
		}		

		/*
		 * Metoda zmniejszajaca liczbe firm w grupie i razy.
		 * Pzy dzieleniu grupy przez n wartosc pojedynczego przedsiebiorstwa
		 * zwieksza sie n razy. 
		 */
		Group& operator/=(unsigned int i)
		{
			company_number = divide(company_number, i);
			acc_val *= i;
			hs_val *= i;
			exo_val *= i;
		}

		/*
		 * Metoda zwracajaca grupe o liczbie firm i razy mniejszej.
		 * Pzy dzieleniu grupy przez n wartosc pojedynczego przedsiebiorstwa
		 * zwieksza sie n razy. 
		 */
		Group operator/(unsigned int i)
		{
			return *this /= i;
		}

		/*
		 * Metoda sprawdzajaca rownosc.
		 */
		template<class D> bool operator==(Group<D> const& g)
		{
			return (C::hs * company_number == D::hs * g.get_size()) &&
				(C::exo * company_number == D::exo * g.get_size());
		}

		/*
		 * Metoda sprawdzajaca nierownosc.
		 */
		template<class D> bool operator != (Group<D> const& g)
		{
			return !(*this == g);
		}

		/*
		 * Metoda sprawdzajaca wiekszosc.
		 */
		template<class D> bool operator>(Group<D> const& g)
		{
			return (C::hs * company_number + C::exo * company_number) >
				(D::hs * g.get_size() + D::exo * g.get_size());
		}

		/*
		 * Metoda sprawdzajaca mniejszosc. 
		 */
		template<class D> bool operator<(Group<D> const& g)
		{
			return (C::hs * company_number + C::exo * company_number) <
				(D::hs * g.get_size() + D::exo * g.get_size());
		}	

		/*
		 * Metoda sprawdzajaca bycie nie wieszym.
		 */
		template<class D> bool operator<=(Group<D> const& g)
		{
			return (*this == g) || (*this < g);
		}

		/*
		 * Metoda sprawdzajaca bycie nie mniejszym.
		 */
		template<class D> bool operator>=(Group<D> const& g)
		{
			return (*this == g) || (*this > g);
		}

		/*
		 * Metoda wypisujaca na strumien opis grupy.
		 */

};

template<class C> std::ostream& operator<<(std::ostream& os, const Group<C> & g) //tutaj nie powinno być jeszcze friend? wyrzucilem na zewnątrz, bo w ciele klasy nie chce sie kompilować
{
	os << "Number of companies: " << g.get_size() << "; Value: " << g.get_value() <<
		"\nAccountancies value: " << g.get_acc_val() << ", Hunting shops value: " << g.get_hs_val() <<
		", Exchange offices value: " << g.get_exo_val() << std::endl;
	return os;
}

/*
 * Zwieksza o jeden liczbe przedsiebiorstw (wszystkich typow) wchodzacych w sklad kazdej firmy nalezacej do grupy s1,
 * nie zmieniajac wartosci pojedynczego przedsiebiorstwa 
 */
template<class C>
Group<typename additive_expand_comp<C>::type> const
additive_expand_group(Group<C> const &s1);

/*
 * Zwieksza dziesieciokrotnie liczbe przedsiebiorstw (wszystkich typow) wchodzacych w sklad kazdej firmy nalezacej 
 * do grupy s1, nie zmieniajac wartosci pojedynczego przedsiebiorstwa.
 */
template<class C>
Group<typename multiply_comp<C, 10>::type> const
multiplicative_expand_group(Group<C> const &s1);

/*
 * Zmniejsza o jeden liczbe przedsiebiorstw (wszystkich typow) wchodzacych w sklad kazdej firmy nalezacej 
 * do grupy s1, nie zmieniajac wartosci pojedynczego przedsiebiorstwa.
 */
template<class C>
Group<typename additive_rollup_comp<C>::type> const
additive_rollup_group(Group<C> const &s1);

/*
 * Zmniejsza dziesieciokrotnie liczbe przedsiebiorstw (wszystkich typow) wchodzacych w sklad kazdej firmy 
 * nalezacej do grupy s1, nie zmieniajac wartosci pojedynczego przedsiebiorstwa.
 */
template<class C>
Group<typename split_comp<C, 10>::type> const
multiplicative_rollup_group(Group<C> const &s1);

/*
 * Funkcja, ktora pomoze nam okreslac, czy mozliwe jest wylonienie zwyciezcy przetargu 
 * w przypadku, gdy startuja w nim grupy g1, g2 oraz g3. Zwyciezca zostaje grupa,
 * ktora jest najwieksza w sensie porzadku zdefiniowanego na grupach.
 */
template<class C1, class C2, class C3>
bool
solve_auction(Group<C1> const &g1, Group<C2> const &g2, Group<C3> const &g3);

#endif
