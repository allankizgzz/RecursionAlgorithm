#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
int n = 4, m = 2; // C4取2
vector<int> nums(n);
vector<vector<int>> result;
vector<int> path;
void F(int num);
void C(vector<int> &nums, int m, vector<vector<int>> &result, vector<int> &path);

void F(int num)
{ // 不用lambda寫fuction
    if (find(path.begin(), path.end(), num) == path.end() && (path.empty() || num > path.back()))
    {
        // 將當前數字添加到路徑中
        path.push_back(num);
        // 遞歸地生成由 nums 中 m 個元素組成的排列
        C(nums, m, result, path);
        // 將當前數字從路徑中刪除
        path.pop_back();
    }
}
// 生成由 nums 中 m 個元素組成的排列的遞迴函數
void C(vector<int> &nums, int m, vector<vector<int>> &result, vector<int> &path)
{
    // 基本情況：如果當前路徑已達到 m 的大小，將其添加到結果中並返回
    if (path.size() == m)
    {
        result.push_back(path);
        return;
    }

    // 遞迴情況：對 nums 向量中的每個數字，
    for_each(nums.begin(), nums.end(), F);
}
/* 選擇排序
arr[]: 待排序的數組
n: 數組中元素的個數
*/
void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i; // 記錄當前區間的最小值的索引
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[minIndex])
            {
                minIndex = j; // 更新最小值的索引
            }
        }
        swap(arr[i], arr[minIndex]); // 把當前區間的最小值放到正確的位置
    }
}

/*三分搜尋法(ternarySearch)
首先找到兩個mid點，將數列分成三個區間，分別為[low, mid1-1]、[mid1+1, mid2-1]、[mid2+1, high]。
接著比較key和兩個mid點的大小，如果其中一個mid點等於key，則回傳mid點的位置。
如果key小於mid1，在左區間進行遞迴
如果key大於mid2，在右區間進行遞迴
否則在中間區間進行遞迴
如果key不在數列中，則回傳-1。
*/
int ternarySearch(int arr[], int low, int high, int key)
{
    if (high >= low)
    {
        int mid1 = low + (high - low) / 3;
        int mid2 = high - (high - low) / 3;
        if (arr[mid1] == key)
        {
            return mid1;
        }
        if (arr[mid2] == key)
        {
            return mid2;
        }
        if (key < arr[mid1])
        {
            return ternarySearch(arr, low, mid1 - 1, key);
        }
        else if (key > arr[mid2])
        {
            return ternarySearch(arr, mid2 + 1, high, key);
        }
        else
        {
            return ternarySearch(arr, mid1 + 1, mid2 - 1, key);
        }
    }
    return -1;
}

// 每次循環比較相鄰的兩個元素，如果前一個元素比後一個元素大，則交換它們的位置。
// 重複進行多次，直到所有元素都按照遞增或遞減順序排列完成。
// arr 待排序的整數陣列
// n 陣列中元素的個數
void bubbleSort(int arr[], int n)
{
    if (n == 1)
    {
        return;
    }
    for (int i = 0; i < n - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            swap(arr[i], arr[i + 1]);
        }
    }
    bubbleSort(arr, n - 1);
}

// 二分搜尋法 (Binary Search)
// arr: 要搜尋的陣列
// low: 搜尋範圍的左端點
// high: 搜尋範圍的右端點
// key: 要搜尋的值
// 回傳值: 如果搜尋成功，回傳值為目標值的索引，否則回傳 -1
/*如果上限大於等於下限，則計算中間位置 mid，如果中間位置的元素正好是關鍵字，則返回 mid。
  如果中間位置的元素大於關鍵字，則遞迴查找數組左半部分，否則遞迴查找數組右半部分。
  如果上限小於下限，則返回 -1 表示沒有找到關鍵字want。*/
int binarySearch(int arr[], int low, int high, int key)
{
    if (high >= low)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key)
        {
            return mid;
        }
        if (arr[mid] > key)
        {
            return binarySearch(arr, low, mid - 1, key);
        }
        return binarySearch(arr, mid + 1, high, key);
    }
    return -1;
}

