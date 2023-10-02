#include <iostream>
#include <vector>
#include <list>
#include <tuple>
using namespace std;
/*!
 * \brief Признак TEST предназначен для включения и отключения тестов
 */
#define TEST 0

#include "print_ip.h"

int main()
{

    if (TEST)
    {
        std::vector<int> v1;
        std::list<int> l1;
        int i=0;
        auto t=std::make_tuple(123,456,789,0);
        cout<<"has iterator (yes) "<<hasIterator<decltype (v1)>::value<<endl;
        cout<<"has iterator (no) "<<hasIterator<decltype (i)>::value<<endl;
        cout<<"is vector or list  (yes) "<<is_vector_or_list_std<decltype (v1)>::value<<endl;
        cout<<"is vector or list (no) "<<is_vector_or_list_std<decltype (i)>::value<<endl;
        cout<<"is vector or list (yes)"<<is_vector_or_list_std<decltype (l1)>::value<<endl;
        cout<<"is tuple (yes)"<<is_Tuple<decltype (t)>::value<<endl;
        cout<<"is tuple (no)"<<is_Tuple<decltype (l1)>::value<<endl;
    }


    print_ip( int8_t{-1});
    print_ip( int16_t{0});
    print_ip( int32_t{2130706433});
    print_ip( int64_t{8875824491850138409});
    print_ip( std::string{"Hello World!"});
    print_ip( std::vector<int>{100,200,300,400});
    print_ip( std::list<short>{400,300,200,100});
    print_ip( std::make_tuple(123,456,789,0));

    //print_ip( std::make_tuple(123,"str",789,0));


    return 0;
}
