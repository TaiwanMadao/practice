#include "heap.h"
#include "util.h"

struct _heap *create(const struct _node * const item, int const num){
	struct _heap *heap;
	if(num >= MAX_HEAP_NUM){
		fprintf(stderr, "The number of input elements should be less than MAX_HEAP_NUM: %d\n", MAX_HEAP_NUM);
		exit(1);
	}
	
	heap = malloc(sizeof *heap);
	memcpy(&heap->tree[1], item, num * sizeof *item);
	heap->num = num;
	for(int idx = (num >> 1); idx >= 1; idx--){
		heapify(heap, idx, DOWNWARD);
	}
	
	return heap;
}

void heapify(struct _heap * const heap, const int idx, const DIRECTION flag){
	int parent, child, count, min;
	
	if(flag){
		if(idx > (heap->num >> 1))
			return;
		child = idx << 1;
		min = idx;
		for(int i = 0; i < 2 && (child + i) <= heap->num; i++){
			if(heap->tree[min].key > heap->tree[child + i].key){
				min = child + i;
				count = i;
			}
		}
		if(min != idx){
			child += count;
			swap(heap->tree[idx], heap->tree[child]);
			heapify(heap, child, DOWNWARD);
		}
	}else{
		if(idx <= 1)
			return;
		parent = idx >> 1;
		if(heap->tree[idx].key < heap->tree[parent].key){
			swap(heap->tree[idx], heap->tree[parent]);
			heapify(heap, parent, UPWARD);
		}
	}
}

int top(const struct _heap * const heap){
	if(heap->num <= 0){
		fprintf(stderr, "Empty heap\n");
		exit(1);
	}
	return heap->tree[1].element;
}

void push(struct _heap * const heap, const struct _node * const node){
	int idx = ++heap->num;
	heap->tree[idx] = *node;
	heapify(heap, idx, UPWARD);
}

int pop(struct _heap * const heap){
	int min;
	if(heap->num <= 0){
		fprintf(stderr, "Empty heap\n");
		exit(1);
	}
	min = heap->tree[1].element;
	heap->tree[1] = heap->tree[heap->num--];
	heapify(heap, 1, DOWNWARD);
	return min;
}

void change(struct _heap * const heap, const int element, const int key){
	int idx, flag;
	for(idx = 1; idx <= heap->num; idx++){
		if(heap->tree[idx].element == element)
			break;
	}
	if(idx > heap->num){
		fprintf(stderr, "Unable to find element: %d", element);
		exit(1);
	}
	
	flag = (key > heap->tree[idx].key);
	heap->tree[idx].key = key;
	
	if(flag)  //increase key
		heapify(heap, idx, DOWNWARD);
	else      //decrease key
		heapify(heap, idx, UPWARD);
	
}