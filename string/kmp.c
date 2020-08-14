#include "util.h"

struct _queue
{
	int box[MAX_STR_SIZE];
	int head;
	int tail;
	int num;
};

void KMP(const char * const, const char * const);
int match(const char * const, const char * const, const int * const, const int);
void fail(const char * const, int *);
void push(struct _queue * const, const int);
int pop(struct _queue * const);

int main(void)
{
	char txt[MAX_STR_SIZE];
	char pat[MAX_STR_SIZE];
	
	printf("A pratice of kmp algorithm in C.\n");
	printf("Please enter text:\n");
	scanf("%s", txt);
	printf("Please enter pattern:\n");
	scanf("%s", pat);
	
	KMP(txt, pat);
	
	return 0;
}

void KMP(const char * const txt, const char * const pat)
{
	const int txtlen = strlen(txt);
	const int patlen = strlen(pat);
	int txtbase = 0, flag = 0;
	int * const F = calloc(patlen, sizeof *F);
	struct _queue* Q = malloc(sizeof *Q);;
	
	fail(pat, F);
	Q->tail = -1;
	
	while(patlen <= (txtlen - txtbase))
	{
		int pos = match(&txt[txtbase], pat, F, flag);
		if(pos == -1)
			break;
		push(Q, txtbase += pos);
		txtbase += patlen;
		txtbase -= F[patlen - 1];
		flag = 1;
	}
	
	printf("Position: ");
	while(Q->num > 0)
		printf("%d ", pop(Q));
	
	free(F);
	free(Q);
}

int match(const char * const txt, const char * const pat, const int * const F, const int flag)
{
	const int txtlen = strlen(txt);
	const int patlen = strlen(pat);
	int txtidx;
	int patidx;
	txtidx = patidx = flag ? F[patlen - 1] : 0;
	
	while(txtidx < txtlen && patidx < patlen)
	{
		if(txt[txtidx] == pat[patidx])
		{
			txtidx++;
			patidx++;
		}
		else if(patidx == 0)
			txtidx++;
		else
			patidx = F[patidx - 1];
	}
	
	return patidx == patlen ? (txtidx - patlen) : -1;
}

void fail(const char* pat, int *F)
{
	int patlen = strlen(pat);
	int i = 0;
	int j = 1;
	
	while(j < patlen)
	{
		if(pat[i] == pat[j])
		{
			//The K-Part of KMP algorithm
			if(i > 0)
				F[j - 1] = F[F[j - 1] - 1];
			//Avoid the frequent jumps
			F[j] = i + 1;
			i++;
			j++;
		}
		else if(i == 0)
			j++;
		else
			i = F[i - 1];
	}
}

void push(struct _queue * const Q, const int v)
{
	Q->num++;
	Q->box[++Q->tail] = v;
}

int pop(struct _queue * const Q)
{
	Q->num--;
	return Q->box[Q->head++];
}
