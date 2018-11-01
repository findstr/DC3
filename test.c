#include <assert.h>
#include <stdint.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include "dc3.h"

#define NEW(t, n)		malloc((n) * sizeof(t))
static int
compare(const uint8_t *a, int na, const uint8_t *b, int nb)
{
	int i, x;
	x = na > nb ? nb : na;
	for (i = 0; i < x; i++) {
		if (a[i] < b[i])
			return -1;
		if (a[i] > b[i])
			return 1;
	}
	if (na < nb)
		return -1;
	if (na > nb)
		return 1;
	return 0;
}

static void
print(const char *title, int *a, int s)
{
	int i;
	printf("%s:", title);
	for (i = 0; i < s; i++) {
		printf("'%d', ", a[i]);
	}
	printf("\n");
}

static void
printC(const char *title, const uint8_t *a, int s)
{
	int i;
	printf("%s:", title);
	for (i = 0; i < s; i++) {
		printf("'%c', ", a[i]);
	}
	printf("\n");
}

static void
print_rank(const uint8_t *buf, int r, int from, int size)
{
	int i;
	printf("rank:%02d start:%02d = '", r, from);
	for (i = from; i < size; i++) {
		if (isalpha(buf[i]))
			printf("%c ", buf[i]);
		else
			printf("%d ", buf[i]);
	}
	printf("'\n");
}

static void
print_all_rank(const uint8_t *buf, int *SA, int sn, int size)
{
	int i;
	for (i = 0; i < sn; i++) {
		print_rank(buf, i, SA[i], size);
	}
}

static void
check_all_rank(const uint8_t *buf, int *SA, int sn, int size)
{
	int i;
	for (i = 0; i < sn - 1; i++) {
		int eq = compare(&buf[SA[i]], size - SA[i], &buf[SA[i+1]], size - SA[i+1]);
		if (eq > 0) {
			printf("assert:%d sa:%d sa+1:%d res:%d\n", i, SA[i], SA[i+1], eq);
			assert(eq < 0);
		}
	}
}




int
main(int argc, char * argv[])
{
	time_t t = time(NULL);
	printf("srand:%ld\n", t);
	srand(t);
	int k;
	for (k = 0; k < 1024 ; k++) {
		int *SA;
		int size = rand() % 1204 + 2;
		int j;
		int *p = NEW(int, size);
		for (j = 0; j < size; j++)
			p[j] = rand() % 26 + 'A';
		SA = dc3(p, size);
//		print_all_rank(p, SA, size, size);
		check_all_rank(p, SA, size, size);
		free(SA);
		free(p);
	}
	printf("test finish\n");
	return 0;
}

