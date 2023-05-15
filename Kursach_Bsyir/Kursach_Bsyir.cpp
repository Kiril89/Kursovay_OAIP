#include <stdlib.h>
#include <iostream>
#include <stdio.h>
//#include <time.h>
#include <algorithm>
#include <conio.h>
#include<chrono>
#include <fstream>//подключаем библиотеку для работы с файлами

using namespace std;

ifstream e("Estestv_sort.txt");
ifstream p("Prost_sort.txt");
//ifstream r;
ofstream of;

void merge(int k1, int k2, int* mass1, int* mass2, int* x) // слияние 2 массивов
{
    int z1 = 0; int z2 = 0; int i;// счетчики позиций на временных массивах и в результирующем
    for (unsigned int i = 0; i < k1 + k2; ++i)
    {
        if (z1 >= k1)
        {
            x[i] = mass2[z2++]; // сливаем по возрастанию элементов
        }
        else if (z2 >= k2) {
            x[i] = mass1[z1++];
        }
        else {
            if (mass1[z1] <= mass2[z2]) {
                x[i] = mass1[z1++];
            }
            else {
                x[i] = mass2[z2++];
            }
        }
    }
}


void E_Sort(int q, int x[])
{
    int k1, k2, st, u, fl;
    int* tm1 = new int[q];
    // временный массив 1
    int* tm2 = new int[q];
    // временный массив 2
    int pos;
    k1 = 0;
    std::sort(x, x + q - 1);
    while (k1 < q - 1)
    {
        st = 1;
        fl = 1;
        pos = 0;
        while (fl == 1)
        {
            u = 0;
            while ((x[u + st - 1] <= x[u + st]) && (u + st - 1 < q)) // выбираем возрастающие цепочки элементов.
            {
                tm1[u] = x[u + st - 1];
                u++;
            }
            if ((x[u + st - 1] >= x[u + st]) || (u + st - 1 == q - 1))
            {
                tm1[u] = x[u + st - 1]; u++;
            }
            k1 = u;
            st = st + k1;
            u = 0;
            while ((x[u + st - 1] <= x[u + st]) && (u + st - 1 < q))
                // аналогичным образом формируем второй массив
            {
                tm2[u] = x[u + st - 1];
                u++;
            }
            if ((x[u + st - 1] >= x[u + st]) || (u + st - 1 == q - 1))
            {
                tm2[u] = x[u + st - 1]; u++;
            }
            k2 = u;
            st = st + k2;
            if (u > 0)
                merge(k1, k2, tm1, tm2, x);
            // сливаем эти два массива в один
            if (st >= q) fl = 0;
        }
    }
    delete[] tm1;
    delete[] tm2;
}

void Sliv_mass(int* Mas, int first, int last) //функция, сливающая массивы
{
    int middle, start, final, j;//переменные целого типа
    int* mas = new int[100];// описан указатель mas и ему присвоен адрес начала непрерывной области динамической памяти, выделенной с помощью оператора new:
    middle = (first + last) / 2; //вычисление среднего элемента
    start = first;//начало левой части
    final = middle + 1;//начало правой части
    for (j = first; j <= last; j++)//выполнять от начала до конца
        if ((start <= middle) && ((final > last) || (Mas[start] < Mas[final])))
        {
            mas[j] = Mas[start];
            start++;//увеличить start на 1
        }
        else
        {
            mas[j] = Mas[final];
            final++;//увеличить final на 1
        }
    for (j = first; j <= last; j++)
        Mas[j] = mas[j];//возвращение результата в список
    delete[]mas;
}

void p_sort(int* Mas, int first, int last)//рекурсивная процедура сортировки
{
    {
        if (first < last)
        {
            p_sort(Mas, first, (first + last) / 2);//сортировка левой части
            p_sort(Mas, (first + last) / 2 + 1, last);//сортировка правой части
            Sliv_mass(Mas, first, last);//слияниеC двух частей
        }
    }
}

