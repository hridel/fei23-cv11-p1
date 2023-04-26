# Cvičení 11
## qsort

Vycházejte z [příkladu 2 cvičení 10](https://github.com/hridel/fei23-cv10-p2).

Rozšiřte řádkový výpis hráče o sloupeček s počtem vstřelených gólů a o sloupeček s počtem zaznamenaných asistencí.

Doplňte funkci pro seřazení pole hráčů. Tato funkce bude využívat funkci `qsort`.

Možnosti, jak seřadit hráče budou:

* podle jména
* podle počtu zápasů
* podle počtu gólů
* podle počtu asistencí

Tyto možnosti budou definované _výčtovým typem_.

Dále funkce pro seřazení rozšiřte o možnost určit, zda pole seřadíte sestupně nebo vzetupně.

Upravte hlavní funkci a menu tak, aby byla nabízena možnost seřadit pole podle zadaných kritérií
a také přidejte funkci pro výpis prvních 10 hráčů utříděného pole.

---

**Nápověda:**

### qsort

Funkce `qsort` je funkce v jazyce C, která slouží k řazení prvků v poli. `qsort` je zkratka pro "quick sort",
což znamená, že algoritmus řazení, který je v této funkci použit, je rychlý a efektivní pro řazení prvků v poli.

Syntaxe funkce `qsort` v jazyce C je následující:

```
void qsort(void *base, size_t count, size_t size, int (*compare)(const void *, const void *));
```

- `base` - Ukazatel na začátek pole, které má být seřazeno.
- `count` - Počet prvků v poli.
- `size` - Velikost jednoho prvku v poli.
- `compare` - Ukazatel na funkci, která se používá pro porovnání prvků v poli.

Funkce `qsort` seřadí prvky v poli v rostoucím pořadí podle hodnot, které jsou určeny pomocí funkce `compare`. Funkce `compare` musí být funkce, která přijímá dva argumenty typu `const void *` a vrací celočíselnou hodnotu. Pokud první prvek je menší než druhý prvek, funkce `compare` by měla vrátit hodnotu menší než nula. Pokud jsou oba prvky stejné, funkce by měla vrátit hodnotu nula. Pokud je první prvek větší než druhý prvek, funkce by měla vrátit hodnotu větší než nula.

Příklad použití funkce `qsort`:

```
#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int arr[] = {4, 2, 7, 1, 3};
    int n = sizeof(arr)/sizeof(arr[0]);
    qsort(arr, n, sizeof(int), compare);
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}
```

V tomto příkladu funkce `qsort` řadí pole `arr` o velikosti `n` (5) pomocí funkce `compare`, která porovnává celá čísla v poli. Pořadí prvků v poli je poté vypsáno na výstup.

### výčtový typ

Výčtový typ v jazyce C je datový typ, který umožňuje definovat množinu výčtových konstant, také nazývaných výčtové hodnoty. Tyto konstanty představují pojmenované hodnoty, které mohou být použity v programu. Každá konstanta v množině výčtových konstant je reprezentována celočíselným kódem.

Definice výčtového typu v jazyce C začíná klíčovým slovem "enum", po kterém následuje jméno typu a seznam výčtových konstant uzavřených v závorkách a oddělených čárkami. Například:

```
enum den_v_tydnu { pondeli, utery, streda, ctvrtek, patek, sobota, nedele };
```

V tomto příkladu jsou výčtové konstanty pojmenované dny v týdnu. Konstanty jsou implicitně přiřazeny hodnoty od nuly, takže první konstanta má hodnotu 0, druhá 1, atd.

V programu lze výčtové konstanty používat jako běžné proměnné. Například:

```
enum den_v_tydnu dnesni_den = ctvrtek;
```

Toto přiřazení vytvoří proměnnou "dnesni_den" typu "den_v_tydnu" a nastaví ji na hodnotu "ctvrtek".

Přístup k jednotlivým výčtovým konstantám se provádí pomocí tečkové notace. Například:

```
printf("Dnes je %s\n", dnesni_den == ctvrtek ? "ctvrtek" : "jiný den");
```

Tento kód vytiskne "Dnes je ctvrtek", pokud má proměnná "dnesni_den" hodnotu "ctvrtek", nebo "jiný den" v opačném případě.