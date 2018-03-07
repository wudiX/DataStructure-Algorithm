#ifndef SORT_H_
#define SORT_H_
#include <vector>
#include <iostream>
#include <string>
#include <map>

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

/* An implementation of "Merge Sort" algorithm.*/
template<typename _T>
void MergeSort(std::vector<_T> & arr) {
	if (arr.size() == 1)
		return;
	// 将arr分为左右两部分.
	std::vector<_T> left(arr.begin(), arr.begin() + arr.size() / 2);
	std::vector<_T> right(arr.begin() + arr.size() / 2, arr.end());
	
	// 分别对左右子序列递归排序.
	MergeSort(left);
	MergeSort(right);

	int left_ind = 0;
	int right_ind = 0;
	int i = 0;
	while (left_ind < left.size() && right_ind < right.size()) {
		if (left[left_ind] < right[right_ind]) {
			arr[i++] = left[left_ind++];
		}
		else
			arr[i++] = right[right_ind++];
	}
	if (left_ind == left.size()) {
		while (i < arr.size())
			arr[i++] = right[right_ind++];
	}
	else
		while (i < arr.size())
			arr[i++] = left[left_ind++];
}

/* An implementation of "Quick Sort" algorithm.*/
template<typename _T>
void QuickSort(std::vector<_T> & arr) {
	QuickSort(arr, 0, arr.size() - 1);
}

template<typename _T>
void QuickSort(std::vector<_T> & arr, int left, int right) {
	// 计算枢纽元.
	if (right - left <= 1)
		return;
	int center = (left + right) / 2;
	if (arr[center] < arr[left])
		std::swap(arr[center], arr[left]);
	if (arr[right] < arr[left])
		std::swap(arr[right], arr[left]);
	if (arr[right] < arr[center])
		std::swap(arr[right], arr[center]);
	std::swap(arr[right - 1], arr[center]);// 将枢纽元放到right-1位置.
	_T pivot = arr[right - 1];// 枢纽元.

	int i = 0;
	int j = right - 1;
	while (1) {
		while (arr[++i] < pivot) {}
		while (arr[--j] > pivot) {}
		if (i < j)
			std::swap(arr[i], arr[j]);
		else
			break;
	}
	std::swap(arr[i], arr[right - 1]);

	// 递归排序左右两个子集.
	QuickSort(arr, left, i - 1);
	QuickSort(arr, i + 1, right);
}

typedef void (*Func)(std::vector<int> &); // 函数指针类型.
typedef std::map<std::string, Func> registry; // 函数名和函数指针关联.

static registry & Registry() {
	static registry * g_registry = new registry(); // 只建立一次.
	return *g_registry; // 全局的关联容器，记住了函数名和函数指针的对应关系.
}

static void Add_registry(const std::string name, Func func ) {
	registry & g_registry = Registry();
	g_registry[name] = func;
}

void unit_testing(const std::string & func_name) {
	// 注册函数.
	Add_registry("InsertSort", InsertSort);
	Add_registry("ShellSort", ShellSort);
	Add_registry("HeapSort", HeapSort);
	Add_registry("MergeSort", MergeSort);
	Add_registry("QuickSort", QuickSort);

	// 单元测试.
	std::vector<int> vec = { 1, 5, 2, 10, 7, 3, 8, 4 };
	std::cout << "The original vector is:\n";
	DispalyVector(vec);
	registry & g_registry = Registry();
	g_registry[func_name](vec); // 根据函数名调用相应的排序函数.
	std::cout << "After " << func_name << ", the vector is:\n";
	DispalyVector(vec);
}
#endif
