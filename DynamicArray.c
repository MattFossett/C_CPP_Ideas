#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


typedef struct ArrayList ArrayList;
struct ArrayList {
	int TYPE_SIZE;
	void *base;
	int size;
	int capacity;
};

void *get(struct ArrayList* arr, int index);

void set(ArrayList* arr, int index, void *value);

void trim(ArrayList* arr);

void AL_remove(ArrayList* arr, int index);

void __Array(ArrayList* arr, int t_size, int initSize)
{
	
	arr->TYPE_SIZE = t_size;
	arr->capacity = 10;

	arr->base = malloc(arr->capacity * arr->TYPE_SIZE);
	arr->size = initSize; 
} // void *memcpy(void *dest, const void * src, size_t n)

void reserve(ArrayList* arr, int goodSize)
{
	if (arr->capacity > goodSize){
		return;
	}
	
	arr->capacity = goodSize + 10;
	
	
	void* p = realloc(arr->base, arr->capacity * arr->TYPE_SIZE);

	if (!p)
	{
		printf("bad");
	}
	else
	{
		arr->base = p;
	}
}

void resize(ArrayList* arr, int newSize)
{
	reserve(arr, newSize);
	
	arr->size = newSize;
	trim(arr);
}

void add (ArrayList* arr, int index, void* value){
	arr->size++;
	
	reserve (arr, arr->size);

	memmove (arr->base + (index+1) * arr->TYPE_SIZE, arr->base + (index) * arr->TYPE_SIZE,
		(arr->size - index) * arr->TYPE_SIZE);
	set (arr, index, value);
}

void set(ArrayList* arr, int index, void *value)
{
	void *dest = get(arr , index);
	memcpy(dest, value, arr->TYPE_SIZE);
}

void *get(ArrayList* arr, int index)
{
	return (arr->base + index * arr->TYPE_SIZE);
}

/**
 * Gross Getter Section :) 
 */

int getInt(ArrayList* arr, int index){
	return *(int *) get(arr, index);
}

long getLong(ArrayList* arr, int index){
	return *(long *) get(arr, index);
}

char getChar(ArrayList* arr, int index){
	return *(char *) get(arr, index);
}

float getFloat(ArrayList* arr, int index){
	return *(float *) get(arr, index);
}

double getDouble(ArrayList* arr, int index){
	return *(double *) get(arr, index);
}

/**
 * End Gross Getter Section :)
 */

void push_back(ArrayList* arr, void *value)
{
	arr->size++;
	
	reserve(arr, arr->size + 1);
	
	set(arr, arr->size - 1, value);
}

void pop_back(ArrayList* arr)
{
	arr->size--;
}

void AL_remove(ArrayList* arr, int index){
	arr->size--;
	memmove (arr->base + (index) * arr->TYPE_SIZE, arr->base + (index+1) * arr->TYPE_SIZE,
		(arr->size - index) * arr->TYPE_SIZE );

	
}

int getSize(ArrayList* arr)
{
	return arr->size;
}

void trim(ArrayList* arr){
	arr->capacity = arr->size;
	void* tempPtr = realloc (arr->base, arr->size * arr->TYPE_SIZE);
	arr->base = tempPtr;
}

void deleteArray(ArrayList* arr){
	free (arr->base);
	free (arr);
}



ArrayList* __ArrayList(int size_t, int size){
	ArrayList* malcd = malloc(sizeof(ArrayList));
	__Array(malcd, size_t, size);
	return malcd;
}

int main()
{
	ArrayList* arr = __ArrayList(sizeof(long), 10);

	int N = 100;
	
	for (int i = 0; i < N; i++)
	{
		long j = i;
		add(arr, i, &j);
	}

	
	for (int i=0; i<N + 10; i++){
		AL_remove (arr, arr->size / 2);
	}
	
	trim(arr);

	for (int i = 0; i < getSize(arr); i++)
	{
		printf("Value: %ld\n", getLong(arr, i));
	}


	
	return 0;
}
