
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
template>class C> struct additive_rollup_comp;

/*
 * Klasa reprezentująca grupę równoważnych firm.
 */
class Group<Company> {
	private:

	public:
		/*
		 * Konstruktor domyślny tworzący grupę skłądającą się tylko z jednej firmy.
		 */
		Group();

		/*
		 * Konstruktor tworzący grupę składającą się z k-firm o identycznej strukturze.
		 */
		Group(int k);

		/*
		 * Konstruktor kopiujący.
		 */
		Group(Group<Gear> const&);

		/*
		 * Zwraca liczbę firm wchodzących w skład grupy.
		 */
		unsigned int const& get_size() const;

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
		 * Metoda zwracająca wartość grupy.
		 */
		unsigned int const& get_value() const;
}
