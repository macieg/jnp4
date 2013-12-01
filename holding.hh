/*
 * Struktura reprezentująca połącznie dwóch firm - C1 i C2.
 */
template<class C1, class C2> struct add_comp;

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
class Group<Company> {
	private:

	public:
		/*
		 * Definicja typu reprezentujacego strukture pojedynczej firmy.
		 */
		
		
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
		Group(Group<Company> const& g);

		/*
		 * Zwraca liczbę firm wchodzących w skład grupy.
		 */
		unsigned int get_size() const;

		/*
		 * Ustawia nową liczbę biur podatkowych.
		 */
		void set_acc_val(unsigned int i);

		/*
		 * Ustawia nową liczbę sklepów myśliwskich.
		 */
		void set_hs_val(unsigned int i);

		/*
		 * Ustawia nową liczbę kantorów.
		 */
		void set_exo_val(unsigned int i);

		/*
		 * Metoda zwracająca wartość biura rachunkowego.
		 */		
		unsigned int get_acc_val() const;
		
		/*
		 * Metoda zwracająca wartość sklepu mysliwskiego.
		 */		
		unsigned int get_hs_val() const;
		
		/*
		 * Metoda zwracająca wartość kantoru.
		 */
		unsigned int get_exo_val() const;

		/*
		 * Metoda zwracająca wartość grupy.
		 */
		unsigned int get_value() const;
		
		/*
		 * Metoda dodajaca do liczby firm w grupie liczbe firm z drugiej grupy.
		 * Wartość pojedynczego przedsiębiorstwa w nowej grupie liczymy jako średnią 
		 * ważoną wartości firm z sumowanych grup.
		 */
		Group& operator += (Group<Company> const& g);
		
		/*
		 * Metoda zwracajaca nowa grupe o liczbie firm rownej sumie liczb firm z dwoch grup.
		 */
		Group operator + (Group<Company> const& g);
		
		/*
		 * Metoda zodejmujaca od liczby firm z grupy liczbe firm z drugiej grupy.
		 * Wartość pojedynczego przedsiębiorstwa w nowej grupie liczymy jako średnią 
		 * ważoną wartości firm z sumowanych grup.
		 */
		Group& operator -= (Group<Company> const& g);
		
		/*
		 * Metoda zwracajaca nowa grupe o liczbie firm rownej roznicy liczb firm z dwoch grup.
		 */
		Group operator - (Group<Company> const& g);
		
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
		ostream& operator << (ostream& os, Group const& g);
}
