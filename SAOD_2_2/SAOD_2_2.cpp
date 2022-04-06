#include <iostream>
#include <locale>
#include <set>

using namespace std;

void PrintArray(int*, int);

int* CreateArray(int volume)
{
    int* array = new int[volume];
    for (int i = 0; i < volume; i++)
    {
        array[i] = rand();
    }
    PrintArray(array, volume);
    return array;
}

void PrintArray(int* array, int volume)
{
    for (int i = 0; i < volume; i++)
    {
        cout << array[i] << " ";
    }
}

void SortBubble(int* array, int volume, int& countCompares, int& countExchanges)
{
    int temp;
    countCompares = countExchanges = 0;
    for (int i = 1; i < volume; i++)
    {
        int j = volume - 1;
        while (j >= i)
        {
            if (array[j - 1] > array[j])
            {
                temp = array[j - 1];
                array[j - 1] = array[j];
                array[j] = temp;
                countExchanges++;
            }
            j--;
            countCompares++;
        }
    }

    PrintArray(array, volume);
}

void SortChoice(int* array, int volume, int& countCompares, int& countExchanges)
{
    int temp;
    countCompares = countExchanges = 0;
    for (int i = 0; i < volume - 1; i++)
    {
        int k = i; temp = array[i];
        for (int j = i + 1; j < volume; j++)
        {
            if (array[j] < temp)
            {
                k = j; temp = array[j];
            }
            countCompares++;
        }
        countExchanges++;
        array[k] = array[i]; array[i] = temp;
    }

    PrintArray(array, volume);
}

void SortInsert(int* array, int volume, int& countCompares, int& countExchanges)
{
    int temp;
    countCompares = countExchanges = 0;
    for (int i = 1; i < volume; i++)
    {
        temp = array[i]; int j = i - 1;
        while (j >= 0 && temp < array[j])
        {
            countCompares++;
            countExchanges++;
            array[j + 1] = array[j];
            j--;
        }
        countCompares++;
        array[j + 1] = temp;
    }

    PrintArray(array, volume);
}

void SortShell(int* a, int volume, int& countCompares, int& countExchanges)
{
    int temp, j, k;
    countCompares = countExchanges = 0;
    int t = (int)log2(volume) - 1; int copyT = t;
    int* h = new int[t];
    for (int i = 0; copyT > 0 ; i++, copyT--)
    {
        h[i] = 2 * copyT - 1;
    }

    for (int m = 0; m < t; m++)
    {
        k = h[m];
        for (int i = k; i < volume; i++)
        {
            temp = a[i]; j = i - k;
            while (j >= 0 && temp < a[j])
            {
                countCompares++;
                a[j + k] = a[j]; j = j - k;
                countExchanges++;
            }
            countCompares++;
            a[j + k] = temp;
        }
    }

    delete[] h;
    PrintArray(a, volume);
}

void QuickSort(int* a, int begin, int end, int& countCompares, int& countExchanges)
{
    int temp, avrg, i = begin, j = end;
    avrg = a[(begin + end) / 2];
    do
    {
        while (a[i] < avrg)
        {
            i++;
            countCompares++;
        }
        while (a[j] > avrg)
        {
            j--;
            countCompares++;
        }
        countCompares += 2;
        if (i <= j)
        {
            temp = a[i]; a[i] = a[j]; a[j] = temp;
            i++; j--;
            countExchanges++;
        }
    } while (i <= j);

    if (begin < j) { QuickSort(a,begin, j, countCompares, countExchanges); }
    if (i < end) { QuickSort(a, i, end, countCompares, countExchanges); }
}

void Sito(int* mas, int left, int right, int& countCompares, int& countExchanges)
{
    int i = left, j = 2 * left, x = mas[left];
    if (j < right && mas[j + 1] > mas[j])
    {
        j++;
    }
    countCompares++;
    while (j <= right && mas[j] > x)
    {
        countCompares++;
        mas[i] = mas[j]; i = j; j = 2 * j;
        countExchanges++;
        if (j < right && mas[j + 1] > mas[j])
        {
            j++;
        }
        countCompares++;
    }
    countCompares++;
    mas[i] = x;
    countExchanges++;
}

