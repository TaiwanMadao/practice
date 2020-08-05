#include "util.h"
#define LFT 0x0
#define RGT 0x1
#define REVERSE(D) ((D & RGT) ? LFT : RGT)

struct thrtree{
	char data;
	int thread[2];
	struct thrtree *child[2];
};

struct thrtree *innbr(const struct thrtree * const, const int);
void intrav(const struct thrtree * const);
struct thrtree *insrch(const struct thrtree * const, const char);
void insert(struct thrtree * const, struct thrtree * const, const int);

int main(){
	char txt[MAX_STR_SIZE];
	struct thrtree *root = malloc(sizeof *root);
	root->data = 'R';
	memcpy(&root->thread, (int [2]){1, 0}, sizeof(int [2]));
	memcpy(&root->child, (struct thrtree * [2]){root, root}, sizeof(struct thrtree * [2]));
	printf("Enter a threaded tree\n");
	scanf("%s", txt);
	return 0;
}

struct thrtree *innbr(const struct thrtree * const n, const int dir){
	int anr = REVERSE(dir);
	struct thrtree *tmp = n->child[dir];
	if(!n->thread[dir])
		for(; !tmp->thread[anr]; tmp = tmp->child[anr]);
	return tmp;
}

void intrav(const struct thrtree * const root){
	for(struct thrtree *tmp = innbr(root, RGT); tmp != root; tmp = innbr(tmp, RGT)){
		printf("%c", tmp->data);
	}
	printf("\n");
}

struct thrtree *insrch(const struct thrtree * const root, char data){
	struct thrtree *tmp = innbr(root, RGT);
	for(; tmp != root; tmp = innbr(tmp, RGT)){
		if(tmp->data == data)
			return tmp;
	}
	fprintf(stderr, "Data:%d not found\n", data);
	exit(1);
}

void insert(struct thrtree * const p, struct thrtree * const c, const int dir){
	int anr = REVERSE(dir);
	
	c->thread[dir] = p->thread[dir];
	c->child[dir] = p->child[dir];
	
	p->thread[dir] = 0;
	p->child[dir] = c;
	
	c->thread[anr] = 1;
	c->child[anr] = p;
	
	if(!c->thread[dir])
		innbr(c, dir)->child[anr] = c;
}