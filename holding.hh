template <unsigned int acc_counter, unsigned int hs_counter, unsigned int exo_counter>
struct Company {
	const unsigned int acc_counter = acc_counter;
	const unsigned int hs_counter = hs_counter;
	const unsigned int exo_counter = exo_counter;
}

/*  ???? jak mamy to zapisac?
struct Accountancy = Company<1,0,0>
struct Hunting_shop = Company<0,1,0>
struct Exchange_office = Company<0,0,1>
*/



/*
 * Struktura reprezentująca połącznie dwóch firm - C1 i C2.
 */
template<class C1, class C2> struct add_comp {
 	/*Struktura powinna zawierać publiczną definicję type, opisującą nową firmę. ???*/

}

/*
 * Struktura reprezentująca firmę C1 pomniejszoną o C2.
 */
template<class C1, class C2> struct remove_comp;

/*
 * Struktura reprezentująca firmę C1 powiększoną n-krotnie.
 */
template<class C1, int n> struct multiply_comp;

/*
 * Struktura rozbijająca firmę C1 na n mniejszych (całkowitoliczbowo, reszta przepada).
 */
template<class C1, int n> struct split_comp;

/*
 * Struktura reprezentująca firmę C z powiększoną o jeden liczbą wszystkich przedsiębiorstw wchodzących w skład firmy.
 */
template<class C> struct additive_expand_comp;

/*
 * Struktura reprezentująca firmę C z pomniejszoną o jeden liczbą wszystkich przedsiębiorstw wchodzączych w skład firmy.
 */
template<class C> struct additive_rollup_comp;

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
}
