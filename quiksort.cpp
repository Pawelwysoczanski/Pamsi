#include <iostream>
#include <ctime>

using namespace std;
int *tab, n, opcja, c, *pom;
int d = 0;
int z = 0;
clock_t start, koniec;
double roznica;

void zamien(int tab[], int indeks1, int indeks2) // Funkcja zmieniająca wartości poszczególnych elementów tablicy
{
    int temp = tab[indeks1];
    tab[indeks1] = tab[indeks2];
    tab[indeks2] = temp;
}

template <typename T>
void kopiec(T tab[], T n, T index_rodzica)
{
    int max_index = index_rodzica;            // indeks korzenia poszczególnej gałęzi
    int leweDziecko = index_rodzica * 2 + 1;  // przypisanie indeksu lewego dziecka dla poszczególnych gałęzi
    int praweDziecko = index_rodzica * 2 + 2; // przypisanie indeksu prawego dziecka dla poszczególnych gałęzi

    if (leweDziecko < n && tab[leweDziecko] > tab[max_index]) // Warunek zgodności czy aby na pewno rodzic jest największym elementem gałęzi
    {
        max_index = leweDziecko; // Przypisanie dziecka jako nowy korzeń gałęzi
    }
    if (praweDziecko < n && tab[praweDziecko] > tab[max_index])
    {
        max_index = praweDziecko;
    }
    if (max_index != index_rodzica) // Sprawdzenie czy korzeń nie jest indeksem rodzica
    {
        zamien(tab, max_index, index_rodzica);
        kopiec(tab, n, max_index);
    }
}

template <typename T>
void sortowanie_przez_kopcowanie(T tab[], T n)
{

    for (int i = n / 2 - 1; i >= 0; i--)
    {
        kopiec(tab, n, i);
    }
    for (int i = n - 1; i > 0; i--)
    {
        zamien(tab, 0, i);
        --n;
        kopiec(tab, n, 0);
    }
}

template <typename T>
void scal(T tab[], T lewy, T srodek, T prawy)
{
    int i = lewy, j = srodek + 1;

    // kopiujemy lewą i prawą część tablicy do tablicy pomocniczej
    for (int i = lewy; i <= prawy; i++)
        pom[i] = tab[i];

    // scalenie dwóch podtablic pomocniczych i zapisanie ich
    // we własciwej tablicy
    for (int k = lewy; k <= prawy; k++)
        if (i <= srodek)
            if (j <= prawy)
                if (pom[j] < pom[i])
                    tab[k] = pom[j++];
                else
                    tab[k] = pom[i++];
            else
                tab[k] = pom[i++];
        else
            tab[k] = pom[j++];
}

template <typename T>
void sortowanie_przez_scalanie(T tab[], T lewy, T prawy)
{
    // gdy mamy jeden element, to jest on już posortowany
    if (prawy <= lewy)
        return;

    // znajdujemy srodek podtablicy
    int srodek = (prawy + lewy) / 2;

    // dzielimy tablice na częsć lewą i prawa
    sortowanie_przez_scalanie(tab, lewy, srodek);
    sortowanie_przez_scalanie(tab, srodek + 1, prawy);

    // scalamy dwie już posortowane tablice
    scal(tab, lewy, srodek, prawy);
}

