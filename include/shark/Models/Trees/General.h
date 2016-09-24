//===========================================================================
/*!
 *
 *
 * \brief       General functions for Tree modeling.
 *
 *
 *
 * \author      J. Wrigley
 * \date        2016
 *
 *
 * \par Copyright 1995-2015 Shark Development Team
 *
 * <BR><HR>
 * This file is part of Shark.
 * <http://image.diku.dk/shark/>
 *
 * Shark is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Shark is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Shark.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
//===========================================================================

#ifndef SHARK_MODELS_TREES_GENERAL_H
#define SHARK_MODELS_TREES_GENERAL_H
namespace shark {
namespace detail {
namespace cart {
// Helper functions
#define DEBUG(msg) std::cout << msg << std::endl
template<class Iterator>
inline std::size_t argmax(Iterator begin, Iterator end) {
	std::size_t maxIndex = 0;
	typename Iterator::value_type max = 0.;
	for(Iterator i = begin; i<end; ++i){
		if(*i>max){
			max = *i;
			maxIndex = i.index();
		}
	}
	return maxIndex;
}
template<class Container>
inline std::size_t argmax(Container c) {
	return argmax(std::begin(c),std::end(c));
}

template<class Container,class F> static
inline void generate_i(Container & v, F&& f){
	for(std::size_t i, s = v.size(); i<s; ++i) v[i] = f(i);
};
template<class Container, class F> static
inline void generate_i(std::size_t length, Container & v, F&& f){
	v.clear();
	for(std::size_t i=0; i<length; ++i) v.push_back(f(i));
}

template<class T, class F>
inline T sum(std::size_t i, std::size_t n, F&& f) {
	if(i>=n) return T{};
	T out = f(i);
	for(++i;i<n;++i) out += f(i);
	return out;
}
template<class T, class F>
inline T sum(std::size_t n, F&& f) {
	return sum<T>(0,n,std::forward<F>(f));
}
template<class T, class Container, class F> static
inline T sum(Container const& v, F&& f) {
	auto iter = std::begin(v);
	auto end = std::end(v);
	if(!(iter!=end)) return T{};
	auto out = T{f(*iter)};
	for(++iter;iter != end; ++iter) out += f(*iter);
	return out;
}
//END Helper functions


}}} // namespace shark::detail::cart

#endif //SHARK_MODELS_TREES_GENERAL_H
