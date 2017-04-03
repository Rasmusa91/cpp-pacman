#ifndef ARRAYLIST_H
#define ARRAYLIST_H

template<class T>
class ArrayList
{
private:
	int mArrayListCap;
	int mArrayListCapIncr;
	int mArrayListSize;
	T ** mArrayList;

public:
	ArrayList();
	ArrayList(const int pCapacity);
	ArrayList(const int pCapacity, const int pCapacityIncreasement);
	ArrayList(const ArrayList<T> & pOther);
	~ArrayList();

	ArrayList<T> operator=(const ArrayList<T> & pOther) const;
	T * operator[](const int pIndex) const;

	T * GetAt(const int pIndex) const;
	T * GetLast() const;
	T * GetFirst() const;

	void Push(T * pObject);
	void Insert(T * pObject);
	void InsertAt(T * pObject, const int pIndex);

	void RemoveAt(const int pIndex);
	void RemoveFirst();
	void RemoveLast();
	void RemoveBetween(const int pStart, const int pEnd);
	void Clear();

	int GetSize() const;

	void Resize();
	void CopyAll(const ArrayList<T> & pOther);
	void FreeAll();
};

// Default constructor
template<class T>
ArrayList<T>::ArrayList()
{
	mArrayListCap = 2;
	mArrayListCapIncr = 2;
	mArrayListSize = 0;
	mArrayList = new T*[mArrayListCap];
}

// Constructor with capacity
template<class T>
ArrayList<T>::ArrayList(const int pCapacity)
{
	mArrayListCap = pCapacity;
	mArrayListCapIncr = 2;
	mArrayListSize = 0;
	mArrayList = new T*[mArrayListCap];
}

// Initialize with capacity and increasement
template<class T>
ArrayList<T>::ArrayList(const int pCapacity, const int pCapacityIncreasement)
{
	mArrayListCap = pCapacity;
	mArrayListCapIncr = pCapacityIncreasement;
	mArrayListSize = 0;
	mArrayList = new T*[mArrayListCap];
}

// Copy-constructor
template<class T>
ArrayList<T>::ArrayList(const ArrayList<T> & pOther)
{
	CopyAll(pOther);
}

// Destructor
template<class T>
ArrayList<T>::~ArrayList()
{
	FreeAll();
}

// Equal operator
template<class T>
ArrayList<T> ArrayList<T>::operator=(const ArrayList<T> & pOther) const
{
	if (this != &pOther)
	{
		FreeAll();
		CopyAll(pOther);
	}

	return *this;
}

// [] operator to get the element at a specified position
template<class T>
T * ArrayList<T>::operator[](const int pIndex) const
{
	return mArrayList[pIndex];
}

// Get the size of the list
template<class T>
int ArrayList<T>::GetSize() const
{
	return mArrayListSize;
}

// Get a element at a specified position
template<class T>
T * ArrayList<T>::GetAt(const int pIndex) const
{
	return mArrayList[pIndex];
}

// Get the element at the last position
template<class T>
T * ArrayList<T>::GetLast() const
{
	return mArrayList[mArraySize - 1];
}

// Get hte element at the first position
template<class T>
T * ArrayList<T>::GetFirst() const
{
	return mArrayList[0];
}

// Add an element to the end of the list
template<class T>
void ArrayList<T>::Push(T * pObject)
{
	if (mArrayListSize >= mArrayListCap) {
		Resize();
	}

	mArrayList[mArrayListSize++] = pObject;
}

// Insert an element to the start
template<class T>
void ArrayList<T>::Insert(T * pObject)
{
	InsertAt(pObject, 0);
}

// Insert an element at a specified position
template<class T>
void ArrayList<T>::InsertAt(T * pObject, const int pIndex)
{
	if (mArrayListSize >= mArrayListCap) {
		Resize();
	}

	for (int i = mArrayListSize - 1; i >= pIndex; i--) {
		mArrayList[i + 1] = mArrayList[i];
	}

	mArrayList[pIndex] = pObject;
	mArrayListSize++;
}

// Remove an element at a specified position
template<class T>
void ArrayList<T>::RemoveAt(const int pIndex)
{
	//T removedItemCopy;

	if (pIndex >= 0 && pIndex < mArrayListSize)
	{
		//removedItemCopy = *mArrayList[pIndex];
		delete mArrayList[pIndex];

		for (int i = pIndex; i < mArrayListSize; i++)
		{
			if (i < mArrayListSize - 1) {
				mArrayList[i] = mArrayList[i + 1];
			}
			else {
				mArrayList[i] = nullptr;
			}
		}

		mArrayListSize--;
	}

	//return removedItemCopy;
}

// Remove the first element in the list
template<class T>
void ArrayList<T>::RemoveFirst()
{
	RemoveAt(0);
}

// Remove the last element in the list
template<class T>
void ArrayList<T>::RemoveLast()
{
	RemoveAt(mArrayListSize - 1);
}

// Remove all elements between 2 positions
template<class T>
void ArrayList<T>::RemoveBetween(const int pStart, const int pEnd)
{
	for (int i = pEnd; i >= pStart; i--)
	{
		RemoveAt(i);
	}
}

// Remove all elements
template<class T>
void ArrayList<T>::Clear()
{
	RemoveBetween(0, mArrayListSize);
}

// Resize the list
template<class T>
void ArrayList<T>::Resize()
{
	mArrayListCap += mArrayListCapIncr;
	T ** temObjects = new T*[mArrayListCap];

	for (int i = 0; i < mArrayListSize; i++) {
		temObjects[i] = mArrayList[i];
	}

	delete[] mArrayList;
	mArrayList = temObjects;
}

// Copy all from an object of the same type
template<class T>
void ArrayList<T>::CopyAll(const ArrayList<T> & pOther)
{
	mArrayListCap = pOther.mArrayListCap;
	mArrayListCapIncr = pOther.mArrayListCapIncr;
	mArrayListSize = pOther.mArrayListSize;
	
	mArrayList = new T*[mArrayListCap];

	for (int i = 0; i < this->mArrayListSize; i++) {
		this->mArrayList[i] = new T(* pOther.mArrayList[i]);
	}
}

// Free all memory
template<class T>
void ArrayList<T>::FreeAll()
{
	for (int i = 0; i < mArrayListSize; i++) {
		delete mArrayList[i];
	}

	delete[] mArrayList;
}

#endif