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


	btreenode(int, bool);

	void traverse();
	int findkey(int);
	void splitchild(int i, btreenode* y);
	void remove(int);
	void borrowfromprev(int);
	void removefromleaf(int);
	void insertnonfull(int, File);
	void merge(int);
	void removefromnonleaf(int);
	btreenode* search(int);
	void borrowfromnext(int);
	int getpred(int);
	int getsucc(int);
	void fill(int);

	friend class btree;

};
