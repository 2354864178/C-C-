
#pragma once
#include <iostream>

#define BinNodePosi(T) BinNode<T>*

void run_binnode_test();

typedef enum {RB_RED, RB_BLACK} RBColor;

template <typename T>
struct BinNode {
	T data;
	BinNodePosi(T) lchild = nullptr;
	BinNodePosi(T) rchild = nullptr;
	BinNodePosi(T) parent = nullptr;
	int height = 0;
	int npl = 1;
	RBColor color = RB_RED;

	BinNode() = default;
	BinNode(const T& e, BinNodePosi(T) p = nullptr, BinNodePosi(T) l = nullptr, BinNodePosi(T) r = nullptr)
		: data(e), lchild(l), rchild(r), parent(p) {}

	BinNodePosi(T) insertAsLC(const T& e) { lchild = new BinNode(e, this); return lchild; }
	BinNodePosi(T) insertAsRC(const T& e) { rchild = new BinNode(e, this); return rchild; }

	int size() const {
		int s = 1;
		if (lchild) s += lchild->size();
		if (rchild) s += rchild->size();
		return s;
	}

	BinNodePosi(T) succ() {
		BinNodePosi(T) s = this;
		if (s->rchild) {
			s = s->rchild;
			while (s->lchild) s = s->lchild;
			return s;
		}
		while (s->parent && s == s->parent->rchild) s = s->parent;
		return s->parent;
	}

	template <typename VST>
	void travPre(const VST& visit) {
		visit(data);
		if (lchild) lchild->travPre(visit);
		if (rchild) rchild->travPre(visit);
	}

	template <typename VST>
	void travIn(const VST& visit) {
		if (lchild) lchild->travIn(visit);
		visit(data);
		if (rchild) rchild->travIn(visit);
	}

	template <typename VST>
	void travPost(const VST& visit) {
		if (lchild) lchild->travPost(visit);
		if (rchild) rchild->travPost(visit);
		visit(data);
	}

	bool operator<(const BinNode& bn) const { return data < bn.data; }
	bool operator>(const BinNode& bn) const { return data > bn.data; }
	bool operator==(const BinNode& bn) const { return data == bn.data; }
	bool operator!=(const BinNode& bn) const { return data != bn.data; }
	bool operator>=(const BinNode& bn) const { return data >= bn.data; }
	bool operator<=(const BinNode& bn) const { return data <= bn.data; }
};


