#pragma once
#ifndef WLIB_PUBLISHER_HPP_INCLUDED
#define WLIB_PUBLISHER_HPP_INCLUDED

#include <wlib-Callback.hpp>

namespace wlib
{
  template <typename T> class Puplisher_Interface
  {
  public:
    virtual ~Puplisher_Interface() = default;

    class Subsription_Token_Interface;

  protected:
    static void invoke(Subsription_Token_Interface& sub, T const& val) { return sub.notify(val); }

  private:
    virtual void add_subsriber(Subsription_Token_Interface& sub)    = 0;
    virtual void remove_subsriber(Subsription_Token_Interface& sub) = 0;
  };

  template <typename T> class Puplisher_Interface<T>::Subsription_Token_Interface
  {
  public:
    Subsription_Token_Interface(Puplisher_Interface& pub)
        : m_pub(pub)
    {
      this->m_pub.add_subsriber(*this);
    }

    virtual ~Subsription_Token_Interface() { this->m_pub.remove_subsriber(*this); }

  private:
    friend Puplisher_Interface<T>;

    virtual void notify(T const&) = 0;

    Puplisher_Interface<T>& m_pub;
  };

}    // namespace wlib

#endif
