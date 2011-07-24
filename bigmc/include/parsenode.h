#ifndef _PARSENODE_H
#define _PARSENODE_H

#define NODE_PARSE 0
#define NODE_PREFIX 1
#define NODE_PARALLEL 2
#define NODE_REACTION 4
#define NODE_NAME 8
#define NODE_HOLE 16
#define NODE_SEQ 32
#define NODE_INTERFACE 64
#define NODE_SIGNATURE 128
#define NODE_CONTROL 256
#define NODE_PROPERTY 512
#define NODE_BIN	1024
#define NODE_QUERY	2048
#define NODE_NOT	4096
#define NODE_PRED	8192
#define NODE_NUM	16384
#define NODE_IF		32768

#define OPR_NEQ	1
#define OPR_EQ	2
#define OPR_LEQ	3
#define OPR_GEQ	4
#define OPR_GT	5
#define OPR_LT	6
#define OPR_AND	7
#define OPR_OR	8

class parsenode {
	int filepos;
public:
	int type;
	parsenode();
	~parsenode();
	virtual string to_string();
	virtual bool is_valid();
	virtual vector<parsenode *> get_children();
};

class namenode : public parsenode {
public:
	char *nme;
	name hash;
	namenode(char *id);
	~namenode();
	string to_string();
	bool is_valid();
	vector<parsenode *> get_children();
};

class controlnode : public parsenode {
public:
	parsenode *name;
	parsenode *links;
	controlnode(parsenode *id, parsenode *linkseq);
	controlnode(namenode *id, parsenode *linkseq);
	~controlnode();
	string to_string();
	bool is_valid();
	vector<parsenode *> get_children();
};

class prefixnode : public parsenode {
public:
	controlnode *prefix;
	parsenode *suffix;
	prefixnode(parsenode *p, parsenode *q);
	prefixnode(controlnode *p, parsenode *q);
	~prefixnode();
	string to_string();
	bool is_valid();
	vector<parsenode *> get_children();
};

class parallelnode : public parsenode {
public:
	parsenode *lhs;
	parsenode *rhs;
	parallelnode(parsenode *l, parsenode *r);
	~parallelnode();
	string to_string();
	bool is_valid();
	vector<parsenode *> get_children();
};

class reactionnode : public parsenode {
public:
	parsenode *redex;
	parsenode *reactum;
	reactionnode(parsenode *red, parsenode *reac);
	~reactionnode();
	string to_string();
	bool is_valid();
	vector<parsenode *> get_children();
};



class holenode : public parsenode {
public:
	int n;
	holenode(int id);
	~holenode();
	string to_string();
	bool is_valid();
	vector<parsenode *> get_children();
};

class seqnode : public parsenode {
public:
	parsenode *lhs;
	parsenode *rhs;
	seqnode(parsenode *l, parsenode *r);
	~seqnode();
	string to_string();
	bool is_valid();
	vector<parsenode *> get_children();
};

class interfacenode : public parsenode {
public:
	parsenode *name;
	bool outer;
	interfacenode(parsenode *n, bool is_outer);
	~interfacenode();
	string to_string();
	bool is_valid();
	vector<parsenode *> get_children();
};

class signaturenode : public parsenode {
public:
	parsenode *name;
	bool active;
	int arity;
	signaturenode(parsenode *n, bool is_active, int ar);
	~signaturenode();
	string to_string();
	bool is_valid();
	vector<parsenode *> get_children();
};

class propertynode : public parsenode {
public:
	parsenode *prop;
	string name;
	propertynode(char *nm, parsenode *p);
	~propertynode();
	string to_string();
};


class binnode : public parsenode {
public:
	parsenode *lprop;
	parsenode *rprop;
	int oper;
	binnode(parsenode *l, int opr, parsenode *r);
	~binnode();
	string to_string();
};

class notnode : public parsenode {
public:
	parsenode *prop;
	notnode(parsenode *p);
	~notnode();
	string to_string();
};

class prednode : public parsenode {
public:
	parsenode *prop;
	string name;
	prednode(char *name, parsenode *n);
	~prednode();
	string to_string();
};

class numnode : public parsenode {
public:
	int data;
	numnode(int d);
	~numnode();
	string to_string();
};

class querynode : public parsenode {
public:
	parsenode *prop;
	string name;
	querynode(char *name, parsenode *n);
	~querynode();
	string to_string();
};

class ifnode : public parsenode {
public:
	parsenode *cond;
	parsenode *tbranch;
	parsenode *fbranch;
	ifnode(parsenode *c, parsenode *t, parsenode *f);
	~ifnode();
	string to_string();
};


#endif
