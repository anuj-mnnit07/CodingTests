
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

#include "key_value.h"

template<typename K, typename V>
class interval_map {
public:
	V m_valBegin;
	std::map<K,V> m_map;
public:
	// constructor associates whole range of K with val
	interval_map(V const& val)
	: m_valBegin(val)
	{}

    void print(std::map<K, V> test_map) {
        std::cout << "m_valBegin: " << m_valBegin << std::endl;
        std::cout << "test map content is: { ";
        for (auto itr: test_map) {
            std::cout << "(" << itr.first << ", " << itr.second << "), ";
        }
        std::cout << " }" << std::endl;
    }
    void print() {
        #if !defined(NO_USE_PRINT)
        std::cout << "m_valBegin: " << m_valBegin << std::endl;
        std::cout << "map content is: { ";
        for (auto itr: m_map) {
            std::cout << "(" << itr.first;
            std::cout << ", " << itr.second << "), ";
        }
        std::cout << " }" << std::endl;
        #endif
    }
	// look-up of the value associated with key
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
    int verify(std::map<K,V>& test_map) {
       if(m_map.size() != test_map.size()) {
            std::cout << "verification failed with given: " << m_map.size() << " and expected: " << test_map.size() << std::endl;
            print(test_map);
            print();
            return 1;
       }
        for(auto itr : m_map) {
            auto test_itr = test_map.find(itr.first);
            if(test_itr == test_map.end()) {
                std::cout << "verification failed key not found: " << itr.first << std::endl;
                print(test_map);
                print();
                return 1;
            }
            bool ret = test_itr->second == itr.second; 
            if(ret == false) {
                std::cout << "verification failed: value mismatched for key: " << itr.first << std::endl;
                print(test_map);
                print();
                return 1;
            }
        }
        return 0;
    }
    

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
    void assign2(K const& keyBegin, K const& keyEnd, V const& val) {
        if (!(keyBegin < keyEnd))
            return;
        if(m_map.empty()) {
            if(val == m_valBegin) {
                return;
            }
            m_map.emplace(keyBegin, val);
            m_map.emplace(keyEnd, m_valBegin);
            return;
        }
        typename std::map<K, V>::iterator iterBegin;
        typename std::map<K, V>::iterator iterEnd;

        auto lowerKeyBegin = m_map.lower_bound(keyBegin);
        auto upperKeyEnd = m_map.upper_bound(keyEnd);
        
        if(lowerKeyBegin == m_map.end() && upperKeyEnd == m_map.end()) {
            if(val == m_valBegin) {
                return;
            }
            m_map.emplace(keyBegin, val);
            m_map.emplace(keyEnd, m_valBegin);
            return;
        }
        if(upperKeyEnd == m_map.end()) {
            m_map.emplace(keyEnd, m_valBegin);
        }
        auto prevKeyEnd = upperKeyEnd == m_map.cbegin() ? m_map.end() : std::prev(upperKeyEnd);
        if(prevKeyEnd == m_map.end()) {
            if(val == m_valBegin) {
                return;
            }
            m_map.emplace(keyBegin, val);
            m_map.emplace(keyEnd, m_valBegin);
            return;
        }
        if (!(prevKeyEnd->second == val))
        {
            if (!(prevKeyEnd->first < keyEnd) && !(keyEnd < prevKeyEnd->first))
                iterEnd = prevKeyEnd;
            else
                iterEnd = m_map.insert_or_assign(upperKeyEnd, keyEnd, prevKeyEnd->second);
        }
        else
        {
            iterEnd = upperKeyEnd;
        }

        if (lowerKeyBegin != m_map.begin())
        {
            auto prevIter = std::prev(lowerKeyBegin);
            if (!(prevIter->second == val))
            {
                iterBegin = m_map.insert_or_assign(lowerKeyBegin, keyBegin, val);
            }
            else iterBegin = prevIter;
        }
        else
        {
            iterBegin = m_map.insert_or_assign(lowerKeyBegin, keyBegin, val);
        }


        {
            auto nextIterOfBegin = std::next(iterBegin);
            if (nextIterOfBegin != m_map.end())
            {
                m_map.erase(nextIterOfBegin, iterEnd); 
            }
        }
        // Merge intervals to make it canonical
        for(auto iter = m_map.begin(); iter != m_map.end(); ) {
            if(iter->second == m_valBegin) {
                m_map.erase(iter++);
            } else {
                break;
            }
	    }
        for (auto iter = m_map.begin(); iter != m_map.end();) {
            auto iter_next = std::next(iter);
            if (iter_next != m_map.cend() && iter_next->second == iter->second) {
                m_map.erase(iter++);
            } else {
                ++iter;
            }
        }

        
    }

};
