#pragma once
#include<iostream>
#include"File.h"

class btreenode
{
public:
	int* key;
	File* filepath;

	int t;
	btreenode** c;
	int n;
	bool leaf;


	btreenode(int _t, bool _leaf);
	void insertnonfull(int k, File f);

	void splitchild(int i, btreenode* y);
	void traverse();
	btreenode* search(int k);
	int findkey(int k);
	void remove(int k);
	void removefromleaf(int idx);
	void removefromnonleaf(int idx);
	int getpred(int idx);
	int getsucc(int idx);
	void fill(int idx);
	void borrowfromprev(int idx);
	void borrowfromnext(int idx);
	void merge(int idx);

	friend class btree;

};