int main()
{
    setlocale(LC_ALL, "RUS");
    using clock = chrono::system_clock;
    auto start = clock::now();
    auto end = clock::now();

    int i, n;
    int* Mas = new int[100];
    int* x = new int[100];

    //r.open("D:\111\Естественное слияние\Естественное слияние\fail.txt");//открыли файл
    int input = 0;
    //bool run = true;

    cout << "1. О программе\n";
    cout << "2. Сортировка простым слиянием\n";
    cout << "3. Сортировка естественным слиянием\n";
    cout << "4. О авторе\n";
    cout << "5. Выход\n";
    cout << "Введите пункт меню: ";
    cin >> input;
   
        switch (input) {
        case 1:
            cout << "Данная программа реализует сортировку простым и естественным слиянием\n";

            break;
        case 2:
            system("cls");
            cout << "Сортировка простым слиянием \n";
            cout << "Выберите способ ввода \n";
            cout << "1. С клавиатуры\n";
            cout << "2. Из файла\n";
            cin >> input;
            switch (input) {
                case 1:
                    //с клавы простое
                    //int i, n;
                    //int* Mas = new int[100];
                    cout << "Введите размер массива: ";
                    cin >> n;//вводим n с клавиатуры
                    for (i = 1; i <= n; i++)
                    {
                        cout << i << " элемент: ";
                        cin >> Mas[i];
                    }
                    cout << "Исходный массив: ";
                    for (i = 1; i <= n; ++i)
                    {
                        cout << Mas[i] << " ";
                    }
                    start = clock::now();
                    p_sort(Mas, 1, n);//вызов сортирующей процедуры
                    end = clock::now();
                    cout << endl;
                    cout << "Упорядоченный массив: ";//вывод упорядоченного массива
                    for (i = 1; i <= n; i++)
                        cout << Mas[i] << " ";
                    cout << endl;
                    cout << "Продолжительность: " << (chrono::duration<double, milli>(end - start)).count() << "s" << endl;
                    cout << endl;
                    delete[]Mas;//освобождение памяти

                    break;
                case 2:
                    //с файла простое
                    //int n;

                    /*cout << "Размерность массива = " ;
                    cin >> size;
                    int i;
                    
                    r.open("Prost_sort");
                    cout << "Исходный массив: ";
                    for (i = 0; i < size; ++i)
                    {
                        r >> Mas[i];
                    }
                    for (i = 0; i < size; ++i)
                    {
                        cout << Mas[i] << " ";
                    }
                    p_sort(Mas, 1, size); // сортируем
                    cout << endl;
                    cout << "Упорядоченный массив: ";
                    for (i = 0; i < size; ++i)
                    {
                        cout << Mas[i] << " ";
                    }// и ещё раз выводим
                    cout << endl;
                    //system("pause");
                    delete[]Mas;
                    r.close();//закрыли файл*/
                    int N, k;
                    int A[1000];
                    if (!p.good())
                    {
                        cout << "Файл Prost_sort.txt не найден!" << endl;
                    }
                    else
                    {
                        k = 0;
                        while (p >> N)
                        {
                            A[k++] = N;
                        }
                        cout << "Исходный массив: ";
                        for (int i = 0; i < k; i++)
                        {
                            cout << A[i] << " ";
                        }
                        start = clock::now();
                        p_sort(A, 0, k); // сортируем
                        end = clock::now();
                        cout << endl;
                        cout << "Отсортированный массив: ";
                        for (i = 1; i <= k; ++i)
                        {
                            cout << A[i] << " ";
                        }// и ещё раз выводим
                        cout << endl;
                        cout << "Продолжительность: " << (chrono::duration<double, milli>(end - start)).count() << "s" << endl;
                        cout << endl;
                    }
                    p.close();
                    //fout.close();
                    cin.get();
                    return 0;


                    break;
                default:
                cout << "Ошибка, введен неверный пунк меню\n";
            }

            break;
        case 3:
            system("cls");
            cout << "Сортировка естественным слиянием \n";
            cout << "Выберите способ ввода \n";
            cout << "1. С клавиатуры\n";
            cout << "2. Из файла\n";
            cin >> input;
            switch (input) 
            {
                    case 1:
                        int size;
                        cout << "Размерность массива = " ;
                        cin >> size;
                        int i;
                     
                        for (i = 1; i <= size; i++)
                        {
                            cout << i << " элемент: ";
                            cin >> x[i];
                        }
                        cout << "Исходный массив: ";
                        for (i = 1; i <= size; ++i)
                        {
                            cout << x[i] << " ";
                        }
                        start = clock::now();
                        E_Sort(size, x); // сортируем
                        end = clock::now();
                        cout << endl;
                        
                        cout << "Упорядоченный массив: ";//вывод упорядоченного массива
                        for (i = 1; i <= size; i++)
                            cout << x[i] << " ";
                        cout << endl;
                        cout << "Продолжительность: " << (chrono::duration<double, milli>(end - start)).count() << "s" << endl;
                        cout << endl;
                        delete[]x;

                        break;
                    case 2:
                        /*cout << "Размерность массива = " << size << endl;
                        
                        int i;
                        //r.open("D:\111\Естественное слияние\Естественное слияние\fail.txt");//открыли файл
                        r.open("Estestv_sort");
                        cout << "Исходный массив: ";
                        for (i = 0; i < size; ++i)
                        {
                            r >> x[i];
                        }
                        for (i = 0; i < size; ++i)
                        {
                            cout << x[i] << " ";
                        }
                        E_Sort(size, x); // сортируем
                        cout << endl;
                        cout << "Отсортированный массив: ";
                        for (i = 0; i < size; ++i)
                        {
                            cout << x[i] << " ";
                        }// и ещё раз выводим
                        cout << endl;
                        system("pause");
                        r.close();//закрыли файл*/
                        //ifstream fin("input.txt");
                        //ofstream fout("output.txt");
                        int N, k;
                        int A[1000];
                        if (!e.good())
                        {
                            cout << "Файл Estestv_sort.txt не найден!" << endl;
                        }
                        else
                        {
                            k = 0;
                            while (e >> N)
                            {
                                A[k++] = N;
                            }
                            cout << "Исходный массив: ";
                            for (int i = 0; i < k; i++)
                            {
                                cout << A[i] << " ";
                            }
                            start = clock::now();
                            E_Sort(k, A); // сортируем
                            end = clock::now();
                            cout << endl;
                            cout << "Отсортированный массив: ";
                            for (i = 1; i <= k; ++i)
                            {
                                cout << A[i] << " ";
                            }// и ещё раз выводим
                            cout << endl;
                            cout << "Продолжительность: " << (chrono::duration<double, milli>(end - start)).count() << "s" << endl;
                            cout << endl;
                        }
                        e.close();
                        //fout.close();
                        cin.get();
                        return 0;

                        break;
                    default:
                        cout << "Ошибка, введен неверный пунк меню\n";
            }

                    break;
        case 4:
            cout << "Курсовой проект выполнил Чураков Кирилл Андреевич, группы 281071\n";
            break;
        case 5:
            break;
        default:

            cout << "Ошибка, введен неверный пунк меню\n";
            //cout << "Введите занова номер пункта меню\n";
            //cin >> input;
            //input = 0;
            //run = true;
            break;
        
        cin.get();

        }
    
    system("pause");

   // r.close();//закрыли файл


    return 0;
}