/*P排列
這個程式會先要求使用者輸入 n 和 m，然後建立一個陣列 arr 來存放數字。
接著呼叫 p 函式來執行排列演算法，並輸出範圍內的排列。
p 函式使用 start 和 end 來指定目前正在處理的陣列範圍，m 則代表所需的排列長度。
如果 start 等於 m，表示已經達到所需的排列長度，就會輸出該排列。
若不是，程式則會從 start 開始和 end 及後面的數字進行交換，直到所有可能的排列都被印出來為止。*/
void P(int arr[], int start, int end, int m)
{
    if (start == m)
    {
        for (int i = 0; i < m; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
    else
    {
        for (int i = start; i <= end; i++)
        {
            swap(arr[start], arr[i]);
            P(arr, start + 1, end, m);
            swap(arr[start], arr[i]);
        }
    }
}

// 將元素插入已排序的子陣列中
void insert(int arr[], int n)
{
    if (n <= 1)
    {
        return;
    }
    // 先將前n-1個元素排序
    insert(arr, n - 1);

    // 將第n個元素插入到已排序的子陣列中
    int j = n - 2; // j指向已排序的子陣列中最後一個元素
    int temp = arr[n - 1];
    while (j >= 0 && arr[j] > temp)
    {
        arr[j + 1] = arr[j]; // 將元素向右移動
        j--;
    }
    arr[j + 1] = temp; // 插入元素
}
// 插入排序遞迴函數
void insertionSort(int arr[], int n)
{
    if (n <= 1)
    {
        return;
    }
    // 先將前n-1個元素排序
    insertionSort(arr, n - 1);

    // 將第n個元素插入到已排序的子陣列中
    insert(arr, n);
}

int main()
{
    // 插入排序法
    int array1[4] = {4, 2, 3, 1};
    insertionSort(array1, 4);
    cout << "插入排序法:" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << array1[i] << endl;
    } // 選擇排序法
    int array2[4] = {2, 4, 3, 1};
    selectionSort(array2, 4);
    cout << "選擇排序法:" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << array2[i] << endl;
    } // 泡沫排序法
    int array4[4] = {3, 1, 2, 4};
    bubbleSort(array4, 4);
    cout << "BubbleSort:" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << array4[i] << endl;
    }
    // 將 nums 向量填充為 1~n 的整數
    for (int i = 0; i < n; i++)
    {
        nums[i] = i + 1;
    }
    //=============C排列
    cout << "C排列:" << endl;
    // 生成由 nums 中 m 個元素組成的排列
    C(nums, m, result, path);
    // 將結果輸出到控制台
    for (const auto &vec : result)
    {
        for (const auto &num : vec)
        {
            cout << num << " ";
        }
        cout << endl;
    }
    //=============P排列
    int n, m;
    cout << "P排列n and m: ";
    cin >> n >> m;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        arr[i] = i + 1;
    }
    P(arr, 0, n - 1, m);
    //==============二分法
    cout << "Binary Search:" << endl;
    int array3[] = {1, 3, 4, 7, 8, 9};
    int k = sizeof(array3) / sizeof(array3[0]);
    int want;
    cout << "Enter Search key:" << endl;
    cin >> want;
    int result = binarySearch(array3, 0, k - 1, want);
    if (result == -1)
    {
        cout << "沒有找到" << endl;
    }
    else
    {
        cout << "找到元素並放在index: " << result << "." << endl;
    }
    //==============三分法
    cout << "ternarySearch:" << endl;
    int array5[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    int o = sizeof(array5) / sizeof(array5[0]);
    cout << "Enter Search key:" << endl;
    int want1;
    cin >> want1;
    int index = ternarySearch(array5, 0, o - 1, want1);
    if (index != -1)
    {
        cout << "找到元素並放在index: " << index << endl;
    }
    else
    {
        cout << "沒有找到" << endl;
    }
    return 0;
}