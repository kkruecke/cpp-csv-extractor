#ifndef CSV_BACK_INSERTER
#define CSV_BACK_INSERTER
/*
 * This is the vector_inserter from <iterators????>.
 * TODO: Modify it for csvparser, making it a nested class. Messy but a good exercise.
 */


template <class Container> // vector<string>
class csv_back_inserter : public iterator<output_iterator_tag,void,void,void,void> {
protected:

  Container* container; // vector<string>

public:
  typedef Container container_type;

  explicit vector_inserter (Container& x) : container(&x) {}

  vector_inserter<Container>& operator= (typename Container::const_reference value);

  vector_inserter<Container>& operator* ();

  vector_inserter<Container>& operator++ ();

  vector_inserter<Container> operator++ (int);
};

template <class Container> inline vector_inserter<Container>& vector_inserter<Container>::operator= (typename Container::const_reference value) // OK
{
/*
 *
 */
 
  // Remove enclosing quotes if present from submatches.
 if (value.front() == '"') {
              
    (*container).emplace_back(move(value.substr(1, string_ref.length() - 2)) );
              
 } else {
                             
    (*container).emplace_back(move(value)); 
 }

 return *this; 
}

template <class Container> inline vector_inserter<Container>& vector_inserter<Container>::operator*()
{ 
  return *this; 
}

template <class Container> inline vector_inserter<Container>& vector_inserter<Container>::operator++ ()
{ 
   return *this;
}

template <class Container> inline  vector_inserter<Container> vector_inserter<Container>::operator++ (int)
{ 
  return *this; 
}
#endif
