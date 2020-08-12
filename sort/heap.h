#ifndef HEAP_H
#define HEAP_H
#define MAX_HEAP_NUM 256
struct _node{
	int key;
	int element;
};
struct _heap{
	struct _node tree[MAX_HEAP_NUM];
	int num;
};
typedef enum {UPWARD, DOWNWARD} DIRECTION;
struct _heap *create(const struct _node * const, int const);
void heapify(struct _heap * const, const int, const DIRECTION);
int top(const struct _heap * const);
void push(struct _heap * const, const struct _node * const);
int pop(struct _heap * const);
void change(struct _heap * const, const int, const int);
#endif