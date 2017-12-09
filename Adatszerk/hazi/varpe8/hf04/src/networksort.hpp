#ifndef NETWORKSORT_H_
#define NETWORKSORT_H_

#include <vector>
#include <algorithm>

template <typename T>
void rendezo_halozat(T *tomb, int meret)
{   
    unsigned int m = (unsigned int)meret;
    for (unsigned int k = 1; k < m; k*=2)
        for (unsigned int i = k; i >= 1; i/=2)
        {
            bool irany = true;
            unsigned int irany_counter = 0;
            std::vector<bool> v(m,false);
            for (unsigned int j = 0; j+i < m; j++)
            {
                if (v[j]) continue; v[j+i]=true;
                if (irany_counter==k) {irany=!irany; irany_counter=0;} irany_counter++;
                if (irany) {if (tomb[j]>tomb[i+j]) std::swap<T>(tomb[j],tomb[i+j]);}
                else {if (tomb[j]<tomb[i+j]) std::swap<T>(tomb[j],tomb[i+j]);}
            }
        }
}

#endif