// Copyright (c) 1997-2000
// Utrecht University (The Netherlands),
// ETH Zurich (Switzerland),
// INRIA Sophia-Antipolis (France),
// Max-Planck-Institute Saarbruecken (Germany),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org)
//
// $URL$
// $Id$
// SPDX-License-Identifier: LGPL-3.0-or-later OR LicenseRef-Commercial
//
//
// Author(s)     : Michael Seel <seel@mpi-sb.mpg.de>
//                 Lutz Kettner <kettner@inf.ethz.ch>

#ifndef CGAL_UNIQUE_HASH_MAP_H
#define CGAL_UNIQUE_HASH_MAP_H

#include <memory>
#include "robin_hood.h"
#include "Handle_hash_function.h"

namespace CGAL {

template <class Key_, class Data_,
          class UniqueHashFunction = Handle_hash_function,
          class Allocator_ = std::allocator<Data_> >
class Unique_hash_map {
public:
    typedef Key_                                     Key;
    typedef Data_                                    Data;
    typedef UniqueHashFunction                       Hash_function;
    typedef Allocator_                               Allocator;
    typedef std::equal_to<Key_>                      Equal;

    // STL compliance
    typedef Key_                                     key_type;
    typedef Data_                                    data_type;
    typedef UniqueHashFunction                       hasher;

    typedef Unique_hash_map<Key,Data,Hash_function,Allocator> Self;

private:
    typedef robin_hood::unordered_node_map<Key,Data,Hash_function,Equal> Map;
    typedef typename Map::const_iterator                                 Item;

    Map            m_map;
    Data           m_default;

public:

    Unique_hash_map()
    : m_default(Data())
    {
    }

    Unique_hash_map(const Data& def)
    : m_default(def)
    {
    }

    Unique_hash_map(const Data& def,std::size_t table_size)
    : m_default(def)
    {
       m_map.reserve(table_size);
    }

    Unique_hash_map(Key first1,Key beyond1,Data first2,
                    const Data& def,std::size_t table_size)
    : m_default(def)
    {
        m_map.reserve(table_size);
        insert(first1,beyond1,first2);
    }

    Data default_value() const
    {
        return m_default;
    }

    void clear()
    {
        m_map.clear();
    }

    void clear(const Data& def)
    {
        clear();
        m_default = def;
    }

    bool is_defined(const Key& key) const
    {
        return m_map.find(key) != m_map.end();
    }

    const Data& operator[](const Key& key) const
    {
        Item f=m_map.find(key);
        if(f != m_map.end())
            return f->second;
        return m_default;
    }

    Data& operator[](const Key& key)
    {
        return m_map.try_emplace(key,m_default).first->second;
    }

    Data insert(Key first1,Key beyond1,Data first2)
    {
        for ( ; first1 != beyond1; (++first1,++first2)) {
            m_map.insert_or_assign(first1,first2);
        }
        return first2;
    }

    size_t size() const {
        return m_map.size();
    }

};



} //namespace CGAL

namespace boost {
  template <typename UniquePairAssociativeContainer>
  class associative_property_map;

  struct lvalue_property_map_tag;

  template <typename KeyType, typename ValueType,
            typename HashFunction, typename Allocator>
  class associative_property_map<CGAL::Unique_hash_map<KeyType, ValueType,
                                                       HashFunction, Allocator> >
  {
    typedef CGAL::Unique_hash_map<KeyType, ValueType, HashFunction, Allocator> C;

  public:
    typedef KeyType key_type;
    typedef ValueType value_type;
    typedef const value_type& reference;
    typedef lvalue_property_map_tag category;
    associative_property_map() : m_c(0) { }
    associative_property_map(C& c) : m_c(&c) { }
    value_type& operator[](const key_type& k) const {
      return (*m_c)[k];
    }

  friend
  const value_type&
  get(const associative_property_map<C>& uhm, const key_type& key)
  {
    return uhm[key];
  }

  friend
  void
  put(associative_property_map<C>& uhm, const key_type& key, const value_type& val)
  {
    uhm[key] = val;
  }

  private:
    C* m_c;
  };

  template <typename KeyType, typename ValueType,
            typename HashFunction, typename Allocator>
  associative_property_map<CGAL::Unique_hash_map<KeyType, ValueType,
                                                 HashFunction, Allocator> >
  make_assoc_property_map(CGAL::Unique_hash_map<KeyType, ValueType,
                                                HashFunction, Allocator>& c)
  {
    return associative_property_map<CGAL::Unique_hash_map<KeyType, ValueType,
                                                          HashFunction, Allocator> >(c);
  }

}

#include <CGAL/enable_warnings.h>

#endif // CGAL_UNIQUE_HASH_MAP_H
// EOF
