#include "../include/SortedSet.h"
#include "../include/SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
  // TODO - Implementation
  this->relation = r;
  this->capacity = 10;
  this->head = -1;
  this->tail = -1;
  this->array = new TComp[this->capacity];
  this->next = new int[this->capacity];
  this->prev = new int[this->capacity];
  this->firstEmpty = 0;
  for (int i = 0; i < this->capacity - 1; i++) {
    this->next[i] = i + 1;
    this->prev[i] = i - 1;
  }
  this->next[this->capacity - 1] = -1;
  this->prev[0] = -1;
  this->prev[this->capacity - 1] = this->capacity - 2;
}

bool SortedSet::add(TComp elem) {
  // TODO - Implementation
  // check if the set is full:
  if (this->size() == this->capacity) {
    // I'm not making a separate resize function so enjoy the following
    // spaghetti:
    this->capacity *= 2;
    TComp *newarray = new TComp[this->capacity];
    int *newnext = new int[this->capacity];
    int *newprev = new int[this->capacity];
    for (int i = 0; i < this->size(); i++) {
      newarray[i] = this->array[i];
      newnext[i] = this->next[i];
      newprev[i] = this->prev[i];
    }
    for (int i = this->size(); i < this->capacity - 1; i++) {
      newnext[i] = i + 1;
      newprev[i] = i - 1;
    }
    newnext[this->capacity - 1] = -1;
    newprev[0] = -1;
    newprev[this->capacity - 1] = this->capacity - 2;
    delete[] this->array;
    delete[] this->next;
    delete[] this->prev;
    this->array = newarray;
    this->next = newnext;
    this->prev = newprev;
  }
  // check if the element is already in the set:
  if (this->search(elem)) {
    return false;
  }
  // find the position where the element should be inserted:
  int current = this->head;
  while (current != -1 && this->relation(this->array[current], elem)) {
    current = this->next[current];
  }

  // if current reached -1, the element should be inserted at the end of the set
  if (current == -1) {
    this->tail = this->firstEmpty;
    this->firstEmpty = this->next[this->firstEmpty]; // maybe don't forget to
                                                     // update firstEmpty yknow
    this->array[this->tail] = elem;
    this->next[this->tail] = -1;
    this->prev[this->tail] = current;
    if (current != -1) {
      this->next[current] = this->tail;
    } else {
      this->head = this->tail;
    }
    return true;
  }

  // insert the element:
  int newpos = this->firstEmpty;
  this->firstEmpty = this->next[this->firstEmpty]; // maybe don't forget to
                                                   // update firstEmpty yknow
  this->array[newpos] = elem;
  this->next[newpos] = current;
  this->prev[newpos] = this->prev[current];
  if (this->prev[current] != -1) {
    this->next[this->prev[current]] = newpos;
  } else {
    this->head = newpos;
  }
  this->prev[current] = newpos;
  return true;
}

bool SortedSet::remove(TComp elem) {
  // TODO - Implementation
  // check if the element is in the set:
  if (!this->search(elem)) {
    return false;
  }
  // find the position of the element:
  int current = this->head;
  while (current != -1 && this->relation(current, elem) &&
         this->array[current] != elem) {
    current = this->next[current];
  }
  // if current reached -1, the element is not in the set
  if (current == -1) {
    return false;
  }
  // remove the element:
  if (this->prev[current] != -1) {
    this->next[this->prev[current]] = this->next[current];
    this->prev[this->next[current]] = this->prev[current];
  } else {
    this->head = this->next[current];
    this->prev[this->head] = -1;
    this->next[head] = this->next[current];
  }
  this->next[current] = this->firstEmpty;
  this->firstEmpty = current;
  return true;
}

bool SortedSet::search(TComp elem) const {
  // TODO - Implementation
  int current = this->head;
  int current2 = this->tail;
  // i learned te hard way to binary search it
  while (current <= current2) {
    int mid = (current + current2) / 2;
    if (this->array[mid] == elem) {
      return true;
    }
    if (this->relation(this->array[mid], elem)) {
      current = mid + 1;
    } else {
      current2 = mid - 1;
    }
  }
  return false;
}

int SortedSet::size() const {
  // TODO - Implementation
  if (this->isEmpty()) {
    return 0;
  }
  int count = 0;
  int current = this->head;
  int current2 = this->tail;
  while (current <= current2) {
    count += 2;
    current++;
    current2--;
  }
  if (current == current2)
    count++; // if the set has an odd number of elements

  return count;
}

bool SortedSet::isEmpty() const {
  // TODO - Implementation
  if (this->head == -1) {
    return true;
  }
  return false;
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
