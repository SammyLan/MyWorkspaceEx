#pragma once
template <bool> struct StaticAssertFailed;
template <>struct StaticAssertFailed<true>{ enum{ val = true};};
#define STATIC_ASSERT(exp) StaticAssertFailed<(bool)exp>::val

template<size_t N> struct isPowOf2{ enum {val  =  !(N & (N-1))};};

template<size_t N>
struct __LogOf2
{
	enum {val = 1 + __LogOf2<(N>>1)>::val};
};
template<> struct __LogOf2<1>{	enum {val = 0};};

template<size_t N>
struct LogOf2
{
	enum {val = __LogOf2<N>::val};
	enum {bEnsure = STATIC_ASSERT(isPowOf2<N>::val)};
};

template<size_t offset,size_t N,bool bCont>
struct __Mask{ enum { val = 1 | __Mask<offset,N + offset,N < 32>::val << offset };};
template<size_t offset,size_t N> struct __Mask<offset,N,false> { enum { val = 0};};

template<size_t N>
struct Mask{
	enum { val = __Mask<LogOf2<N>::val,0,true>::val};
};

/*
判断n是否是N的整数次方
其中N必须是2的整数次方且大于1,如果传的N不符合规范,则编译错误
*/
template <size_t N>
bool isPowerOf(size_t n)
{
	return  ((n&( n-1)) ==0) && (n & Mask<N>::val);
}