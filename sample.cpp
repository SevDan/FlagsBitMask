#include <iostream>

#ifndef T_SIZE
#define T_SIZE 32
#endif // T_SIZE

using namespace std;

// Хранение флагов в числе (битах числа) позволяет экономить поля в БД, ускорять взаимодействие, сохраняя связанные флаги в одном месте
// Такой вид хранения используется в Linux-системах, в форумных движках и CMS
// Использовать этот способ вы можете при организации доступа, а также для компактного описания предикатов объекта.
// Рекомендуется использовать в комплекте с перечислениями (enums)

int computeFlagsHash(int* flags, int len) // Перевод из набора флагов в вид числа
{
    if(len > T_SIZE || len <= 0) return 0; // T_SIZE отвечает за разрядность числа. Если нужно использовать больше флагов, заводите ещё одну переменную
    int tmp = 0;
    for(int i = 0; i < len; ++i)
    {
        tmp += flags[i];
        tmp <<= 1;
    }
    return tmp;
}

int getFlagFromHash(int flagsHash, int flagId) // получаем флаг по id из числа-хэша. Порядок справа-налево (от младших битов)
{
    if(flagId < 0 || flagId >= T_SIZE) return 0;
    flagsHash >>= flagId;
    return flagsHash % 2;
}

bool compareFlagAndHash(int flagHash, int flagId, int flagState) // функция проверки состояния флага
{
    if(getFlagFromHash(flagHash, flagId) == flagState) return true;
    return false;
}


int main()
{
    int flags = 0;

    cout << "Your Flags" << endl; // здесь ваш интерфейс ввода
    cin >> flags;
    cout << getFlagFromHash(flags,2) << endl;
}
