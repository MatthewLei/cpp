// simple file for implementing merge sort on a integer array
#include <iostream>
#include <vector>

using namespace std;

void printlist(vector<int>* arr, int size) {
    for (int i = 0; i < size; i++) {
	cout << arr->at(i) << " ";
    }
    cout << endl;
}

void merge(vector<int>* arr, int l, int m, int r) {
    vector<int> tmp_l (arr->begin() + l, (arr->begin() + m) + 1);
    vector<int> tmp_r ((arr->begin() + m) + 1, (arr->begin() + r) + 1);

    /// merge two lists back into arr
    int itL = 0;
    int itR = 0;
    cout << "changing from this list: ";
    printlist(arr, arr->size());
    for (int i = l; i <= r; ++i) {
	if (itL == tmp_l.size()) {        /// left is empty
	    arr->at(i) = tmp_r.at(itR);
	    itR += 1;
	} else if (itR == tmp_r.size()) { /// right is empty
	    arr->at(i) = tmp_l.at(itL);
	    itL += 1;
	} else {
	    if (tmp_l.at(itL) < tmp_r.at(itR)) {
		arr->at(i) = tmp_l.at(itL);
		itL += 1;
	    } else {
		arr->at(i) = tmp_r.at(itR);
		itR += 1;
	    }
	}
    }
    cout << "merged this list from " << l << " to " << r << " into ";
    for (int j = l; j <= r; j++) {
	cout << arr->at(j) << " ";
    }
    cout << endl;
    cout << "changing into this list: ";
    printlist(arr, arr->size());
    cout << endl;
}

void mergesort(vector<int>* arr, int l, int r) {
    if (l < r) {
	int m = (l + r) / 2;

	mergesort(arr, l, m);
	mergesort(arr, m+1, r);

	merge(arr, l, m, r);
    }
}

int main(int argc, char** argv)
{
    int tmp[] = {6,5,4,3,2,1};
    int arr_size = sizeof(tmp) / sizeof(tmp[0]);
    vector<int> arr (tmp, tmp + arr_size);

    /// apply merge sort
    mergesort(&arr, 0, arr_size - 1);
    cout << "merge sorted array: ";
    printlist(&arr, arr.size());
    return 0;
}
