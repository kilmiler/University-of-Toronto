#include <galaxy-explorer/AsteroidList.hpp>


AsteroidListItem::AsteroidListItem() {
	this->next = nullptr;
	this->data = nullptr;
}

AsteroidListItem::AsteroidListItem(Asteroid a) {
	this->next = nullptr;
	this->data = new Asteroid(a);
}

AsteroidListItem::~AsteroidListItem() {
    if(this->data != nullptr){
        this->data = nullptr;
    }
}

AsteroidList::AsteroidList() {
    
}

AsteroidList::AsteroidList(const AsteroidList& src)
{
    //new pointer that points to first ALI in AL(src)
    const AsteroidListItem* ptr = src.begin(); //ptr points at src's 1st asteroid
    AsteroidListItem* ptr2 = this->beforeBegin();
    
    while(ptr != nullptr){
        AsteroidListItem* newALI = new AsteroidListItem(ptr -> getData());
        ptr2 -> setNext(newALI);
        ptr2 = ptr2 -> getNext();
        ptr = ptr -> getNext();
    }
}

AsteroidList::~AsteroidList() {
    this -> clear();
}

void AsteroidList::pushFront(Asteroid e) {
    AsteroidListItem* newAst = new AsteroidListItem(e);
    newAst -> setNext(head.getNext());
    head.setNext(newAst);
    //now newAst is after head
}

Asteroid& AsteroidList::front() {
    //if head = last, there is no 1st ALI, thus no 1st Asteroid, thus no Asteroids in general.
    if(this->beforeBegin() != this->beforeEnd()){
        return this->begin()->getData(); //returns 1st Asteroid.
    }else{
        return *(Asteroid*)nullptr;
    }
}

const Asteroid& AsteroidList::front() const {
    if(this->beforeBegin() != this->beforeEnd()){
        return this->begin()->getData(); //returns 1st Asteroid.
    }else{
        return *(const Asteroid*)nullptr;
    }
}

bool AsteroidList::isEmpty() const {
    //if head = last, there are no Asteroids
    if(this->beforeBegin() == this->beforeEnd()){
        return true;
    } else{
        return false;
    }
}

int AsteroidList::size() const {
    int countAst = 0;
    const AsteroidListItem* ptr = this->begin();
    while(ptr != nullptr){
        countAst++;
        ptr = ptr->getNext(); //goes to next ALI
    }
    return countAst;
}

AsteroidListItem* AsteroidList::beforeBegin() {
    AsteroidListItem* ptr = (this->head);
	return ptr;
}

const AsteroidListItem* AsteroidList::beforeBegin() const {
	const AsteroidListItem* ptr = (this->head);
    return ptr;
}

AsteroidListItem* AsteroidList::begin() {
    AsteroidListItem* ptr = (this->head);
    ptr = ptr->getNext();
	return ptr;
}

const AsteroidListItem* AsteroidList::begin() const {
    const AsteroidListItem* ptr = (this->head);
    ptr = ptr->getNext();
    return ptr;
}

AsteroidListItem* AsteroidList::beforeEnd() {
    AsteroidListItem* ptr = begin();
    if(ptr == nullptr){
        return beforeBegin(); //returns head when list is empty
    }else{
        while(ptr->getNext() != nullptr){
            ptr = ptr->getNext();
        }
    }
	return ptr;
}

const AsteroidListItem* AsteroidList::beforeEnd() const {
	const AsteroidListItem* ptr = begin();
    if(ptr == nullptr){
        return beforeBegin();
    }else{
        while(ptr->getNext() != nullptr){
            ptr = ptr->getNext();
        }
    }
    return ptr;
}

AsteroidListItem* AsteroidList::end() {
    AsteroidListItem* ptr = begin();
    if(ptr == nullptr){
        return begin();
    }else{
        while(ptr != nullptr){
            ptr = ptr->getNext();
        }
    }
	return ptr;
}

const AsteroidListItem* AsteroidList::end() const {
	const AsteroidListItem* ptr = begin();
    if(ptr == nullptr){
        return begin();
    }else{
        while(ptr != nullptr){
            ptr = ptr->getNext();
        }
    }
    return ptr;
}

//Add a single asteroid to this list, in the position immediately after `prev`. returns the item that was inserted
AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* prev, Asteroid e) {
    AsteroidListItem* newAst = new AsteroidListItem(e);
    newAst -> setNext(prev -> getNext()); //gets position after 'prev', sets it after newAst
    prev -> setNext(newAst);
    //sets newAst after prev //now prev points to newAst, newAst points to position after 'prev'
	return newAst;
}

AsteroidListItem* AsteroidList::insertAfter(AsteroidListItem* insertion_point, const AsteroidList& others) {
    if(others.begin() == nullptr){
        return insertion_point;
    }else{
        AsteroidList others1 = new AsteroidList(others);
        AsteroidListItem* first = others.begin();
        AsteroidListItem* last = others.beforeEnd();
        insertion_point-> setNext(first);
        last -> setNext(insertion_point->getNext());
    } return last;
}

AsteroidListItem* AsteroidList::eraseAfter(AsteroidListItem* prev) {
    if(prev->getNext() == nullptr){
        return end();
    }else{
        AsteroidListItem* ptr_temp = (prev->getNext());
        prev->setNext(prev->getNext()->getNext());
        delete ptr_temp;
        return prev; //list item that followed the erased item.
    }
}

void AsteroidList::clear() {
    while(head.hasNext()){
        AsteroidListItem* ptr = head.getNext();
        head.setNext(ptr->getNext());
        delete ptr;
    } head.setNext(nullptr);
}

AsteroidList& AsteroidList::operator=(const AsteroidList& src) {
    this -> clear();
    //new pointer that points to first ALI in AL(src)
    const AsteroidListItem* ptr = src.begin(); //ptr points at src's 1st asteroid
    AsteroidListItem* ptr2 = this->beforeBegin();
    
    while(ptr != nullptr){
        AsteroidListItem* newALI = new AsteroidListItem(ptr -> getData());
        ptr2 -> setNext(newALI);
        ptr2 = ptr2 -> getNext();
        ptr = ptr -> getNext();
    }
    
    return(*this);
}

