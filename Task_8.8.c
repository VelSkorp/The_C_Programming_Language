#include <string.h>
#include <limits.h>

#define NALLOC 1024

typedef long Align;

union header
{
	struct
	{
		union header* ptr;
		unsigned size;
	} s;

	Align x;
};

typedef union header Header;

void* mymalloc(unsigned);
void* mycalloc(unsigned, unsigned);
Header* morecore(unsigned);
void myfree(void*);
void bfree(void*, unsigned);

#include <stdio.h>

int main(void)
{
	char* p;
	int i = 0;
	char s[1096];

	if ((p = mycalloc(100, sizeof(p))) == NULL)
	{
		printf("calloc returned NULL.\n");
	}
	else
	{
		for (i = 0; i < 100; i++)
		{
			printf("%08X ", p[i]);

			if (i % 8 == 7)
			{
				printf("\n");
			}
		}

		printf("\n");
		myfree(p);
	}

	printf("array is at %p\n", s);
	bfree(s, sizeof(s));

	if ((p = mycalloc(sizeof(char), 1024)) == NULL)
	{
		printf("calloc returned NULL.\n");
	}
	else
	{
		printf("calloc is at %p\n", p);
		strcpy(p, "Hello!");
		printf("%s\n", p);
		myfree(p);
	}

	return 0;
}

static Header base;
static Header* freep = NULL;

void* mymalloc(unsigned nbytes)
{
	Header* p, * prevp;
	unsigned nunits = (nbytes * sizeof(Header) - 1) / sizeof(Header) + 1;

	if (nbytes == 0 || nbytes >= UINT_MAX - NALLOC)
	{
		fprintf(stderr, "malloc: invalid size %u\n", nbytes);
		return NULL;
	}

	if ((prevp = freep) == NULL)
	{
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}

	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr)
	{
		if (p->s.size >= nunits)
		{
			if (p->s.size == nunits)
			{
				prevp->s.ptr = p->s.ptr;
			}
			else
			{
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}

			freep = prevp;
			return (void*)(p + 1);
		}

		if (p == freep)
		{
			if ((p = morecore(nunits)) == NULL)
			{
				return NULL;
			}
		}
	}
}

void* mycalloc(unsigned n, unsigned size)
{
	void* p;
	unsigned t = n * size;

	if ((p = mymalloc(t)) == NULL)
	{
		return NULL;
	}

	memset(p, 0x00, t);
	return p;
}

Header* morecore(unsigned nu)
{
	char* cp, * sbrk(int);
	Header* up;

	if (nu < NALLOC)
	{
		nu = NALLOC;
	}

	cp = sbrk(nu * sizeof(Header));

	if (cp == (char*)-1)
	{
		return NULL;
	}

	up = (Header*)cp;
	up->s.size = nu;

	myfree((void*)(up + 1));
	return freep;
}

void myfree(void* ap)
{
	Header* bp, * p;

	bp = (Header*)ap - 1;

	if (bp->s.size == 0 || bp->s.size >= UINT_MAX - NALLOC)
	{
		fprintf(stderr, "free: invalid block size %u\n", bp->s.size);
		return;
	}

	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
	{
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
		{
			break;
		}
	}

	if (bp + bp->s.size == p->s.ptr)
	{
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	}
	else
	{
		bp->s.ptr = p->s.ptr;
	}

	if (p + p->s.size == bp)
	{
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	}
	else
	{
		p->s.ptr = bp;
	}

	freep = p;
}

void bfree(void* p, unsigned n)
{
	Header* bp;

	if (n < NALLOC)
	{
		fprintf(stderr, "bfree: block is to short, %u must be at least %u\n", n, NALLOC);
		return;
	}

	bp = (Header*)p;
	bp->s.size = (n / sizeof(Header)) - 1;
	myfree((void*)(bp + 1));
}