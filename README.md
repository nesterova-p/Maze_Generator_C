## Cel projektu

Celem projektu jest stworzenie generatora labiryntów o rozmiarze zadanym przez użytkownika (od 2x2 do 10x10) oraz wygenerowanie skierowanego grafu przechodzącego przez ten labirynt.

## Kompilacja

Aby skompilować program, należy wykonać poniższe polecenie w terminalu:

```bash
gcc main.c stos.c labir.c graficz.c graf.c -lncurses -lm
```

## Wymagania

Dla graficznej reprezentacji labiryntu wymagana jest biblioteka `ncurses`, którą można zainstalować w terminalu za pomocą komendy:

```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

## Przykład działania

Po skompilowaniu użytkownik otrzyma graficzną wizualizację labiryntu wraz z grafem przechodzącym przez jego strukturę.

![Зображення2](https://github.com/user-attachments/assets/0ce0d001-6520-438b-a569-2c8d060817c5)

---

![Зображення1](https://github.com/user-attachments/assets/614a24f4-7d7c-4d54-9d40-ccf5f21a8421)
