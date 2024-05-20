#include "../include/SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet &m) : multime(m) {
  // TODO - Implementation
  this->current = this->multime.head;
}

void SortedSetIterator::first() {
  // TODO - Implementation
  this->current = this->multime.head;
}

void SortedSetIterator::next() {
  // TODO - Implementation
  if (!this->valid())
    throw exception();
  else
    this->current = this->multime.next[this->current];
}

TElem SortedSetIterator::getCurrent() {
  // TODO - Implementation
  if (!this->valid())
    throw exception();
  else
    return this->multime.array[this->current];
}

bool SortedSetIterator::valid() const {
  // TODO - Implementation
  // if the set is empty we do be kinda false tho
  if (this->multime.isEmpty())
    return false;
  // if the current element is the last element in the set we do be kinda false
  // tho x2
  if (this->current == -1)
    return false;
  return true;
}
