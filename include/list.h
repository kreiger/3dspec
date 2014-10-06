template<class T>
class Listnode
{
	public:
		Listnode(Listnode<T> *foo, T bar)
		:info(bar), next(foo) {}
		T info;
		Listnode<T> *next;
		friend class List;
};

template<class T>
class List
{
	public:
		List () : first(0),len(0) {}

		bool Get_From_List (T& foo)
		{
			if (len==0) return false;
			foo = first->info;
			Listnode<T> *bar = first;
			first = first->next;
			delete bar;
			len--;
			return true;
		}
		void Add_To_List (T foo)
		{
			first = new Listnode<T> (first,foo);
			len++;
		}
		int Length() {return len;}
	private:
		int len;
		Listnode<T> *first;
};
