#ifndef SORT_H_
#define SORT_H_
#include <vector>
#include <iostream>

/* Display a vector.*/
template<typename _T>
void DispalyVector(const std::vector<_T> & a) {
	std::cout << "[";
	for (int i = 0; i < a.size(); i++) {
		std::cout << a[i] << ", ";
	}
	std::cout << "]" << std::endl;
}

/* An implementation of "Insert Sort" algorithm.*/
template<typename _T>
void InsertSort(std::vector<_T> & a) {
	int length = a.size();
	for (int i = 1; i < length; i++) {
		_T tmp = a[i];
		int j = i;
		while (j > 0) {
			if (a[j - 1] > tmp)
				a[j] = a[j - 1];
			else
				break;
			j--;
		}
		a[j] = tmp;
	}
}

/* An unit testing of "Insert Sort".*/
void test_InsertSort() {
	std::vector<int> vec = {1,5,2,10,7,3,8,4};
	std::cout << "The original vector is:\n";
	DispalyVector(vec);
	InsertSort(vec);
	std::cout << "After InsertSort, the vector is:\n";
	DispalyVector(vec);
}

/* An implementation of "Shell Sort" algorithm.*/
template<typename _T>
void ShellSort(std::vector<_T> & arr) {
	// 用shell增量.
	int inc = arr.size() / 2; // 初始化增量.
	while (inc > 0) {
		// 用跳跃式插入排序.
		for (int i = inc; i < arr.size(); i++) {
			_T tmp = arr[i];
			int j = i;
			while (j - inc >= 0 && arr[j - inc] > tmp) {
				arr[j] = arr[j - inc];
				j -= inc;
			}
			arr[j] = tmp;
		}
		inc /= 2;
	}
}

/* An unit testing of "Shell Sort".*/
void test_ShellSort() {
	std::vector<int> vec = { 1, 5, 2, 10, 7, 3, 8, 4 };
	std::cout << "The original vector is:\n";
	DispalyVector(vec);
	ShellSort(vec);
	std::cout << "After ShellSort, the vector is:\n";
	DispalyVector(vec);
}

/* An implementation of "Heap Sort" algorithm.*/
template<typename _T>
void HeapSort(std::vector<_T> & arr) {
	// 建立堆.
	for (int i = arr.size() / 2; i >= 0; i--) { // 从尾节点的父节点开始.
		percolateDown(arr, i, arr.size());
	}
	// DeleteMax
	for (int i = arr.size() - 1; i > 0; i--) {
		std::swap(arr[0], arr[i]);
		percolateDown(arr, 0, i);
	}
}

// 从start节点开始向下渗透到end节点，结果是start到end-1节点的堆是有序的.
template<typename _T>
void percolateDown(std::vector<_T> & arr, int start, int end) {
	_T tmp = arr[start];
	int child = 2 * start + 1; // 左儿子.
	while (child < end) {
		if (child != end-1 && arr[child] < arr[child + 1])
			child++;
		if (arr[child] > tmp)
			arr[start] = arr[child];
		else
			break;
		start = child;
		child = 2 * start + 1;
	}
	arr[start] = tmp;
}

/* An unit testing of "Heap Sort".*/
void test_HeapSort() {
	std::vector<int> vec = { 1, 5, 2, 10, 7, 3, 8, 4 };
	std::cout << "The original vector is:\n";
	DispalyVector(vec);
	HeapSort(vec);
	std::cout << "After HeapSort, the vector is:\n";
	DispalyVector(vec);
}

#endif
