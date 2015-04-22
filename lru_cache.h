/*
 * lru_cache.h
 *
 *  Created on: Apr 22, 2015
 *      Author: ugumus
 */

#ifndef LRU_CACHE_H_
#define LRU_CACHE_H_

#include <map>
#include <unordered_map>
#include <list>
#include <string>

namespace gms
{
    class cache_exception : public std::exception
    {
    public:
        explicit cache_exception(std::string const& ex): ex_str_(ex){}
        ~cache_exception(){}
        char const* what() const throw() { return ex_str_.c_str(); }
    private:
        std::string ex_str_;
    };

    template<class key_type, class value_type>
    class lru_cache
    {
    public:

        lru_cache(unsigned capacity)
        : capacity_(capacity)
        {
        }

        ~lru_cache(){}

        value_type get(key_type const& key)
        {
            typename cache_type::iterator it = cache_.find(key);
            if (it != cache_.end())
            {
                item_list_.splice(item_list_.begin(), item_list_, it->second);

                return it->second->second;
            }

            throw cache_exception("key not found");
        }

        void set(key_type const& key, value_type const& value)
        {
            // search for key in cache
            typename cache_type::iterator it = cache_.find(key);

            // key not found
            if (it == cache_.end())
            {
                // lru_cache reached max capacity
                if (item_list_.size() == capacity_)
                {
                    cache_.erase(item_list_.back().first);
                    item_list_.pop_back();
                }

                item_list_.push_front(std::make_pair(key, value));

                cache_[key] = item_list_.begin();

            }
            // key found in cache
            else {
                // update value
                it->second->second = value;

                // update item list. make updated item as MRU
                item_list_.splice(item_list_.begin(), item_list_, it->second);
            }
        }

        unsigned const& get_capacity() const
        {
            return capacity_;
        }

        unsigned const& get_size() const
        {
            return item_list_.size();
        }

    private:

        typedef std::unordered_map<key_type, typename std::list<std::pair<key_type, value_type> >::iterator > cache_type;
        typedef std::list<std::pair<key_type, value_type> > list_type;

        // capacity of lru cache
        unsigned capacity_;

        // map of [key -> item list iterator]
        cache_type cache_;

        // list of key value pair. most recently used --> least recently used
        list_type item_list_;
    };
}

#endif /* LRU_CACHE_H_ */
