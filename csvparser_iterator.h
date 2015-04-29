/*
 * This is the back_insert_iterator from <iterators????>.
 * TODO: Modify it for csvparser, making it a nested class. Messy but a good exercise.
 */
template <class Container>
  class back_insert_iterator : public iterator<output_iterator_tag,void,void,void,void>
{
protected:

  Container* container;

public:
  typedef Container container_type;

  explicit back_insert_iterator (Container& x) : container(&x) {}

  back_insert_iterator<Container>& operator= (typename Container::const_reference value);

  back_insert_iterator<Container>& operator* ();

  back_insert_iterator<Container>& operator++ ();

  back_insert_iterator<Container> operator++ (int);
};

template <class Container> inline back_insert_iterator<Container>& back_insert_iterator<Container>::operator= (typename Container::const_reference value)
{ 
  container->emplace_back(value); 
 return *this; 
}

template <class Container> inline back_insert_iterator<Container>& back_insert_iterator<Container>::operator*()
{ 
  return *this; 
}

template <class Container> inline back_insert_iterator<Container>& back_insert_iterator<Container>::operator++ ()
{ 
   return *this;
}

template <class Container> inline  back_insert_iterator<Container> back_insert_iterator<Container>::operator++ (int)
{ 
  return *this; 
}