void PyramidSort(int* a, int volume, int& countCompares, int& countExchanges)
{
    int temp;
    countCompares = countExchanges = 0;
    int left = (volume / 2) + 2; int right = volume - 1;
    while (left > 0)
    {
        left--; Sito(a, left, right, countCompares, countExchanges);
    }
    while (right > 0)
    {
        temp = a[0]; a[0] = a[right]; a[right] = temp;
        countExchanges++;
        right--; Sito(a, left, right, countCompares, countExchanges);
    }

    PrintArray(a,volume);
}

int CheckedInput(int begin, int end) // Ввод целочисленного значения с проверкой
{
    int choice;
    while (true)
    {
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(32767, '\n');
            cout << "Вводите данные корректно: ";
            continue;
        }
        cin.ignore(32767, '\n');
        if (choice < begin || choice > end)
        {
            cout << "Вводите данные корректно: ";
            continue;
        }
        break;
    }
    return choice;
}

int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "RUS");
    bool work = true;
    int choice;
    int volume{ 0 };
    cout << "Введите объём массива (до 10000): "; volume = CheckedInput(1, 10000);
    int* array = CreateArray(volume);
    int* arrCopy = new int[volume];
    while (work)
    {
        cout << "\nВыбор метода сортировки:\n1 - Сортировка обменом (метод пузырька)\n2 - Сортировка выбором\n3 - Сортировка вставками\n4 - Сортировка методом Шелла\n";
        cout << "5 - Метод быстрой сортировки\n6 - Пирамидальная сортировка\n7 - Завершение работы\n";
        cout << "Действие: "; choice = CheckedInput(1, 7);
        int countCompares{ 0 }, countExchanges{ 0 };
        switch (choice)
        {
        case 1:
            cout << "Отсортированный массив: \n";
            memcpy(arrCopy, array, sizeof(int) * volume);
            SortBubble(arrCopy, volume, countCompares, countExchanges);
            cout << "\nЧисло сравнении: " << countCompares << endl;
            cout << "Число перестановок: " << countExchanges;
            cout << "\n\n";
            break;
        case 2:
            cout << "Отсортированный массив: \n";
            memcpy(arrCopy, array, sizeof(int) * volume);
            SortChoice(arrCopy, volume, countCompares, countExchanges);
            cout << "\nЧисло сравнении: " << countCompares << endl;
            cout << "Число перестановок: " << countExchanges;
            cout << "\n\n";
            cout << "\n\n";
            break;
        case 3:
            cout << "Отсортированный массив: \n";
            memcpy(arrCopy, array, sizeof(int) * volume);
            SortInsert(arrCopy, volume, countCompares, countExchanges);
            cout << "\nЧисло сравнении: " << countCompares << endl;
            cout << "Число перестановок: " << countExchanges;
            cout << "\n\n";
            break;
        case 4:
            cout << "Отсортированный массив: \n";
            memcpy(arrCopy, array, sizeof(int) * volume);
            SortShell(arrCopy, volume, countCompares, countExchanges);
            cout << "\nЧисло сравнении: " << countCompares << endl;
            cout << "Число перестановок: " << countExchanges;
            cout << "\n\n";
            break;
        case 5:
            cout << "Отсортированный массив: \n";
            memcpy(arrCopy, array, sizeof(int) * volume);
            countCompares = countExchanges = 0;
            QuickSort(arrCopy, 0, volume - 1, countCompares, countExchanges);
            PrintArray(arrCopy, volume);
            cout << "\nЧисло сравнении: " << countCompares << endl;
            cout << "Число перестановок: " << countExchanges;
            cout << "\n\n";
            break;
        case 6:
            cout << "Отсортированный массив: \n";
            memcpy(arrCopy, array, sizeof(int) * volume);
            PyramidSort(arrCopy, volume, countCompares, countExchanges);
            cout << "\nЧисло сравнении: " << countCompares << endl;
            cout << "Число перестановок: " << countExchanges;
            cout << "\n\n";
            break;
        case 7:
            delete[] array;
            delete[] arrCopy;
            work = false;
            break;
        default:
            break;
        }

    }
}
