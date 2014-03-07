#pragma once
#include "boilerplate.hpp"

template <typename T>
struct Treap {
	Treap(const T& elem)
		: elem(elem),
		  p(rng()),
		  left(nullptr),
		  right(nullptr)
	{ }
	
	T elem;
	int p;
	Treap<T>* left;
	Treap<T>* right;
};

template <typename T>
Treap<T>* addNode(Treap<T>*& treap, Treap<T>* node) {
	if(treap == nullptr) {
		treap = node;
	} else {
		if(node->elem < treap->elem) {
			addNode(treap->left, node);
			Treap<T>* v = treap->left;
			if(v->p > treap->p) {
				treap->left = v->right;
				v->right = treap;
				treap = v;
			}
		} else {
			addNode(treap->right, node);
			Treap<T>* v = treap->right;
			if(v->p > treap->p) {
				treap->right = v->left;
				v->left = treap;
				treap = v;
			}
		}
	}
	return node;
}

template <typename T>
Treap<T>* lowerBound(Treap<T>* treap, const T& elem) {
	if(treap == nullptr) return nullptr;
	
	if(treap->elem >= elem) {
		Treap<T>* x = lowerBound(treap->left, elem);
		if(x) return x;
		return treap;
	} else {
		return lowerBound(treap->right, elem);
	}
}

template <typename T>
Treap<T>* addNode(Treap<T>*& treap, const T& elem) {
	return addNode(treap, new Treap<T>(elem));
}
