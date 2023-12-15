#pragma once
#include<iostream>
#include"File.h"
#include"BTreeNode.h"

class btree
{
	btreenode* root;
	int t;

public:

	btree(int);
	void insert(int, File);
	void traverse();
	void remove(int);
	btreenode* search(int);
};