template <typename T>
void quick_sort(T *tab, T lewy, T prawy)
{
    if (prawy <= lewy)
        return;

    int i = lewy - 1, j = prawy + 1,
        pivot = tab[(lewy + prawy) / 2]; // wybieramy punkt odniesienia

    while (1)
    {
        // szukam elementu wiekszego lub rownego piwot stojacego
        // po prawej stronie wartosci pivot
        while (pivot > tab[++i])
            ;

        // szukam elementu mniejszego lub rownego pivot stojacego
        // po lewej stronie wartosci pivot
        while (pivot < tab[--j])
            ;

        // jesli liczniki sie nie minely to zamień elementy ze soba
        // stojace po niewlasciwej stronie elementu pivot
        if (i <= j)
            // funkcja swap zamienia wartosciami tab[i] z tab[j]
            swap(tab[i], tab[j]);
        else
            break;
    }

    if (j > lewy)
        quick_sort(tab, lewy, j);
    if (i < prawy)
        quick_sort(tab, i, prawy);
}
int main()
{
    cout.setf(ios::fixed);
    cout.precision(10);
    do
    {
        cout << "Menu" << endl;
        cout << "1. Metoda wypełnienia tablicy" << endl;
        cout << "2. Wybierz algorytm sortowania sortowania" << endl;
        cout << "3. Zakończ działanie programu" << endl;
        cout << "4. Wyswietl zawartosc tablicy" << endl;
        cout << "5 Sprawdzenie poprawności sortowania tablicy" << endl;
        cin >> opcja;
        switch (opcja)
        {
        case 1:
            cout << "Wprowadź ilość elementów do posortowania: " << endl;
            cin >> n;
            tab = new int[n]; // przydzielenie pamięci na elementy tablicy
            pom = new int[n];
            cout << "1. Wypełnienie liczbami losowymi" << endl;
            cout << "2. Wypełnienie liczbami losowymi od pewnego momentu" << endl;
            cout << "3. Wypełnienie tabliczy od wartości najmniejszej do największej" << endl;
            cin >> c;
            switch (c)
            {
            case 1:
                for (int i = 0; i < n; i++)
                    tab[i] = rand() % n;

                break;
            case 2:
                int procent;
                cout << "Podaj wartosc w procentach" << endl;
                cin >> procent;
                for (int p = 0; p < n; p++)
                    if (p < ((procent * n) / 1000))
                    {
                        tab[p] = p + 1;
                    }
                    else
                    {
                        tab[p] = rand() % n;
                    }
                break;
            case 3:
                for (int o = 0; o < n; o++)
                    tab[o] = n - o;

                // wypełnienie od tyłu
                break;
            default:
                break;
            }
            break;
        case 2:
            cout << "1. quiksort" << endl;
            cout << "2. przez scalanie" << endl;
            cout << "3. przez kopcowanie" << endl;
            cin >> c;
            switch (c)
            {
            case 1:
                start = clock();
                quick_sort(tab, 0, n - 1);
                koniec = clock();
                cout << endl;

                // wypisanie posortowanych elementów

                cout << endl;

                cout << endl;
                roznica = (koniec - start) / (double)CLOCKS_PER_SEC;
                cout << "Czas wykonania: " << roznica << endl;
                break;
            case 2:

                start = clock();
                sortowanie_przez_scalanie(tab, 0, n - 1);
                koniec = clock();
                cout << endl;

                // wypisanie posortowanych elementów

                cout << endl;
                roznica = (koniec - start) / (double)CLOCKS_PER_SEC;
                cout << "Czas wykonania: " << roznica << endl;
                break;
            case 3:
                start = clock();
                sortowanie_przez_kopcowanie(tab, n);
                koniec = clock();
                cout << endl;

                // wypisanie posortowanych elementów

                cout << endl;
                roznica = (koniec - start) / (double)CLOCKS_PER_SEC;
                cout << "Czas wykonania: " << roznica << endl;
                break;
            default:
                break;
            }
            break;
        case 4:
            for (int i = 0; i < n; i++)
            {
                cout << tab[i] << " ";
            }
            cout << endl;
            break;
        case 5:

            for (int i = 0; i < n; i++)
            {
                if (tab[i] <= tab[i + 1])
                {
                    cout << "ok!" << endl;
                    d++;
                }
                else
                {
                    cout << "Tablica posortowana błędnie !!!" << endl;
                    z++;
                }
            }
            cout << "Ilość poprawnych: " << d << endl;
            cout << "Ilość błędów: " << z << endl;

            break;
        default:
            break;
        }
    } while (opcja != 3);
    //  cin.ignore();
    //    cin.get();
    return 0;
}
