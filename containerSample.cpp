#include <iostream>

#ifndef T_SIZE
#define T_SIZE 32
#define SERIALIZE_COUNT 2
#endif // T_SIZE

using namespace std;

// Хранение флагов в контейнере (битах чисел) позволяет экономить поля в БД, ускорять взаимодействие, сохраняя связанные флаги в одном месте
// Такой вид хранения используется в Linux-системах, в форумных движках и CMS
// Использовать этот способ вы можете при организации доступа, а также для компактного описания предикатов объекта.
// Рекомендуется использовать в комплекте с перечислениями (enums), пример продемонстрирован ниже

// При реализации в объектном или структурном виде нужно также организовать процедуру сериализации и десериализации

int flags[2]; // наш контейнер флагов

enum Groups { // Имеющиеся группы флагов
    B1 = 0,
    B2 = 1
};

enum FlagsGroupB1 { // Связанная группа флагов 1
    B1Default = 1<<0, 
    B1Chat = 1<<1, 
    B1Block = 1<<2,
    B1Transport = 1<<3,
    B1Etc = 1<<4
};

enum FlagsGroupB2 { // Связанная группа флагов 2
    B2Teleports = 1<<0,
    B2Licences = 1<<1,
    B2Skills = 1<<2,
    B2Etc = 1<<3
};

void setFlag(int* flags, int group, int flagId, bool flagValue) {
    flags[group] = flags[group] | (flagValue<<flagId); // установка флага - это процедура побитового или с флагом в его позиции
}

int getFlagFromContainer(int* flags, int group, int flagId) // получаем флаг по id из числа-хэша. Порядок справа-налево (от младших битов)
{
    if(flagId < 0 || flagId >= T_SIZE) return 0;
    int tmp = 0;
    
    tmp = flags[group] & (1<<flagId); // id - по сути смещение бита флага относительно единицы (0-го бита)
    
    tmp >>= flagId;
    return tmp % 2;
}

bool checkFlagStatement(int* flags, int flagGroup, int flagId, bool flagState) // функция проверки состояния флага
{
    if(getFlagFromContainer(flags, flagGroup, flagId) == flagState) return true;
    return false;
}


int main()
{
    // пример работы
    flags[0] = 0;
    Groups worksGroup = B1;
    FlagsGroupB1 flag = B1Default;
    cout << getFlagFromContainer(flags, worksGroup, flag) << endl;
}
