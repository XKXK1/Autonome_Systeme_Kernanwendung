#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <vector>
#include <mutex>
#include <condition_variable>

template <class T>
class RingQueue {

private:
	int _maxSize;
	int _currentSize = 0;
	T* _container;

	int _head;
	int _tail;

    std::mutex _m;
    std::condition_variable _cv;

    
public:
	RingQueue(int size) : _maxSize(size), _currentSize(0), _head(0), _tail(0) {
		_container = new T[size];
	}
	RingQueue() : _maxSize(0), _currentSize(0), _head(0), _tail(0) {
		_container = nullptr;
	}
	~RingQueue() {
		if(_container != nullptr){
			delete _container;
		}
	}

	void push(T elem);
	T pop();

	int size();
	void resize(int size);
	bool empty();

};

template<class T>
int RingQueue<T>::size() {
	std::lock_guard<std::mutex> lk(_m);
	return _currentSize;
}

template<class T>
void RingQueue<T>::resize(int size){
	std::lock_guard<std::mutex> lk(_m);

	if(_container != nullptr){
		delete _container;
	}
	_container = new T[size];
	_currentSize = 0;
	_head = 0;
	_tail = 0;
}

template<class T>
T RingQueue<T>::pop(){

	 std::unique_lock<std::mutex> lk(_m);
    _cv.wait(lk, [=]{ return 0 < _currentSize; });

	T temp = _container[_head];

	_head = (_head + 1) % _maxSize;
	_currentSize--;

	return temp;
}

template<class T>
bool RingQueue<T>::empty() {
	std::lock_guard<std::mutex> lk(_m);
	if(_currentSize == 0){
		return true;
	} else {
		return false;
	}
}

template<class T>
void RingQueue<T>::push(T elem){
	    std::lock_guard<std::mutex> lk(_m);

		if (_maxSize != _currentSize) {
			_container[_tail] = elem;
			_tail = (_tail + 1) % _maxSize;
			_currentSize++;
			_cv.notify_one();
	}	
}

#endif
