/* Auto-generated by genmsg_cpp for file /home/shahhome/workspace/se306_example/msg/IdentityRequest.msg */
#ifndef SE306_EXAMPLE_MESSAGE_IDENTITYREQUEST_H
#define SE306_EXAMPLE_MESSAGE_IDENTITYREQUEST_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace se306_example
{
template <class ContainerAllocator>
struct IdentityRequest_ {
  typedef IdentityRequest_<ContainerAllocator> Type;

  IdentityRequest_()
  : sender()
  , px(0)
  , py(0)
  {
  }

  IdentityRequest_(const ContainerAllocator& _alloc)
  : sender(_alloc)
  , px(0)
  , py(0)
  {
  }

  typedef std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  _sender_type;
  std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other >  sender;

  typedef int32_t _px_type;
  int32_t px;

  typedef int32_t _py_type;
  int32_t py;


  typedef boost::shared_ptr< ::se306_example::IdentityRequest_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::se306_example::IdentityRequest_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct IdentityRequest
typedef  ::se306_example::IdentityRequest_<std::allocator<void> > IdentityRequest;

typedef boost::shared_ptr< ::se306_example::IdentityRequest> IdentityRequestPtr;
typedef boost::shared_ptr< ::se306_example::IdentityRequest const> IdentityRequestConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::se306_example::IdentityRequest_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::se306_example::IdentityRequest_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace se306_example

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::se306_example::IdentityRequest_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::se306_example::IdentityRequest_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::se306_example::IdentityRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "266d9378bc44386f0004ef17e730e855";
  }

  static const char* value(const  ::se306_example::IdentityRequest_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x266d9378bc44386fULL;
  static const uint64_t static_value2 = 0x0004ef17e730e855ULL;
};

template<class ContainerAllocator>
struct DataType< ::se306_example::IdentityRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "se306_example/IdentityRequest";
  }

  static const char* value(const  ::se306_example::IdentityRequest_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::se306_example::IdentityRequest_<ContainerAllocator> > {
  static const char* value() 
  {
    return "string sender\n\
int32 px\n\
int32 py\n\
\n\
";
  }

  static const char* value(const  ::se306_example::IdentityRequest_<ContainerAllocator> &) { return value(); } 
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::se306_example::IdentityRequest_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.sender);
    stream.next(m.px);
    stream.next(m.py);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct IdentityRequest_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::se306_example::IdentityRequest_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::se306_example::IdentityRequest_<ContainerAllocator> & v) 
  {
    s << indent << "sender: ";
    Printer<std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other > >::stream(s, indent + "  ", v.sender);
    s << indent << "px: ";
    Printer<int32_t>::stream(s, indent + "  ", v.px);
    s << indent << "py: ";
    Printer<int32_t>::stream(s, indent + "  ", v.py);
  }
};


} // namespace message_operations
} // namespace ros

#endif // SE306_EXAMPLE_MESSAGE_IDENTITYREQUEST_H
