Unfortunately, this program also did not pass.

This time, it failed to meet this criterion:

Type requirements are met: You must adhere to the specification of the key and value type given above. For example, many solutions we receive use operations other than those that are explicitly stated in the task description. We have to reject many solutions because they assume that V is default-constructible, e.g., by using std::map::operator[].
Correctness: Your program should produce a working interval_map with the behavior described above. In particular, pay attention to the validity of iterators. It is illegal to dereference end iterators. Consider using a checking STL implementation such as the one shipped with Visual C++ or GCC. Many solutions we receive do not create the data structure that was asked for, e.g., some interval ends up being associated with the wrong value. Others contain a code path that will eventually dereference an invalid or end iterator.
Canonicity: The representation in m_map must be canonical. Some solutions we receive create consecutive map entries containing the same value, or repeat the value of m_valBegin at the beginning of the map.
Running time: Imagine your implementation is part of a library, so it should be big-O optimal. In addition:

Do not make big-O more operations on K and V than necessary because you do not know how fast operations on K/V are; remember that constructions, destructions and assignments are operations as well.
Do not make more than one operation of amortized O(log N), in contrast to O(1), running time, where N is the number of elements in m_map. Overloads of std::map::insert/emplace/delete that need to find an element position for a given key, have a running time of amortized O(log N). Overloads of std::map::insert/emplace/delete that take an iterator to the position of the inserted/deleted element,have a running time of amortized O(1), if the iterator points to the correct position.
Otherwise favor simplicity over minor speed improvements.
We regret that we cannot provide you with information specific to your solution, or with a correct version of the algorithm, because if we did, then we could no longer use this challenge for our interview process. We sincerely hope for your understanding on this matter.