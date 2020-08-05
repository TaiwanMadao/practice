#include "util.h"
#include "heap.h"
#include "limits.h"

//comparison sort
void selection(int * const, const int);
void insertion(int * const, const int);
void bubble(int * const, const int);
void merge(int * const, const int);
void quick(int * const, const int);
void heap(int * const, const int);   //advanced selection sort
void shell(int * const, const int);  //advanced insertion sort
void shaker(int * const, const int); //advanced bubble sort
//distribution sort
void counting(int * const, const int);
void bucket(int * const, const int);
void radix(int * const, const int);
//other method
void survey(int * const, int const, int * const, int * const);
void shift(int * const, int const, const int, const int);

void (*sort[])(int *const, const int) = {
	selection,
	insertion,
	bubble,
	merge,
	quick,
	heap,
	shell,
	shaker,
	counting,
	bucket,
	radix
};

int main(){
	int type, num, *item;
	printf("Enter the sort type\n");
	printf("Comparison   -> 0.selection 1.insertion 2.bubble 3.merge 4.quick 5.heap 6.shell 7.shaker\n");
	printf("Distribution -> 8.counting 9.bucket 10.radix\n");
	scanf("%d", &type);
	printf("Enter the number of item\n");
	scanf("%d", &num);	
	item = malloc(num * sizeof *item);
	printf("Enter items\n");
	for(int i = 0; i < num; i++)
		scanf("%d", &item[i]);
	
	sort[type](item, num);
	
	for(int i = 0; i < num; i++)
		printf("%d ", item[i]);	
	free(item);
	return 0;
}

void selection(int * const item, const int num){
	for(int i = 0; i < num; i++){
		int min = i;
		for(int j = i; j < num; j++){
			if(item[min] > item[j])
				min = j;
		}
		swap(item[i], item[min]);
	}
}

void insertion(int * const item, const int num){
	for(int i = 1; i < num; i++){
		int j = i, tmp = item[i];
		for(; j > 0 && item[j - 1] > tmp; j--){
			item[j] = item[j - 1];
		}
		item[j] = tmp;
	}
}

void bubble(int * const item, const int num){
	for(int i = 0, flag = 1; flag && i < num; i++){
		flag = 0;
		for(int j = 1; j < (num - i); j++){
			if(item[j] < item[j - 1]){
				swap(item[j], item[j - 1]);
				flag = 1;
			}
		}
	}
}

void merge(int * const item, const int num){
	if(num == 1)
		return;
	int f_num, r_num, *front, *rear;
	f_num = num >> 1;
	r_num = num - f_num;
	front = malloc(f_num * sizeof *front);
	rear  = malloc(r_num * sizeof *rear );
	memcpy(front, &item[0],     f_num * sizeof *front);
	memcpy(rear,  &item[f_num], r_num * sizeof *rear);
	
	merge(front, f_num);
	merge(rear,  r_num);
	
	for(int f = 0, r = 0, n = 0; f < f_num || r < r_num;){
		if(f == f_num){
			memcpy(&item[n], &rear[r],  (r_num - r) * sizeof *rear);
			break;
		}
		else if(r == r_num){
			memcpy(&item[n], &front[f], (f_num - f) * sizeof *front);
			break;
		}			
		else if(front[f] > rear[r])
			item[n++] = rear[r++];
		else
			item[n++] = front[f++];
	}	
	
	free(front);
	free(rear);
}

void quick(int * const item, const int num){
	if(num == 0 || num == 1)
		return;
	int pivot = item[num - 1], p = 0;
	for(int i = 0; i < num - 1; i++){
		if(item[i] < pivot)
			swap(item[p++], item[i]);
	}
	swap(item[num - 1], item[p]);
	quick(&item[0],     p);
	quick(&item[p + 1], num - p - 1);
}

void heap(int * const item, const int num){
	struct _heap* heap;
	struct _node* _item = malloc(num * sizeof *_item);
	for(int i = 0; i < num; i++){
		_item[i] = (struct _node){ item[i], item[i] };
	}
	
	heap = create(_item, num);
	for(int i = 0; i < num; i++){
		item[i] = pop(heap);
	}
	
	free(heap);
	free(_item);
}

