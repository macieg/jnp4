#ifndef HOLDINGHH
#define HILDINGHH

/*
 * Pomocnicze funkcje constexpr z podstawowymi operacjami arytmetycznymi.
 */
constexpr unsigned int minus(unsigned int a, unsigned int b)
{
	return (a > b) ? (a-b) : 0;
}

constexpr unsigned int divide(unsigned int a, unsigned int b)
{
	return (b != 0) ? a/b : 0;
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
 * Firmy skladajace się tylko z jednego przedsiabiorstwa.
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
 * Struktura reprezentująca firmę C1 pomniejszoną o C2.
 */
template<class C1, class C2> struct remove_comp {
	typedef Company
	<
		minus(C1::acc, C2::acc),
		minus(C1::hs, C2::hs),
		minus(C1::exo, C2::exo)
	> type;
};

/*
 * Struktura reprezentująca firmę C1 powiększoną n-krotnie.
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
 * Struktura rozbijająca firmę C1 na n mniejszych (całkowitoliczbowo, reszta przepada).
 */
template<class C1, int n> struct split_comp {
	typedef Company
	<
		divide(C1::acc, n),
		divide(C1::hs, n),
		divide(C1::exo, n)
	> type;
};

/*
 * Struktura reprezentująca firmę C z powiększoną o jeden liczbą wszystkich przedsiębiorstw wchodzących w skład firmy.
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
 * Struktura reprezentująca firmę C z pomniejszoną o jeden liczbą wszystkich przedsiębiorstw wchodzączych w skład firmy.
 */
template<class C> struct additive_rollup_comp {
	typedef Company
	<
		minus(C::acc, 1),
		minus(C::hs, 1),
		minus(C::exo, 1)
	> type;
};

/*
 * Zwiększa o jeden liczbę przedsiębiorstw (wszystkich typów) wchodzących w skład każdej firmy należącej do grupy s1,
 * nie zmieniając wartości pojedynczego przedsiębiorstwa 
 */
template<class C>
Group<typename additive_expand_comp<C>::type> const
additive_expand_group(Group<C> const &s1);

/*
 * Zwiększa dziesięciokrotnie liczbę przedsiębiorstw (wszystkich typów) wchodzących w skład każdej firmy należącej 
 * do grupy s1, nie zmieniając wartości pojedynczego przedsiębiorstwa.
 */
template<class C>
Group<typename multiply_comp<C, 10>::type> const
multiplicative_expand_group(Group<C> const &s1);

/*
 * Zmniejsza o jeden liczbę przedsiębiorstw (wszystkich typów) wchodzących w skład każdej firmy należącej 
 * do grupy s1, nie zmieniając wartości pojedynczego przedsiębiorstwa.
 */
template<class C>
Group<typename additive_rollup_comp<C>::type> const
additive_rollup_group(Group<C> const &s1);

/*
 * Zmniejsza dziesięciokrotnie liczbę przedsiębiorstw (wszystkich typów) wchodzących w skład każdej firmy 
 * należącej do grupy s1, nie zmieniając wartości pojedynczego przedsiębiorstwa.
 */
template<class C>
Group<typename split_comp<C, 10>::type> const
multiplicative_rollup_group(Group<C> const &s1);

/*
 * Funkcja, która pomoże nam określać, czy możliwe jest wyłonienie zwycięzcy przetargu 
 * w przypadku, gdy startują w nim grupy g1, g2 oraz g3. Zwycięzcą zostaje grupa,
 * która jest największa w sensie porządku zdefiniowanego na grupach.
 */
template<class C1, class C2, class C3>
bool
solve_auction(Group<C1> const &g1, Group<C2> const &g2, Group<C3> const &g3);

/*
 * Klasa reprezentująca grupę równoważnych firm.
 */
template<struct S> //...?
class Group<Company> {
	private:
		unsigned int company_counter;
		unsigned int acc_val;
		unsigned int hs_val;
		unsigned int exo_val;
	public:
		/*
		 * Definicja typu reprezentujacego strukture pojedynczej firmy.
		 */
		typedef typename Company company_type; //??
		
		/*
		 * Zmienna statyczna.
		 */
		company_type company;
		
		/*
		 * Konstruktor domyślny tworzący grupę skłądającą się tylko z jednej firmy.
		 */
		Group();

		/*
		 * Konstruktor tworzący grupę składającą się z k-firm o identycznej strukturze.
		 */
		Group(unsigned int k);

		/*
		 * Konstruktor kopiujący.
		 */
		Group(Group<Company> const& g) { 
			this.company_type = g.company_type;
			this.company_counter = g.get_size();
			this.company.acc_counter = g.company.acc_counter;
			this.company.hs_counter = g.company.hscounter;
			this.company.exo_counter = g.company.exo_counter;
			set_acc_val(g.company.get_acc_val());
			set_hs_val(g.company.get_hs_val());
			set_exo_val(g.company.get_exo_val());
			return this;
		}

		/*
		 * Zwraca liczbę firm wchodzących w skład grupy.
		 */
		unsigned int get_size() const {
			return company_counter;
		}

		/*
		 * Ustawia nową wartosc biur podatkowych.
		 */
		void set_acc_val(unsigned int i) {
			acc_val = i;
		}

		/*
		 * Ustawia nową wartosc sklepów myśliwskich.
		 */
		void set_hs_val(unsigned int i) {
			hs_val = i;
		}

		/*
		 * Ustawia nową wartosc kantorów.
		 */
		void set_exo_val(unsigned int i) {
			exo_val = i;
		}

		/*
		 * Metoda zwracająca wartość biura rachunkowego.
		 */		
		unsigned int get_acc_val() const {
			return acc_val;
		}
		
		/*
		 * Metoda zwracająca wartość sklepu mysliwskiego.
		 */		
		unsigned int get_hs_val() const {
			return hs_val;
		}
		
		/*
		 * Metoda zwracająca wartość kantoru.
		 */
		unsigned int get_exo_val() const {
			return exo_val;
		}

		/*
		 * Metoda zwracająca wartość grupy.
		 */
		unsigned int get_value() const {
			return (acc_val * company.acc_counter) + (hs_val * company.hs_counter)
				+ (exo_val * company.exo_counter); 
		}
		
		/*
		 * Metoda dodajaca do liczby firm w grupie liczbe firm z drugiej grupy.
		 * Wartość pojedynczego przedsiębiorstwa w nowej grupie liczymy jako średnią 
		 * ważoną wartości firm z sumowanych grup.
		 */
		Group& operator += (Group<Company> const& g) { /*bardzo mozliwe, ze do g trzeb sie dostac poprzez g.get..()*/
			this->acc_val = (company.acc_counter * acc_val + g.company.acc_counter * g.get_acc_val())
				/ (company.acc_counter + g.company.acc_counter);
			this->hs_val = (company.hs_counter * acc_val + g.company.hs_counter * g.get_hs_val())
				/ (company.hs_counter + g.company.hs_counter);
			this->acc_val = (company.exo_counter * exo_val + g.company.exo_counter * g.get_exo_val())
				/ (company.exo_counter + g.company.exo_counter);
			this->company_counter += g.get_size();
			return *this;
		}
		
		/*
		 * Metoda zwracajaca nowa grupe o liczbie firm rownej sumie liczb firm z dwoch grup.
		 */
		Group operator + (Group<Company> const& g) {
			//nie daloby sie jakos tak? z uzyciem kontrukotra kopiujacego i gornej metody?
			return Group(this += g);
		}
		
		/*
		 * Metoda zodejmujaca od liczby firm z grupy liczbe firm z drugiej grupy.
		 * Wartość pojedynczego przedsiębiorstwa w nowej grupie liczymy jako średnią 
		 * ważoną wartości firm z sumowanych grup.
		 */
		Group& operator -= (Group<Company> const& g);
			this->acc_val = (company.acc_counter * acc_val - g.company.acc_counter * g.get_acc_val())
				/ (company.acc_counter - g.company.acc_counter);
			this->hs_val = (company.hs_counter * acc_val - g.company.hs_counter * g.get_hs_val())
				/ (company.hs_counter - g.company.hs_counter);
			this->acc_val = (company.exo_counter * exo_val - g.company.exo_counter * g.get_exo_val())
				/ (company.exo_counter - g.company.exo_counter);
			this->company_counter += g.get_size();
			return *this;
		/*
		 * Metoda zwracajaca nowa grupe o liczbie firm rownej roznicy liczb firm z dwoch grup.
		 */
		Group operator - (Group<Company> const& g) {
			//podobne poytanie jak w dodawaniu
		}
		
		/*
		 * Metoda zwiekszajaca liczbe firm w grupie i razy.
		 * Przy mnożeniu grupy przez n wartość pojedynczego przedsiębiorstwa
		 * ulega zmniejszeniu n razy.
		 */
		Group& operator *= (unsigned int i);
		
		/*
		 * Metoda zwracajaca grupe o liczbie firm i razy wiekszej.
		 * Przy mnożeniu grupy przez n wartość pojedynczego przedsiębiorstwa
		 * ulega zmniejszeniu n razy.
		 */
		Group operator * (unsigned int i);		
		
		/*
		 * Metoda zmniejszajaca liczbe firm w grupie i razy.
		 * Pzy dzieleniu grupy przez n wartość pojedynczego przedsiębiorstwa
		 * zwiększa się n razy. 
		 */
		Group& operator /= (unsigned int i);
		
		/*
		 * Metoda zwracajaca grupe o liczbie firm i razy mniejszej.
		 * Pzy dzieleniu grupy przez n wartość pojedynczego przedsiębiorstwa
		 * zwiększa się n razy. 
		 */
		Group operator / (unsigned int i);		
		
		/*
		 * Metoda sprawdzajaca rownosc
		 */
		bool operator == (Group const& g);
		
		/*
		 * Metoda sprawdzajaca nierownosc
		 */
		bool operator != (Group const& g);	
		
		/*
		 * Metoda sprawdzajaca wiekszosc
		 */
		bool operator > (Group const& g);	
		
		/*
		 * Metoda sprawdzajaca mniejszosc 
		 */
		bool operator == (Group const& g);		
		
		/*
		 * Metoda sprawdzajaca bycie nie wieszym
		 */
		bool operator <= (Group const& g);

		/*
		 * Metoda sprawdzajaca bycie nie mniejszym
		 */
		bool operator >= (Group const& g);	
		
		/*
		 * Metoda wypisujaca na strumien opis grupy
		 */
		ostream& operator << (ostream& os, Group const& g) {
			os << "Number of companies: " << g.get_size() << "; Value: " << g.get_value() <<
				"\nAccountancies value: " << g.get_acc_val() << ", Hunting shops value: " << g.get_hs_val() <<
				", Exchange offices value: " << g.get_exo_val() << endl;
			return os;
		}
};

#endif
