#pragma once

#include <wonderwaffel/igun.hpp>

namespace wfc
{

template<typename I, typename Opt>
class tank_gun: public igun<I, Opt>
{
public:
  typedef igun<I, Opt> super;

  typedef typename super::interface_type target_interface;
  typedef typename super::interface_ptr target_ptr;
  typedef typename super::options_type options_type;
  typedef typename super::request_type request_type;
  typedef typename super::response_type response_type;
  typedef typename super::user_options user_options;
  typedef typename super::bang_handler bang_handler;

  typedef std::unique_ptr<request_type> request_ptr;
  typedef std::unique_ptr<response_type> response_ptr;
  typedef std::function< void(response_ptr) >  handler_t;
  typedef void (I::* target_method)(request_ptr, handler_t);

  typedef std::function<bool(const user_options&, request_ptr&)> request_generator;
  typedef std::function<bool(const user_options&, const response_ptr&)> response_checker;

  tank_gun(
    target_method tm,
    request_generator req_gen,
    response_checker res_check
  )
    : _target_method(tm)
    , _req_gen(req_gen)
    , _res_check(res_check)
  {}

  virtual void initialize( target_ptr target, const options_type& opt) override
  {
    _target = target;
    _options = opt;
  }

  virtual bool bang(bang_handler handler) override
  {
    auto req = std::make_unique<request_type>();
    *req = _options.request;
    if ( _req_gen!=nullptr && !_req_gen(_options, req) )
      return false;

    (_target.get()->*_target_method)(std::move(req), [handler, this](response_ptr res)
    {
      handler( res!=nullptr && (this->_res_check == nullptr || this->_res_check(this->_options, res) ) );
    });

    return true;
  }
private:
  target_ptr _target;
  target_method _target_method;
  options_type _options;
  request_generator _req_gen;
  response_checker _res_check;
};


}
