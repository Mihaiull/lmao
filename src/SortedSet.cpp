#include "../include/SortedSet.h"
#include "../include/SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
  // TODO - Implementation
	this->relation = r;
	this->capacity = 11;
	this->head = -1;
	this->array = new TComp[this->capacity];
	this->next = new int[this->capacity];
	this->prev = new int[this->capacity];
	for (int i = 0; i < this->capacity; i++) {
		this->next[i] = i + 1;
		this->prev[i] = i - 1;
	}
	this->next[this->capacity - 1] = this->capacity;
	this->firstEmpty = 0;
}

int SortedSet::allocate() {

	int poz = this->firstEmpty;
	this->firstEmpty = this->next[poz];

	this->next[poz] = -1;

	return poz;
}


void SortedSet::resize() {

	TComp* new_array = new TComp[this->capacity * 2];
	int* new_next = new int[this->capacity * 2];
	int* new_prev = new int[this->capacity * 2];

	for (int i = 0; i < this->capacity; i++) {
		new_array[i] = this->array[i];
		new_next[i] = this->next[i];
		new_prev[i] = this->prev[i];
	}

	for (int i = this->capacity; i < this->capacity * 2; i++) {
		new_next[i] = i + 1;
		new_prev[i] = i - 1;
	}

	new_next[this->capacity * 2 - 1] = -1;

	this->firstEmpty = this->capacity;

	delete[] this->array;
	delete[] this->next;
	delete[] this->prev;

	this->array = new_array;
	this->next = new_next;
	this->prev = new_prev;

	this->capacity *= 2;
}

void SortedSet::deallocate(int i) {
	this->next[i] = this->firstEmpty;
	this->firstEmpty = i;
}

int SortedSet::createNode(TComp elem) {

	if (this->size() == this->capacity - 1)
		this->resize();

	int poz = this->allocate();

	if (poz != -1) {
		this->array[poz] = elem;
		this->next[poz] = -1;
		this->prev[poz] = -1;
	}

	return poz;
}


bool SortedSet::add(TComp elem) {
	// Check if the element already exists in the set
	if (this->search(elem))
		return false;

	// Create a new node for the element
	int poz = this->createNode(elem);

	// If the set is empty, insert the new node as the head
	if (this->head == -1) {
		this->head = poz;
	}
	else {
		int current = this->head;
		int prev = -1;

		// find where to insert the new node
		while (current != -1 && this->relation(this->array[current], elem)) {
			prev = current;
			current = this->next[current];
		}

		if (prev == -1) { // Insert at the beginning
			this->next[poz] = this->head;
			this->prev[this->head] = poz;
			this->head = poz;
		}
		else if (current == -1) { // Insert at the end
			this->next[prev] = poz;
			this->prev[poz] = prev;
		}
		else { // Insert in it somewhere idk
			this->next[poz] = current;
			this->prev[poz] = prev;
			this->next[prev] = poz;
			this->prev[current] = poz;
		}
	}
	return true;
}


bool SortedSet::remove(TComp elem) {
  // TODO - Implementation
	int current = this->head;
	bool found = false;
	int prev = -1;
	while (current != -1 && !found) {
		if (this->array[current] == elem)
			found = true;
		else {
			prev = current;
			current = this->next[current];
		}
	}
	if (!found)
		return false;
	if (prev == -1)
		this->head = this->next[current];
	else
		this->next[prev] = this->next[current];
	this->deallocate(current);
	return true;
}

bool SortedSet::search(TComp elem) const {
  // TODO - Implementation
	int current = this->head;
	while (current != -1 && relation(this->array[current], elem)) {
		if (this->array[current] == elem)
			return true;
		current = this->next[current];
	}
	return false;
}

int SortedSet::size() const {
  // TODO - Implementation
	int current = this->head;
	int size = 0;
	while (current != -1) {
		size++;
		current = this->next[current];
	}
	return size;
}

bool SortedSet::isEmpty() const {
	// TODO - Implementation
	return this->size() == 0;
}

SortedSetIterator SortedSet::iterator() const {
  return SortedSetIterator(*this);
}

SortedSet::~SortedSet() {
  // TODO - Implementation
	delete[] this->array;
	delete[] this->next;
	delete[] this->prev;
}

#include <iostream>
void SortedSet::printset() const { // for debugging purposes
	int current = this->head;
	while (current != -1) {
		std::cout << this->array[current] << " ";
		current = this->next[current];
	}
	std::cout << std::endl;
}