void shell(int * const item, const int num){
	for(int gap = num >> 1; gap > 0; gap >>= 1){
		for(int base = 0; base < gap; base++){
			for(int i = base + gap; i < num; i += gap){
				int j = i, tmp = item[i];
				for(; (j / gap) > 0 && item[j - gap] > tmp; j -= gap){
					item[j] = item[j - gap];
				}
				item[j] = tmp;
			}
		}
	}
}

void shaker(int * const item, const int num){
	for(int i = 0, flag; i < (num >> 1); i++){
		flag = 0;
		for(int j = i + 1; j < (num - i); j++){
			if(item[j] < item[j - 1]){
				swap(item[j], item[j - 1]);
				flag = 1;
			}
		}
		if(!flag)
			break;
		
		flag = 0;
		for(int k = (num - i - 2); k > i; k--){
			if(item[k] < item[k - 1]){
				swap(item[k], item[k - 1]);
				flag = 1;
			}
		}
		if(!flag)
			break;
	}
}

void counting(int * const item, const int num){
	int offset, range, *arr;
	survey(item, num, &offset, &range);
	shift(item, num, offset, 1);
	arr = malloc(range * sizeof *arr);
	memset(arr, 0, range * sizeof *arr);
	
	for(int i = 0; i < num; i++){
		arr[item[i]]++;
	}
	
	for(int v = 0, n = 0; v < range; v++){
		for(int i = 0; i < arr[v]; i++){
			item[n++] = v;
		}
	}
	
	shift(item, num, offset, 0);	
	free(arr);
}

void bucket(int * const item, const int num){
	int offset, range, c = 10, **b, *n;
	survey(item, num, &offset, &range);
	shift(item, num, offset, 1);
	b = malloc(c * sizeof *b);
	for(int i = 0; i < c; i++){
		b[i] = malloc(num * sizeof *b[i]);
	}
	n = malloc(c * sizeof *n);
	memset(n, 0, c * sizeof *n);
	
	for(int i = 0; i < num; i++){
		int idx = item[i] / ((float)range / c);
		b[idx][n[idx]++] = item[i];
	}
	
	for(int i = 0, idx = 0; i < c; i++){
		quick(b[i], n[i]);
		memcpy(&item[idx], b[i], n[i] * sizeof *item);
		idx += n[i];
		free(b[i]);
	}
	
	shift(item, num, offset, 0);	
	free(b);
	free(n);
}

void radix(int * const item, const int num){
	int offset, range, bit, base, exp, mask, c, **b, *n;
	bit = 4;
	base = 1 << bit;
	exp = 1;
	mask = base - 1;
	c = base;
	
	survey(item, num, &offset, &range);
	shift(item, num, offset, 1);	
	b = malloc(c * sizeof *b);
	for(int i = 0; i < c; i++){
		b[i] = malloc(num * sizeof *b[i]);
	}
	n = malloc(c * sizeof *n);
	memset(n, 0, c * sizeof *n);
	
	for(int iter = 0; exp <= range; iter++, exp <<= bit, mask <<= bit){
		for(int i = 0; i < num; i++){
			int r = (item[i] & mask) >> (iter * bit);
			b[r][n[r]++] = item[i];
		}
		for(int i = 0, idx = 0; i < c; i++){
			memcpy(&item[idx], b[i], n[i] * sizeof *item);
			idx += n[i];
			n[i] = 0;
		}
	}
	
	shift(item, num, offset, 0);
	for(int i = 0; i < c; i++){
		free(b[i]);
	}
	free(b);
	free(n);
}

void survey(int * const item, int const num, int * const offset, int * const range){
	int min = 0, max = 0;
	for(int i = 1; i < num; i++){
		if(item[i] < item[min])
			min = i;
		if(item[i] > item[max])
			max = i;
	}
	*offset = item[min];
	*range = item[max] - *offset + 1;
}

void shift(int * const item, int const num, const int offset, const int flag){
	for(int i = 0; i < num; i++){
		item[i] = item[i] - (flag ? offset : -offset);
	}
}