
class IntrusiveLink {
	IntrusiveLink *prev, *next;

	// non-copyable
	IntrusiveLink(const IntrusiveLink &);
	IntrusiveLink &operator=(const IntrusiveLink &);

public:
	IntrusiveLink() : prev(0), next(0) {}
	~IntrusiveLink() { unlink(); }

	void unlink() {
		if (prev) prev->next = next;
		if (next) next->prev = prev;
		prev = 0;
		next = 0;
	}

	bool is_linked() {
		return prev != 0;
	}

private:
	IntrusiveLink(IntrusiveLink *prev, IntrusiveLink *next) : prev(prev), next(next) {}

	void insert_after(IntrusiveLink *a) {
		assert(a);
		IntrusiveLink *b = a->next;
		assert(b);
		assert(!prev);
		assert(!next);
		prev = a;
		next = b;
		a->next = this;
		b->prev = this;
	}

	void swap(IntrusiveLink &link) {
		IntrusiveLink *p = prev;
		IntrusiveLink *n = next;
		prev = link.prev;
		next = link.next;
		link.prev = p;
		link.next = n;
	}

	template <class T, IntrusiveLink T::*LinkField> friend class List;
};
