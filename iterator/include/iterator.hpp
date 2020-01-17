/* Image iterator.
 * @file
 * @date 2020-01-15
 * @author Serega
 */

#ifndef __ITERATOR_HPP__
#define __ITERATOR_HPP__

#include <algorithm>
#include <type_traits>
#include <vector>
#include <utility>

#include <boost/iterator/iterator_adaptor.hpp>

//{ image iterator
template<class Iterator>
class image_iterator: public boost::iterator_adaptor<image_iterator<Iterator>,
                                                    Iterator, 
                                                    boost::use_default,
                                                    boost::random_access_traversal_tag>
{
public:
    explicit image_iterator(Iterator it, size_t w, size_t s) : image_iterator::iterator_adaptor(it), 
                                                                position(0), 
                                                                width_im(w), 
                                                                stride_im(s) {}
   
   using diff_type = typename image_iterator::iterator_adaptor::difference_type;

   void advance(diff_type pos){ position += pos;}
   typename image_iterator::iterator_adaptor::reference dereference() const { return *get_iter();}
   typename image_iterator::iterator_adaptor::reference dereference() { return *get_iter(); }
   bool equal(const image_iterator& it_im) const 
   {
       return this->get_iter() == it_im.get_iter();
   }
   void increment() { position++; }
   void decrement() { position--; }
   
   diff_type distance_to(const image_iterator& it_im) const
   {
       auto dist = std::distance(this->base(), it_im.base());
       return dist / static_cast<diff_type>(stride_im) * width_im + static_cast<diff_type>(it_im.position) - static_cast<diff_type>(this->position);
   }
    
private:
   auto get_iter() const 
   {
       return this->base_reference() + (position / width_im * stride_im + position % width_im); 
   }
   size_t position;
   size_t width_im;
   size_t stride_im;
};
//}

template<class Container = std::vector<uint8_t>>
class image
{
public:
    image(size_t width, size_t height, size_t stride):
        data(stride * height),
        width_(width),
        stride_(stride)
    {}

    auto begin()
    {
        return image_iterator(data.begin(), width_, stride_);
    }

    auto end()
    {
        return image_iterator(data.end(), width_, stride_);
    }

    auto begin() const
    {
        return image_iterator(data.begin(), width_, stride_);
    }

    auto end() const
    {
        return image_iterator(data.end(), width_, stride_);
    }

private:
    Container data; // image data including strides. Access by (x, y): data[y * stride_ + x]
    size_t width_;
    size_t stride_;
};

#endif // __ITERATOR_HPP__
