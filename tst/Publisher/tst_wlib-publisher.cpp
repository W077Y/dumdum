#include <array>
#include <iostream>
#include <ut_catch.hpp>
#include <wlib.hpp>

namespace
{
  class dummy_pub_int: public wlib::Puplisher_Interface<int>
  {
  public:
    void puplish(int const& val)
    {
      for (auto& el : this->m_subs)
      {
        if (el == nullptr)
          continue;
        wlib::Puplisher_Interface<int>::invoke(*el, val);
      }
    }

  private:
    std::array<Subsription_Token_Interface*, 5> m_subs{};

    // Inherited via Puplisher_Interface
    void add_subsriber(Subsription_Token_Interface& sub) override
    {
      for (auto& el : this->m_subs)
      {
        if (el != nullptr)
          continue;

        el = &sub;
        return;
      }
      // TODO: error from base
    }

    void remove_subsriber(Subsription_Token_Interface& sub) override
    {
      for (auto& el : this->m_subs)
      {
        if (el != &sub)
          continue;

        el = nullptr;
        return;
      }
      // TODO: error from base
    }
  };

  class dummy_sub_int: public wlib::Puplisher_Interface<int>::Subsription_Token_Interface
  {
  public:
    dummy_sub_int(wlib::Puplisher_Interface<int>& pub, int& val)
        : Subsription_Token_Interface(pub)
        , m_val(val)
    {
    }

  private:
    // Inherited via Subsription_Token_Interface
    void notify(int const& val) override { this->m_val = val; }

    int& m_val;
  };
}    // namespace

TEST_CASE()
{
  dummy_pub_int pub;

  int vals[3]{};
  for (auto& ent : vals)
  {
    ent = -1;
  }

  REQUIRE(vals[0] == -1);
  REQUIRE(vals[1] == -1);
  REQUIRE(vals[2] == -1);

  dummy_sub_int sub_1{ pub, vals[0] };

  pub.puplish(1);
  REQUIRE(vals[0] == 1);
  REQUIRE(vals[1] == -1);
  REQUIRE(vals[2] == -1);

  {
    dummy_sub_int sub_2{ pub, vals[1] };
    pub.puplish(2);
    REQUIRE(vals[0] == 2);
    REQUIRE(vals[1] == 2);
    REQUIRE(vals[2] == -1);
  }

  dummy_sub_int sub_3{ pub, vals[2] };
  pub.puplish(3);
  REQUIRE(vals[0] == 3);
  REQUIRE(vals[1] == 2);
  REQUIRE(vals[2] == 3);
}

namespace
{
  struct A;
  struct B
  {
    int b;
  };

  class dummy_sub_A_B: public wlib::Puplisher_Interface<A>::Subsription_Token_Interface
  {
  public:
    dummy_sub_A_B(wlib::Puplisher_Interface<A>& pub, B (&transform)(A const&), B& val)
        : Subsription_Token_Interface(pub)
        , m_val(val)
        , m_transform(transform)
    {
    }

  private:
    void notify(A const& val) override { return this->forward(this->m_transform(val)); }
    void forward(B const& val) { this->m_val = val; }

    B& m_val;
    B (&m_transform)(A const&);
  };

  struct A
  {
    int a;
  };

  class dummy_pub_A: public wlib::Puplisher_Interface<A>
  {
  public:
    void puplish(A const& val)
    {
      for (auto& el : this->m_subs)
      {
        if (el == nullptr)
          continue;
        wlib::Puplisher_Interface<A>::invoke(*el, val);
      }
    }

  private:
    std::array<Subsription_Token_Interface*, 5> m_subs{};

    // Inherited via Puplisher_Interface
    void add_subsriber(Subsription_Token_Interface& sub) override
    {
      for (auto& el : this->m_subs)
      {
        if (el != nullptr)
          continue;

        el = &sub;
        return;
      }
      // TODO: error from base
    }

    void remove_subsriber(Subsription_Token_Interface& sub) override
    {
      for (auto& el : this->m_subs)
      {
        if (el != &sub)
          continue;

        el = nullptr;
        return;
      }
      // TODO: error from base
    }
  };

}    // namespace

B transform_1(A const& val) { return { val.a + 1 }; }
B transform_2(A const& val) { return { val.a * 2 }; }
B transform_3(A const& val) { return { val.a - 1 }; }

TEST_CASE()
{
  dummy_pub_A pub;

  B vals[3]{};
  for (auto& ent : vals)
  {
    ent.b = -1;
  }

  REQUIRE(vals[0].b == -1);
  REQUIRE(vals[1].b == -1);
  REQUIRE(vals[2].b == -1);

  dummy_sub_A_B sub_1{ pub, transform_1, vals[0] };

  pub.puplish({ 1 });
  REQUIRE(vals[0].b == 2);
  REQUIRE(vals[1].b == -1);
  REQUIRE(vals[2].b == -1);

  {
    dummy_sub_A_B sub_2{ pub, transform_2, vals[1] };
    pub.puplish({ 2 });
    REQUIRE(vals[0].b == 3);
    REQUIRE(vals[1].b == 4);
    REQUIRE(vals[2].b == -1);
  }

  dummy_sub_A_B sub_3{ pub, transform_3, vals[2] };
  pub.puplish({ 3 });
  REQUIRE(vals[0].b == 4);
  REQUIRE(vals[1].b == 4);
  REQUIRE(vals[2].b == 2);
}
