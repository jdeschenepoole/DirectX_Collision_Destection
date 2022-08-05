#ifndef _TGetRandom_HG_
#define _TGetRandom_HG_

template <class T>
T getRand(T lowRange, T highRange)
{
	if ( lowRange > highRange )
	{
		T temp = lowRange;
		lowRange = highRange;
		highRange = temp;
	}
	T delta = highRange - lowRange;
	delta = ( static_cast<T>( rand() ) / static_cast<T>(RAND_MAX) ) * delta;
	return delta + lowRange;
}
#endif