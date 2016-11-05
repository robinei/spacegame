
template <class T, IntrusiveLink T::*LinkField>
class IntrusiveList {
	IntrusiveLink head;

	static T *value_of(IntrusiveLink *link) {
		return (T *)((char *)link - (intptr_t)&(((T *)0)->*LinkField));
	}
	static const T *value_of(const IntrusiveLink *link) {
		return (const T *)((const char *)link - (intptr_t)&(((T *)0)->*LinkField));
	}

public:
	typedef int size_type;
	typedef T *value_type;

	IntrusiveList() : head(&head, &head) {}
	~IntrusiveList() { clear(); }

	void clear() {
		while (head.next != &head)
			head.next->unlink();
	}

	void push_front(T *value) {
		(value->*LinkField).insert_after(&head);
	}
	void push_back(T *value) {
		(value->*LinkField).insert_after(head.prev);
	}

	void pop_front() { assert(!empty()); head.next->unlink(); }
	void pop_back()  { assert(!empty()); head.prev->unlink(); }

	T *front() { assert(!empty()); return value_of(head.next); }
	T *back()  { assert(!empty()); return value_of(head.prev); }

	const T *front() const { assert(!empty()); return value_of(head.next); }
	const T *back() const  { assert(!empty()); return value_of(head.prev); }

	size_type size() const {
		size_type count = 0;
		const IntrusiveLink *link = head.next;
		while (link != &head) {
			++count;
			link = link->next;
		}
		return count;
	}
	bool empty() const { return &head == head.next; }

#define LIST_ITERATOR_GUTS(Iter, Const, Prev, Next)                 \
private:                                                            \
	friend IntrusiveList;                                                    \
	Const IntrusiveLink *link;                                           \
public:                                                             \
	typedef typename IntrusiveList::value_type value_type;                   \
	                                                                \
	Iter() : link(0) {}                                             \
	Iter(Const IntrusiveLink *link) : link(link) {}                      \
	Iter(Const T *value) : link(&(value->*LinkField)) {}            \
	                                                                \
	Const T *operator*()  Const { return IntrusiveList::value_of(link); }    \
	Const T *operator->() Const { return IntrusiveList::value_of(link); }    \
	                                                                \
	bool operator==(Iter it) const { return link == it.link; }      \
	bool operator!=(Iter it) const { return link != it.link; }      \
	                                                                \
	Iter &operator++() {                                            \
		link = link->Next;                                          \
		return *this;                                               \
	}                                                               \
	Iter &operator--() {                                            \
		link = link->Prev;                                          \
		return *this;                                               \
	}                                                               \
	Iter operator++(int) {                                          \
		Iter orig(*this);                                           \
		link = link->Next;                                          \
		return orig;                                                \
	}                                                               \
	Iter operator--(int) {                                          \
		Iter orig(*this);                                           \
		link = link->Prev;                                          \
		return orig;                                                \
	}

		class const_iterator {
			LIST_ITERATOR_GUTS(const_iterator, const, prev, next)
		};
		class iterator {
			LIST_ITERATOR_GUTS(iterator, , prev, next)
			operator const_iterator() { return const_iterator(link); }
		};
		class const_reverse_iterator {
			LIST_ITERATOR_GUTS(const_reverse_iterator, const, next, prev)
			operator const_iterator() { return const_iterator(link); }
		};
		class reverse_iterator {
			LIST_ITERATOR_GUTS(reverse_iterator, , next, prev)
			operator const_reverse_iterator() { return const_reverse_iterator(link); }
			operator iterator() { return iterator(link); }
		};

#undef LIST_ITERATOR_GUTS

		iterator begin() { return iterator(head.next); }
		iterator end()   { return iterator(&head); }

		const_iterator begin() const { return const_iterator(head.next); }
		const_iterator end()   const { return const_iterator(&head); }

		reverse_iterator rbegin() { return reverse_iterator(head.prev); }
		reverse_iterator rend()   { return reverse_iterator(&head); }

		const_reverse_iterator rbegin() const { return const_reverse_iterator(head.prev); }
		const_reverse_iterator rend()   const { return const_reverse_iterator(&head); }

		void erase(iterator position) {
			position.link->unlink();
		}

		void insert(iterator position, T *value) {
			(value->*LinkField).insert_after(position.link->prev);
		}
		//template <class InputIterator>
		//void insert(iterator position, InputIterator first, InputIterator last) {
		//}

		void swap(IntrusiveList &list) {
			head.swap(list.head);
		}
};
