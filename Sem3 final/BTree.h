#pragma once
#include<iostream>
#include"File.h"
#include"BTreeNode.h"

class btree
{
	btreenode* root;
	int t;

public:

	btree(int _t);
	void traverse();
	void insert(int k, File f);
	btreenode* search(int k);
	void remove(int k);
};

