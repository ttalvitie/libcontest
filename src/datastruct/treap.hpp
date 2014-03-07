#pragma once
#include "boilerplate.hpp"

template <typename T>
struct Treap {
	Treap(const T& elem)
		: elem(elem),
		  p(rng()),
		  c{nullptr, nullptr}
	{ }
	
	T elem;
	int p;
	Treap<T>* c[2];
};

template <typename T>
Treap<T>* addNode(Treap<T>*& treap, Treap<T>* node) {
	if(treap == nullptr) {
		treap = node;
	} else {
		int s = make_pair(treap->elem, treap) < make_pair(node->elem, node);
		addNode(treap->c[s], node);
		Treap<T>* v = treap->c[s];
		if(v->p > treap->p) {
			treap->c[s] = v->c[1 - s];
			v->c[1 - s] = treap;
			treap = v;
		}
	}
	return node;
}

template <typename T>
Treap<T>* addNode(Treap<T>*& treap, const T& elem) {
	return addNode(treap, new Treap<T>(elem));
}

template <typename T>
Treap<T>* lowerBound(Treap<T>* treap, const T& elem) {
	if(treap == nullptr) return nullptr;
	
	if(treap->elem >= elem) {
		Treap<T>* x = lowerBound(treap->c[0], elem);
		if(x) return x;
		return treap;
	} else {
		return lowerBound(treap->c[1], elem);
	}
}
