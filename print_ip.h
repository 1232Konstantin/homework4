#ifndef PRINT_IP_H
#define PRINT_IP_H

#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <tuple>


template < typename T>
struct hasIterator
{
    static const T t;

    template <typename U>
    struct True { char dummy[2];};

    typedef char False;

    static auto func(...) ->False {};

    template <typename U>
    static auto func (U u)->True<decltype (u.begin())> {}

    static const bool value= (sizeof (func(t))!=sizeof (False))? true : false;
};


template < typename T>
struct is_not_empty_Tuple
{
    static const T t;

    template <typename U>
    struct True { char dummy[2];};

    typedef char False;

    static auto func(...) ->False {};

    template <typename U>
    static auto func (U u)->True<decltype (std::get<0>(u))> {}

    static const bool value= (sizeof (func(t))!=sizeof (False))? true : false;
};


/*!
 * \brief Проверка класса Т на предмет принадлежности к std::vector или std::list
 * \param T шаблонный параметр.
 *
 * \paragraph is_vector_or_list_std Пример использования
 * \code
 * std::vector<int> v1; //создаем объект класса вектор
 * cout<<"is_vector_or_list_std (yes) "<<is_vector_or_list_std <decltype (v1)>::value<<endl; //проверяем действительно ли v1 это вектор
 * \endcode
 *
 */
template <typename T, bool =hasIterator<T>::value>
struct is_vector_or_list_std
{
    static const bool value=false;
};

template <typename T>
struct is_vector_or_list_std<T, true>
{
    using InsideType= typename std::iterator_traits<typename T::iterator>::value_type;
    static const bool value=(std::is_same<T, std::list<InsideType>>::value)? true : (std::is_same<T, std::vector<InsideType>>::value)? true :false;
};














/*!
 * \brief Вывод на экран "псевдо" IP адреса из std::string
 * \param data пареметр типа std::string
 *
 * \paragraph print_ip Пример использования
 * \code
 *  print_ip( std::string{"Hello World!"});
 * \endcode
 *
 */


template <typename T, typename F=typename std::enable_if< std::is_same<T, std::string>::value >::type>
auto  print_ip(T data)-> typename std::enable_if< std::is_same<T, std::string>::value >::type{
    std::cout<<data<<std::endl;
}


/*!
 * \brief Вывод на экран "псевдо" IP адреса из любого целочисленного типа
 * \param data пареметр целочисленного типа
 *
 * \paragraph print_ip Пример использования
 * \code
 *  print_ip( int8_t{-1});
 *  print_ip( int16_t{0});
 *  print_ip( int32_t{2130706433});
 *  print_ip( int64_t{8875824491850138409});
 * \endcode
 *
 */
template <typename T, typename F=typename std::enable_if< std::is_integral<T>::value >::type>
auto print_ip(T data)->typename std::enable_if< std::is_integral<T>::value >::type {
    auto size=sizeof (data);
    size_t count=1;
    auto arr=reinterpret_cast<uint8_t*>(&data);
    for (size_t i=size; i>0; --i)
    {
        auto divider=(count!=size)? "." : "\n";
        count++;
        std::cout<<static_cast<int>(arr[i-1])<<divider;
    }

}

/*!
 * \brief Вывод на экран "псевдо" IP адреса из std::vector или std::list
 * \param data пареметр типа std::list<X> или std::vector<X>  где Х некий тип, выводимый в стандартный ostream).
 *
 * \paragraph print_ip Пример использования
 * \code
 * print_ip( std::vector<int>{100,200,300,400}); //вывод "псевдо" IP  в ostream
 * print_ip( std::list<short>{400,300,200,100}); //вывод "псевдо" IP  в ostream
 * \endcode
 *
 */

template <typename T, typename F=typename std::enable_if< is_vector_or_list_std<T>::value >::type>
auto print_ip(T data)->typename std::enable_if< is_vector_or_list_std<T>::value >::type {
    size_t count=1;
    for(typename T::iterator it= data.begin(); it!=data.end(); it++)
    {
        auto divider=(count!=data.size())? "." : "\n";
        count++;
        std::cout<<*it<<divider;
    }

}

//*****************************************tuple************************************

template<bool>
struct howToDo{
    static const char value=1;
};

template<>
struct howToDo<false>{
    static const bool value=false;
};


template<typename TupleType, size_t Idx, size_t IdxMax>
void printElement(TupleType& , const bool){
    //stop
}

template<typename TupleType, size_t Idx, size_t IdxMax>
void printElement(TupleType& tuple, char)
{
    constexpr bool usl=(Idx!=IdxMax)? true : false;
    auto tupleElement=std::get<Idx>(tuple);
    auto divider=(usl)? "." : "\n";

    static_assert(std::is_same<typename std::tuple_element<0,TupleType>::type, typename std::tuple_element<Idx,TupleType>::type>::value, "Different types in tuple");
    std::cout<<tupleElement<<divider;
    constexpr size_t newIdx=Idx+1;
    printElement<TupleType, newIdx, IdxMax>(tuple, howToDo<usl>::value);
}



/*!
 * \brief Вывод на экран "псевдо" IP адреса из std::tuple (элементы кортежа должны иметь одинаковый тип)
 * \param data пареметр типа std::tuple<X,X,X...> где Х некий тип, выводимый в стандартный ostream).
 *
 * \paragraph print_ip Пример использования
 * \code
 * print_ip( std::make_tuple(123,456,789,0)); //вывод "псевдо" IP  в ostream
 * \endcode
 *
 */


template <typename T, typename F=typename std::enable_if< is_not_empty_Tuple<T>::value >::type>
auto print_ip(T data)->typename std::enable_if< is_not_empty_Tuple<T>::value >::type {
    constexpr auto size=std::tuple_size<T>();
    printElement<T, 0, size-1>(data, 'a');
}




#endif // PRINT_IP_H
